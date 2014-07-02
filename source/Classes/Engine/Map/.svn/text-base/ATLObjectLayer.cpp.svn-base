
#include "ATLObjectLayer.h"
#include "spriteDataList.h"
#include "AspriteManager.h"
#include "AnimSprite.h"
#include "EnginePlayerManager.h"
#include "LevelLayer.h"
#include "spriteDataList.h"


// ------------------------------------------------------------------------

AlphaTestBatchNode::AlphaTestBatchNode()
{

}

AlphaTestBatchNode::~AlphaTestBatchNode()
{

}

AlphaTestBatchNode* AlphaTestBatchNode::create( const char* pszFileName )
{
	AlphaTestBatchNode* graySprite = new AlphaTestBatchNode();
	if (graySprite && graySprite->initWithFile(pszFileName, 100))
	{
		graySprite->autorelease();
		return graySprite;
	}
	else
	{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

bool AlphaTestBatchNode::initWithFile(const char* fileImage, unsigned int capacity)
{
	CCTexture2D *pTexture2D = CCTextureCache::sharedTextureCache()->addImage(fileImage);
	return initWithTexture(pTexture2D, capacity);
}

bool AlphaTestBatchNode::initWithTexture(CCTexture2D* pTexture, unsigned int capacity )
{
	do{
		CC_BREAK_IF(!CCSpriteBatchNode::initWithTexture(pTexture, capacity));

		GLchar* pszFragSource =
			"#ifdef GL_ES \n \
			precision mediump float; \n \
			#endif \n \
			uniform sampler2D u_texture; \n \
			varying vec2 v_texCoord; \n \
			varying vec4 v_fragmentColor; \n \
			void main(void) \n \
			{ \n \
				// Convert to greyscale using NTSC weightings \n \
				//calculate the fragment color based on the texture and the vertex colour \n \
				vec4 basecolor = texture2D(u_texture, v_texCoord); \n \
				if(basecolor.a == 0.0) \n \
				{ \n \
					//throw this fragment away \n \
					discard; \n \
				} \n \
				gl_FragColor = basecolor; \n \
			}";

		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
		this->setShaderProgram(pProgram);
		pProgram->release();
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();

		return true;
	} while (0);
	return false;
}

void AlphaTestBatchNode::draw()
{
	CCSpriteBatchNode::draw();
}

// ------------------------------------------------------------------------


RoleShadowBatchNode::RoleShadowBatchNode()
{
	
}


RoleShadowBatchNode::~RoleShadowBatchNode()
{

}


RoleShadowBatchNode* RoleShadowBatchNode::create( const char* pszFileName )
{
	RoleShadowBatchNode* graySprite = new RoleShadowBatchNode();
	if (graySprite && graySprite->initWithFile(pszFileName, 100))
	{
		graySprite->autorelease();
		return graySprite;
	}
	else
	{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

void RoleShadowBatchNode::visit()
{
	int i,j,length = m_pChildren->data->num;
	CCNode ** x = (CCNode**)m_pChildren->data->arr;
	CCNode *tempItem;

	// insertion sort
	for(i=0; i<length; i++)
	{
		tempItem = x[i];
		if(tempItem)
		{
			CCNode* pRole = (CCNode*)(tempItem->getUserData());
			if(pRole)
			{
				tempItem->setPosition(pRole->getPosition());
			}
		}
	}

	//m_bReorderChildDirty = true;
	CCSpriteBatchNode::visit();
}

void RoleShadowBatchNode::RemoveShadow( CCNode* child )
{
	int i,j,length = m_pChildren->data->num;
	CCNode ** x = (CCNode**)m_pChildren->data->arr;
	CCNode *tempItem;

	// insertion sort
	for(i=0; i<length; i++)
	{
		tempItem = x[i];
		if(tempItem)
		{
			CCNode* pRole = (CCNode*)(tempItem->getUserData());
			if(pRole == child)
			{
				removeChild(tempItem, true);
			}
		}
	}
}

// ------------------------------------------------------------------------


CATLObjectLayer::CATLObjectLayer()
	:m_height(0)
	, m_pRoleShadow(NULL)
{
	m_name = "ATLObjectLayer";
}

CATLObjectLayer::~CATLObjectLayer()
{
	RemoveLayerObjects();
}

void CATLObjectLayer::draw(void)
{
	cocos2d::CCLayer::draw();
}



void CATLObjectLayer::ParseLayer(CATLObjectInfo::LAYER::BASE* pLayer, CATLObjectInfo::VECTOR2D parentPos)
{
	CATLObjectInfo::VECTOR2D pos = parentPos;
	CATLObjectInfo::LAYER::OBJECT* pObject = dynamic_cast<CATLObjectInfo::LAYER::OBJECT*>(pLayer);
	if(pObject != NULL)
	{
		ASprite* pAsprite = NULL;
		CCSpriteBatchNode* pBatchNode = NULL;
		cocos2d::CCTexture2D* pTexture = NULL;

		std::map<std::string, OBJECT_BATCHNODE>::iterator iter = m_objectBatchNode.find(pObject->spriteFile);
		if(iter != m_objectBatchNode.end())
		{
			pAsprite = iter->second.pAsprite;
			pTexture = iter->second.pTexture;
			pBatchNode = iter->second.pBatchNode;
		}
		else
		{
			pAsprite = AspriteManager::getInstance()->getAsprite((std::string("Decoration/") + pObject->spriteFile).c_str());
			
			if(pAsprite)
			{
				pBatchNode = AlphaTestBatchNode::create(pAsprite->getImageName().c_str());
				pTexture = pBatchNode->getTexture();
			}

			OBJECT_BATCHNODE ob;
			ob.pAsprite = pAsprite;
			ob.pTexture = pTexture;
			ob.pBatchNode = pBatchNode;
			m_objectBatchNode.insert(std::make_pair(pObject->spriteFile, ob));

			if(pObject->zOrder == MAP_Z_LIGHT)
			{
				cocos2d::ccBlendFunc bf;
				bf.src = GL_SRC_ALPHA;
				bf.dst = GL_ONE;
				pBatchNode->setBlendFunc(bf);
			}
			else
			{
				cocos2d::ccBlendFunc bf;
				bf.src = GL_SRC_ALPHA;
				bf.dst = GL_ONE_MINUS_SRC_ALPHA;
				pBatchNode->setBlendFunc(bf);
			}

			
			// 决定画的顺序。
			addChild(pBatchNode, pObject->zOrder);

			// 父节点的ZDepth也会影响到子节点的ZDepth。
			pBatchNode->setVertexZ(0.0f);


		}

		if(pAsprite == NULL || pBatchNode == NULL || pTexture == NULL)
		{
			CCLog("Error : parse object layer : %s", pObject->spriteFile.c_str());
			return;
		}

		pos.x += pObject->pos.x;
		pos.y += pObject->pos.y;
		cocos2d::CCPoint cp(pos.x, pos.y );

		if(pAsprite->GetAFrames(pObject->animID) > 1)
		{
			ParseAnimationLayer(pObject, cp, pAsprite, pTexture);
		}
		else
		{
			ParseImmovableLayer(pObject, cp, pBatchNode, pAsprite, pTexture);
		}
		
	}
	else
	{
		for(size_t i = 0; i < pLayer->childrens.size(); i++)
		{
			ParseLayer(pLayer->childrens[i], pos);
		}
	}
}

void CATLObjectLayer::ParseObject(CATLObjectInfo* pObjectInfo, int levelID, LevelLayer* pLevelLayer)
{
	if(pObjectInfo == NULL)
		return;

	// TODO : 区分Level？？
	for(size_t i = 0; i < pObjectInfo->m_levels.size(); i++)
	{
		int id = atoi(pObjectInfo->m_levels[i]->name.c_str());
		if(id == levelID)
		{
			m_height = pLevelLayer->getMapSizeInPixel().height;// - pLevelLayer->getMapTileSizeInPixel().height;
			for(size_t j = 0; j < pObjectInfo->m_levels[i]->layers.size(); j++)
			{

				ParseLayer(pObjectInfo->m_levels[i]->layers[j], pObjectInfo->m_levels[i]->pos);
			}
		}		
	}
}

void CATLObjectLayer::reorderChild(cocos2d::CCNode *child, int zOrder)
{
	child->setVertexZ((float)zOrder / (float)MAP_Z_DYNAMIC_END);
    CCLayer::reorderChild(child, zOrder);
}

void CATLObjectLayer::addChild( CCNode * child, int zOrder )
{
    child->setVertexZ((float)zOrder / (float)MAP_Z_DYNAMIC_END);
	CCLayer::addChild(child, zOrder);
}


void CATLObjectLayer::RemoveLayerObjects()
{
	for(size_t i = 0; i < m_lstAnimSprites.size(); i++)
	{
		AnimSprite* anim = m_lstAnimSprites[i];
		EnginePlayerManager::getInstance()->removeAsprite(anim, true);
	}

	m_lstAnimSprites.clear();
}

size_t CATLObjectLayer::getBatchNodeNumber()
{
	return 0;
}

void CATLObjectLayer::ParseImmovableLayer( CATLObjectInfo::LAYER::OBJECT* pObject, const cocos2d::CCPoint& pos, CCSpriteBatchNode* pBatchNode, ASprite* pAsprite, cocos2d::CCTexture2D* pTexture )
{
	if(pAsprite != NULL)
	{
		int animID = pObject->animID;
		int frame = pAsprite->GetAnimFrame(animID, 0);
		if(frame >= 0)
		{
			int animOffsetX = pAsprite->GetAFrameOffsetX(animID, 0, 0);
			int animOffsetY = pAsprite->GetAFrameOffsetY(animID, 0, 0);

			int moduleCount = pAsprite->GetFModules(frame);
			for(int k = 0; k < moduleCount; k++)
			{
				int moduleID = pAsprite->GetFrameModule(frame, k);
				CCRect frameRect(0,0,0,0);
				frameRect.size.width = (float)pAsprite->GetModuleWidth(moduleID);
				frameRect.size.height = (float)pAsprite->GetModuleHeight(moduleID);
				frameRect.origin.x = (float)pAsprite->GetModuleX(moduleID);
				frameRect.origin.y = (float)pAsprite->GetModuleY(moduleID);
				int frameOffsetX = pAsprite->GetFrameModuleX(frame, k);
				int frameOffsetY = pAsprite->GetFrameModuleY(frame, k);
				CCSprite *pSprite = new CCSprite();
				pSprite->autorelease();

				pSprite->initWithTexture(pTexture,frameRect);

				pSprite->setAnchorPoint(ccp(0.0f, 0.0f));

				// 因为在引擎中坐标的原点为左下角，在ATL编辑器中，坐标系的原点为左上角，所以要加上frameRect.size.height
				CCPoint pt(pos.x + animOffsetX + frameOffsetX, pos.y + animOffsetY + frameOffsetY + frameRect.size.height );
				pt.y = m_height - pt.y;

				

				bool bFlipX = false;
				bool bFlipY = false;	// 在游戏中坐标系的原点在左下角，在地图编辑器中，坐标系为左上角

				int flag = pAsprite->GetFModuleFlags(frame, k);

				switch(flag)
				{
				case 1:
					// 水平翻转
					bFlipX = !bFlipX;
					break;
				case 2:
					// 竖直翻转;
					bFlipY = !bFlipY;
					break;
				case 3:
					bFlipX = !bFlipX;
					bFlipY = !bFlipY;
					break;
				default:
					break;
				}

				flag = pObject->flags;
				switch(flag)
				{
				case 1:
					// 水平翻转
					bFlipX = !bFlipX;
					break;
				case 2:
					// 竖直翻转
					bFlipY = !bFlipY;
					break;
				case 3:
					bFlipX = !bFlipX;
					bFlipY = !bFlipY;
					break;
				default:
					break;
				}

				switch(pObject->renderFlag)
				{
				case CATLObjectInfo::LAYER::OBJECT::E_FLIP_X:
					//pSprite->setRotationY(180.0f);
					// pParentNode->setScaleX(-1.0f * pParentNode->getScaleX());
					bFlipX = !bFlipX;
					break;
				case CATLObjectInfo::LAYER::OBJECT::E_FLIP_Y:
					//pSprite->setRotationX(180.0f);
					bFlipY = !bFlipY;
					break;
				case CATLObjectInfo::LAYER::OBJECT::E_FLIP_XY:
					/*pSprite->setRotationX(180.0f);
					pSprite->setRotationY(180.0f);*/
					bFlipX = !bFlipX;
					bFlipY = !bFlipY;
					break;
				default:
					break;
				}

				// 必须要先旋转后再设置坐标
				pSprite->setPosition(pt);

				pSprite->setFlipX(bFlipX);	
				pSprite->setFlipY(bFlipY);	

				int zOrder = pObject->zOrder; 
				if(zOrder == MAP_Z_OBJECT || zOrder == MAP_Z_OBJ_SHADOW)
				{
					zOrder = LevelLayer::sCalcZorder(ccp(pos.x, m_height - pos.y));
				}

				pSprite->setVertexZ((float)zOrder / (float)MAP_Z_DYNAMIC_END);
				pBatchNode->addChild(pSprite, zOrder);

			}
		}
	}
}

void CATLObjectLayer::ParseAnimationLayer( CATLObjectInfo::LAYER::OBJECT* pObject, const cocos2d::CCPoint& pos, ASprite* pAsprite, cocos2d::CCTexture2D* pTexture )
{
	AnimSprite *anim = EnginePlayerManager::getInstance()->addAnimSprite(pAsprite, 0.0f, 0.0f);			
	if(anim != NULL)
	{
		anim->SetAnim(pObject->animID,1,true);	

		/// store animsprites
		m_lstAnimSprites.push_back(anim);

		/// bind to the bathNode
		CCSprite * pParentNode = anim->getParentNode();	

		CCSpriteBatchNode* pBatchNode = anim->getBatchNode();

#if _DEBUG
		if(pBatchNode)
		{
			pBatchNode->m_name = pObject->spriteFile;
		}
#endif
		pParentNode->setAnchorPoint(ccp(0.5f, 0.5f));				
		switch(pObject->renderFlag)
		{
		case CATLObjectInfo::LAYER::OBJECT::E_FLIP_X:
			pParentNode->setRotationY(180.0f);
			// pParentNode->setScaleX(-1.0f * pParentNode->getScaleX());

			break;
		case CATLObjectInfo::LAYER::OBJECT::E_FLIP_Y:
			pParentNode->setRotationX(180.0f);
			break;
		case CATLObjectInfo::LAYER::OBJECT::E_FLIP_XY:
			pParentNode->setRotationX(180.0f);
			pParentNode->setRotationY(180.0f);
			break;
		default:
			break;
		}

		// 必须要先旋转后再设置坐标
		CCPoint cp(pos);
		cp.y = m_height - cp.y;
		pParentNode->setPosition(cp);

		int zOrder = pObject->zOrder; 
		if(zOrder == MAP_Z_LIGHT)
		{
			cocos2d::ccBlendFunc bf;
			bf.src = GL_SRC_ALPHA;
			bf.dst = GL_ONE;
			pBatchNode->setBlendFunc(bf);
		}
		else if(zOrder == MAP_Z_OBJECT)
		{
			zOrder = LevelLayer::sCalcZorder(cp);
		}
		
		addChild(pBatchNode, zOrder);
	}
}

void CATLObjectLayer::AddRoleShadow( cocos2d::CCNode* pRole )
{
	if(m_pRoleShadow == NULL)
	{
		ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("spriteBin/shadow.bin");
		if(pAsprite != NULL)
		{
			m_pRoleShadow = RoleShadowBatchNode::create(pAsprite->getImageName().c_str());
			addChild(m_pRoleShadow, MAP_Z_ROLE_SHADOW);
			m_pRoleShadow->setVertexZ(0.0f);
		}
	}
	
	if(m_pRoleShadow)
	{
		CCPoint cp;
		ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("spriteBin/shadow.bin");

		CCSprite* pCSprite = pAsprite->getSpriteFromFrame(0, 0, cp);
		if(pCSprite != NULL)
		{
			pCSprite->setTexture(m_pRoleShadow->getTexture());
			cp = pRole->getPosition();
			pCSprite->setPosition(cp);
			pCSprite->setTag(SHADOW_TAG);
			pCSprite->setUserData(pRole);
			int zOrder = LevelLayer::sCalcZorder(cp);
			pCSprite->setVertexZ((float)MAP_Z_ROLE_SHADOW / (float)MAP_Z_DYNAMIC_END);
			m_pRoleShadow->addChild(pCSprite, zOrder);


		}
	}
}

void CATLObjectLayer::removeChild( CCNode* child, bool cleanup )
{
	if(m_pRoleShadow)
	{
		m_pRoleShadow->RemoveShadow(child);
	}
	CCLayer::removeChild(child, cleanup);
}
