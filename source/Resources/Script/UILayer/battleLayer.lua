require("Script/UILayer/PlayerInfo") 
require("Script/GameConfig/characterString")
CCLuaLog("load battleLayer.lua");

local battleLayout = TXGUI.UIManager:sharedManager():getUILayout("BattleUI");
local backBtn = battleLayout:FindChildObjectByName("backToTown").__UIButton__:getMenuItemSprite();

local playerInfo = {};

local heroInfo;
local function initHeroInfo()
	heroInfo = LuaPlayerInfo:createPlayerInfo();
	heroInfo:setPlayerId(UserData:getUserId());
	heroInfo:setCurrentHp(UserData:getHeroHp());
	heroInfo:setTotalHp(UserData:getHeroTotalHp());
	local heroHpBar = battleLayout:FindChildObjectByName("hpBar").__UIPicture__:getCurrentNode();
	if heroHpBar ~= nil then
		local ptx,pty = heroHpBar:getPosition();
		heroHpBar:setAnchorPoint(ccp(0,0.5));
		local scale =  TXGUI.UIManager:sharedManager():getScaleFactor();
		heroHpBar:setPosition(ccpSub(ccp(ptx,pty),ccp(scale * heroHpBar:getContentSize().width * 0.5,0)));
		heroInfo:setHpBar(heroHpBar);
	end
end

local function updateHeroHp()
	local layout = TXGUI.UIManager:sharedManager():getUILayout("BattleUI");
	if (layout ~= nil) and (heroInfo ~= nil) then
		heroInfo:playHpAni(UserData:getHeroHp());
	end
end

initHeroInfo();

local function getTableSize(aTable)
	local count = 0;
	for k,v in pairs(aTable) do
 	   count = count + 1;
 	end
 	return count;
end

local function setTeammeatStatus(player)
	CCLuaLog("**************************************************************************");
	if (battleLayout ~= nil)then
		local playerNum = getTableSize(playerInfo);
		local container = battleLayout:FindChildObjectByName(string.format("TeammeatContainer%d",playerNum)).__UIContainer__;
		if container ~= nil then
			container:setVisible(true);
		end
		if player.type ~= nil then
			local headIconName = getCharacterField(player.type,"HeadPicture");			
	
			--local playerStatus = battleLayout:FindChildObjectByName(string.format("teammeatHpFrame%d",playerNum)).__UIPicture__;
		---	if playerStatus ~= nil then
		--		playerStatus:setVisible(true);
		--	end			
			local headIcon = battleLayout:FindChildObjectByName(string.format("teammeatHead%d",playerNum)).__UIPicture__;
			if headIcon ~= nil then
				--headIcon:setVisible(true);
				local headFrame = AspriteManager:getInstance():getOneFrame(KUI_BIN,"map_ui_FRAME_ICON_HEADSHOTINBATTLE");
				if headFrame ~= nil then 
					headIcon:setSprite(headFrame);
					headIcon:setScale(0.8);
					local playerIcon = AspriteManager:getInstance():getOneFrame("UI/ui_system_icon.bin",headIconName);
					if playerIcon ~= nil then 
						playerIcon:setScale(0.6);
						headIcon:addExtraPic(playerIcon,ccp(0,0));
					end
				end
			end			
			local hpBar = battleLayout:FindChildObjectByName(string.format("teammeatHpBar%d",playerNum)).__UIPicture__:getCurrentNode();
			if hpBar ~= nil then
				local ptx,pty = hpBar:getPosition();
				local point = hpBar:getAnchorPoint();
				if point.x == 0.5 then
					hpBar:setAnchorPoint(ccp(0,0.5));
					local scale =  TXGUI.UIManager:sharedManager():getScaleFactor();
					hpBar:setPosition(ccpSub(ccp(ptx,pty),ccp(scale * hpBar:getContentSize().width * 0.5,0)));
				end
			end
			
			local nameLabel = battleLayout:FindChildObjectByName(string.format("teammeatNameLabel%d",playerNum)).__UILabel__;
			if (nameLabel ~= nil) and (player.name ~= nil) then
	--			nameLabel:setVisible(true);
				nameLabel:setString(player.name);
			end			
			
		--	winSize = CCDirector:sharedDirector():getVisibleSize(); 
		--	CCLuaLog(string.format("winSize: %f,%f,%d",winSize.width,winSize.height,playerNum));
		--	node:setPosition(ccp(0,winSize.height * (0.5) * scale - playerNum * heightPos * 1.3- heightPos * 2));
			player:setHpBar(hpBar);
			player:setUINode(container:getCurrentNode());
		end
	end
end 


function showTeammeatsInfo()
	
end

function onBackTown(obj)
	CCLuaLog(" battleLayer.lua : onBackTown");
	--CCDirector:sharedDirector():getScheduler():unscheduleScriptEntry(battleLayerUpdateFun);
end

backBtn:registerScriptTapHandler(onBackTown);

local function unRegisterBattleHandlers()
	CCLuaLog("battleLayer.lua : unRegisterBattleHandlers");
	CCDirector:sharedDirector():getScheduler():unscheduleScriptEntry(battleLayerUpdateFun);
	--backBtn:unregisterScriptTapHandler();
end

local sum = 0;
function updateTeammeat(dt)
	local uiLayer = TXGUI.UIManager:sharedManager():getUILayout("BattleUI");
	if uiLayer == nil then
		unRegisterBattleHandlers();
	else
		updateHeroHp();	
		local isPPVE = LevelManager:sShareInstance():isCurrentPPVELevel();
		if isPPVE then
			local players = GameApi:getOtherPlayerInfo();
			--CCLuaLog(string.format("players.count = %d",table.getn(players)));
			for index,value in pairs(players) do
				if value ~= nil then
					if playerInfo[value.uid] == nil then
						local player = LuaPlayerInfo:createPlayerInfo();
						player:setPlayerType(value.type);
						player:setPlayerName(value.name);
						player:setPlayerId(value.uid);
						player:setCurrentHp(value.currentHp);
						player:setTotalHp(value.totalHp);
						playerInfo[player.id] = player;
						setTeammeatStatus(player);
					else
						local otherPlayer = playerInfo[value.uid];
						--CCLuaLog("playerId: %d,hp = %d / %d ",otherPlayer:getPlayerId(),otherPlayer:getCurrentHp(),otherPlayer:getTotalHp());
						if otherPlayer:getCurrentHp() ~= value.currentHp then		
							otherPlayer:playHpAni(value.currentHp);
						end
					end
				end
			end
		
			for index,value in pairs(playerInfo) do
				local isRelease = true;
				for k,v in pairs(players) do
					if v.uid == value:getPlayerId() then
						isRelease = false;
						break;
					end
				end
				if isRelease then
					local layout = TXGUI.UIManager:sharedManager():getUILayout("BattleUI");
					local node = value:getUINode();
					if (layout ~= nil) and (node ~= nil) then
						node:setVisible(false);
						playerInfo[index] = nil;
					end
				end
			end
		end
	end
	
	--CCLuaLog(string.format("battleLayer.lua update: %f, %f",dt,sum));
end

battleLayerUpdateFun = CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(updateTeammeat, 1.0, false);

