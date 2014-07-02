#include "OnlineNetworkManager.h"
#include "PvAIManager.h"
#include "GameManager.h"
#include "SkillDispMgr.h"
#include "LevelManager.h"
#include "BaseAttackState.h"
#include "LevelLayer.h"
#include "TXGUIHeader.h"
#include "UserData.h"
#include "Localization.h"
#include "LuaTinkerManager.h"
#include "GameFontManager.h"
#include "MainMenuLayer.h"
#include "TimeManager.h"
#include "UIManager.h"

#define AUTO_ATTACK_CD 0.2f

PvAIManager::PvAIManager()
	:aiPlayer(NULL)
	,aiAutoAttack(false)
	,aiAutoAttackCDTime(0.0f)
	,aiPlayerId(0)
{
}

PvAIManager::~PvAIManager()
{
}

void PvAIManager::Update(float dt)
{
	if (aiAutoAttackCDTime < AUTO_ATTACK_CD)
	{
		aiAutoAttackCDTime += dt;
	}
	else if (aiAutoAttack)
	{
		moveToHero();
		aiAutoAttackCDTime = 0.0f;
	}
}

void PvAIManager::sendPvAIReq(int buttonIndex)
{
	this->aiPlayerId = aiPlayerVec[buttonIndex - 1].id;
	OnlineNetworkManager::sShareInstance()->sendPvAIReq(aiPlayerId);
	OnlineNetworkManager::sShareInstance()->sendGetUserSkillReqMessage(aiPlayerId);
	if (GameManager::Get()->GetSceneLayer())
    {
        GameManager::Get()->GetSceneLayer()->showLoading(true);
    }
}

void PvAIManager::sendPvAIInfoReq()
{
	OnlineNetworkManager::sShareInstance()->sendPvAIInfoReq();
}

void PvAIManager::setAIAutoAttack(bool autoAttack)
{	
	this->aiAutoAttack = autoAttack;
	if (this->aiAutoAttack)
	{
		LevelLayer * layer = LevelManager::sShareInstance()->getCurrentLevelLayer();
		if (layer && aiPlayerId)
		{
			aiPlayer = layer->getPlayer(aiPlayerId);
			aiPlayer->SetMoveType(MOVE_BY_MOUSE);
			//初始化技能vector
			SkillDispMgr * skillMgr = SkillDispMgr::Get();
			vector<int> skillTmp = skills;
			skills.clear();
			for (size_t i = 0; i < skillTmp.size(); i++)
			{
				const SKILL_INFO * info = skillMgr->GetSkillInfo(skillTmp[i]);
				//buff技能不加入
				if (!info->bBuff && info->partID == 1)
				{
					skills.push_back(skillTmp[i]);
				}
			}
		}
	}
	else
	{
		aiPlayer->moveToTarget(aiPlayer->getPosition(), aiPlayer->getPosition());
	}
}

void PvAIManager::moveToHero()
{
	SpriteSeer * hero = GameManager::Get()->getHero();

	SkillDispMgr * skillMgr = SkillDispMgr::Get();

	int skillId = getBestSkill();
	if (skillId)
	{
		for (size_t i = 0; i < skills.size(); i++)
		{
			if (skillId == skills[i])
			{
				skills.erase(skills.begin() + i);
				skills.push_back(skillId);
				break;
			}
		}

		if (skillMgr->GetSkillInfo(skillId)->type != ToNormalAttack)
		{
			CCPoint vec = ccpSub(hero->getPosition(), aiPlayer->getPosition());
			vec = ccpNormalize(vec);
			aiPlayer->setDirection(vec);
			if(!aiPlayer->DoSkillAttack(skillId))
			{
				if (hero)
				{
					if( aiPlayer->canMove )
						aiPlayer->moveToTarget(hero->getPosition(), aiPlayer->getPosition());
				}
			}
		}
		else
		{
			CCPoint vec = ccpSub(hero->getPosition(), aiPlayer->getPosition());
			vec = ccpNormalize(vec);
			aiPlayer->setDirection(vec);
			aiPlayer->DoNormalAttack();
		}
	}
	else if (hero)
	{
		CCPoint pt = hero->getPosition();
		CCPoint pixPos = aiPlayer->getPosition();
		if (LevelManager::sShareInstance()->isPointReachable(pt))
		{
			aiPlayer->moveToTarget(pt, pixPos);
		}
		else
		{
			CCPoint vec = ccpNormalize(ccpSub(pt, pixPos));
			do
			{
				pt = ccpSub(pt, vec);
			} while (!LevelManager::sShareInstance()->isPointReachable(pt));
			aiPlayer->moveToTarget(pt, pixPos);
		}
	}

	return;
}

int PvAIManager::getBestSkill()
{
	int skillId = 0;
	int normalAttackId = 0;
	bool canDoSkill = false;

	SpriteSeer * hero = GameManager::Get()->getHero();
	if (!hero)
	{
		return skillId;
	}

	//循环遍历确定是否有技能正在释放
	SkillDispMgr * skillMgr = SkillDispMgr::Get();

	bool doingSkill = false;
	for (size_t i = 0; i < skills.size(); i++)
	{
		const SKILL_INFO * info = skillMgr->GetSkillInfo(skills[i]);
	
		if (aiPlayer->m_pStateMachine->CheckStateRuning(info->type))
		{
			doingSkill = true;
			break;
		}
	}

	//从头遍历可以释放的技能
	for (size_t i = 0; i < skills.size(); i++)
	{
		const SKILL_INFO * info = skillMgr->GetSkillInfo(skills[i]);
		
		//找出普通攻击id
		if (info->type == ToNormalAttack)
		{
			normalAttackId = skills[i];
			continue;
		}

		//未释放技能时才检测技能cd及距离
		if (!doingSkill)
		{

			if (skillMgr->IsCD(aiPlayerId, skills[i]))
			{
				continue;
			}		

			if (ccpDistance(aiPlayer->getPosition(), hero->getPosition()) < info->longDistanceAttackRange)
			{
				canDoSkill = true;
				skillId = skills[i];
			
				break;
			}
		}		
	}

	//普通攻击
	if (!canDoSkill && normalAttackId)
	{
		const SKILL_INFO * info = skillMgr->GetSkillInfo(normalAttackId);		
		if (ccpDistance(aiPlayer->getPosition(), hero->getPosition()) < info->longDistanceAttackRange)
		{
			skillId = normalAttackId;
		}
	}


	return skillId;
}

void PvAIManager::refreshPvAILayer()
{
	UIManager *manager = UIManager::sharedManager();
	pvaiLayout = manager->getUILayout("PvAILayout");

	if (pvaiLayout)
	{
		//玩家昵称
		UILabel *heroNameLabel = pvaiLayout->FindChildObjectByName<UILabel>("pvaiMcName");
		if (heroNameLabel)
		{
			string heroName = UserData::getUserName();
			heroNameLabel->setString(heroName.c_str());
		}	

		//玩家排名
		UILabel *heroRankLabel = pvaiLayout->FindChildObjectByName<UILabel>("pvaiMcRank");
		if (heroRankLabel)
		{
			stringstream heroRankStream;
			heroRankStream << heroRank;
			string heroRankStr = heroRankStream.str();
			string heroRankText = Localizatioin::getLocalization("M_PVAI_RANK");

			heroRankText += heroRankStr;
			heroRankLabel->setString(heroRankText.c_str());
		}

		//玩家声望
		UILabel *heroReputationLabel = pvaiLayout->FindChildObjectByName<UILabel>("pvaiMcReputation");
		if (heroReputationLabel)
		{
			int heroReputation = UserData::GetUserInfo().m_reputation;

			stringstream heroReputationStream;
			heroReputationStream << heroReputation;
			string heroReputationStr = heroReputationStream.str();
			string heroReputationText = Localizatioin::getLocalization("M_PVAI_REPUTATION");

			heroReputationText += heroReputationStr;
			heroReputationLabel->setString(heroReputationText.c_str());
		}

		////剩余挑战次数
		//UILabel *lastTimeLabel = pvaiLayout->FindChildObjectByName<UILabel>("pvaiTodayLastTime");
		//if (lastTimeLabel)
		//{
		//	stringstream herolastTimeStream;
		//	herolastTimeStream << basicInfo.remainCount;
		//	string herolastTimeStr = herolastTimeStream.str();
		//	lastTimeLabel->setString(herolastTimeStr.c_str());
		//}

		////奖励金币数
		//UILabel *rewardCoinLabel = pvaiLayout->FindChildObjectByName<UILabel>("pvaiRewardCoin");
		//if (rewardCoinLabel)
		//{
		//	stringstream herolastTimeStream;
		//	herolastTimeStream << basicInfo.rewardCoin;
		//	string herolastTimeStr = herolastTimeStream.str();
		//	rewardCoinLabel->setString(herolastTimeStr.c_str());
		//}

		////奖励声望
		//UILabel *rewardReputationLabel = pvaiLayout->FindChildObjectByName<UILabel>("pvaiRewardReputation");
		//if (rewardReputationLabel)
		//{
		//	stringstream herolastTimeStream;
		//	herolastTimeStream << basicInfo.rewardReputation;
		//	string herolastTimeStr = herolastTimeStream.str();
		//	rewardReputationLabel->setString(herolastTimeStr.c_str());
		//}

		////奖励领取时间
		//TimeManager::Get()->renewTimer(TIMER_PVAI_REWARD, TimeManager::Get()->getCurServerTime() + basicInfo.rewardGetTime);

		////冷却时间
		//TimeManager::Get()->renewTimer(TIMER_PVAI_COOLDOWN, TimeManager::Get()->getCurServerTime() + basicInfo.coolDownTime);

		//挑战玩家列表
		int playerCount = aiPlayerVec.size();
		int minPlayerCount = min(playerCount, 5);
		for (int i = minPlayerCount; i < 5; i++)
		{
			stringstream iconOtherStream;
			iconOtherStream << "iconOther" << i+1;
			string iconOtherStr = iconOtherStream.str();
			UIPicture *iconOtherPic= pvaiLayout->FindChildObjectByName<UIPicture>(iconOtherStr);
			iconOtherPic->setVisible(false);

			iconOtherStream.str("");
			iconOtherStream << "gridOther" << i+1;
			iconOtherStr = iconOtherStream.str();
			iconOtherPic= pvaiLayout->FindChildObjectByName<UIPicture>(iconOtherStr);
			iconOtherPic->setVisible(false);

			iconOtherStream.str("");
			iconOtherStream << "pvaiOtherPlayerName" << i+1;
			iconOtherStr = iconOtherStream.str();
			UILabel * iconOtherLabel= pvaiLayout->FindChildObjectByName<UILabel>(iconOtherStr);
			iconOtherLabel->setVisible(false);

			iconOtherStream.str("");
			iconOtherStream << "pvaiOtherPlayerLevel" << i+1;
			iconOtherStr = iconOtherStream.str();
			iconOtherLabel= pvaiLayout->FindChildObjectByName<UILabel>(iconOtherStr);
			iconOtherLabel->setVisible(false);

			iconOtherStream.str("");
			iconOtherStream << "pvaiOtherPlayerRank" << i+1;
			iconOtherStr = iconOtherStream.str();
			iconOtherLabel= pvaiLayout->FindChildObjectByName<UILabel>(iconOtherStr);
			iconOtherLabel->setVisible(false);

			iconOtherStream.str("");
			iconOtherStream << "pvaiFightBtn" << i+1;
			iconOtherStr = iconOtherStream.str();
			UIButton * iconOtherBtn= pvaiLayout->FindChildObjectByName<UIButton>(iconOtherStr);
			iconOtherBtn->setVisible(false);

			iconOtherStream.str("");
			iconOtherStream << "pvaiFightText" << i+1;
			iconOtherStr = iconOtherStream.str();
			iconOtherLabel= pvaiLayout->FindChildObjectByName<UILabel>(iconOtherStr);
			iconOtherLabel->setVisible(false);
		}
		for (int i = 0; i < minPlayerCount; i++)
		{
			//头像
			stringstream iconOtherStream;
			iconOtherStream << "iconOther" << i+1;
			string iconOtherStr = iconOtherStream.str();
			UIPicture *iconOtherPic= pvaiLayout->FindChildObjectByName<UIPicture>(iconOtherStr);

			int playerType = aiPlayerVec[i].type;
			const char * playerIconName = LuaTinkerManager::Get()->getLuaConfig<const char *>("characterString", "Characters", playerType, "HeadPicture");
			int idx = getResourceIDByName(playerIconName);
			CCPoint pt;
			ASprite *as = AspriteManager::getInstance()->getAsprite(KICON_BIN); 
			CCSprite * headPic = as->getSpriteFromFrame_Middle( idx, 0, pt);
			if(headPic)
			{
				iconOtherPic->addExtraPic(headPic);
			}	

			//昵称
			stringstream otherPlayerNameStream;
			otherPlayerNameStream << "pvaiOtherPlayerName" << i+1;
			string otherPlayerNameStr = otherPlayerNameStream.str();
			UILabel *otherPlayerNameLabel = pvaiLayout->FindChildObjectByName<UILabel>(otherPlayerNameStr);

			otherPlayerNameLabel->setString(aiPlayerVec[i].name.c_str());

			//等级
			stringstream otherPlayerLevelStream;
			otherPlayerLevelStream << "pvaiOtherPlayerLevel" << i+1;
			string otherPlayerLevelStr = otherPlayerLevelStream.str();
			UILabel *otherPlayerLevelLabel = pvaiLayout->FindChildObjectByName<UILabel>(otherPlayerLevelStr);

			int playerLevel = aiPlayerVec[i].level;
			stringstream levelStream;
			levelStream << "Lv" << playerLevel;
			string levelStr = levelStream.str();

			otherPlayerLevelLabel->setString(levelStr.c_str());

			//排名
			stringstream otherPlayerRankStream;
			otherPlayerRankStream << "pvaiOtherPlayerRank" << i+1;
			string otherPlayerRankStr = otherPlayerRankStream.str();
			UILabel *otherPlayerRankLabel = pvaiLayout->FindChildObjectByName<UILabel>(otherPlayerRankStr);

			int playerRank = aiPlayerVec[i].rank;
			string rankText = Localizatioin::getLocalization("M_PVAI_RANK2");
			stringstream rankStream;
			rankStream << rankText << playerRank;
			string rankStr = rankStream.str();

			otherPlayerRankLabel->setString(rankStr.c_str());
		}

		//最近日志列表
		float fontSize = GameFontManager::smallFontSize();
		int logCount = aiLogInfoVec.size();
		int minLogCount = min(logCount, 4);
		//隐藏多余项目
		for (int i = minLogCount; i < 4; i++)
		{
			stringstream attackTextStream;
			attackTextStream << "pvaiChallenge" << i+1;
			string attackTextStr = attackTextStream.str();
			UILabel *attackOrgLabel = pvaiLayout->FindChildObjectByName<UILabel>(attackTextStr);
			attackOrgLabel->setVisible(false);

			stringstream resultStream;
			resultStream << "pvaiChallengeResult" << i+1;
			string resultStr = resultStream.str();
			UILabel *resultLabel = pvaiLayout->FindChildObjectByName<UILabel>(resultStr);
			resultLabel->setVisible(false);
		}

		for (int i = 0; i < minLogCount; i++)
		{
			float factor = UIManager::sharedManager()->getScaleFactor();
			stringstream attackTextStream;
			attackTextStream << "pvaiChallenge" << i+1;
			string attackTextStr = attackTextStream.str();
			UILabel *attackOrgLabel = pvaiLayout->FindChildObjectByName<UILabel>(attackTextStr);
			UIContainer * container = pvaiLayout->FindChildObjectByName<UIContainer>("pvaiLayerContainer");
			attackOrgLabel->setVisible(false);
			CCPoint orgPos = attackOrgLabel->getPosition();
			CCPoint orgLeftPos = ccp(orgPos.x - attackOrgLabel->getLabelTTF()->getContentSize().width * factor / 2, orgPos.y);
			
			//挑战方向
			if (aiLogInfoVec[i].direct)
			{
				//主动攻击
				string attackText = Localizatioin::getLocalization("M_PVAI_FIGHT1");
				string attackName = aiLogInfoVec[i].name;
				UILabelTTF * attackTextLabel = UILabelTTF::create(attackText.c_str(), KJLinXin, fontSize * factor, CCSizeZero,kCCTextAlignmentLeft,kCCVerticalTextAlignmentBottom);
				UILabelTTF * attackNameLabel = UILabelTTF::create(attackName.c_str(), KJLinXin, fontSize * factor, CCSizeZero,kCCTextAlignmentLeft,kCCVerticalTextAlignmentBottom);				

				attackTextLabel->setPosition(ccp(orgLeftPos.x + attackTextLabel->getContentSize().width / 2, orgLeftPos.y));
				attackNameLabel->setPosition(ccp(orgLeftPos.x + attackTextLabel->getContentSize().width + attackNameLabel->getContentSize().width/ 2, orgLeftPos.y));

				UILabel * aTextLabel = new UILabel(attackTextLabel, container->getCurrentNode());
				UILabel * aNameLabel = new UILabel(attackNameLabel, container->getCurrentNode());
				aNameLabel->setColor(KAILogNameColor);
			}
			else
			{
				//被攻击
				string defenceName = aiLogInfoVec[i].name;
				string defenceText = Localizatioin::getLocalization("M_PVAI_FIGHT2");
				UILabelTTF * defenceTextLabel = UILabelTTF::create(defenceText.c_str(), KJLinXin, fontSize, CCSizeZero,kCCTextAlignmentLeft,kCCVerticalTextAlignmentBottom);
				UILabelTTF * defenceNameLabel = UILabelTTF::create(defenceName.c_str(), KJLinXin, fontSize, CCSizeZero,kCCTextAlignmentLeft,kCCVerticalTextAlignmentBottom);

				defenceNameLabel->setPosition(ccp(orgLeftPos.x + defenceNameLabel->getContentSize().width / 2, orgLeftPos.y));
				defenceTextLabel->setPosition(ccp(orgLeftPos.x + defenceNameLabel->getContentSize().width + defenceTextLabel->getContentSize().width / 2, orgLeftPos.y));

				UILabel * aTextLabel = new UILabel(defenceTextLabel, container->getCurrentNode());
				UILabel * aNameLabel = new UILabel(defenceNameLabel, container->getCurrentNode());
				aNameLabel->setColor(KAILogNameColor);
			}

			//挑战结果
			stringstream resultStream;
			resultStream << "pvaiChallengeResult" << i+1;
			string resultStr = resultStream.str();
			UILabel *resultLabel = pvaiLayout->FindChildObjectByName<UILabel>(resultStr);

			if (aiLogInfoVec[i].win == aiLogInfoVec[i].direct)
			{
				string resultText = Localizatioin::getLocalization("M_PVAI_WIN");
				resultLabel->setString(resultText.c_str());
				resultLabel->setColor(ccYELLOW);
			}
			else
			{
				string resultText = Localizatioin::getLocalization("M_PVAI_LOST");
				resultLabel->setString(resultText.c_str());
				resultLabel->setColor(ccRED);
			}
		}
	}
}