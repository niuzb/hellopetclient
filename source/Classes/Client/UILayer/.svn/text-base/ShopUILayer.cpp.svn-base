//
//  ShopUILayer.cpp
//  HelloLua
//
//  Created by rickycheng  on 13-6-18.
//
//
#include "PVPMessage.h"
#include "GMessage.h"
#include "ShopUILayer.h"
#include "Localization.h"
#include "GameFontManager.h"
#include "resources.h"
#include "particle_manager.h"
#include "UserData.h"
#include "GameAudioManager.h"
#include "MainMenuLayer.h"
#include "GameManager.h"
#include "ItemManager.h"
#include "TipMgr.h"

using namespace TXGUI;

ShopUILayer::ShopUILayer()
{
    this->m_bCloseLayerCallBack = false;
    this->m_pIconButtonLayer = NULL;
}

ShopUILayer::~ShopUILayer()
{
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void ShopUILayer::setTouchEnabled(bool value)
{
	CCLayer::setTouchEnabled(value);
}

bool ShopUILayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	UIManager *manager = UIManager::sharedManager();
	m_pLayer = manager->CreateUILayoutFromFile("UIplist/ShopUI.plist", this, "ShopUI", true);
    manager->RegisterMenuHandler("ShopUI","ShopUILayer::OnClose", menu_selector(ShopUILayer::OnClose), this);
	return true;
}

void ShopUILayer::sendShopList()
{
    PVPMessage::Get()->sendShopItems();
}

void ShopUILayer::setupShopList(std::vector<shopItem>& shoplist)
{
    std::vector<shopItem>::iterator it = shoplist.begin();
    for(; it != shoplist.end(); ++it)
    {
    }
}

void ShopUILayer::setupIconButtons()
{
    m_pIconButtonLayer = CCLayer::create();
	if(m_pLayer)
	{
		UIPicture* frame = m_pLayer->FindChildObjectByName<UIPicture>("autohook_grid_area");
		if(frame)
		{
			int row = 2;
			int column = 6;
			CCSize size = frame->getSpriteSize();
			float width = size.width / column;
			float height = size.height / row;
			ASprite* as = AspriteManager::getInstance()->getAsprite(KUI_BIN);
			for(int i=0; i<row; i++)
			{
				for(int j=0; j<column; j++)
				{
					CCSprite* pEmptyItem = CCSprite::create();
					pEmptyItem->setContentSize(CCSize(width,height));
					CCPoint pt;
					CCSprite* pSelectItem = as->getSpriteFromFrame_Middle(map_ui_FRAME_ALCHEMY_ICON_CLICKED,0,pt);
					IconButton * pIcon = new IconButton(pEmptyItem, NULL, pSelectItem, this, NULL);
					pIcon->autorelease();
					int index = i * column + j;
					pIcon->SetButtonIndex(index+1);
					pIcon->setContentSize(pEmptyItem->getContentSize());
					pIcon->creatDragReceiver(EAlchemyBag);
					pIcon->SetTappedHandler(this,menu_selector(ShopUILayer::onItemTapped),menu_selector(ShopUILayer::onTapCancel));
					float x = (j - column /2 + 0.5f) * width;
					float y = (-i + row /2 - 0.5f) * height;
                    
					pIcon->setPosition(ccp(x,y));
                    
					m_pIconButtonList.push_back(pIcon);
					m_pIconButtonLayer->addChild(pIcon,index+1);
				}
			}
			m_pIconButtonLayer->setPosition(frame->getWorldPosition());
			m_pLayer->getCurrentNode()->addChild(m_pIconButtonLayer);
		}
	}
}

void ShopUILayer::setItemIcon(int item_num, int item_id, unsigned int item_index)
{
    if(m_pLayer && m_pLayer->isVisible())
    {
        IconButton* button = m_pIconButtonList[item_index];
        button->setTag(item_index);
        m_VecIconIDs.push_back(item_id);
        
        if(button)
        {
            CCSprite* sprite = ItemManager::Get()->getIconSpriteById(item_id);
            
            char buf[10];
            sprintf(buf, "%d", item_num);
            UILabelTTF* label_name = UILabelTTF::create(buf, KJLinXin, 20);
            sprite->addChild(label_name);
            label_name->setPosition(ccp(sprite->getContentSize().width-label_name->getContentSize().width/2-5,
                                        label_name->getContentSize().height+5));
            
            button->SetNormalIcon(sprite);
            button->creatDragReceiver(EAlchemyBag);
            showSpriteParticleEffect(sprite,item_id,ccp(sprite->getContentSize().width * 0.5,sprite->getContentSize().height * 0.5));
        }
    }
}

void ShopUILayer::closeLayerCallBack(void)
{
	m_bCloseLayerCallBack = true;
	OnClose(NULL);
	m_bCloseLayerCallBack = false;
}

void ShopUILayer::OnClose(CCObject *sender)
{
    setVisible(false);
}

void ShopUILayer::onTapCancel(CCObject* sender)
{
    TipMgr::Get()->destroyTip();
}

void ShopUILayer::onItemTapped(CCObject* sender)
{
    if(m_VecIconIDs.size() <= 0)
        return;
    
    UIMenu* menu = dynamic_cast<UIMenu*>(sender);
	if(menu)
	{
		CCNode* parent = menu->getParent();
		IconButton* button = dynamic_cast<IconButton*>(parent);
		if(button)
		{
            int item_index = button->getTag();
            int item_id = m_VecIconIDs[item_index];
            ItemManager::Get()->showItemTipsById(item_id, menu->getTouchPoint());
		}
	}
}

void ShopUILayer::showSpriteParticleEffect(CCNode* parent,unsigned int id,CCPoint pt)
{
	char particleName[30];
	sprintf(particleName,"particle_effect_spirit_%d",id);
    CCNode* particle = ParticleManagerX::sharedManager()->getParticles(particleName);
    if(particle != NULL)
    {
		CCNode* child = parent->getChildByTag(100);
		if(child)
		{
			child->removeFromParentAndCleanup(true);
			child = NULL;
		}
        parent->addChild(particle,100,100);
        particle->setPosition(pt);
    }
}




