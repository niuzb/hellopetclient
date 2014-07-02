require("Script/ChatToolLayer")
require("Script/CommonDefine")
require("Script/UILayer/EnchaseGemStoneTable")
require("Script/UILayer/enchaseExchangeUILayer")
require("Script/UILayer/enchaseRecastContainer")
require("Script/GameConfig/ExchangeParameter")

EnchaseUILayer = {
	uiLayerInstance = nil;
	uiLayout = nil;
	exchangeUILayer = nil;
	recastContainer = nil;
	notificationFunc = nil;
	equipBtnList = {};
	selectedEquipStones = {};
	heroEquipToggle = nil;
	fairyEquipToggle = nil;
	selectedEquipIndex = 0;
	selectedStoneIndex = 0;
	selectEquipFlag = true;

	diamondLabel = nil;
	creamLabel = nil;
}

EnchaseEquipBtn = {
	equipNode = nil;
	button = nil;
	pic = nil;
	nameLabel = nil;
	levelLabel = nil;
	smallArmoryList = {};
}

EnchaseSmallArmoryIcon = {
}

function EnchaseSmallArmoryIcon:createEnchaseSmallArmoryIcon(extension)
	local enchasesmallArmoryIcn = setmetatable(extension or {},self);
	self.__index = self;
	return enchasesmallArmoryIcn;
end

function EnchaseEquipBtn:createEnchaseEquipBtn(extension)
	CCLuaLog("-------------------create new EnchaseEquipBtn---------------");
	local enchaseEquipBtn = setmetatable(extension or {},self);
	self.__index = self;
	return enchaseEquipBtn;
end

function EnchaseUILayer:CreateLayer()
	CCLuaLog("EnchaseUILayer:CreateLayer()!");
	if self.uiLayerInstance == nil then 
		self.uiLayerInstance = CCLayer:create()
		local parentNode = TXGUI.UIManager:sharedManager():getUIDefaultRoot()
		if parentNode ~= nil then
			parentNode:addChild(self.uiLayerInstance)
			self.uiLayout = TXGUI.UIManager:sharedManager():createUILayoutFromFile("UIplist/enchaseUI.plist",self.uiLayerInstance, "enchaseUI", true)
			self:InitLayer();
		end
	end
end

function EnchaseUILayer:RemoveLayer()
	CCLuaLog("EnchaseUILayer:RemoveLayer()!");
	if self.exchangeUILayer ~= nil then
		self.exchangeUILayer:destory()
		self.exchangeUILayer = nil
	end
	if	self.recastContainer ~= nil then
		self.recastContainer:destory()
		self.recastContainer = nil
	end
	if self.uiLayerInstance ~= nil then
		TXGUI.UIManager:sharedManager():removeUILayout("enchaseUI")
		self.uiLayout = nil
		self.uiLayerInstance:removeFromParentAndCleanup(true)
		self.uiLayerInstance = nil
	end

	if self.notificationFunc ~= nil then
		NotificationCenter:defaultCenter():unregisterScriptObserver(self.notificationFunc);
		self.notificationFunc = nil
	end
	SetChatBar(true,-1)
end

local function getRecastCostNum(exchangeId)
	local str = ExchangeParameter[exchangeId]["FromItems"]
	local beganPos = string.find(str,"/") + 1
	local endPos = string.len(str)
	local num = string.sub(str,beganPos,endPos)
	if num == nil then
		num = 0
	end
	return num
end

function EnchaseUILayer:showRecastSpend()
	local userInfo = UserData:GetUserInfo();
	if userInfo.m_gemRecastTimes > 0 then
		self.recastContainer:setFreeCastTime(userInfo.m_gemRecastTimes)
	else
		local lockNum = 0;
		for i = 1,4 do
			if (self.selectedEquipStones[i].isLock) and (self.selectedEquipStones[i].gemId ~= 0) then
				lockNum = lockNum + 1
			end
		end
		local castedGemNum = 0;
		local castedDiamond = 0;
		if lockNum == 0 then
			castedDiamond = getRecastCostNum(20790)
			castedGemNum = getRecastCostNum(20791)
		elseif lockNum == 1 then
			castedDiamond = getRecastCostNum(20800)
			castedGemNum = getRecastCostNum(20801)	
		elseif lockNum == 2 then
			castedDiamond = getRecastCostNum(20900)
			castedGemNum = getRecastCostNum(20901)
		else
			castedDiamond = getRecastCostNum(21000)
			castedGemNum = getRecastCostNum(21001)		
		end
		self.recastContainer:setRecastCost(castedDiamond,castedGemNum)
	end
end

function EnchaseUILayer:showEquipmentStoneInfo(index,isKeepingLock)
	local equipPos = index;
	if self.selectEquipFlag then
		equipPos = equipPos + kItemHeroEquip
	else
		equipPos = equipPos + kItemFairyEquip
	end
	local backItem = ItemManager:Get():findItemByPos(equipPos)
	if backItem ~= nil then
		if (backItem.isLocked == false) and (backItem.isEmpty == false) then
			if backItem.m_equipInfo ~= nil then
				local equipHoles = backItem.m_equipInfo:getEquipHole()
				if equipHoles ~= nil then
					for i = 1,4 do 
						if equipHoles[i] ~= nil then
							if equipHoles[i].item_gem_id == 0 then
								local lock = EnchaseUILayer.selectedEquipStones[i].isLock
								EnchaseUILayer.selectedEquipStones[i]:unselectItem(true)
								if isKeepingLock and lock then
									EnchaseUILayer.selectedEquipStones[i]:changeLockState()
								end
							else
								local lock = EnchaseUILayer.selectedEquipStones[i].isLock
								EnchaseUILayer.selectedEquipStones[i]:setGem(equipHoles[i].item_gem_id,equipHoles[i].hole_index,equipHoles[i].attr_key,equipHoles[i].attr_value,equipHoles[i].min_value,equipHoles[i].max_value)
								if isKeepingLock and lock then
									EnchaseUILayer.selectedEquipStones[i]:changeLockState()
								end
							end
						else
							EnchaseUILayer.selectedEquipStones[i]:unselectItem(false)
						end
					end
				end
			end
		else
			for i = 1,4 do 
				EnchaseUILayer.selectedEquipStones[i]:unselectItem(false)
			end
		end
	end
	self:showRecastSpend()
end

function EnchaseUILayer:setChoosedEquipment(index)
	if self.selectedEquipIndex == index then
		if self.equipBtnList[index] ~= nil and self.equipBtnList[index].button ~= nil then
			self.equipBtnList[index].button:getMenuItemSprite():selected()
		end
		return
	end

	if self.equipBtnList[self.selectedEquipIndex] ~= nil and self.equipBtnList[self.selectedEquipIndex].button ~= nil then
		self.equipBtnList[self.selectedEquipIndex].button:getMenuItemSprite():unselected()
	end
	if self.equipBtnList[index] ~= nil and self.equipBtnList[index].button ~= nil then
		self.equipBtnList[index].button:getMenuItemSprite():selected()
	end

	self.selectedEquipIndex = index
	self:showEquipmentStoneInfo(index,false)
end

function EnchaseUILayer:checkEquipHoleExist(equipPos,index)
	local hasHole = 0;
	local backItem = ItemManager:Get():findItemByPos(equipPos)
	if backItem ~= nil then
		if (backItem.isLocked == false) and (backItem.isEmpty == false) then
			if backItem.m_equipInfo ~= nil then
				local equipHoles = backItem.m_equipInfo:getEquipHole()
				if equipHoles ~= nil and equipHoles[index] ~= nil then
					if  equipHoles[index].item_gem_id == 0 then
						hasHole = 1; -- 装备孔存在，但无宝石
					else	
						hasHole = 2; -- 装备孔存大，但已经有宝石
					end
				end
			end
		end
	end
	return hasHole
end

local function confirmToInlay(obj)
	local equipPos = EnchaseUILayer.selectedEquipIndex;
	if EnchaseUILayer.selectEquipFlag == true then
		equipPos = equipPos + kItemHeroEquip
	else
		equipPos = equipPos + kItemFairyEquip
	end
	EnchaseUILayer.exchangeUILayer:show(true,equipPos,EnchaseUILayer.selectedStoneIndex)
end

local function confirmToUnlockEquipHole(obj)
	local equipPos = EnchaseUILayer.selectedEquipIndex;
	if EnchaseUILayer.selectEquipFlag == true then
		equipPos = equipPos + kItemHeroEquip
	else
		equipPos = equipPos + kItemFairyEquip
	end

	local exchangeId = 40080 + 10 * EnchaseUILayer.selectedStoneIndex

	GemStonesFromLua:getInstance():GemHoleUnlockReq(exchangeId,equipPos)
end

function EnchaseUILayer:showDiamondLabel()
	if self.diamondLabel ~= nil then
		local info = UserData:GetUserInfo()
		local diamond = info.m_diamond
		self.diamondLabel:setString(diamond)
	end
end

function EnchaseUILayer:showCreamLabel()
	if EnchaseUILayer.creamLabel ~= nil then
			local info = UserData:GetUserInfo()
			local anima = info.m_playerGemAnima
			EnchaseUILayer.creamLabel:setString(anima)
		end
end

function EnchaseUILayer:reqUnlockHole()
	local equipPos = self.selectedEquipIndex;
	if self.selectEquipFlag == true then
		equipPos = equipPos + kItemHeroEquip
	else
		equipPos = equipPos + kItemFairyEquip
	end
	-- 计算解锁需要钻石用于显示，
	local backItem = ItemManager:Get():findItemByPos(equipPos)
	if backItem ~= nil then
		if (not backItem.isLocked) and (not backItem.isEmpty) and (backItem.m_equipInfo ~= nil) then
			local equipHoles = backItem.m_equipInfo:getEquipHole()
			if equipHoles ~= nil then
				local diamond = 0;
				for i = 1,self.selectedStoneIndex do
					if equipHoles[i] == nil then
						local exchangeId = 40080 + 10 * i
						local str = ExchangeParameter[exchangeId]["FromItems"]
						local beganPos = string.find(str,"/") + 1
						local endPos = string.len(str)
						local num = string.sub(str,beganPos,endPos)
						if num == nil then
							num = 0
						end
						diamond = diamond + num
					end
				end
				MessageBox:Show(string.format("插槽已锁，是否花%d钻提前解锁",diamond),confirmToUnlockEquipHole,nil,MB_YESNO,ccc3(255,255,255),26)
			end
		end
	end
end

function EnchaseUILayer:oneStoneLockClicked(index)
	local equipPos = self.selectedEquipIndex;
	if self.selectEquipFlag == true then
		equipPos = equipPos + kItemHeroEquip
	else
		equipPos = equipPos + kItemFairyEquip
	end
	local hasHole = self:checkEquipHoleExist(equipPos,index)
	if hasHole == 2 then
		self.selectedEquipStones[index]:changeLockState()
		self:showRecastSpend()
	end
end

function EnchaseUILayer:oneStoneClicked(index)
	self.selectedStoneIndex = index
	local equipPos = self.selectedEquipIndex;
	if self.selectEquipFlag == true then
		equipPos = equipPos + kItemHeroEquip
	else
		equipPos = equipPos + kItemFairyEquip
	end
	local hasHole = self:checkEquipHoleExist(equipPos,self.selectedStoneIndex)
	if hasHole == 1 then
		self.exchangeUILayer:show(true,equipPos,self.selectedStoneIndex)
	elseif hasHole == 2 then
		MessageBox:Show("已有宝石存在，是否要覆盖原有宝石",confirmToInlay,nil,MB_YESNO,ccc3(255,255,255),26)
	else
		--GameApi:showMessage("插槽已锁");
		self:reqUnlockHole();
	end
	
end

local function closeEnchaseLayerBt(obj)
	CCLuaLog("EnchaseUILayer:closeEnchaseLayerBt()!");
	RemoveOneLayer(EnchaseUILayer.uiLayerInstance)
	EnchaseUILayer:RemoveLayer();
end

local function exchageCreamBtClicked(obj)
	EnchaseUILayer.exchangeUILayer:show(false,0,0)
end

local function oneEquipmentClicked(tag)
	EnchaseUILayer:setChoosedEquipment(tag)
end

local function onGemStoneIconClicked(tag)
	EnchaseUILayer:oneStoneClicked(tag)
end

local function onGemStoneLockClicked(tag)
	EnchaseUILayer:oneStoneLockClicked(tag)
end

local function onRecastBtnClicked(tag)
	local equipPos = EnchaseUILayer.selectedEquipIndex;
	if EnchaseUILayer.selectEquipFlag == true then
		equipPos = equipPos + kItemHeroEquip
	else
		equipPos = equipPos + kItemFairyEquip
	end
	local holes = {};
	for i = 1,4 do
		if EnchaseUILayer.selectedEquipStones[i].isLock then
			holes[i] = 0;
		else
			holes[i] = i;
		end
	end
	local spenndType = EnchaseUILayer.recastContainer.spendFlag;
	GemStonesFromLua:getInstance():GemRecastReq(equipPos,holes[1],holes[2],holes[3],holes[4],spenndType)
end

local function updateNotification(message)
	CCLuaLog("EnchaseUILayer:updateNotification()!");
	if message == GM_NETWORK_DISCONNCT then
		if EnchaseUILayer.exchangeUILayer ~= nil then
			EnchaseUILayer.exchangeUILayer:destory()
			EnchaseUILayer.exchangeUILayer = nil
		end
		if	EnchaseUILayer.recastContainer ~= nil then
			EnchaseUILayer.recastContainer:destory()
			EnchaseUILayer.recastContainer = nil
		end
		TXGUI.UIManager:sharedManager():removeUILayout("enchaseUI")
		EnchaseUILayer.uiLayerInstance = nil
		EnchaseUILayer.uiLayout = nil
		EnchaseUILayer.notificationFunc = nil
	elseif message == GM_LUA_LAYER_CLOSE then
		if nil ~= EnchaseUILayer.uiLayerInstance then
			if G_CurLayerInstance ~= EnchaseUILayer.uiLayerInstance then
				closeEnchaseLayerBt(nil)
			end
		end
	elseif message == GM_ATTR_SP_DIAMOND_UPDATE then
		EnchaseUILayer:showDiamondLabel()
	elseif message == GM_ATTR_PLAYER_GEM_ANIMA then
		CCLuaLog("message == GM_ATTR_PLAYER_GEM_ANIMA")
		EnchaseUILayer:showCreamLabel()
	end
end

local function showEquipName(index,name,color)
	if(EnchaseUILayer.equipBtnList[index] ~= nil) and (EnchaseUILayer.equipBtnList[index].nameLabel ~= nil) then
		EnchaseUILayer.equipBtnList[index].nameLabel:setString(name)
		if color ~= nil then
			EnchaseUILayer.equipBtnList[index].nameLabel:setColor(color)
		end
	end
end

local function showEquipPicture(index,sprite,frame)
	if(EnchaseUILayer.equipBtnList[index] ~= nil) and (EnchaseUILayer.equipBtnList[index].pic ~= nil) then
		EnchaseUILayer.equipBtnList[index].pic:setSprite(sprite)
		if frame ~= nil then
			EnchaseUILayer.equipBtnList[index].pic:addExtraPic(frame,ccp(0,0))
		end
	end
end

local function showEquipLevel(index,level,color)
	if(EnchaseUILayer.equipBtnList[index] ~= nil) and (EnchaseUILayer.equipBtnList[index].levelLabel ~= nil) then
		EnchaseUILayer.equipBtnList[index].levelLabel:setString(level)
		if color ~= nil then
			EnchaseUILayer.equipBtnList[index].levelLabel:setColor(color)
		end
	end
end

local function getSmallArmoryIconSprite(id)
	local iconName = nil
	if id == 417001 then
		iconName = "map_ui2_FRAME_ENCHASE_ICON_SMALL_ARMORYGREEN"
	elseif id == 417002 then
		iconName = "map_ui2_FRAME_ENCHASE_ICON_SMALL_ARMORYBLUE"
	elseif id == 417003 then
		iconName = "map_ui2_FRAME_ENCHASE_ICON_SMALL_ARMORYPURPLE"
	elseif id == 417004 then
		iconName = "map_ui2_FRAME_ENCHASE_ICON_SMALL_ARMORYYELLOW"
	elseif id == 417005 then
		iconName = "map_ui2_FRAME_ENCHASE_ICON_SMALL_ARMORYORANGE"
	end

	if iconName ~= nil then
		local icon = AspriteManager:getInstance():getOneFrame("UI/ui2.bin",iconName)
		return icon;
	else
		return nil
	end
end

local function showSingleEquip(pos,index)
	local backItem = ItemManager:Get():findItemByPos(pos)
		if backItem ~= nil then
			if (backItem.isLocked == false) and (backItem.isEmpty == false) then
				local itemInfo = backItem:getItemInfo()
				if itemInfo ~= nil then
					local sprite = ItemManager:Get():getIconSpriteById(backItem:getItemId())
					if sprite ~= nil then
						local frame = nil
						if itemInfo.m_quality > 0 then
							frame = ItemManager:Get():getIconFrame(itemInfo.m_quality)
						end
						showEquipPicture(index,sprite,frame)
						local nameColor = ItemManager:Get():getLabelColorByQuality(itemInfo.m_quality)
						showEquipName(index,itemInfo.m_name,nameColor)
						showEquipLevel(index,string.format("Lv %d",backItem.itemLevel));
					end
				end
				if backItem.m_equipInfo ~= nil then
					local equipHoles = backItem.m_equipInfo:getEquipHole()
					if equipHoles ~= nil then
						for i = 1,4 do 
							if equipHoles[i] ~= nil then
								if equipHoles[i].item_gem_id == 0 then
									EnchaseUILayer.equipBtnList[index].smallArmoryList[i]:setSprite(nil)
								else
									local sprite = getSmallArmoryIconSprite(equipHoles[i].item_gem_id)
									EnchaseUILayer.equipBtnList[index].smallArmoryList[i]:setSprite(sprite)
								end
							else
								local lockSprite = AspriteManager:getInstance():getOneFrame("UI/ui2.bin","map_ui2_FRAME_ENCHASE_ICON_SMALL_LOCK")
								if EnchaseUILayer.equipBtnList[index] ~= nil and EnchaseUILayer.equipBtnList[index].smallArmoryList[i] ~= nil then
									EnchaseUILayer.equipBtnList[index].smallArmoryList[i]:setSprite(lockSprite)
								end
							end
						end
					end
				end
			else
				showEquipName(index,"",nil)
				showEquipLevel(index,"",nil)
				showEquipPicture(index,nil)
				for i = 1,4 do 
					if EnchaseUILayer.equipBtnList[index] ~= nil and EnchaseUILayer.equipBtnList[index].smallArmoryList[i] ~= nil then
							EnchaseUILayer.equipBtnList[index].smallArmoryList[i]:setSprite(nil)
					end		
				end
			end
		end
end

local function showHeroEquip()
	for i =1,6 do
		showSingleEquip(kItemHeroEquip + i,i)
	end
end

local function showFairyEquip()
	for i =1,6 do
		showSingleEquip(kItemFairyEquip + i,i)
	end
end

local function unSelectEquip()
	if EnchaseUILayer.selectedEquipIndex == 0 then
		return
	end

	if EnchaseUILayer.equipBtnList[EnchaseUILayer.selectedEquipIndex] ~= nil and EnchaseUILayer.equipBtnList[EnchaseUILayer.selectedEquipIndex].button ~= nil then
		EnchaseUILayer.equipBtnList[EnchaseUILayer.selectedEquipIndex].button:getMenuItemSprite():unselected()
	end

	EnchaseUILayer.selectedEquipIndex = 0
end

function EnchaseUILayer:setDefaultSelectedEquip()
	local pos = 0;
	if self.selectEquipFlag == true then
		pos = kItemHeroEquip
	else
		pos = kItemFairyEquip
	end

	for i =1,6 do
		local backPackItem = ItemManager:Get():findItemByPos(pos + i)
		if backPackItem ~= nil and backPackItem.isEmpty == false and backPackItem.isLocked == false then
			self:setChoosedEquipment(i)
			return;
		end
	end

	
	-- 没有任何装备
	--for i = 1,4 do 
		--EnchaseUILayer.selectedEquipStones[i]:unselectItem(false)
	--end
end

local function enchaseHeroToggleClicked(obj)
	if EnchaseUILayer.fairyEquipToggle ~= nil then
		EnchaseUILayer.fairyEquipToggle:unselected()
	end

	if EnchaseUILayer.heroEquipToggle ~= nil then
		EnchaseUILayer.heroEquipToggle:selected()
	end

	if EnchaseUILayer.selectEquipFlag == false then
		EnchaseUILayer.selectEquipFlag = true;
		showHeroEquip();
		unSelectEquip();
		EnchaseUILayer:setDefaultSelectedEquip();
	end
end

local function enchaseFairyToggleClicked(obj)
	if EnchaseUILayer.fairyEquipToggle ~= nil then
		EnchaseUILayer.fairyEquipToggle:selected()
	end

	if EnchaseUILayer.heroEquipToggle ~= nil then
		EnchaseUILayer.heroEquipToggle:unselected()
	end

	if EnchaseUILayer.selectEquipFlag == true then
		CCLuaLog("set EnchaseUILayer.selectEquipFlag = false; ***********************************")
		EnchaseUILayer.selectEquipFlag = false;
		showFairyEquip();
		unSelectEquip();
		EnchaseUILayer:setDefaultSelectedEquip();
	end
end

function EnchaseUILayer:InitRecastContainer()
	self.recastContainer = EnchaseRecastContainer:create(self.uiLayout)
	self.recastContainer.recastBtn:getMenuItemSprite():registerScriptTapHandler(onRecastBtnClicked)
end

function EnchaseUILayer:InitExchangeUI()
	self.exchangeUILayer = EnchaseExchangeLayer:create(self.uiLayerInstance)
	--self.exchangeUILayer:init(self.uiLayerInstance)
end

function EnchaseUILayer:InitEquipmentUI()
	local scale =  TXGUI.UIManager:sharedManager():getScaleFactor();
	local parentControl = self.uiLayout:FindChildObjectByName("enchaseContainer").__UIContainer__;
	local equipBigBg,bgPt =  AspriteManager:getInstance():getOneFrameAndPosition("UI/ui2.bin","map_ui2_FRAME_ENCHASE_FRAME_EQUIPAREA");
	CCLuaLog(string.format("equipBigBg: wh = %f, %f, pt: %f, %f",equipBigBg:getContentSize().width,equipBigBg:getContentSize().height,bgPt.x,bgPt.y))
	for i = 1,6 do
		self.equipBtnList[i] = EnchaseEquipBtn:createEnchaseEquipBtn();
		self.equipBtnList[i].smallArmoryList = EnchaseSmallArmoryIcon:createEnchaseSmallArmoryIcon();
		self.equipBtnList[i].equipNode = CCNode:create();

		local normalSprite = AspriteManager:getInstance():getOneFrame("UI/ui2.bin","map_ui2_FRAME_ENCHASE_FRAME_EQUIP_HELMET")
		local clickedSprite = AspriteManager:getInstance():getOneFrame("UI/ui2.bin","map_ui2_FRAME_ENCHASE_FRAME_EQUIP_HELMET_CLICKED")
		local menuItem = CCMenuItemSprite:create(normalSprite,clickedSprite);
		self.equipBtnList[i].button = TXGUI.UIButton:new(string.format("enchaseBt%d",i), i, 0, parentControl, menuItem, nil,-130, "");
		menuItem:registerScriptTapHandler(oneEquipmentClicked)

		self.equipBtnList[i].button:setScale(scale)
		local equipBtNode,nodePt = AspriteManager:getInstance():getOneFrameAndPosition("UI/ui2.bin","map_ui2_FRAME_ENCHASE_FRAME_EQUIP1");
		local equipSprite,picPt = AspriteManager:getInstance():getOneFrameAndPosition("UI/ui2.bin","map_ui2_FRAME_ENCHASE_FRAME_ICON");
		local equipPic = TXGUI.UIPicture:new(string.format("enchasePic%d",i),i,1,parentControl,equipSprite)
		--equipPic:setPosition(ccp(picPt.x - nodePt.x,picPt.y - nodePt.y));
		equipPic:setScale(scale)
		self.equipBtnList[i].pic = equipPic;

		local equipName,namePt = AspriteManager:getInstance():getOneFrameAndPosition("UI/ui2.bin","map_ui2_FRAME_ENCHASE_TEXT_EQUIP_HELMET");	
		local nameLabel = TXGUI.UILabelTTF:create(" ",KJLinXin,24,equipName:getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		nameLabel:setScale(scale)
		self.equipBtnList[i].equipNode:addChild(nameLabel);
		nameLabel:setPosition(ccp(namePt.x * scale - nodePt.x * scale,namePt.y * scale - nodePt.y * scale ));
		self.equipBtnList[i].nameLabel = nameLabel;

		local equipLevel,levelPt = AspriteManager:getInstance():getOneFrameAndPosition("UI/ui2.bin","map_ui2_FRAME_ENCHASE_TEXT_LEVEL_HELMET");
		local levelLabel = TXGUI.UILabelTTF:create(" ",KJLinXin,24,equipLevel:getContentSize(),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		levelLabel:setScale(scale)
		self.equipBtnList[i].equipNode:addChild(levelLabel);
		levelLabel:setPosition(ccp(levelPt.x * scale - nodePt.x * scale,levelPt.y * scale - nodePt.y * scale));
		self.equipBtnList[i].levelLabel = levelLabel;
			
		local totalRow = 3;
		local totalColumn = 2;
		local column = (i - 1) % totalColumn;
		local row = (i - 1 - column) / totalColumn;
		local spaceX = equipBigBg:getContentSize().width * scale - 2 * equipBtNode:getContentSize().width * scale
		local spaceY = equipBigBg:getContentSize().height * scale - 3 * equipBtNode:getContentSize().height * scale
		local containerPtX,containerPtY = parentControl:getCurrentNode():getPosition()
		local x = (bgPt.x - 568)* scale  +(column - 0.5) * (spaceX * 0.5 +  equipBtNode:getContentSize().width * scale)
		local y =(bgPt.y - 320)* scale +(1 - row) * (spaceY / 3  + equipBtNode:getContentSize().height * scale)
		CCLuaLog(string.format("containerPtX: containerPtY = %f, %f",containerPtX,containerPtY))

		self.equipBtnList[i].equipNode:setPosition(ccp(x,y))
		self.equipBtnList[i].button:setPosition(ccp(x,y))
		self.equipBtnList[i].pic:setPosition(ccp(picPt.x * scale - nodePt.x * scale + x,picPt.y * scale - nodePt.y * scale + y))
		for j = 1,4 do
			local smallArmorySprite,smallPt = AspriteManager:getInstance():getOneFrameAndPosition("UI/ui2.bin",string.format("map_ui2_FRAME_ENCHASE_FRAME_SMALL_ARMORY%d",j));
			local smallPic = TXGUI.UIPicture:new(string.format("enchaseSmallPic_%d_%d",i,j),i,2,parentControl,smallArmorySprite)
			smallPic:setScale(scale)
			smallPic:setPosition(ccp(x + smallPt.x * scale- nodePt.x * scale,y + smallPt.y * scale - nodePt.y * scale));
			self.equipBtnList[i].smallArmoryList[j] = smallPic
		end

		parentControl:getCurrentNode():addChild(self.equipBtnList[i].equipNode)
	end
	for i = 1,4 do
		self.selectedEquipStones[i] = EnchaseGemStoneTable:createSelectGemStoneTable();
		self.selectedEquipStones[i]:init(self.uiLayout,i);
		self.selectedEquipStones[i].iconBtn:getMenuItemSprite():registerScriptTapHandler(onGemStoneIconClicked);
		self.selectedEquipStones[i].lockBtn:getMenuItemSprite():registerScriptTapHandler(onGemStoneLockClicked);
	end

end

function EnchaseUILayer:InitLayer()
	CCLuaLog("EnchaseUILayer:InitLayer()!");

	self:InitEquipmentUI()
	self:InitExchangeUI()
	self:InitRecastContainer()
	showHeroEquip()

	local closeBt = self.uiLayout:FindChildObjectByName("closeBt").__UIButton__:getMenuItemSprite();
	closeBt:registerScriptTapHandler(closeEnchaseLayerBt);
	local exchangeBt = self.uiLayout:FindChildObjectByName("exchangeCreamBt").__UIButton__:getMenuItemSprite();
	exchangeBt:registerScriptTapHandler(exchageCreamBtClicked);
	self.heroEquipToggle = self.uiLayout:FindChildObjectByName("heroEnchaseButtonToggle").__UIButtonToggle__;
	self.fairyEquipToggle = self.uiLayout:FindChildObjectByName("fairyEnchaseButtonToggle").__UIButtonToggle__;
	self.diamondLabel = self.uiLayout:FindChildObjectByName("diamondLabel").__UILabel__;
	self.creamLabel = self.uiLayout:FindChildObjectByName("creamLabel").__UILabel__;
	local heroToggle = self.heroEquipToggle:getMenuItemToggle()
	if heroToggle ~= nil then
		heroToggle:registerScriptTapHandler(enchaseHeroToggleClicked);
	end

	local fairyToggle = self.fairyEquipToggle:getMenuItemToggle()
	if fairyToggle ~= nil then
		fairyToggle:registerScriptTapHandler(enchaseFairyToggleClicked);
	end
	self.notificationFunc = NotificationCenter:defaultCenter():registerScriptObserver(updateNotification);
	self.selectEquipFlag = true;
	self:setDefaultSelectedEquip();
	self:showRecastSpend()
	self:showDiamondLabel()
	self:showCreamLabel()
	PushOneLayer(self.uiLayerInstance,"","")
	SetChatBar(false,-1)
end

function onReceiveEquipInlayGem(error)
	if error == 0 then
		GameApi:showMessage("镶嵌成功");
		EnchaseUILayer.exchangeUILayer:hide();
		local equipPos = EnchaseUILayer.selectedEquipIndex;
		if EnchaseUILayer.selectEquipFlag == true then
			equipPos = equipPos + kItemHeroEquip
		else
			equipPos = equipPos + kItemFairyEquip
		end
		showSingleEquip(equipPos,EnchaseUILayer.selectedEquipIndex)
		EnchaseUILayer:showEquipmentStoneInfo(EnchaseUILayer.selectedEquipIndex,true)
	else
		GameApi:showMessage("宝石不存在" .. error);
	end
end

function onRecieveGemRecast(error)
	if error == 0 then
		GameApi:showMessage("重铸成功");
		EnchaseUILayer:showEquipmentStoneInfo(EnchaseUILayer.selectedEquipIndex,true)
		EnchaseUILayer:showRecastSpend()
	else
		GameApi:showMessage("重铸失败" .. error);
	end
end

function onReceiveEquipHoleUnlock(ret)
	if ret then
		GameApi:showMessage("解锁成功");
		local equipPos = EnchaseUILayer.selectedEquipIndex;
		if EnchaseUILayer.selectEquipFlag == true then
			equipPos = equipPos + kItemHeroEquip
		else
			equipPos = equipPos + kItemFairyEquip
		end
		showSingleEquip(equipPos,EnchaseUILayer.selectedEquipIndex)
		EnchaseUILayer:showEquipmentStoneInfo(EnchaseUILayer.selectedEquipIndex,false)
	else
		GameApi:showMessage("解锁失败");
	end
end
