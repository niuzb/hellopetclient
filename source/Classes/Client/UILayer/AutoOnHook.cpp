//
//  AutoOnHook.cpp
//  HelloLua
//
//  Created by rickycheng  on 13-5-20.
//
//
#include "PVPMessage.h"
#include "AutoOnHook.h"
#include "GameResourceManager.h"
#include "Localization.h"
#include "GameFontManager.h"
#include "resources.h"
#include "GMessage.h"
#include "PVPMessage.h"
#include "ItemManager.h"
#include "particle_manager.h"
#include "GameConfigFromLuaManager.h"
#include "TipMgr.h"
#include "LuaTinkerManager.h"
#include "MainMenuLayer.h"
#include "TaskManager.h"

using namespace TXGUI;

AutoOnHook::AutoOnHook()
{
    this->m_pListH = NULL;
    this->m_pListV = NULL;
    this->m_FuBenIcon = NULL;
    this->m_FuBenName =  NULL;
    this->m_MasterFuBenName = NULL;
    this->m_pIconButtonLayer = NULL;
    this->m_pLayer = NULL;
    
    this->m_pLabelCDNumber = NULL;
    this->m_pLabelCDText = NULL;
    this->m_pCDFrame = NULL;

    this->m_dt  = 0;
    this->m_cnt = 60;
    this->m_musicTime = 0;
    
    this->m_pStartBtn = NULL;
    this->m_pSpeedUpBtn = NULL;
    this->m_pStopBtn = NULL;
    
    this->m_pTurnBtn1 = NULL;
    this->m_pTurnBtn2 = NULL;
    this->m_pTurnBtn3 = NULL;
    
    this->m_pTurnText1 = NULL;
    this->m_pTurnText2 = NULL;
    
    this->m_pTurnSami1 = NULL;
    this->m_pTurnSami2 = NULL;
    this->m_pTurnSami3 = NULL;
    
    this->m_pTurnFrame = NULL;
    
    this->m_turnId = 2;
    this->m_instanceId = 0;
    
    this->m_bCloseLayerCallBack = false;
    
    this->m_pStartLabel = NULL;
    this->m_pSpeedupLabel = NULL;
    this->m_pStopLabel = NULL;
    this->m_pUseDiamand = NULL;
    this->m_bStopSel = false;
    
    this->m_pCloseBtn = NULL;
    
    this->m_num_diamand = 0;
    this->m_num_coin = 0;
    this->m_num_exploit = 0;
    this->m_num_exp = 0;
}

AutoOnHook::~AutoOnHook()
{
    UIManager::sharedManager()->RemoveUILayout("AutoOnHookUI");
    UIManager::sharedManager()->RemoveUILayout("UseDiamand");
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void AutoOnHook::setTouchEnabled(bool value)
{
	CCLayer::setTouchEnabled(value);
}

bool AutoOnHook::init()
{
    if(!CCLayer::init())
	{
		return false;
	}
    
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	UIManager *manager = UIManager::sharedManager();
	m_pLayer = manager->CreateUILayoutFromFile("UIplist/AutoOnHookUI.plist", this, "AutoOnHookUI", true);
    manager->RegisterMenuHandler("AutoOnHookUI","AutoOnHook::OnClose",	menu_selector(AutoOnHook::OnClose), this);
    manager->RegisterMenuHandler("AutoOnHookUI","AutoOnHook::OnSpeedUpHook",	menu_selector(AutoOnHook::OnSpeedUpHook), this);
    manager->RegisterMenuHandler("AutoOnHookUI","AutoOnHook::OnStopHook",	menu_selector(AutoOnHook::OnStopHook), this);
    manager->RegisterMenuHandler("AutoOnHookUI","AutoOnHook::OnStartAutoHook",	menu_selector(AutoOnHook::OnStartAutoHook), this);
    manager->RegisterMenuHandler("AutoOnHookUI","AutoOnHook::OnClickTurn1",	menu_selector(AutoOnHook::OnClickTurn1), this);
    manager->RegisterMenuHandler("AutoOnHookUI","AutoOnHook::OnClickTurn2",	menu_selector(AutoOnHook::OnClickTurn2), this);
    manager->RegisterMenuHandler("AutoOnHookUI","AutoOnHook::OnClickTurn3",	menu_selector(AutoOnHook::OnClickTurn3), this);
    m_pListV = m_pLayer->FindChildObjectByName<UIScrollList>("hook_characterScrollList_V");
    
    setupTurns();
    setupIconButtons();
    this->setIconAllGet(0, 0, 0, 0);
    
    m_pCloseBtn = m_pLayer->FindChildObjectByName<UIButton>("hook_close");
    m_pUseDiamand = manager->CreateUILayoutFromFile("UIplist/UseDiamand.plist", this, "UseDiamand", true);
    manager->RegisterMenuHandler("UseDiamand","TalentLayer::OnConfirm",	menu_selector(AutoOnHook::OnConfirm), this);
    manager->RegisterMenuHandler("UseDiamand","TalentLayer::OnCancle",	menu_selector(AutoOnHook::OnCancle), this);
    m_pUseDiamand->setVisible(false);
    setDiamandTxt();
    
	return true;
}

void AutoOnHook::clearVecIDs()
{
    m_VecIDs.clear();
}

void AutoOnHook::sendCSABMonsterReq(unsigned int instance_id)
{
    m_instanceId = instance_id;
    PVPMessage::Get()->sendCSABMonsterReq(m_instanceId);
    //setPictureAndWord(instance_id);
}

void AutoOnHook::startCD(int timeout)
{
    if(timeout != 0)
    {
        processVisibleCD(true);
        convertSecToMinute(timeout);
        
        char buf[10];
        sprintf(buf, "%d", m_musicTime);
        std::string strname = buf;
        
        strname += ":";
        char buf2[10];
        sprintf(buf2, "%d", m_cnt);
        
        if(m_cnt < 10)
        {
            strname += "0";
            strname += buf2;
        }
        else
            strname += buf2;
        
        setUpCDTime(strname.c_str());
        unscheduleUpdate();
        scheduleUpdate();
        showStartBtn(false);
    }
    else
    {
        showStartBtn(true);
        const char* start_txt = Localizatioin::getLocalization("M_AUTOFIGHT_COMPLETE");
        m_pStartLabel->setString(start_txt);
        unscheduleUpdate();
        //setUpCDTime("挂机完成");
        setUpCDText("");
        processVisibleCD(true);
        TaskManager::getInstance()->RqsTaskFromServer();
    }
}

void AutoOnHook::processVisibleCD(bool visible)
{
    m_pLabelCDNumber->setVisible(visible);
    m_pLabelCDText->setVisible(visible);
    m_pCDFrame->setVisible(visible);
    
    m_pTurnBtn1->setVisible(!visible);
    m_pTurnBtn2->setVisible(!visible);
    m_pTurnBtn3->setVisible(!visible);
    
    m_pTurnFrame->setVisible(!visible);
    m_pTurnText1->setVisible(!visible);
    m_pTurnText2->setVisible(!visible);
    
    m_pTurnSami1->setVisible(!visible);
    m_pTurnSami2->setVisible(!visible);
    m_pTurnSami3->setVisible(!visible);
}

void AutoOnHook::setupTurns()
{    
    UILabel* plabel1_turn = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_turn1");
    UILabel* plabel1_stamina = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_stamina1");
    UILabel* plabel2_turn = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_turn2");
    UILabel* plabel2_stamina = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_stamina2");
    UILabel* plabel3_stamina = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_stamina3");
    
    
    const char* turnstr1 = Localizatioin::getLocalization("M_AUTOFIGHT_TURN1");
    const char* turnstr1_cost = Localizatioin::getLocalization("M_AUTOFIGHT_TURN1_COST");
    const char* turnstr2 = Localizatioin::getLocalization("M_AUTOFIGHT_TURN2");
    const char* turnstr2_cost = Localizatioin::getLocalization("M_AUTOFIGHT_TURN2_COST");
    const char* turnstr3_cost = Localizatioin::getLocalization("M_AUTOFIGHT_TURN3_COST");


	plabel1_turn->setString(turnstr1);
	plabel1_stamina->setString(turnstr1_cost);

	plabel2_turn->setString(turnstr2);
	plabel2_stamina->setString(turnstr2_cost);

	plabel3_stamina->setString(turnstr3_cost);
    
    plabel1_turn->setColor(ccWHITE);
    plabel1_stamina->setColor(ccWHITE);
    
    plabel2_turn->setColor(ccWHITE);
    plabel2_stamina->setColor(ccWHITE);
    
    plabel3_stamina->setColor(ccWHITE);
    
    m_pTurnFrame = m_pLayer->FindChildObjectByName<UIPicture>("autohook_turn_background");
    m_pTurnText1 = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_turn1");
    m_pTurnText2 = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_turn2");
    
    m_pTurnBtn1 = m_pLayer->FindChildObjectByName<UIButton>("hook_turn1");
    m_pTurnBtn2 = m_pLayer->FindChildObjectByName<UIButton>("hook_turn2");
    m_pTurnBtn3 = m_pLayer->FindChildObjectByName<UIButton>("hook_turn3");
    
    m_pTurnBtn1->getMenuItemSprite()->selected();
    
    m_pTurnSami1 = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_stamina1");
    m_pTurnSami2 = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_stamina2");
    m_pTurnSami3 = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_stamina3");

    m_pCDFrame = m_pLayer->FindChildObjectByName<UIPicture>("autohook_frame_countdown");
    m_pLabelCDText = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_countdown");
    m_pLabelCDNumber = m_pLayer->FindChildObjectByName<UILabel>("auto_number_countdown");
        
    UIPicture* pListChapterArea = m_pLayer->FindChildObjectByName<UIPicture>("autohook_list_chapterarea");
    pListChapterArea->setVisible(false);
    
    UIPicture* pListChapterArrow = m_pLayer->FindChildObjectByName<UIPicture>("autohook_chapterselect_arrow");
    pListChapterArrow->setVisible(false);
    
    m_pStartBtn = m_pLayer->FindChildObjectByName<UIButton>("hook_start");
    m_pSpeedUpBtn = m_pLayer->FindChildObjectByName<UIButton>("hook_speedup");
    m_pStopBtn = m_pLayer->FindChildObjectByName<UIButton>("hook_stop");
    
    m_pStartBtn->setVisible(true);
    m_pSpeedUpBtn->setVisible(false);
    m_pStopBtn->setVisible(false);
    
    m_pStartLabel = m_pLayer->FindChildObjectByName<UILabel>("auto_text_start");
    m_pSpeedupLabel = m_pLayer->FindChildObjectByName<UILabel>("auto_text_speedup");
    m_pStopLabel = m_pLayer->FindChildObjectByName<UILabel>("auto_text_stop");
    
    const char* start_txt = Localizatioin::getLocalization("M_AUTOFIGHT_START");
    const char* speedup_txt = Localizatioin::getLocalization("M_AUTOFIGHT_SPEEDUP");
    const char* stop_txt = Localizatioin::getLocalization("M_AUTOFIGHT_STOP");
    
    m_pStartLabel->setString(start_txt);
    m_pSpeedupLabel->setString(speedup_txt);
    m_pStopLabel->setString(stop_txt);
    
    m_pStartLabel->setVisible(true);
    m_pSpeedupLabel->setVisible(false);
    m_pStopLabel->setVisible(false);
    
    processVisibleCD(false);
}

void AutoOnHook::setFuBen(const char *fuBenName)
{
    if(m_MasterFuBenName)
        m_MasterFuBenName->setString(fuBenName);
}

void AutoOnHook::setFuBen(int frame, const char* fuBenName)
{
    if(m_FuBenName)
        m_FuBenName->setString(fuBenName);
    
    ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("UI/ui2.bin");
    pAsprite->setImageName(0, "UI/ui.png");
    CCPoint pt = CCPointZero;
    m_FuBenIcon = pAsprite->getSpriteFromFrame_Middle(frame, 0, pt);
}

void AutoOnHook::setScrollistH(const std::vector<std::string>& values)
{
    m_pListH->clearChildrens();
    ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("UI/ui2.bin");
    pAsprite->setImageName(0, "UI/ui.png");
    
    std::vector<std::string>::const_iterator it = values.begin();
    for(; it != values.end(); it++)
    {
        const char* name = (*it).c_str();
        
        CCPoint pt = CCPointZero;
        CCSprite* normal = pAsprite->getSpriteFromFrame_Middle(map_ui2_FRAME_GENIUS_BUTTON_TALENT1 ,0, pt);
        CCSprite* clicked= pAsprite->getSpriteFromFrame_Middle(map_ui2_FRAME_GENIUS_BUTTON_TALENT1_SELECTED, 0, pt);
        
        UIButton* pItem = m_pListV->AddNewItem(normal,
                                               clicked,
                                               "TalentLayer::OnClickListItem",
                                               "",
                                               ccGREEN,
                                               kCCScrollMenuPriority);
        if(pItem)
        {
            CCLabelTTF* label_name = CCLabelTTF::create(name, KJLinXin, 14);
            pItem->getAnimationNode()->addChild(label_name);
        }
    }
}

void AutoOnHook::setScrollist(const std::vector<OnHookA2>& onHooksA2)
{
    m_pListV->clearChildrens();
    ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("UI/ui2.bin");
    pAsprite->setImageName(0, "UI/ui.png");
    std::vector<OnHookA2>::const_iterator it = onHooksA2.begin();
    for(; it != onHooksA2.end(); ++it)
    {
        int mon_id = it->mon_id;
        int mon_num = it->mon_num;
        
        std::string name = "ENEMY_NAME_";
        char buf[10];
        sprintf(buf, "%d", mon_id);
        name += buf;
        
        name = Localizatioin::getLocalization(name.c_str());
        
        sprintf(buf, "%d", mon_num);
        string value = "X";
        value += buf;
        
        CCPoint pt = CCPointZero;
        CCSprite* normal = pAsprite->getSpriteFromFrame_Middle(map_ui2_FRAME_AUTOFIGHT_TEXT_MONSTERNAME ,0, pt);
        CCSprite* clicked= pAsprite->getSpriteFromFrame_Middle(map_ui2_FRAME_AUTOFIGHT_TEXT_MONSTERNAME, 0, pt);
        UIButton* pItem = m_pListV->AddNewItem(normal,
                                              clicked,
                                              "TalentLayer::OnClickListItem",
                                              "",
                                              ccGREEN,
                                              kCCScrollMenuPriority);
        if(pItem)
        {
            UILabelTTF* label_name = UILabelTTF::create(name.c_str(), KJLinXin, 24);
            UILabelTTF* label_value = UILabelTTF::create(value.c_str(), KJLinXin, 24);
            pItem->getAnimationNode()->addChild(label_name,10);
            pItem->getAnimationNode()->addChild(label_value,10);
            
            label_name->setPosition(ccp(label_name->getContentSize().width/2-normal->getContentSize().width/2, 0));
            label_value->setPosition(ccp(normal->getContentSize().width/2 , 0));
        }
    }
    
    setPictureAndWord(m_instanceId);
}

void AutoOnHook::setupIconButtons()
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
					pIcon->SetTappedHandler(this,menu_selector(AutoOnHook::onItemTapped),menu_selector(AutoOnHook::onTapCancel));
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

void AutoOnHook::setItemIcon(int item_num, int item_id, unsigned int item_index)
{
	//CCAssert(position != 0,"Error AutoOnHook position");
    if(m_pLayer && m_pLayer->isVisible())
    {
        IconButton* button = m_pIconButtonList[item_index];
        button->setTag(item_index);
        m_VecIDs.push_back(item_id);
        
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

void AutoOnHook::showSpriteParticleEffect(CCNode* parent,unsigned int id,CCPoint pt)
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

void AutoOnHook::setIconAllGet(int number_diamand, int number_coin, int number_exploit, int number_exp)
{
    UIPicture* allget = m_pLayer->FindChildObjectByName<UIPicture>("autohook_icon_allget");
    UILabel* diamand = m_pLayer->FindChildObjectByName<UILabel>("auto_number_diamond");
    UILabel* coin = m_pLayer->FindChildObjectByName<UILabel>("auto_number_coin");
    UILabel* exploit = m_pLayer->FindChildObjectByName<UILabel>("auto_number_exploit");
    UILabel* exp = m_pLayer->FindChildObjectByName<UILabel>("auto_number_exp");
    
    UILabel* autotxt = m_pLayer->FindChildObjectByName<UILabel>("auto_text_get");
    std::string msg = "";
    msg = Localizatioin::getLocalization("M_AUTOFIGHT_GETREWARD");
    autotxt->setString(msg.c_str());
    
    m_num_diamand += number_diamand;
    char buf[10];
    sprintf(buf, "%d\n", m_num_diamand);
    diamand->setString(buf);
    
    m_num_coin += number_coin;
    sprintf(buf, "%d\n", m_num_coin);
    coin->setString(buf);
    
    m_num_exploit += number_exploit;
    sprintf(buf, "%d\n", m_num_exploit);
    exploit->setString(buf);
    
    m_num_exp += number_exp;
    sprintf(buf, "%d\n", m_num_exp);
    exp->setString(buf);
    
    autotxt->setVisible(true);
    allget->setVisible(true);
    diamand->setVisible(true);
    coin->setVisible(true);
    exploit->setVisible(true);
    exp->setVisible(true);
}

void AutoOnHook::setIconAllGet(bool visible)
{
    UIPicture* allget = m_pLayer->FindChildObjectByName<UIPicture>("autohook_icon_allget");
    UILabel* diamand = m_pLayer->FindChildObjectByName<UILabel>("auto_number_diamond");
    UILabel* coin = m_pLayer->FindChildObjectByName<UILabel>("auto_number_coin");
    UILabel* exploit = m_pLayer->FindChildObjectByName<UILabel>("auto_number_exploit");
    UILabel* exp = m_pLayer->FindChildObjectByName<UILabel>("auto_number_exp");
    UILabel* autotxt = m_pLayer->FindChildObjectByName<UILabel>("auto_text_get");
    
    allget->setVisible(visible);
    diamand->setVisible(visible);
    coin->setVisible(visible);
    exploit->setVisible(visible);
    exp->setVisible(visible);
    autotxt->setVisible(visible);
    
}

void AutoOnHook::setPictureAndWord(int instance_id)
{
    if(m_instanceId <= 0)
        return;
    
	std::string instanceConfigName = LuaTinkerManager::Get()->getLuaConfig<const char *>("InstanceList", "instances", m_instanceId, "RaidName");
    UIPicture* icon_instance = m_pLayer->FindChildObjectByName<UIPicture>("autohook_frame_instance");
    
    //icon_instance->setVisible(false);
    
    UILabel* text_instance = m_pLayer->FindChildObjectByName<UILabel>("autohook_text_instance");
    UILabel* text_chapter = m_pLayer->FindChildObjectByName<UILabel>("autohook_chapter");
    
    text_instance->setString(instanceConfigName.c_str());
    text_chapter->setVisible(false);
    
    ASprite *as = AspriteManager::getInstance()->getAsprite(KUI_BIN);
	instanceConfigName = LuaTinkerManager::Get()->getLuaConfig<const char *>("InstanceList", "instances", instance_id, "Icon");
	std::transform(instanceConfigName.begin(), instanceConfigName.end(), instanceConfigName.begin(), towupper);
	instanceConfigName = std::string("map_ui_system_icon_FRAME_") + instanceConfigName;
    
    CCPoint pt;
    int instanceIconId = getResourceIDByName(instanceConfigName.c_str());
	ASprite *as1 = AspriteManager::getInstance()->getAsprite(KICON_BIN);
	CCSprite *pIcon = as1->getSpriteFromFrame_Middle(instanceIconId, 0, pt);
    CCNode*node = icon_instance->getCurrentNode();
    node->removeChildByTag(100);
    node->addChild(pIcon,10,100);
    pIcon->setPosition(ccp(node->getContentSize().width/2, node->getContentSize().height/2));
}

void AutoOnHook::update(float dt)
{
    if((m_musicTime == 0 && m_cnt == 0) || m_musicTime < 0)
    {
        unscheduleUpdate();
        //setUpCDTime("00:00");
        setUpCDText("");
        showStartBtn(true);
        const char* start_txt = Localizatioin::getLocalization("M_AUTOFIGHT_COMPLETE");
        m_pStartLabel->setString(start_txt);
        return;
    }
    
    m_dt += dt;
    if(m_dt >= 1.0f)
    {
        m_dt = 0;
        m_cnt -= 1;
        if(m_cnt <= 0)
        {
            m_cnt = 59;
            m_musicTime -= 1;
            
            if((m_musicTime == 0 && m_cnt == 0) || m_musicTime < 0)
            {
                unscheduleUpdate();
                //setUpCDTime("00:00");
                setUpCDText("");
                showStartBtn(true);
                const char* start_txt = Localizatioin::getLocalization("M_AUTOFIGHT_COMPLETE");
                m_pStartLabel->setString(start_txt);
                return;
            }
        }
        
        std::string strtime = "";
        char buf[20] = "";
        sprintf(buf, "%d", m_musicTime);
        
        strtime += buf;
        strtime += ":";
        
        char buf2[10];
        sprintf(buf2, "%d", m_cnt);
        
        if(m_cnt < 10)
        {
            strtime += "0";
            strtime += buf2;
        }
        else
            strtime += buf2;
        
        setUpCDTime(strtime.c_str());
    }
}

void AutoOnHook::setUpCDTime(const char* strtime)
{
    string strval = strtime;
    m_pLabelCDNumber->setString(strval.c_str());
}

void AutoOnHook::setUpCDText(const char* strtxt)
{
    //m_pLabelCDText->setString(strtxt);
    std::string strover = Localizatioin::getLocalization("M_AUTOFIGHT_OVER");
    m_pLabelCDNumber->setString(strover.c_str());
}

void AutoOnHook::setDiamandTxt()
{
    UILabel* confirmLabel = m_pUseDiamand->FindChildObjectByName<UILabel>("useDia_confirm");
    UILabel* cancleLabel = m_pUseDiamand->FindChildObjectByName<UILabel>("useDia_cancel");
    UILabel* tileLabel = m_pUseDiamand->FindChildObjectByName<UILabel>("useDia_tile");
    
    std::string msg = "";
    msg = Localizatioin::getLocalization("M_CONFIRM");
    confirmLabel->setString(msg.c_str());
    
    msg = Localizatioin::getLocalization("M_CANCEL");
    cancleLabel->setString(msg.c_str());
    
    msg = Localizatioin::getLocalization("M_SKIP_CD");
    tileLabel->setString(msg.c_str());
    
    confirmLabel->setColor(ccWHITE);
    cancleLabel->setColor(ccWHITE);
    tileLabel->setColor(ccWHITE);
}

void AutoOnHook::convertSecToMinute(int time)
{
    m_musicTime = time /60;
    m_cnt = time % 60;
    return;
}

void AutoOnHook::showStartBtn(bool visible)
{
    m_pStartBtn->setVisible(visible);
    m_pStartLabel->setVisible(visible);
    
    m_pSpeedUpBtn->setVisible(!visible);
    m_pSpeedupLabel->setVisible(!visible);
    
    m_pStopBtn->setVisible(!visible);
    m_pStopLabel->setVisible(!visible);
}

void AutoOnHook::clearItemBtn()
{
    m_VecIDs.clear();
    for(int i=0; i<m_pIconButtonList.size(); i++)
    {
        IconButton* button = m_pIconButtonList[i];
        button->SetNormalIcon(NULL);
        
    }
}

void AutoOnHook::closeLayerCallBack( void )
{
	m_bCloseLayerCallBack = true;
	OnClose(NULL);
	m_bCloseLayerCallBack = false;
}

void AutoOnHook::OnSpeedUpHook(CCObject* sender)
{
    CCLog("onSpeedUpHook\n");
    m_pUseDiamand->setVisible(true);
}

void AutoOnHook::OnStopHook(CCObject* sender)
{
    CCLog("onStopHook\n");
    PVPMessage::Get()->sendCSCancelAutoBattleReq();
    showStartBtn(true);
    processVisibleCD(false);
    m_pCloseBtn->setVisible(true);
    freshBag();
    
    //const char* start_txt = Localizatioin::getLocalization("M_AUTOFIGHT_COMPLETE");
    //m_pStartLabel->setString(start_txt);
    //m_bStopSel = true;
}

void AutoOnHook::OnStartAutoHook(CCObject* sender)
{
    if(m_VecIDs.size() > 0 || m_bStopSel)
    {
        freshBag();
    }
    
    else
    {
        PVPMessage::Get()->sendCSAutoBattleReq(m_instanceId, m_turnId);
        
        m_pStartBtn->setVisible(false);
        m_pStartLabel->setVisible(false);
        
        m_pSpeedUpBtn->setVisible(true);
        m_pSpeedupLabel->setVisible(true);
        
        m_pStopBtn->setVisible(true);
        m_pStopLabel->setVisible(true);
        
        m_pCloseBtn->setVisible(false);
        
        processVisibleCD(true);
    }
}

void AutoOnHook::onTapCancel(CCObject* sender)
{
    TipMgr::Get()->destroyTip();
}

void AutoOnHook::onItemTapped(CCObject* sender)
{
    if(m_VecIDs.size() <= 0)
        return;
    
    UIMenu* menu = dynamic_cast<UIMenu*>(sender);
	if(menu)
	{
		CCNode* parent = menu->getParent();
		IconButton* button = dynamic_cast<IconButton*>(parent);
		if(button)
		{
            int item_index = button->getTag();
            int item_id = m_VecIDs[item_index];
            ItemManager::Get()->showItemTipsById(item_id, menu->getTouchPoint());
		}
	}
}

void AutoOnHook::OnMasterClickListItem(CCObject* sender)
{
}

void AutoOnHook::OnClickTurn1(CCObject* sender)
{
    CCLog("OnClickTurn1\n");
    m_pTurnBtn1->getMenuItemSprite()->selected();
    m_pTurnBtn2->getMenuItemSprite()->unselected();
    m_pTurnBtn3->getMenuItemSprite()->unselected();
    this->m_turnId = 2;
}

void AutoOnHook::OnClickTurn2(CCObject* sender)
{
    CCLog("OnClickTurn2\n");
    m_pTurnBtn2->getMenuItemSprite()->selected();
    m_pTurnBtn1->getMenuItemSprite()->unselected();
    m_pTurnBtn3->getMenuItemSprite()->unselected();
    this->m_turnId = 4;
}

void AutoOnHook::OnClickTurn3(CCObject* sender)
{
    CCLog("OnClickTurn3\n");
    m_pTurnBtn3->getMenuItemSprite()->selected();
    m_pTurnBtn1->getMenuItemSprite()->unselected();
    m_pTurnBtn2->getMenuItemSprite()->unselected();
    this->m_turnId = 0;
}

void AutoOnHook::OnClose(CCObject *sender)
{
    unscheduleUpdate();
    UIManager *manager = UIManager::sharedManager();
	manager->RemoveUILayout("AutoOnHookUI");
	NotificationCenter::defaultCenter()->broadcast(GM_CLOSE_AUTOONHOOK, this);
    PVPMessage::Get()->sendCSCancelAutoBattleReq();    
}

void AutoOnHook::OnConfirm(CCObject *sender)
{
    int diamand_id = 10400;
    PVPMessage::Get()->sendSpeedUpReq(diamand_id);
    m_pUseDiamand->setVisible(false);
}

void AutoOnHook::OnCancle(CCObject *sender)
{
    m_pUseDiamand->setVisible(false);
}

void AutoOnHook::freshBag()
{
    clearItemBtn();
    const char* start_txt = Localizatioin::getLocalization("M_AUTOFIGHT_START");
    m_pStartLabel->setString(start_txt);
    processVisibleCD(false);
    //setIconAllGet(false);
    m_bStopSel = false;
    m_pCloseBtn->setVisible(true);
    
    this->m_num_diamand = 0;
    this->m_num_coin = 0;
    this->m_num_exploit = 0;
    this->m_num_exp = 0;
    setIconAllGet(0,0,0,0);
    
    TaskManager::getInstance()->RqsTaskFromServer();
}

void AutoOnHook::hideCloseBtn()
{
    m_pCloseBtn->setVisible(false);
}


