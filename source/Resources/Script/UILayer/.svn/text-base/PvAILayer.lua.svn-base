require("Script/MainMenuUILayer")
require("Script/CommonDefine")
require("Script/Language")

PvAILayer = {
	LayerInstance = nil,
	Layout = nil,
	otherPlayerId = {}
}

--本地函数
--更新挑战冷却时间
local function onUpdateCoolDownTime(remainTime)		
	local remainText = LanguageLocalization:GetLocalization("M_PVAI_COOLDOWNTIME")
	local remainStr = TimeManager:Get():secondsToString(remainTime)
	local coolDownLabel = PvAILayer.Layout:FindChildObjectByName("pvaiCoolDownTime").__UILabel__
	if	coolDownLabel ~= nil then
		if remainTime ~= 0 then
			coolDownLabel:setString(remainText..remainStr)
		else
			coolDownLabel:setString("")
		end
	end
end

--更新奖励获取时间
local function onUpdateRewardGetTime(remainTime)	
	local remainText = LanguageLocalization:GetLocalization("M_PVAI_GETREWARDTIME")
	local remainStr = TimeManager:Get():secondsToString(remainTime)
	local rewardGetLabel = PvAILayer.Layout:FindChildObjectByName("pvaiRewardGetTime").__UILabel__
	if	rewardGetLabel ~= nil then
		if remainTime ~= 0 then
			rewardGetLabel:setString(remainText..remainStr)
		else
			rewardGetLabel:setString(remainText..remainStr)
			--rewardGetLabel:setString("")
		end
	end
end

--关闭页面
local function closePvAILayer(obj)
	RemoveOneLayer(PvAILayer.LayerInstance)
	PvAILayer.LayerInstance:setVisible(false)
end

--销毁页面
local function destroyPvAILayer()
	if PvAILayer.LayerInstance ~= nil then		
		TXGUI.UIManager:sharedManager():removeUILayout("PvAILayout")
		CCTextureCache:sharedTextureCache():removeUnusedTextures()
		RemoveOneLayer(PvAILayer.LayerInstance)	
		PvAILayer:ResetValue()
		TimeManager:Get():stopTimer(TIMER_PVAI_COOLDOWN)
		TimeManager:Get():stopTimer(TIMER_PVAI_REWARD)
	end
end

--接收消息
local function onReceiveMessage(message)
	if message == GM_NETWORK_DISCONNCT then
		destroyPvAILayer()
	end
end

NotificationCenter:defaultCenter():registerScriptObserver(onReceiveMessage)	

--根据职业获取头像
function PvAIGetHeadIcon(character)
	
	local frameResTable =  {
		"map_ui_character_select_FRAME_CHARACTER_SELECT_SWORDSMAN",
		"map_ui_character_select_FRAME_CHARACTER_SELECT_SWORDSWOMAN",
		"map_ui_character_select_FRAME_CHARACTER_SELECT_WIZARDMAN",
		"map_ui_character_select_FRAME_CHARACTER_SELECT_WIZARDWOMAN",
		"map_ui_character_select_FRAME_CHARACTER_SELECT_ASSASINMAN",
		"map_ui_character_select_FRAME_CHARACTER_SELECT_ASSASINWOMAN",
		"map_ui_character_select_FRAME_CHARACTER_SELECT_HUNTERMAN",
		"map_ui_character_select_FRAME_CHARACTER_SELECT_HUNTERWOMAN",
	}

	return AspriteManager:getInstance():getOneFrame("UI/ui_character_select.bin", frameResTable[character])	 
end

local function onPressFightBtn(obj)
	print("FightBtn...."..obj)
	PvAIManager:Get():sendPvAIReq(obj)
	closePvAILayer(nil)
end

--PvAILayer  类函数
--重置
function PvAILayer:ResetValue()
	self.LayerInstance = nil
	self.Layout = nil
end


function PvAILayer:openPvAILayer()

	if	self.LayerInstance == nil then
		self:CreateLayer()
	end

	self.LayerInstance:setVisible(true)	
	self.LayerInstance:setScale(0)

	local arrayOfActions = CCArray:create()
	local scaleIn = CCScaleTo:create(0.1, 1.0)

	arrayOfActions:addObject(scaleIn)

	local sequence = CCSequence:create(arrayOfActions)

	self.LayerInstance:runAction(sequence)

	PushOneLayer(self.LayerInstance, "", "")
end


--创建页面
function PvAILayer:CreateLayer()
	self:ResetValue()
	self.LayerInstance = CCLayer:create()
	self.LayerInstance:setTag(G_PvAILayerTag)
	
	local uiLayout = TXGUI.UIManager:sharedManager():createUILayoutFromFile("UIplist/PVAIUI.plist",self.LayerInstance, "PvAILayout", true)
	self.Layout = uiLayout	

	local mainMenuNode = GetMainMenuLayerNode()
	mainMenuNode:addChild(self.LayerInstance)

	self:InitChallengeCoolDownTime(100)
	self:InitRewardGetTime(150)
	self:InitLayer()	
end

--初始化页面
function PvAILayer:InitLayer()
    --注册回调函数
	--关闭按钮
	local closeBtn = self.Layout:FindChildObjectByName("closeBtn").__UIButton__:getMenuItemSprite()
	closeBtn:registerScriptTapHandler(closePvAILayer)

	--挑战按钮
	local fightBtnTable = {}
	for	i=1, 5 do
		fightBtnTable[i] = self.Layout:FindChildObjectByName("pvaiFightBtn"..i).__UIButton__:getMenuItemSprite()
		fightBtnTable[i]:setTag(i)
		fightBtnTable[i]:registerScriptTapHandler(onPressFightBtn)
	end

	--初始化玩家头像
	local userHeadIconObj = self.Layout:FindChildObjectByName("iconCharacter")
	if userHeadIconObj ~= nil then
		local userHeadIcon = userHeadIconObj.__UIPicture__
		local userType = UserData:GetUserType()
		local userHeadIconRes = PvAIGetHeadIcon(userType)
		if userHeadIconRes ~= nil then
			userHeadIcon:setSprite(userHeadIconRes)
		end
	end

	--初始化对手列表头像
	for i=1, 5 do
		local iconObj = self.Layout:FindChildObjectByName(string.format("iconOther%d",i))
		if	iconObj ~= nil then
			local iconOther = iconObj.__UIPicture__
			if iconOther ~= nil then
				local gridOtherFrame = AspriteManager:getInstance():getOneFrame(KUI_BIN,"map_ui_FRAME_INSTANCE_GRID1")
				if gridOtherFrame ~= nil then 
					iconOther:setSprite(gridOtherFrame)
					local factor = TXGUI.UIManager:sharedManager():getScaleFactor()
					iconOther:setScale(0.4 * factor)
				end
			end		
		end
	end	
end

--初始化挑战冷却时间
function PvAILayer:InitChallengeCoolDownTime(seconds)
	local nowTime = TimeManager:Get():getCurServerTime()
	TimeManager:Get():registerLuaTimer(onUpdateCoolDownTime, TIMER_PVAI_COOLDOWN, nowTime + seconds)

	local remainStr = TimeManager:Get():secondsToString(seconds)

	local coolDownLabel = PvAILayer.Layout:FindChildObjectByName("pvaiCoolDownTime").__UILabel__
	if	coolDownLabel ~= nil then
		coolDownLabel:setString(remainStr)
	end
end

--初始化奖励获取时间
function PvAILayer:InitRewardGetTime(seconds)
	local nowTime = TimeManager:Get():getCurServerTime()
	TimeManager:Get():registerLuaTimer(onUpdateRewardGetTime, TIMER_PVAI_REWARD, nowTime + seconds)

	local remainStr = TimeManager:Get():secondsToString(seconds)

	local rewardGetLabel = PvAILayer.Layout:FindChildObjectByName("pvaiRewardGetTime").__UILabel__
	if	rewardGetLabel ~= nil then
		rewardGetLabel:setString(remainStr)
	end
end