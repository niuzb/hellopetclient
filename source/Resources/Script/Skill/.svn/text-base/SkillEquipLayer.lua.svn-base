require("Script/CommonDefine")
require("Script/OsCommonMethod")
require("Script/MainMenuUILayer")
require("Script/ChatToolLayer")
require("Script/Skill/SkillDataCenter")

SkillEquipLayer = {
	LayerInstance = nil,
	Layout = nil,
	iconContentLabel = nil,
	exploitContentLabel = nil,

}

function SkillEquipLayer:ResetValue()
	self.LayerInstance = nil
	self.Layout = nil
	self.iconContentLabel = nil
	self.exploitContentLabel = nil

end

local function closeLayerCallBack(message)
	if message == GM_LUA_LAYER_CLOSE then
		if nil ~= SkillEquipLayer.LayerInstance then
			if G_CurLayerInstance ~= SkillEquipLayer.LayerInstance then
				SkillEquipLayerCloseBtnClick(nil)
			end
		end
	end
end

--Note: 创建Layer
function SkillEquipLayer:CreateLayer(parentLayer)
	self:ResetValue()

	if parentLayer == nil then
		self.LayerInstance = CCLayer:create()
	else
		self.LayerInstance = parentLayer
	end
	
	local uiLayout = TXGUI.UIManager:sharedManager():createUILayoutFromFile("UIplist/SkillEquip.plist",self.LayerInstance, "SkillEquipPanel", true);
	self.Layout = uiLayout
	
	if parentLayer == nil then
		local mainMenuNode = GetMainMenuLayerNode()
		mainMenuNode:addChild(self.LayerInstance)
		InitMoneyConfigLayer(self.LayerInstance)
	end	

	self:InitLayer()
	self:ShowLeftBgIcons()

	for index,value in pairs(SkillDataCenter.DataTable) do
		self:ShowOneSkillItem(index,value.SkillID)
	end	
	
	PushOneLayer(self.LayerInstance,"","")
	--SetChatBar(true,-1)
end

function SkillEquipLayer:InitLayer()
	local closeBtn = self.Layout:FindChildObjectByName("closeBtn").__UIButton__:getMenuItemSprite();
	closeBtn:registerScriptTapHandler(SkillEquipLayerCloseBtnClick);

	local backToSkillLearnBtn = self.Layout:FindChildObjectByName("backSkillLearnBtn").__UIButton__:getMenuItemSprite();
	backToSkillLearnBtn:registerScriptTapHandler(BackToSkillLearnPanelBtnClick);

	for index = 1,5 do
		local btnName = "skillIconBtn_" .. index
		local btn = self.Layout:FindChildObjectByName(btnName).__UIButton__:getMenuItemSprite();
		btn:registerScriptTapHandler(SkillEquipLayerSkillIconBtnClick);
		btn:setTag(index)
	end

	self.iconContentLabel = self.Layout:FindChildObjectByName("MoneyLabel").__UILabel__
	self.exploitContentLabel = self.Layout:FindChildObjectByName("ExpolitLabel").__UILabel__
	local money = UserData:GetUserInfo().m_gold
	local moneyContent = MainMenuLayer:GetNumByFormat(money)
	self.iconContentLabel:setString("" .. moneyContent)
	local expolit = UserData:GetUserInfo().m_player_exploit
	local expolitContent = MainMenuLayer:GetNumByFormat(expolit)
	self.exploitContentLabel:setString("" .. expolitContent)
end

function SkillEquipLayer:ShowLeftBgIcons()
	local bgIconPath = "UI/ui_skillequip.png"
	local bgIcon = CCSprite:create(bgIconPath)
	local bgIconFramePic = self.Layout:FindChildObjectByName("equipFrameRect").__UIPicture__
	if nil ~= bgIconFramePic then
		bgIconFramePic:setSprite(bgIcon);
	end

	for index,value in pairs(SkillDataCenter.SlotDataTable) do
		self:ShowOneSlotIcon(value.SkillId,value.SlotIndex)
	end

	local attackFrameIconName = "skillIconAttack"
	local attackFrameIconPic = self.Layout:FindChildObjectByName(attackFrameIconName).__UIPicture__
	local attackIconName = "map_ui_system_icon_FRAME_ICON_ATTACK"
	local attackIconPic = AspriteManager:getInstance():getOneFrame(KICON_BIN,attackIconName)
	attackFrameIconPic:setSprite(attackIconPic);
end

function SkillEquipLayer:ShowOneSlotIcon(skillId,slotIndex)

	local btnName = "skillIconBtn_" .. slotIndex
	local btn = self.Layout:FindChildObjectByName(btnName).__UIButton__;

	local iconName = ""
	local isLock = SkillDataCenter:IsOneSlotLock(slotIndex)
	if isLock then
		--Note: 锁定状态
		iconName = "map_ui2_FRAME_SKILLLEARN_ICON_UNLOCK"
		local skillIcon = AspriteManager:getInstance():getOneFrame(KUI_BIN_2,iconName)
		btn:setIconSprite(skillIcon)
		btn:setDragMove(false)
	else
		if skillId >0 then
			--Note: 技能状态
			iconName = SkillDataCenter:GetOneSkillIconName(skillId);
			local skillIcon = AspriteManager:getInstance():getOneFrame(KICON_BIN,iconName)
			btn:setIconSprite(skillIcon)
			btn:setDragMove(true)
		else
			--Note: Nothing to do
			btn:setIconSprite(nil)
			btn:setDragMove(false)
		end		
	end
end

--Note: 显示技能Item itemIndex 1 - 5 skillId 0 锁住 
function SkillEquipLayer:ShowOneSkillItem(itemIndex,skillId)

	local unLockLevelTxt = "";
	local skillName = "";
	local skillLevelTxt = ""
	local skillIconName = ""	

	local skillLevel = SkillDataCenter:GetOneSkillLevel(skillId);

	local containerName = "skillItem_" .. itemIndex
	local container = self.Layout:FindChildObjectByName(containerName).__UIContainer__;

	--Note ： 显示Btn
	local skillIconSprite = nil

	if skillLevel == 0 then
		skillIconName = "map_ui2_FRAME_SKILLLEARN_ICON_UNLOCK"
		skillIconSprite = AspriteManager:getInstance():getOneFrame(KUI_BIN_2,skillIconName)
	else
		skillIconName = SkillDataCenter:GetOneSkillIconName(skillId)
		skillIconSprite = AspriteManager:getInstance():getOneFrame(KICON_BIN,skillIconName)
	end

	local skillIconBtn = container:FindChildObjectByName("skillBtn").__UIButton__;
	skillIconBtn:setIconSprite(skillIconSprite)
	if skillLevel == 0 then
		skillIconBtn:setDragMove(false)
	else
		skillIconBtn:setDragMove(true)
	end	

	--Note : 显示解锁等级
	local unLockLevelLabel = container:FindChildObjectByName("unLockLabel").__UILabel__;
	if skillLevel == 0 then
		local txt = "Lv" .. SkillDataCenter:GetOneSkillUnLockLevel(skillId);
		unLockLevelLabel:setString(txt)
	else
		unLockLevelLabel:setString("")
	end

	--Note : 显示技能名称
	local skillNameLabel = container:FindChildObjectByName("skillNameLabel").__UILabel__;
	skillName = SkillDataCenter:GetSkillName(skillId)
	skillNameLabel:setString(skillName)

	--Note : 显示技能等级
	local skillLevelLabel = container:FindChildObjectByName("SkillLevelLabel").__UILabel__; 
	if skillLevel == 0 then
		skillLevelLabel:setString("")
	else		
		local txt = "Lv" .. SkillDataCenter:GetOneSkillLevel(skillId);
		skillLevelLabel:setString(txt)
	end

end

-------------------事件回调------------------------------------------------
function SkillEquipLayerCloseBtnClick(pObj)
	TXGUI.UIManager:sharedManager():removeUILayout("SkillEquipPanel")
	--TXGUI.UIManager:sharedManager():removeUILayout("chatToolbar")
	SetChatBar(true,-1)
	CCTextureCache:sharedTextureCache():removeUnusedTextures()

	RemoveOneLayer(SkillEquipLayer.LayerInstance)
	--NotificationCenter:defaultCenter():unregisterScriptObserver(SkillEquipLayer.closeCallBackFun)

	SkillEquipLayer.LayerInstance:removeFromParentAndCleanup(true);
	SkillEquipLayer.LayerInstance = nil
	SkillEquipLayer:ResetValue()
end

function SkillEquipLayerSkillIconBtnClick(nTag)
	print("function SkillEquipLayerSkillIconBtnClick(nTag) " .. nTag)
end

function BackToSkillLearnPanelBtnClick(pObj)
	SkillEquipLayerCloseBtnClick(nil)
	SkillSelectLayer:CreateLayer(nil)
end

---------------------C++ 回调 -----------------------------------------------
function ListItemDragToSLotItem(skillItemIndex,slotIndex)
	--Note: 判断slot是否锁住

	local isLock = SkillDataCenter:IsOneSlotLock(slotIndex)
	if false == isLock then
		local skillId = SkillDataCenter:GetSkillIdByTableIndex(skillItemIndex);
		local toSlotSkillId = SkillDataCenter:GetOneSlotSkillId(slotIndex)
		if 0 == toSlotSkillId then
			local isExist,dstSlotIndex = SkillDataCenter:GetOneSkillExistInOtherSlot(slotIndex,skillId)
			if isExist then
				SkillDataCenter:SetOneSlotSkillId(dstSlotIndex,0)
				SkillDataCenter:SetOneSlotSkillId(slotIndex,skillId)
				SkillUIManager:getInstance():sendSetSlotAttributeMessage(dstSlotIndex,0)
				SkillUIManager:getInstance():sendSetSlotAttributeMessage(slotIndex,skillId)
				SkillEquipLayer:ShowOneSlotIcon(0,dstSlotIndex)
				SkillEquipLayer:ShowOneSlotIcon(skillId,slotIndex)				
			else
				SkillEquipLayer:ShowOneSlotIcon(skillId,slotIndex)
				SkillUIManager:getInstance():sendSetSlotAttributeMessage(slotIndex,skillId)
				SkillDataCenter:SetOneSlotSkillId(slotIndex,skillId)				
			end
		else
			if toSlotSkillId == skillId then
				--Note : Nothing to do
			else
				--Note : 判断是否已经存在该技能在其他槽中
				local isExist,dstSlotIndex = SkillDataCenter:GetOneSkillExistInOtherSlot(slotIndex,skillId)
				if isExist then
					SkillDataCenter:SetOneSlotSkillId(slotIndex,skillId)
					SkillDataCenter:SetOneSlotSkillId(dstSlotIndex,toSlotSkillId)
					SkillUIManager:getInstance():sendSetSlotAttributeMessage(slotIndex,skillId)
					SkillUIManager:getInstance():sendSetSlotAttributeMessage(dstSlotIndex,toSlotSkillId)
					SkillEquipLayer:ShowOneSlotIcon(skillId,slotIndex)
					SkillEquipLayer:ShowOneSlotIcon(toSlotSkillId,dstSlotIndex)		
				else
					SkillEquipLayer:ShowOneSlotIcon(skillId,slotIndex)
					SkillUIManager:getInstance():sendSetSlotAttributeMessage(slotIndex,skillId)
					SkillDataCenter:SetOneSlotSkillId(slotIndex,skillId)
				end
			end
		end
	end

	return true
end

function SlotItemToSelf(preSlotIndex,toSlotIndex)
	--Note: 判断slot是否锁住

	local isLock = SkillDataCenter:IsOneSlotLock(toSlotIndex)
	if false == isLock then
		--Note: 判断原槽中是否有技能
		local preSlotSkillId = SkillDataCenter:GetOneSlotSkillId(preSlotIndex)
		local toSlotSkillId = SkillDataCenter:GetOneSlotSkillId(toSlotIndex)

		if 0 == toSlotSkillId then
			SkillDataCenter:SetOneSlotSkillId(preSlotIndex,0)
			SkillDataCenter:SetOneSlotSkillId(toSlotIndex,preSlotSkillId)
			SkillUIManager:getInstance():sendSetSlotAttributeMessage(preSlotIndex,0)
			SkillUIManager:getInstance():sendSetSlotAttributeMessage(toSlotIndex,preSlotSkillId)
			SkillEquipLayer:ShowOneSlotIcon(0,preSlotIndex)
			SkillEquipLayer:ShowOneSlotIcon(preSlotSkillId,toSlotIndex)
		else
			SkillDataCenter:SetOneSlotSkillId(preSlotIndex,toSlotSkillId)
			SkillDataCenter:SetOneSlotSkillId(toSlotIndex,preSlotSkillId)
			SkillUIManager:getInstance():sendSetSlotAttributeMessage(preSlotIndex,toSlotSkillId)
			SkillUIManager:getInstance():sendSetSlotAttributeMessage(toSlotIndex,preSlotSkillId)
			SkillEquipLayer:ShowOneSlotIcon(toSlotSkillId,preSlotIndex)
			SkillEquipLayer:ShowOneSlotIcon(preSlotSkillId,toSlotIndex)			
		end
	end

	return true
end

local function updateNotification(message)
	if message == GM_NETWORK_DISCONNCT then
		TXGUI.UIManager:sharedManager():removeUILayout("SkillEquipPanel")
		--TXGUI.UIManager:sharedManager():removeUILayout("chatToolbar")
		SetChatBar(true,-1)
		CCTextureCache:sharedTextureCache():removeUnusedTextures()

		SkillEquipLayer.LayerInstance = nil
		SkillEquipLayer:ResetValue()
	elseif message == GM_ATTR_COIN_UPDATE then
		if nil ~= SkillSelectLayer.iconContentLabel then
			local money = UserData:GetUserInfo().m_gold
			local moneyContent = MainMenuLayer:GetNumByFormat(money)
			SkillSelectLayer.iconContentLabel:setString("" .. moneyContent)
		end
	elseif message == GM_ATTR_PLAYER_EXPOLIT then
		if nil ~= SkillSelectLayer.exploitContentLabel then
			local expolit = UserData:GetUserInfo().m_player_exploit
			local expolitContent = MainMenuLayer:GetNumByFormat(expolit)
			SkillSelectLayer.exploitContentLabel:setString("" .. expolitContent)
		end
	end
end

-----------------------------------------------------------------
local notificationFunc = NotificationCenter:defaultCenter():registerScriptObserver(updateNotification);
local closeCallBackFun = NotificationCenter:defaultCenter():registerScriptObserver(closeLayerCallBack);