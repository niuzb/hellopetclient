#include "DamageValueEffect.h"
#include "TXGUIHeader.h"
#include "AspriteManager.h"
#include "ASprite.h"
#include "resources.h"
DamageValueEffect::DamageValueEffect()
{

}

DamageValueEffect::~DamageValueEffect()
{
	for(map<CCNode*,float>::iterator it= m_pDamageLabels->begin();
		it != m_pDamageLabels->end(); it++)
	{
		CCNode* label = it->first;
		if(label)
		{
			label->removeFromParentAndCleanup(true);
			label = NULL;
		}
	}
	m_pDamageLabels->clear();
	delete m_pDamageLabels;
	m_pDamageLabels = NULL;
}

bool DamageValueEffect::init()
{
	bool bRet = false;
	do {
		m_pDamageLabels = new std::map<CCNode*,float>;
		schedule(schedule_selector(DamageValueEffect::update), 0.05f);
		bRet = true;
	}while (0);
	return bRet;
}

void DamageValueEffect::HandleDamageNumberEffect(CCNode* parent,unsigned int damage,bool isCrit,bool isHarmFul)
{
	CCPoint seerPos = parent->getPosition();
	if(isCrit)
	{
		CreateCritDamageLable(damage,seerPos,isHarmFul);
	}
	else
	{
		CreateDamageLable(damage,seerPos,isHarmFul);
	}

}

CCLabelAtlas* DamageValueEffect::CreateDamageLable(unsigned int damage,CCPoint parentPos,bool isHarmFul)
{
	CCPoint visibleSize = CCDirector::sharedDirector()->getLevelRenderCameraOffset();

	float pos_x = parentPos.x - visibleSize.x;
	float pos_y = parentPos.y - visibleSize.y;
	CCPoint uiPos = ccp(pos_x, pos_y);
	char damageString[10];
	sprintf(damageString,"%d",damage);
	CCLabelAtlas* lable;
	if(isHarmFul)
	{
		lable = CCLabelAtlas::create(damageString,"UI/ui_numble_1.png",37,50,48);
	}
	else
	{
		lable = CCLabelAtlas::create(damageString,"UI/ui_numble_3.png",37,50,48);
	}
	
	lable->setPosition(uiPos.x,uiPos.y+70);
	lable->setAnchorPoint(ccp(0.5,0.5));
	lable->setScale(0);
	CCActionInterval* actionScale = CCScaleTo::create(0.01f,2);
	CCActionInterval* actionMove = CCMoveBy::create(0.01f,ccp(0,40));
	CCSpawn* FirstAction = CCSpawn::createWithTwoActions(actionScale,actionMove);
	CCActionInterval* actionFade = CCFadeOut::create(0.3f);
	CCActionInterval* bezierAction = CCMoveBy::create(0.3f,ccp(0,40));
	CCSpawn* SecondAction = CCSpawn::createWithTwoActions(bezierAction,actionFade);
	//lable->runAction(actionScale);
	lable->runAction(CCSequence::create(FirstAction,CCScaleTo::create(0.05f,0.7f),CCDelayTime::create(0.2f),SecondAction,
		NULL));
	if(m_pDamageLabels->find(lable) == m_pDamageLabels->end())
	{
		m_pDamageLabels->insert(make_pair(lable,0.6f));
		this->addChild(lable);
	}
	
	return lable;
}

CCNode* DamageValueEffect::CreateCritDamageLable(unsigned int damage,CCPoint parentPos,bool isHarmFul)
{
	CCPoint visibleSize = CCDirector::sharedDirector()->getLevelRenderCameraOffset();

	float pos_x = parentPos.x - visibleSize.x;
	float pos_y = parentPos.y - visibleSize.y;
	CCPoint uiPos = ccp(pos_x, pos_y);

	CCNode* critNode = CCNode::create();
	critNode->setPosition(ccp(uiPos.x,uiPos.y+70));
	critNode->setAnchorPoint(ccp(0.5,0.5));

	ASprite *as = AspriteManager::getInstance()->getAsprite("UI/ui_inbattle.bin"); 
	CCPoint pt;
	CCSprite* critSprite = as->getSpriteFromFrame_Middle(map_ui_inbattle_FRAME_CRITICALBACK,0,pt);
	if(critSprite)
	{
		critSprite->setPosition(CCPointZero);
		critNode->addChild(critSprite,0);
	}

	char damageString[10];
	sprintf(damageString,"%d",damage);
	CCLabelAtlas* label;
	if(isHarmFul)
	{
		label = CCLabelAtlas::create(damageString,"UI/ui_numble_2.png",37,50,48);
	}
	else
	{
		label = CCLabelAtlas::create(damageString,"UI/ui_numble_3.png",37,50,48);
	}

	if(label)
	{
		label->setAnchorPoint(ccp(0.5f,0.5f));
		label->setPosition(CCPointZero);
		critNode->addChild(label,1);
		if(critSprite)
		{
			float scale_x = label->getContentSize().width / (0.6f * critSprite->getContentSize().width);
			float scale_y = label->getContentSize().height / (0.6f * critSprite->getContentSize().height);
			float scale = (scale_x > scale_y) ? scale_x : scale_y; 
			critSprite->setScale(scale);
			critSprite->setPosition(CCPointZero);
			critSprite->setAnchorPoint(ccp(0.5f,0.5f));
		}
	}

	critNode->setScale(0);
	critNode->runAction(getBattleUIAction());
	if(m_pDamageLabels->find(critNode) == m_pDamageLabels->end())
	{
		m_pDamageLabels->insert(make_pair(critNode,0.6f));
		this->addChild(critNode);
	}
	return critNode;
}

CCSprite* DamageValueEffect::CreateMissLabel(CCPoint parentPos)
{
	CCPoint visibleSize = CCDirector::sharedDirector()->getLevelRenderCameraOffset();

	float pos_x = parentPos.x - visibleSize.x;
	float pos_y = parentPos.y - visibleSize.y;
	CCPoint uiPos = ccp(pos_x, pos_y);
	ASprite *as = AspriteManager::getInstance()->getAsprite("UI/ui_inbattle.bin"); 
	CCPoint pt;
	CCSprite* missSprite = as->getSpriteFromFrame_Middle(map_ui_inbattle_FRAME_MISS,0,pt);
	if(missSprite)
	{
		missSprite->setPosition(ccp(uiPos.x,uiPos.y+70));
		missSprite->setAnchorPoint(ccp(0.5,0.5));
		missSprite->setScale(0);

		missSprite->runAction(getBattleUIAction());
		if(m_pDamageLabels->find(missSprite) == m_pDamageLabels->end())
		{
			m_pDamageLabels->insert(make_pair(missSprite,0.6f));
			this->addChild(missSprite);
		}
	}
	return missSprite;
}

CCSprite* DamageValueEffect::CreateBlockLabel(CCPoint parentPos)
{
	CCPoint visibleSize = CCDirector::sharedDirector()->getLevelRenderCameraOffset();

	float pos_x = parentPos.x - visibleSize.x;
	float pos_y = parentPos.y - visibleSize.y;
	CCPoint uiPos = ccp(pos_x, pos_y);
	ASprite *as = AspriteManager::getInstance()->getAsprite("UI/ui_inbattle.bin"); 
	CCPoint pt;
	CCSprite* missSprite = as->getSpriteFromFrame_Middle(map_ui_inbattle_FRAME_BLOCK,0,pt);
	if(missSprite)
	{
		missSprite->setPosition(ccp(uiPos.x,uiPos.y+70));
		missSprite->setAnchorPoint(ccp(0.5,0.5));
		missSprite->setScale(0);
		
		missSprite->runAction(getBattleUIAction());
		if(m_pDamageLabels->find(missSprite) == m_pDamageLabels->end())
		{
			m_pDamageLabels->insert(make_pair(missSprite,0.6f));
			this->addChild(missSprite);
		}
	}
	return missSprite;
}

CCAction* DamageValueEffect::getBattleUIAction()
{
	CCActionInterval* actionScale = CCScaleTo::create(0.01f,2.5f);
	CCActionInterval* actionMove = CCMoveBy::create(0.01f,ccp(0,40));
	CCSpawn* FirstAction = CCSpawn::createWithTwoActions(actionScale,actionMove);
	CCActionInterval* actionFade = CCFadeOut::create(0.3f);
	CCActionInterval* bezierAction = CCMoveBy::create(0.3f,ccp(0,40));
	CCSpawn* SecondAction = CCSpawn::createWithTwoActions(bezierAction,actionFade);
	CCFiniteTimeAction* action = CCSequence::create(FirstAction,CCScaleTo::create(0.05f,0.8f),CCDelayTime::create(0.2f),
		SecondAction, NULL);
	return action;
}

void DamageValueEffect::RemoveLable(CCNode* sender)
{
	//CCLog("DamageValueEffect::RemoveLable");
	if(sender)
	{
		sender->stopAllActions();
		sender->removeFromParentAndCleanup(true);
	}
}

void DamageValueEffect::moveWithParabola(CCSprite* mSprite, CCPoint startPoint, CCPoint endPoint, float time)
{
	CCActionInterval* actionScale = CCScaleTo::create(1.5,1.0);
	CCActionInterval* actionMove = CCMoveBy::create(1.5,ccp(0,200));
	CCSpawn* action = CCSpawn::createWithTwoActions(actionScale,actionMove);
	CCActionInterval* actionFade = CCFadeOut::create(1.0);
	
}

void DamageValueEffect::update(float dt)
{
	map<CCNode*,float>::iterator it= m_pDamageLabels->begin();
	while(it != m_pDamageLabels->end())
	{
		float time = it->second;
		time -= dt;
		if(time <= 0)
		{
			CCNode* label = it->first;
			if(label)
			{
				label->removeFromParentAndCleanup(true);
				m_pDamageLabels->erase(it++);
				label = NULL;
			}
		}
		else
		{
			it->second = time;
			it++;
		}
	}

}