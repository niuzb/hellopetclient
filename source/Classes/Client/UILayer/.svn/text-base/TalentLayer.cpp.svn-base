//
//  TalentLayer.cpp
//  HelloLua
//
//  Created by rickycheng  on 13-5-13.
//
//
#include "PVPMessage.h"
#include "TalentLayer.h"
#include "GameResourceManager.h"
#include "Localization.h"
#include "GameFontManager.h"
#include "resources.h"
#include "GMessage.h"
#include "particle_manager.h"
#include "UserData.h"
#include "GameAudioManager.h"
#include "MainMenuLayer.h"
#include "GameManager.h"

using namespace TXGUI;

TalentLayer::TalentLayer()
{
    this->m_pLayer = NULL;
    this->m_pList = NULL;
    this->m_pUseDiamand = NULL;
    this->m_plevelupBtn = NULL;
    this->m_bTimeLevelUp = true;
    
    this->m_goldCoinNum = 0;
    this->m_diamondNum = 0;
    this->m_gongxiNum = 0;
    this->m_talent_cnt = 0;
    
    this->m_bCloseLayerCallBack = false;
    
    this->m_dt = 0;
    this->m_cnt = 60;
    this->m_musicTime = 0;
    
    this->m_curTalentID = 0;
    this->m_curLevel = 0;
    
    this->m_eachplus = 0;
}

TalentLayer::~TalentLayer()
{
    UIManager::sharedManager()->RemoveUILayout("TalentUI");
	UIManager::sharedManager()->RemoveUILayout("UseDiamand");
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void TalentLayer::setTouchEnabled(bool value)
{
	CCLayer::setTouchEnabled(value);
}

bool TalentLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
    
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    ///show ppve panel
	UIManager *manager = UIManager::sharedManager();
	m_pLayer = manager->CreateUILayoutFromFile("UIplist/TalentUI.plist", this, "TalentUI", true);
    
    m_pUseDiamand = manager->CreateUILayoutFromFile("UIplist/UseDiamand.plist", this, "UseDiamand", true);
    manager->RegisterMenuHandler("UseDiamand","TalentLayer::OnConfirm",	menu_selector(TalentLayer::OnConfirm), this);
    manager->RegisterMenuHandler("UseDiamand","TalentLayer::OnCancle",	menu_selector(TalentLayer::OnCancle), this);
    m_pUseDiamand->setVisible(false);
    setDiamandTxt();
    
    manager->RegisterMenuHandler("TalentUI","TalentLayer::OnClose",	menu_selector(TalentLayer::OnClose), this);
	manager->RegisterMenuHandler("TalentUI","TalentLayer::OnClickListItem",	menu_selector(TalentLayer::OnClickListItem), this);
    manager->RegisterMenuHandler("TalentUI","TalentLayer::OnLevelUpTalent",	menu_selector(TalentLayer::OnLevelUpTalent), this);
    
	m_pList = m_pLayer->FindChildObjectByName<UIScrollList>("talent_characterScrollList");
    //m_pList->setTouchEnabled(false);
    
    m_plevelupBtn = m_pLayer->FindChildObjectByName<UIButton>("talent_updateBtn");
    std::string strname = getLocationTxt(101);
    UILabelTTF *label = UILabelTTF::create(strname.c_str(), KJLinXin, 30);
    m_plevelupBtn->getAnimationNode()->addChild(label,100, 100);
    
    showTalentDetail(false);
    PVPMessage::Get()->getTalentList();
    
    setupCoinAndDiamand();
	return true;
}

void TalentLayer::setupCoinAndDiamand()
{
    int goldnum,diamandnum;
    UILabel* gold_label = m_pLayer->FindChildObjectByName<UILabel>("talent_gold_number");
    UILabel* diamand_label = m_pLayer->FindChildObjectByName<UILabel>("talent_diamand_number");
    USERINFO info =  UserData::GetUserInfo();
    goldnum = info.m_diamond;
    diamandnum = info.m_player_exploit;
    
    char buf[10];
    sprintf(buf, "%d", goldnum);
    gold_label->setString(buf);
    if(strlen(buf) >= 7)
    {
        std::string str = buf;
        str += "k";
        gold_label->setString(str.c_str());
    }
    
    sprintf(buf, "%d", diamandnum);
    diamand_label->setString(buf);
}

void TalentLayer::convertSecToMinute(int time)
{
    m_musicTime = time /60;
    m_cnt = time % 60;
    return;
}

void TalentLayer::updateLevel(int level, int plus, int exploit)
{
    ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("UI/ui2.bin");
    pAsprite->setImageName(0, "UI/ui.png");
    UILabel* levelLabel = m_pLayer->FindChildObjectByName<UILabel>("talent_level_sel");
    UILabel* plusLabel = m_pLayer->FindChildObjectByName<UILabel>("talent_add_sel");
    UILabel* needHonorLabel = m_pLayer->FindChildObjectByName<UILabel>("talent_number_needhonor");
    
    char buf[10];
    std::string strname = "";
    sprintf(buf, "%d\n", level);
    strname = "Lv";
    strname += buf;
    levelLabel->setString(strname.c_str());
    levelLabel->setColor(ccWHITE);
    
    sprintf(buf, "%d", plus);
    std::string strname2 = "+";
    strname2 += buf;
    plusLabel->setString(strname2.c_str());
    
    sprintf(buf, "%d", exploit);
    needHonorLabel->setString(buf);
    
    int i=0;
    for(i=0; i<m_TalentQueries.size(); i++)
    {
        if(m_curTalentID == m_TalentQueries[i].talent_id)
        {
            CCLabelTTF* leveltable = m_LevelLabels[i];
            leveltable->setString(strname.c_str());
            
            CCLabelTTF* plusLabel = m_PlusLabels[i];
            plusLabel->setString(strname2.c_str());
        }
    }
    
    UILabel* nextlevel2 = m_pLayer->FindChildObjectByName<UILabel>("talent_nextlevel2_sel");
    sprintf(buf,"%d\n", level+1);
    strname = "Lv";
    strname += buf;
    nextlevel2->setString(strname.c_str());
    
    UIPicture *Icon = m_pLayer->FindChildObjectByName<UIPicture>("talent_icon_sel");
    CCNode* node = Icon->getCurrentNode();
    showSpriteParticleEffect(node,474014,ccp(node->getContentSize().width * 0.5,node->getContentSize().height * 0.5));
    GameAudioManager::sharedManager()->playEffect(350006,false);
    
    setupCoinAndDiamand();
}

void TalentLayer::startCD(int timeout)
{
    if(timeout != 0)
    {
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
        
        UILabelTTF *label = UILabelTTF::create(strname.c_str(), KJLinXin, 30);
        m_plevelupBtn->getAnimationNode()->removeChildByTag(100);
        m_plevelupBtn->getAnimationNode()->addChild(label, 100, 100);
        
        unschedule(schedule_selector(TalentLayer::updateCDTime));
        schedule(schedule_selector(TalentLayer::updateCDTime),0);
        m_bTimeLevelUp = false;
    }
    else
    {
        unschedule(schedule_selector(TalentLayer::updateCDTime));
        std::string strname = getLocationTxt(101);
        UILabelTTF *label = UILabelTTF::create(strname.c_str(), KJLinXin, 30);
        m_plevelupBtn->getAnimationNode()->removeChildByTag(100);
        m_plevelupBtn->getAnimationNode()->addChild(label,100, 100);
        m_bTimeLevelUp = true;
    }
}

void TalentLayer::addNewTalent(int talent_id, int level_id, int plus)
{
    ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("UI/ui2.bin");
    pAsprite->setImageName(0, "UI/ui.png");
    
    CCPoint pt = CCPointZero;
    CCSprite* normal = pAsprite->getSpriteFromFrame_Middle(map_ui2_FRAME_GENIUS_BUTTON_TALENT1 ,0, pt);
    CCSprite* clicked= pAsprite->getSpriteFromFrame_Middle(map_ui2_FRAME_GENIUS_BUTTON_TALENT1_SELECTED, 0, pt);
    
    UIButton* pItem = m_pList->AddNewItem(normal,
                                          clicked,
                                          "TalentLayer::OnClickListItem",
                                          "",
                                          ccGREEN,
                                          kCCScrollMenuPriority);
    pItem->setTag(talent_id);
    m_UIButtonlist.push_back(pItem);
    
    if(m_talent_cnt == 0)
        pItem->getMenuItemSprite()->selected();
    
    if(pItem)
    {
        m_talent_cnt += 1;
        int frame = map_ui_system_icon_FRAME_ICON_GENIUS_PHYATTACK;
        if(m_talent_cnt == 1)
            frame = map_ui_system_icon_FRAME_ICON_GENIUS_PHYATTACK;
        else if(m_talent_cnt == 2)
            frame = map_ui_system_icon_FRAME_ICON_GENIUS_MAGEATTACK;
        else if(m_talent_cnt == 3)
            frame = map_ui_system_icon_FRAME_ICON_GENIUS_SKILLATTACK;
        else if(m_talent_cnt == 4)
            frame = map_ui_system_icon_FRAME_ICON_GENIUS_PHYDEFENCE;
        else if(m_talent_cnt == 5)
            frame = map_ui_system_icon_FRAME_ICON_GENIUS_MAGEDEFENCE;
        else if(m_talent_cnt == 6)
            frame = map_ui_system_icon_FRAME_ICON_GENIUS_SKILLDEFENCE;
        else
            frame = map_ui_system_icon_FRAME_ICON_GENIUS_LIFE;
        
        CCSprite* icon_frame = pAsprite->getSpriteFromFrame_Middle(map_ui2_FRAME_GENIUS_ICONGRID_TALENT1 ,0, pt);
        
        ASprite* pAsprite2 = AspriteManager::getInstance()->getAsprite("UI/ui_system_icon.bin");
        pAsprite2->setImageName(0, "UI/ui_system_icon.pvr.ccz");
        CCSprite* icon = pAsprite2->getSpriteFromFrame_Middle(frame ,0, pt);
        icon_frame->addChild(icon,-1);
        icon->setPosition(ccp(icon_frame->getContentSize().width/2, icon_frame->getContentSize().height/2));
        
        std::string strname = getLocationTxt(m_talent_cnt);
        CCLabelTTF* name = CCLabelTTF::create(strname.c_str(), KJLinXin, 26);
        name->setColor(ccWHITE);
        
        char buf[10];
        sprintf(buf, "%d\n", level_id);
        strname = "Lv";
        strname += buf;
        CCLabelTTF* level = CCLabelTTF::create(strname.c_str(), KJLinXin, 17);
        level->setColor(ccWHITE);
        m_LevelLabels.push_back(level);
        
        sprintf(buf, "%d\n", plus);
        strname = "+";
        strname += buf;
        CCLabelTTF* addlabel = CCLabelTTF::create(strname.c_str(), KJLinXin, 14);
        addlabel->setColor(ccWHITE);
        m_PlusLabels.push_back(addlabel);
        
        pItem->getAnimationNode()->addChild(icon_frame,10);
        pItem->getAnimationNode()->addChild(name,10);
        pItem->getAnimationNode()->addChild(level,10);
        pItem->getAnimationNode()->addChild(addlabel,10);
        
        icon_frame->setPosition(ccp(icon_frame->getContentSize().width/2 - normal->getContentSize().width/2, 0));
        name->setPosition(ccp(0, normal->getContentSize().height/2-name->getContentSize().height-5));
        level->setPosition(ccp(0, -normal->getContentSize().height/2 + level->getContentSize().height+5));
        addlabel->setPosition(ccp(normal->getContentSize().width/2 - addlabel->getContentSize().width/2-20, -addlabel->getContentSize().height/2));
        
        TalentQuery qu;
        qu.talent_id = talent_id;
        qu.level = level_id;
        m_TalentQueries.push_back(qu);
    }
}

void TalentLayer::showOneTalent(int index, int talent_id, int headIconId, int roleLevel, int addNumber, int attackLevel, int levelNeed, int GongXi)
{
    ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("UI/ui2.bin");
    pAsprite->setImageName(0, "UI/ui.png");
    
    UIPicture *frame = m_pLayer->FindChildObjectByName<UIPicture>("talent_frame_sel");
    UILabel* name = m_pLayer->FindChildObjectByName<UILabel>("talent_name_sel");
    UILabel* level = m_pLayer->FindChildObjectByName<UILabel>("talent_level_sel");

    
    UILabel* add = m_pLayer->FindChildObjectByName<UILabel>("talent_add_sel");
    UIPicture *Icon = m_pLayer->FindChildObjectByName<UIPicture>("talent_icon_sel");
    
    UILabel* attr = m_pLayer->FindChildObjectByName<UILabel>("talent_attri_sel");
    UILabel* effect = m_pLayer->FindChildObjectByName<UILabel>("talent_attri_effect");

    UILabel* nextlevel = m_pLayer->FindChildObjectByName<UILabel>("talent_nextlevel_sel");
    UILabel* rolelevelTxt = m_pLayer->FindChildObjectByName<UILabel>("talent_roleLevel");

    UILabel* nextlevel2 = m_pLayer->FindChildObjectByName<UILabel>("talent_nextlevel2_sel");
    
    UILabel* updatedate = m_pLayer->FindChildObjectByName<UILabel>("talent_updatedate_sel");
    UILabel* number = m_pLayer->FindChildObjectByName<UILabel>("talent_number_needhonor");
    
    frame->setVisible(true);
    name->setVisible(true);
    level->setVisible(true);
    effect->setVisible(true);
    add->setVisible(true);
    Icon->setVisible(true);
    
    attr->setVisible(true);
    nextlevel->setVisible(true);
    rolelevelTxt->setVisible(true);
    nextlevel2->setVisible(true);
    
    updatedate->setVisible(true);
    number->setVisible(true);
    
    CCPoint pt;
    CCNode* node = Icon->getCurrentNode();
    node->removeChildByTag(10, true);
    
    ASprite* pAsprite2 = AspriteManager::getInstance()->getAsprite("UI/ui_system_icon.bin");
    pAsprite2->setImageName(0, "UI/ui_system_icon.pvr.ccz");
    int frameId = map_ui_system_icon_FRAME_ICON_GENIUS_PHYATTACK;
    if(index == 0)
        frameId = map_ui_system_icon_FRAME_ICON_GENIUS_PHYATTACK;
    else if(index == 1)
        frameId = map_ui_system_icon_FRAME_ICON_GENIUS_MAGEATTACK;
    else if(index == 2)
        frameId = map_ui_system_icon_FRAME_ICON_GENIUS_SKILLATTACK;
    else if(index == 3)
        frameId = map_ui_system_icon_FRAME_ICON_GENIUS_PHYDEFENCE;
    else if(index == 4)
        frameId = map_ui_system_icon_FRAME_ICON_GENIUS_MAGEDEFENCE;
    else if(index == 5)
        frameId = map_ui_system_icon_FRAME_ICON_GENIUS_SKILLDEFENCE;
    else
        frameId = map_ui_system_icon_FRAME_ICON_GENIUS_LIFE;
    
    CCSprite* icon = pAsprite2->getSpriteFromFrame_Middle(frameId ,0, pt);
    node->addChild(icon,-1,10);
    icon->setPosition(ccp(node->getContentSize().width/2, node->getContentSize().height/2));
    
    std::string strname = "";
    char buf[10];
    
    index += 1;
    strname = getLocationTxt(index);
    name->setString(strname.c_str());
    name->setColor(ccWHITE);
    
    sprintf(buf, "%d\n", roleLevel);
    strname = "Lv";
    strname += buf;
    level->setString(strname.c_str());
    level->setColor(ccWHITE);
    
    strname = "";
    strname += "+";
    sprintf(buf, "%d\n", addNumber);
    strname += buf;
    add->setString(strname.c_str());
    add->setColor(ccWHITE);
    
    sprintf(buf, "%d\n", attackLevel);
    strname = getLocationTxt(index*10);
    strname += "+";
    strname += buf;
    attr->setString(strname.c_str());
    attr->setColor(ccWHITE);
    
    strname = Localizatioin::getLocalization("M_UPGRADE_EFFECT");
    effect->setString(strname.c_str());
    effect->setColor(ccORANGE);
    
    strname = getLocationTxt(100);
    strname += ":";
    nextlevel->setString(strname.c_str());
    nextlevel->setColor(ccORANGE);
    
    strname = Localizatioin::getLocalization("M_ROLELEVEL");
    rolelevelTxt->setString(strname.c_str());
    rolelevelTxt->setColor(ccWHITE);
    
    sprintf(buf,"%d\n", levelNeed+1);
    strname = "Lv";
    strname += buf;
    nextlevel2->setString(strname.c_str());
    nextlevel2->setColor(ccRED);

    int selflevel = UserData::GetUserLevel();
    if(selflevel >= levelNeed+1)
        nextlevel2->setColor(ccWHITE);
    
    strname = Localizatioin::getLocalization("M_UPGRADECOST");
    strname += ":";
    updatedate->setString(strname.c_str());
    updatedate->setColor(ccORANGE);
    
    sprintf(buf, "%d\n", GongXi);
    number->setString(buf);
    number->setColor(ccWHITE);
}

void TalentLayer::updateCDTime(float dt)
{
    if((m_musicTime == 0 && m_cnt == 0) || m_musicTime < 0)
    {
        unscheduleUpdate();
        std::string strname = getLocationTxt(101);
        UILabelTTF *label = UILabelTTF::create(strname.c_str(), KJLinXin, 30);
        m_plevelupBtn->getAnimationNode()->removeChildByTag(100);
        m_plevelupBtn->getAnimationNode()->addChild(label, 100, 100);
        m_bTimeLevelUp = true;
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
                std::string strname = getLocationTxt(101);
                UILabelTTF *label = UILabelTTF::create(strname.c_str(), KJLinXin, 30);
                m_plevelupBtn->getAnimationNode()->removeChildByTag(100);
                m_plevelupBtn->getAnimationNode()->addChild(label, 100, 100);
                m_bTimeLevelUp = true;
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

//点击天赋
void TalentLayer::OnClickListItem(CCObject* sender)
{
    CCLog("TalentLayer OnClickListItem\n");
    CCNode* node = (CCNode*)sender;
    if(node)
    {
        UIMenu* menu = dynamic_cast<UIMenu*>(node->getParent());
        if(menu)
        {
            UIControlBase* base = menu->getControlNode();
            int tag = base->getTag();
            
            for(int i=0; i<m_TalentQueries.size(); i++)
            {
                TalentQuery qu = m_TalentQueries[i];
                if(qu.talent_id == tag)
                {
                    PVPMessage::Get()->getOneTalent(qu.talent_id, qu.level);
                    setcurTalentID(qu.talent_id);
                    setcurLevel(qu.level);
                    
                    UIButton* pbtn = m_UIButtonlist[i];
                    pbtn->getMenuItemSprite()->selected();
                    
                    for(int j=0; j<m_UIButtonlist.size(); j++)
                    {
                        if(j != i)
                            m_UIButtonlist[j]->getMenuItemSprite()->unselected();
                    }
                    
                    break;
                }
            }
        }
    }
}

//关闭天赋系统
void TalentLayer::OnClose(CCObject *sender)
{
    CCLog("TalentLayer onClose\n");
    unschedule(schedule_selector(TalentLayer::updateCDTime));
    UIManager *manager = UIManager::sharedManager();
	manager->RemoveUILayout("TalentUI");
    
    MainMenuLayer * mLayer = GameManager::Get()->GetSceneLayer()->getMainMenuLayer();
    //mLayer->HideTalentLayer(false);
	ShowChatBar(true,  -1);
	NotificationCenter::defaultCenter()->broadcast(GM_CLOSE_TALENTLAYER, this);
}

//升级天赋
void TalentLayer::OnLevelUpTalent(CCObject* sender)
{
    CCLog("TalentLayer OnLevelUpTalent\n");
    if(m_bTimeLevelUp)
    {
        PVPMessage::Get()->levelUpTalent(m_curTalentID);
    }
    else
    {
        m_pUseDiamand->setVisible(true);
        UILabel* tileLabel = m_pUseDiamand->FindChildObjectByName<UILabel>("useDia_num");
    }
}

void TalentLayer::setDiamandTxt()
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

void TalentLayer::OnConfirm(CCObject *sender)
{
    CCLog("TalentLayer OnConfirm\n");
    m_pUseDiamand->setVisible(false);
    PVPMessage::Get()->sendSpeedUpReq(10100);
}

void TalentLayer::OnCancle(CCObject *sender)
{
    CCLog("TalentLayer OnCancle\n");
    m_pUseDiamand->setVisible(false);
}

void TalentLayer::clearScrollist()
{
	if (m_pList)
	{
		m_pList->clearChildrens();
        m_TalentQueries.clear();
	}
}

void TalentLayer::setUpCDTime(const char* strtime)
{
    UILabelTTF *label = UILabelTTF::create(strtime, KJLinXin, 30);
    m_plevelupBtn->getAnimationNode()->removeChildByTag(100);
    m_plevelupBtn->getAnimationNode()->addChild(label,100,100);
}

std::string TalentLayer::getLocationTxt(int location_id)
{
    std::string msg = "";
    switch (location_id) {
            
        case 1:
            msg = Localizatioin::getLocalization("M_ATTRIBUTE_PHYATTACK");
            break;
            
        case 2:
            msg = Localizatioin::getLocalization("M_ATTRIBUTE_MAGATTACK");
            break;
            
        case 3:
            msg = Localizatioin::getLocalization("M_ATTRIBUTE_SKIATTACK");
            break;
            
        case 4:
            msg = Localizatioin::getLocalization("M_ATTRIBUTE_PHYDEFENCE");
            break;
            
        case 5:
            msg = Localizatioin::getLocalization("M_ATTRIBUTE_MAGDEFENCE");
            break;
            
        case 6:
            msg = Localizatioin::getLocalization("M_ATTRIBUTE_SKIDEFENCE");
            break;
            
        case 7:
            msg = Localizatioin::getLocalization("M_ATTRIBUTE_LIFE");
            break;
            
        case 10:
            msg = Localizatioin::getLocalization("M_GENIUS_PHYATTACK");
            break;

        case 20:
            msg = Localizatioin::getLocalization("M_GENIUS_MAGATTACK");
            break;
        
        case 30:
            msg = Localizatioin::getLocalization("M_GENIUS_SKIATTACK");
            break;
        
        case 40:
            msg = Localizatioin::getLocalization("M_GENIUS_PHYDEFENCE");
            break;

        case 50:
            msg = Localizatioin::getLocalization("M_GENIUS_MAGDEFENCE");
            break;
            
        case 60:
            msg = Localizatioin::getLocalization("M_GENIUS_SKIDEFENCE");
            break;
            
        case 70:
            msg = Localizatioin::getLocalization("M_GENIUS_LIFE");
            break;
            
        case 100:
            msg = Localizatioin::getLocalization("M_UPGRADENEED");
            break;
            
        case 101:
            msg = Localizatioin::getLocalization("M_GENIUS_UPGRADE");
            break;
            
        default:
            break;
    }
    return msg;
}

void TalentLayer::closeLayerCallBack( void )
{
	m_bCloseLayerCallBack = true;
	OnClose(NULL);
	m_bCloseLayerCallBack = false;
}

void TalentLayer::showOne(unsigned int talent_id,
                          unsigned int level,
                          
                          unsigned int plus_add,
                          unsigned int next_exploit,
                          unsigned int next_time,
                          
                          unsigned int diff_physical_attack,
                          unsigned int diff_magic_attack,
                          unsigned int diff_skill_attack,
                                                    unsigned int diff_physical_defence,
                          unsigned int diff_magic_defence,
                          unsigned int diff_skill_defence,
                          
                          unsigned int diff_hp)
{

    int i = 0;
    for(i = 0; i < m_TalentQueries.size(); i++)
    {
        if(m_TalentQueries[i].talent_id == talent_id)
        {
            
            if(i==0)
                showOneTalent(i, talent_id, -1, level, plus_add, diff_physical_attack, level, next_exploit);
            else if(i==1)
                showOneTalent(i, talent_id, -1, level, plus_add, diff_magic_attack, level, next_exploit);
            else if(i==2)
                showOneTalent(i, talent_id, -1, level, plus_add, diff_skill_attack, level, next_exploit);
            else if(i==3)
                showOneTalent(i, talent_id, -1, level, plus_add, diff_physical_defence, level, next_exploit);
            else if(i==4)
                showOneTalent(i, talent_id, -1, level, plus_add, diff_magic_defence, level, next_exploit);
            else if(i==5)
                showOneTalent(i, talent_id, -1, level, plus_add, diff_skill_defence, level, next_exploit);
            else if(i==6)
                showOneTalent(i, talent_id, -1, level, plus_add, diff_hp, level, next_exploit);
            return;
        }
    }
}

void TalentLayer::showTalentDetail(bool visible)
{
	ASprite* pAsprite = AspriteManager::getInstance()->getAsprite("UI/ui2.bin");
	pAsprite->setImageName(0, "UI/ui.png");

	UIPicture *frame = m_pLayer->FindChildObjectByName<UIPicture>("talent_frame_sel");
	UILabel* name = m_pLayer->FindChildObjectByName<UILabel>("talent_name_sel");
	UILabel* level = m_pLayer->FindChildObjectByName<UILabel>("talent_level_sel");

	UILabel* add = m_pLayer->FindChildObjectByName<UILabel>("talent_add_sel");
	UIPicture *Icon = m_pLayer->FindChildObjectByName<UIPicture>("talent_icon_sel");

	UILabel* attr = m_pLayer->FindChildObjectByName<UILabel>("talent_attri_sel");
    UILabel* effect = m_pLayer->FindChildObjectByName<UILabel>("talent_attri_effect");
	UILabel* nextlevel = m_pLayer->FindChildObjectByName<UILabel>("talent_nextlevel_sel");
	UILabel* nextlevel2 = m_pLayer->FindChildObjectByName<UILabel>("talent_nextlevel2_sel");

	UILabel* updatedate = m_pLayer->FindChildObjectByName<UILabel>("talent_updatedate_sel");
	UILabel* number = m_pLayer->FindChildObjectByName<UILabel>("talent_number_needhonor");

	frame->setVisible(visible);
	name->setVisible(visible);
	level->setVisible(visible);
    effect->setVisible(visible);
	add->setVisible(visible);
	Icon->setVisible(visible);

	attr->setVisible(visible);
	nextlevel->setVisible(visible);
	nextlevel2->setVisible(visible);

	updatedate->setVisible(visible);
	number->setVisible(visible);
}

void TalentLayer::showSpriteParticleEffect(CCNode* parent,unsigned int id,CCPoint pt)
{
    std::string particleName = "particle_effect_upgradesuccess";
    CCNode* particle = ParticleManagerX::sharedManager()->getParticles_uieffect(particleName.c_str());
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
