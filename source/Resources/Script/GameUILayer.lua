--[[
@file:GameUILayer.lua
@description 
     Enterpoint of all the script project
keep all the configuration and some game logic here!-- enjoy yourself! , there is only one code here, just for test!
@author:
      jameshuang 
@date
      2013/2/21
--]]
require("Script/Skill/SkillSelectLayer")
require("Script/SpriteElfExplore/ElfExploreLayer")
require("Script/UILayer/enchaseUILayer")
require("Script/UILayer/PvAILayer")

local topLayout = TXGUI.UIManager:sharedManager():getUILayout("MainMenu");
switchButtonNode = topLayout:FindChildObjectByName("button_shrink").__UIButton__:getMenuItemSprite();
pvpButtonNode = topLayout:FindChildObjectByName("button_activity").__UIButton__:getMenuItemSprite();
skillUpgradeNode = topLayout:FindChildObjectByName("button_skillupgrade").__UIButton__:getMenuItemSprite();
elfExploerNode = topLayout:FindChildObjectByName("button_dailytask").__UIButton__:getMenuItemSprite();
communicateNode = topLayout:FindChildObjectByName("button_communicate").__UIButton__:getMenuItemSprite();
enchaseNode = topLayout:FindChildObjectByName("button_enchase").__UIButton__:getMenuItemSprite();

-- switch button message 
function onSwitchButtonClicked(pObj)
	CCLuaLog("onSwitchButtonClicked!");

end


-- pvp button clicked 
-- show the ppve layout
function onPvPButtonClicked(pObj)
	CCLuaLog("onPvPButtonClicked!");
	StopHeroMove()
	-- show ppve ui layout
end

--Note: skill panel enter
function onSkillUpgradeButtonClicked(pObj)
	print("function onSkillUpgradeButtonClicked(pObj)")
	GameAudioManager:sharedManager():playEffect(350001,false);
	StopHeroMove()
	SkillSelectLayer:CreateLayer(nil)
end

function onElfExploerButtonClicked(pObj)
	print("function onElfExploerButtonClicked(pObj)")
	GameAudioManager:sharedManager():playEffect(350001,false);
	StopHeroMove()
	ElfExploerLayer:CreateLayer(nil)
end

local function showNoFuctionAlert()
	local rstString = LanguageLocalization:GetLocalization("M_FUNCTION_NOTOPEN");
    GameApi:showMessage(rstString);
end;

function onDailyTaskButtonClicked(pObj)
	showNoFuctionAlert();
end

function onCommunicateButtonClicked(pObj)
	--showNoFuctionAlert();
	GameAudioManager:sharedManager():playEffect(350001,false);
	StopHeroMove()
	PvAIManager:Get():sendPvAIInfoReq()
	PvAILayer:openPvAILayer()
end

function onEnchaseButtonClicked(pObj)
	--local parentNode = TXGUI.UIManager:sharedManager():getUIDefaultRoot()
	--if parentNode ~= nil then
		--TXGUI.UIManager:sharedManager():createUILayoutFromFile("UIplist/enchaseUI.plist",parentNode, "enchaseUI", true);
	--end
	CCLuaLog("onEnchaseButtonClicked()!");
	EnchaseUILayer:CreateLayer()
end

switchButtonNode:registerScriptTapHandler(onSwitchButtonClicked);
pvpButtonNode:registerScriptTapHandler(onPvPButtonClicked);
skillUpgradeNode:registerScriptTapHandler(onSkillUpgradeButtonClicked);
elfExploerNode:registerScriptTapHandler(onElfExploerButtonClicked);
communicateNode:registerScriptTapHandler(onCommunicateButtonClicked);
enchaseNode:registerScriptTapHandler(onEnchaseButtonClicked);
CCLuaLog("LoadGameUILayer.lua  Loaded!");
