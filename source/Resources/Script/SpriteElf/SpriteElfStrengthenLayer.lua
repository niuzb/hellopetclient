require("Script/CommonDefine")
require("Script/MainMenuUILayer")

CCSpriteElfStrengthenLayer = {
	["SelectItemIndex"] = 0,
	["LayerInstance"] = nil,
	["Layout"] = nil,
	["AwarkContainer"] = nil,
	["SaveContainer"] = nil,
	Items = {},
	ListBtns = {},
	iconContentLabel = nil,
	diamondContentLabel = nil,
	ConsumeItemNums = {
		0,
		0,
		0,
		0
	},
	SelectAwakeType = 0,

}

function SetConsumeItemNumInfo(num_1,num_2,num_3,num_4)
	CCSpriteElfStrengthenLayer.ConsumeItemNums[1] = num_1
	CCSpriteElfStrengthenLayer.ConsumeItemNums[2] = num_2
	CCSpriteElfStrengthenLayer.ConsumeItemNums[3] = num_3
	CCSpriteElfStrengthenLayer.ConsumeItemNums[4] = num_4
end

function GlobalCreateElfStengthenLayer(parentLayer)
	CCSpriteElfStrengthenLayer:CreateElfStengthenLayer(parentLayer)
end

function GlobalCloseLayer()
	TXGUI.UIManager:sharedManager():removeUILayout("spriteElfStrengthenLayer");
	CCTextureCache:sharedTextureCache():removeUnusedTextures();
	
	CCSpriteElfStrengthenLayer:ClearData()
end

function CCSpriteElfStrengthenLayer:GetHeroForce()
	return UserData:GetUserInfo().courage
end

function CCSpriteElfStrengthenLayer:GetHeroIntelligence()
	return UserData:GetUserInfo().charm
end

function CCSpriteElfStrengthenLayer:GetHeroSkill()
	return UserData:GetUserInfo().trick
end

function CCSpriteElfStrengthenLayer:GetMaxForce()
	local sumPotential = GetTotalPotential()
	return (sumPotential + self:GetHeroForce())
end

function CCSpriteElfStrengthenLayer:GetMaxIntelligence()
	local sumPotential = GetTotalPotential()
	return (sumPotential + self:GetHeroIntelligence())
end

function CCSpriteElfStrengthenLayer:GetMaxSkill()
	local sumPotential = GetTotalPotential()
	return (sumPotential + self:GetHeroSkill())
end

local function closeLayerCallBack(message)
	if message == GM_LUA_LAYER_CLOSE then
		if nil ~= CCSpriteElfStrengthenLayer.LayerInstance then
			if G_CurLayerInstance ~= CCSpriteElfStrengthenLayer.LayerInstance then
				ElfStrengthCloseBtnClick(nil)
			end
		end
	end
end

function CCSpriteElfStrengthenLayer:CreateElfStengthenLayer(parentLayer)
	if nil ~= self.LayerInstance then
		return 
	end

	if parentLayer == nil then
		self.LayerInstance = CCLayer:create()
	else
		self.LayerInstance = parentLayer
	end
	
	local uiLayout = TXGUI.UIManager:sharedManager():createUILayoutFromFile("UIplist/SpriteElfStrengthenPanel.plist",self.LayerInstance, "spriteElfStrengthenLayer", true);
	self.Layout = uiLayout
	
	if parentLayer == nil then
		local mainMenuNode = GetMainMenuLayerNode()
		mainMenuNode:addChild(self.LayerInstance)
	end
	
	local awarkContainer = uiLayout:FindChildObjectByName("awarkContainer").__UIContainer__;
	local saveContainer = uiLayout:FindChildObjectByName("saveContainer").__UIContainer__;
	self.AwarkContainer = awarkContainer
	self.SaveContainer = saveContainer
	
	self:ShowMaxPotentialOnTile()
	self:InitElfStrengthenLayer()

	local elfCount = table.getn(G_LuaElfDataTable);
	if 0 == elfCount then
		self:HideDownLayerContainer()
	else
		self:ShowDownLayerContainer(false)
	end	

	self:ShowHeroCourageValue()
	self:ShowHeroCharmValue()
	self:ShowHeroTrickValue()
	self:ShowHeroDeltaCourageValue("")
	self:ShowHeroDeltaCharmValue("")
	self:ShowHeroDeltaTrickValue("")
	
	PushOneLayer(self.LayerInstance,"","")
end

function CCSpriteElfStrengthenLayer:ShowDownLayerContainer(bShowSaveContainer)
	if bShowSaveContainer then
		self.AwarkContainer:setVisible(false)
		self.SaveContainer:setVisible(true)
	else
		self.AwarkContainer:setVisible(true)
		self.SaveContainer:setVisible(false)
		
		self:ShowAwarkListDetailInfo();
		self:ShowAwakeOneListItem(1)
	end
end

function CCSpriteElfStrengthenLayer:HideDownLayerContainer()
	self.AwarkContainer:setVisible(false)
	self.SaveContainer:setVisible(false)
end

function CCSpriteElfStrengthenLayer:ClearData()
	self.SelectItemIndex = 0
	self.LayerInstance = nil
	self.Layout = nil
	self.AwarkContainer = nil
	self.SaveContainer = nil
	self.Items = {};
	self.ListBtns = {};
	self.iconContentLabel = nil
	self.diamondContentLabel = nil

end

function ElfStrengthCloseBtnClick(pObj)
	if CCSpriteElfStrengthenLayer.LayerInstance ~= nil then
		TXGUI.UIManager:sharedManager():removeUILayout("spriteElfStrengthenLayer");
		CCTextureCache:sharedTextureCache():removeUnusedTextures();
		RemoveOneLayer(CCSpriteElfStrengthenLayer.LayerInstance)	
		CCSpriteElfStrengthenLayer:ClearData()
	end
end

function AwakeListOneItemClick(pOjb)
	--print("AwakeListOneItemClick " .. pOjb)
	local index = pOjb
	CCSpriteElfStrengthenLayer:ShowAwakeOneListItem(index)
end

function CCSpriteElfStrengthenLayer:InitElfStrengthenLayer()
	--print("CCSpriteElfStrengthenLayer:InitElfStrengthenLayer")
	local layout = self.Layout
	if nil ~= layout then
		local closeBtn = layout:FindChildObjectByName("closeBtn").__UIButton__:getMenuItemSprite();
		closeBtn:registerScriptTapHandler(ElfStrengthCloseBtnClick);
		
		local awakeBtn = layout:FindChildObjectByName("awarkBtn").__UIButton__:getMenuItemSprite();
		awakeBtn:registerScriptTapHandler(ElfStrengthAwakeButtonClick);
		
		local saveBtn = layout:FindChildObjectByName("saveBtn").__UIButton__:getMenuItemSprite();
		saveBtn:registerScriptTapHandler(ElfStrengthSaveBtnClick);
		
		local cancelBtn = layout:FindChildObjectByName("cancelBtn").__UIButton__:getMenuItemSprite();
		cancelBtn:registerScriptTapHandler(ElfStrengthCancelBtnClick);
		
		for index=1,4,1 do 
			local itemName = "trainSelectIcon" .. index
			local item = layout:FindChildObjectByName(itemName).__UIPicture__;
			local count = table.getn(self.Items)
			self.Items[count+1] = item
		end
		
		for index=1,4,1 do 
			local itemName = "trainItemBtn" .. index
			local item = layout:FindChildObjectByName(itemName).__UIButton__:getMenuItemSprite();
			item:registerScriptTapHandler(AwakeListOneItemClick);
			item:setTag(index)
			local count = table.getn(self.ListBtns)
			self.ListBtns[count+1] = item
		end

		self.iconContentLabel = self.Layout:FindChildObjectByName("MoneyLabel").__UILabel__
		self.diamondContentLabel = self.Layout:FindChildObjectByName("diamondLabel").__UILabel__
		local money = UserData:GetUserInfo().m_gold
		local moneyContent = MainMenuLayer:GetNumByFormat(money)
		self.iconContentLabel:setString("" .. moneyContent)
		local diamond = UserData:GetUserInfo().m_diamond
		local diamondContent = MainMenuLayer:GetNumByFormat(diamond)
		self.diamondContentLabel:setString("" .. diamondContent)
		
	end
end

--Note: 显示潜能数值
function CCSpriteElfStrengthenLayer:DisplayStrengthenDataPanelInfo(courage,charm,trick)
	if nil == self.Layout then
		return
	end
	local uiLayout = self.Layout
	local numPowerNowLable = uiLayout:FindChildObjectByName("trainNumPowerNowLabel").__UILabel__;
	numPowerNowLable:setString("" .. self:GetHeroForce())
	local numPowerMaxLable = uiLayout:FindChildObjectByName("trainNumPowerMaxLabel").__UILabel__;
	if 0 == courage or nil == courage then
		numPowerMaxLable:setString("")
	else
		numPowerMaxLable:setString("" .. courage)		
	end	
	
	local numIntellentNowLable = uiLayout:FindChildObjectByName("trainNumIntellectNowLabel").__UILabel__;
	numIntellentNowLable:setString("" .. self:GetHeroIntelligence())
	local numIntellentMaxLable = uiLayout:FindChildObjectByName("trainNumIntellectMaxLabel").__UILabel__;
	if 0 == charm or nil == charm then
		numIntellentMaxLable:setString("")
	else
		numIntellentMaxLable:setString("" .. charm)
	end	
	
	local numSkillNowLable = uiLayout:FindChildObjectByName("skillNumIntellectNowLabel").__UILabel__;
	numSkillNowLable:setString("" .. self:GetHeroSkill())
	local numSkillMaxLable = uiLayout:FindChildObjectByName("skillNumIntellectMaxLabel").__UILabel__;
	if 0 == trick or nil == trick then
		numSkillMaxLable:setString("")
	else
		numSkillMaxLable:setString("" .. trick)
	end
end

function CCSpriteElfStrengthenLayer:ShowHeroDeltaCourageValue(value)
	if nil == self.Layout then
		return
	end
	local numPowerNowLable = self.Layout:FindChildObjectByName("trainNumPowerMaxLabel").__UILabel__;
	numPowerNowLable:setString("" .. value)
end

function CCSpriteElfStrengthenLayer:ShowHeroDeltaCharmValue(value)
	if nil == self.Layout then
		return
	end
	local numIntellentNowLable = self.Layout:FindChildObjectByName("trainNumIntellectMaxLabel").__UILabel__;
	numIntellentNowLable:setString("" .. value)
end

function CCSpriteElfStrengthenLayer:ShowHeroDeltaTrickValue(value)
	if nil == self.Layout then
		return
	end
	local numSkillNowLable = self.Layout:FindChildObjectByName("skillNumIntellectMaxLabel").__UILabel__;
	numSkillNowLable:setString("" .. value)
end

function CCSpriteElfStrengthenLayer:ShowHeroCourageValue()
	if nil == self.Layout then
		return
	end
	local numPowerNowLable = self.Layout:FindChildObjectByName("trainNumPowerNowLabel").__UILabel__;
	numPowerNowLable:setString("" .. self:GetHeroForce())
end

function CCSpriteElfStrengthenLayer:ShowHeroCharmValue()
	if nil == self.Layout then
		return
	end
	local numIntellentNowLable = self.Layout:FindChildObjectByName("trainNumIntellectNowLabel").__UILabel__;
	numIntellentNowLable:setString("" .. self:GetHeroIntelligence())
end

function CCSpriteElfStrengthenLayer:ShowHeroTrickValue()
	if nil == self.Layout then
		return
	end
	local numSkillNowLable = self.Layout:FindChildObjectByName("skillNumIntellectNowLabel").__UILabel__;
	numSkillNowLable:setString("" .. self:GetHeroSkill())
end

function CCSpriteElfStrengthenLayer:DisplayDataPanelLabelColor(deltaCourage,deltaCharm,deltaTrick)
	local numPowerMaxLable = self.Layout:FindChildObjectByName("trainNumPowerMaxLabel").__UILabel__;
	local numIntellentMaxLable = self.Layout:FindChildObjectByName("trainNumIntellectMaxLabel").__UILabel__;
	local numSkillMaxLable = self.Layout:FindChildObjectByName("skillNumIntellectMaxLabel").__UILabel__;

	local normal = ccc3(255,255,0)
	local green = ccc3(0,255,0)
	local red = ccc3(255,0,0)

	if deltaCourage < 0 then
		numPowerMaxLable:setColor(red)
	elseif deltaCourage == 0 then
		numPowerMaxLable:setColor(normal)
	else 
		numPowerMaxLable:setColor(green)
	end

	if deltaCharm < 0 then
		numIntellentMaxLable:setColor(red)
	elseif deltaCharm == 0 then
		numIntellentMaxLable:setColor(normal)
	else 
		numIntellentMaxLable:setColor(green)
	end

	if deltaTrick < 0 then
		numSkillMaxLable:setColor(red)
	elseif deltaTrick == 0 then
		numSkillMaxLable:setColor(normal)
	else 
		numSkillMaxLable:setColor(green)
	end

end

--Note: Display AwarkList Need Coin Or diamon
function CCSpriteElfStrengthenLayer:ShowAwarkListDetailInfo()
	local uiLayout = self.Layout
	
	for index=1,4,1 do 
		local itemName = "trainNumItemLabel" .. index	
		local label = uiLayout:FindChildObjectByName(itemName).__UILabel__;
		label:setString("" .. self.ConsumeItemNums[index])
	end
end

--Note: Display Select Item Icon By Index
function CCSpriteElfStrengthenLayer:ShowAwakeOneListItem(itemIndex)
	if itemIndex < 1 and itemIndex > 4 then
		print("****ERROR: " .. "CCSpriteElfStrengthenLayer:ShowAwakeOneListItem  " .. "itemIndex < 1 and itemIndex > 4")
	end 
	
	for index=1,4,1 do 
		if index == itemIndex then
			self.Items[index]:setVisible(true)
		else
			self.Items[index]:setVisible(false)
		end
	end

	self.SelectAwakeType = itemIndex
	
	self.SelectItemIndex = itemIndex
end

--Note: Show Max Potiention
function CCSpriteElfStrengthenLayer:ShowMaxPotentialOnTile()
	local sumPotential = GetTotalPotential()
	local uiLayout = self.Layout
	local titleLabel = uiLayout:FindChildObjectByName("trainTxtMaxPotentialLabel").__UILabel__;
	titleLabel:setString("最大潜能+" .. sumPotential)
end

function CCSpriteElfStrengthenLayer:ShowNextAttributeInfo(courage,charm,trick)
	local nextCourage = self:GetHeroForce() + courage
	local nextCharm = self:GetHeroIntelligence() + charm
	local nextTrick = self:GetHeroSkill() + trick
	self:DisplayStrengthenDataPanelInfo(nextCourage,nextCharm,nextTrick)
end

--Note: Awake Button Click Event
function ElfStrengthAwakeButtonClick(nTag)
	print("ElfStrengthAwakeButtonClick")
	local type = 0
	if CCSpriteElfStrengthenLayer.SelectAwakeType == 1 then
		type = 1
	elseif CCSpriteElfStrengthenLayer.SelectAwakeType == 2 then
		type = 2
	elseif CCSpriteElfStrengthenLayer.SelectAwakeType == 3 then
		type = 3
	elseif CCSpriteElfStrengthenLayer.SelectAwakeType == 4 then
		type = 4
	end
	SpriteFactory:sharedFactory():SendElfAwakeMessage(type)
	ShowWaitingLayer()
end

--Note: Save Btn Click Event
function ElfStrengthSaveBtnClick(pObj)
	print("ElfStrengthSaveBtnClick")
	--CCSpriteElfStrengthenLayer:ShowDownLayerContainer(false)	
	SpriteFactory:sharedFactory():SendAwakeConfigMessage()
	ShowWaitingLayer()
end

--Note: Cancel Btn Click Event
function ElfStrengthCancelBtnClick(pObj)
	print("ElfStrengthCancelBtnClick")
	CCSpriteElfStrengthenLayer:ShowDownLayerContainer(false)	
	CCSpriteElfStrengthenLayer:ShowHeroDeltaCourageValue("")
	CCSpriteElfStrengthenLayer:ShowHeroDeltaCharmValue("")
	CCSpriteElfStrengthenLayer:ShowHeroDeltaTrickValue("")
end

function HandleAwakeSuccessMessage(deltaCourage,deltaCharm,deltaTrick,bSuc)
	if bSuc == true then
		CCSpriteElfStrengthenLayer:ShowDownLayerContainer(true)	
		CCSpriteElfStrengthenLayer:ShowNextAttributeInfo(deltaCourage,deltaCharm,deltaTrick)
		CCSpriteElfStrengthenLayer:DisplayDataPanelLabelColor(deltaCourage,deltaCharm,deltaTrick)
	end
	HideWaitingLayer()
end

function HandleSaveAwakeResultMessage()
	--Note: Save 
	CCSpriteElfStrengthenLayer:ShowHeroDeltaCourageValue("")
	CCSpriteElfStrengthenLayer:ShowHeroDeltaCharmValue("")
	CCSpriteElfStrengthenLayer:ShowHeroDeltaTrickValue("")
	CCSpriteElfStrengthenLayer:ShowDownLayerContainer(false)
	HideWaitingLayer()
	return true
end

local function HeroHeroBasicAttributeChange(message)
	if message == GM_ATTR_COURAGE_UPDATE then
		CCSpriteElfStrengthenLayer:ShowHeroCourageValue()
	elseif message == GM_ATTR_CHARM_UPDATE then
		CCSpriteElfStrengthenLayer:ShowHeroCharmValue()
	elseif message == GM_ATTR_TRICK_UPDATE then
		CCSpriteElfStrengthenLayer:ShowHeroTrickValue()
	elseif message == GM_NETWORK_DISCONNCT then
		ElfStrengthCloseBtnClick(nil)
	elseif message == GM_ATTR_COIN_UPDATE then
		if nil ~= CCSpriteElfStrengthenLayer.iconContentLabel then
			local money = UserData:GetUserInfo().m_gold
			local moneyContent = MainMenuLayer:GetNumByFormat(money)
			CCSpriteElfStrengthenLayer.iconContentLabel:setString("" .. moneyContent)
		end
	elseif message == GM_ATTR_SP_DIAMOND_UPDATE then
		if nil ~= CCSpriteElfStrengthenLayer.diamondContentLabel then
			local diamond = UserData:GetUserInfo().m_diamond
			local diamondContent = MainMenuLayer:GetNumByFormat(diamond)
			CCSpriteElfStrengthenLayer.diamondContentLabel:setString("" .. diamondContent)
		end
	end
end

local notificationFunc = NotificationCenter:defaultCenter():registerScriptObserver(HeroHeroBasicAttributeChange);
local closeCallBackFun = NotificationCenter:defaultCenter():registerScriptObserver(closeLayerCallBack)