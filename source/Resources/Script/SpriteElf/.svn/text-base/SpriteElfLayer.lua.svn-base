--File : SpriteElfLayer.lua

require("Script/CommonDefine")

if false == G_IsUseLuaLocal then
	--print("false == G_IsUseLuaLocal")
	require("Script/SpriteElf/ElfConfigParse")
	require("Script/SpriteElf/SpriteElfStrengthenLayer")
	require("Script/ChatToolLayer")
else
	--print("true == G_IsUseLuaLocal")
	dofile("E:/cocos2d-x/Adventure/source/Resources/Script/SpriteElf/ElfConfigParse.lua")
	dofile("E:/cocos2d-x/Adventure/source/Resources/Script/SpriteElf/SpriteElfStrengthenLayer.lua")	
	dofile("E:/cocos2d-x/Adventure/source/Resources/Script/ChatToolLayer.lua")
end


--Note: Data Structure Used For SpriteElf

G_LuaElfDataTable = {}



function InsertNewItem(elfTable,elfId,elfState)
	local count = table.getn(elfTable)
	elfTable[count+1] = {["ElfId"] = elfId , ["ElfState"] = elfState}
	--print ("InsertNewItem " .. table.getn(elfTable))
	return count+1
end

function GetOneItemElfId(elfTable,itemIndex)
	return elfTable[itemIndex].ElfId
end

function GetOneItemElfState(elfTable,itemIndex)
	return elfTable[itemIndex].ElfState
end

function SetOneItemElfState(elfTable,itemIndex,state)
	for index,value in pairs(elfTable) do 
		if value.ElfId == itemIndex then
			elfTable[index].ElfState = state
			return
		end
	end
end

function GetCount(elfTable)
	if nil == elfTable then
		return 0
	end
	return table.getn(elfTable)
end

function RemoveTableLastElement(elfTable)
	for index,value in pairs(elfTable) do 
		local state = value.ElfState
		if 4 == state then
			table.remove(elfTable, index)
			return
		end
	end
end

--END

--Note: Used For Create Layer

G_SpriteElfLayer = nil

local function closeLayerCallBack(message)
	if message == GM_LUA_LAYER_CLOSE then
		print("local function closeLayerCallBack(message)")
		if nil ~= G_SpriteElfLayer then
			if G_CurLayerInstance ~= G_SpriteElfLayer then
				OnElfLayerCloseEvent(nil)
			end			
		end
	end
end
	
function CreateSpriteElfLayer()
	G_SpriteElfLayer = CCLayer:create()	
	local uiLayout = TXGUI.UIManager:sharedManager():createUILayoutFromFile("UIplist/SpriteElfPanel.plist",G_SpriteElfLayer, "SpriteElfPanel", true);	
	local mainMenuNode = GetMainMenuLayerNode()
	mainMenuNode:addChild(G_SpriteElfLayer,10)
	
	InitElfLayer(G_SpriteElfLayer)
	InitSpriteElfLayer()

	PushOneLayer(G_SpriteElfLayer,"","")	
end	

function OnElfLayerCloseEvent(pObj)
	TXGUI.UIManager:sharedManager():removeUILayout("SpriteElfPanel")
	SetChatBar(true,-1)
	CCTextureCache:sharedTextureCache():removeUnusedTextures()

	RemoveOneLayer(G_SpriteElfLayer)
	
	G_SpriteElfLayer:removeFromParentAndCleanup(true);
	SpriteFactory:sharedFactory():ResetValue();
	G_SpriteElfLayer = nil

end
	
--End

G_FightElfID = 0

function ClearElfLayerAllData()
	--print("ClearElfLayerAllData()")
    G_LuaElfDataTable = {}
    G_FightElfID = 0
    InitAllData()
end

--Note: UI Logic Parts
--Note: Start Function
function InitSpriteElfLayer()

	InitAllData()
	RemoveTableLastElement(G_LuaElfDataTable);
	InitChatToolLayerPanel()
	
	g_layout = TXGUI.UIManager:sharedManager():getUILayout("SpriteElfPanel");	
	local layer = g_layout:getCurrentNode():getParent()
	
	g_fightBtn = g_layout:FindChildObjectByName("battleBtn").__UIButton__:getMenuItemSprite();
	g_fightBtn:registerScriptTapHandler(GoToFightBtnClick);	
	g_fightLable = g_layout:FindChildObjectByName("battle_text").__UILabel__;
	
	g_skillNameLabel = g_layout:FindChildObjectByName("skill_name_text").__UILabel__;
	g_skillDescriptionLabel = g_layout:FindChildObjectByName("skill_description_text").__UILabel__;	
	g_frameFairySkillPic = g_layout:FindChildObjectByName("frameFairySkill").__UIPicture__;
	
	g_closeBtn = g_layout:FindChildObjectByName("closeBtn").__UIButton__:getMenuItemSprite();
	g_closeBtn:registerScriptTapHandler(OnElfLayerCloseEvent);	
	
	ShowElfBgPic(g_layout)
	ShowElfList(g_layout)
	
	if 0 == GetCount(G_LuaElfDataTable) then
		HideRightParts()
	end
	
	return true
end

--Note: 隐藏右侧面板
function HideRightParts()
	g_fightBtn:setVisible(false)
	g_fightLable:setVisible(false)
	g_skillNameLabel:setVisible(false)
	g_skillDescriptionLabel:setVisible(false)
	g_frameFairySkillPic:setVisible(false)
end

--[[
Instruction : Show Elf Equip BackGround Picture
@param 
@result 
--]]
function ShowElfBgPic(layout)
	local elfBgPic = layout:FindChildObjectByName("frameDecoration").__UIPicture__
	if nil ~= elfBgPic then
		local path = GameResourceManager:sharedManager():storedFullPathFromRelativePath("UI/ui_fairy.png")
		--print("rcs path " .. path)
		local sprite = CCSprite:create(path)
		elfBgPic:setSprite(sprite)
	end
end

--[[
Instruction : Show Elf Model On Bg
@param 
@result 
--]]
function ShowElfOnLayer(layout,typeId)
	local container = layout:FindChildObjectByName("SpriteElfContainer").__UIContainer__;
	local elfBgPic = layout:FindChildObjectByName("frameShowFairy").__UIPicture__
	if elfBgPic ~= nil then	
		local px,py = elfBgPic:getCurrentNode():getPosition()
		local scale = TXGUI.UIManager:sharedManager():getScaleFactor()
		local modePt = CCPoint(px,py)
		SpriteFactory:sharedFactory():ShowElfOnLayerAtPoint(container:getCurrentNode(),typeId,modePt)
	end
end

function InitAllData()
	g_selectedButton = nil
	g_DisableItemIndex = -1
	g_FightItemIndex = -1
	g_SelectItemIndex = -1
	g_ElfListTable = {}
    g_ElfListItemTable = {}
end

--[[
Instruction : Create And Show List
@param 
@result 
--]]
function ShowElfList(layout)
	if nil ~= layout then		
		
		scrollList = layout:FindChildObjectByName("elfScrollList").__UIScrollList__
		scrollList:clearChildrens()		
				
		if nil ~= G_LuaElfDataTable then
			local disableItem = GetToDisplayDisableElfId()
			--print ("disableItem " .. disableItem)
			if -1 ~= disableItem then
				g_DisableItemIndex = InsertNewItem(G_LuaElfDataTable,disableItem,4)
			end
			
			for index,value in pairsByKeys(G_LuaElfDataTable) do
				local itemState = value.ElfState
				local tmpElfIndex = value.ElfId
				AddNewListItem(scrollList,tmpElfIndex,itemState)
				--print("AddNewListItem(scrollList,value,itemState)" .. itemState)
				if itemState == 3 then
					--print ("fight index " .. index)
					g_FightItemIndex = index
				end
			end	
		end	
				
		SelectDefaultListItem()
	end	
end

--Note: Get One Item Disable to user
function GetToDisplayDisableElfId()
	local elfId = -1
	for index,value in pairsByKeys(G_LuaElfDataTable) do
		local tmpElfId = value.ElfId
		local nextId = tonumber(fairys[tmpElfId].next)
		if nextId ~= nil then
			if nextId == -1 then
				return -1
			else
				elfId = nextId
			end
		end
	end	
	return elfId
end

--[[
Instruction : Add New Item To List
@param listItemState 1 Normal 2 Lock
@param elfState 1 waiting 2 new 3 fight 4 lock
@result 
--]]
g_ElfListTable = {}
g_ElfListItemTable = {}

backGroundFrameName = "map_ui_FRAME_FAIRY_FRAME_FAIRYBAR";

function AddNewListItem(scrollList,elfId,itemState)
	
		backGroundFrameName = "map_ui_FRAME_FAIRY_FRAME_FAIRYBAR";
		local pBGFrame = AspriteManager:getInstance():getOneFrame(KUI_BIN,backGroundFrameName);
		local bgFrameSize = pBGFrame:getContentSize();		

		-- Note: Frame Elf Nor BackGround
		childFrameName = "map_ui_FRAME_FAIRY_FRAME_FAIRYICON";
		local normal = AspriteManager:getInstance():getOneFrame(KUI_BIN,childFrameName)
		childFrameName = "map_ui_FRAME_FAIRY_FRAME_FAIRYICON_SELECTED";
		local clicked = AspriteManager:getInstance():getOneFrame(KUI_BIN,childFrameName)

		if itemState == 4 then
			childFrameName = "map_ui_FRAME_FAIRY_FRAME_FAIRYICON_LOCKED";
			normal = AspriteManager:getInstance():getOneFrame(KUI_BIN,childFrameName)
			clicked = AspriteManager:getInstance():getOneFrame(KUI_BIN,childFrameName)
		end 
		
		local button = scrollList:AddNewItem(normal,
			clicked,
			"",
			"",
			ccc3(255,255,255),
			-130);
			
		local menuItem = button:getMenuItemSprite();
		menuItem:registerScriptTapHandler(onListItemClick);
		
		if nil == g_ElfListTable then
			g_ElfListTable = {}
		end
		
		if nil == g_ElfListItemTable then
			g_ElfListItemTable = {}
		end
		
		local listItemNum = table.getn(g_ElfListTable)
		g_ElfListTable[listItemNum+1] = menuItem		
		g_ElfListItemTable[listItemNum+1] = button

		local relativePoint = CCPoint(0,0);
		local anchorPoint = CCPoint(0.5,0.5);
		local childFrameName = "";

		childFrameName = "map_ui_FRAME_FAIRY_FRAME_FAIRYICON";
		AspriteManager:getInstance():getFramesRelativePos(KUI_BIN,backGroundFrameName,childFrameName,anchorPoint,relativePoint);
		menuItem:setPosition(relativePoint);

		if itemState == 1 then
			-- Note: nothing do
		elseif itemState == 2 then
			-- Note: Frame Flag New BackGround
			childFrameName = "map_ui_FRAME_FAIRY_ICON_NEW";
			pChildSprite = AspriteManager:getInstance():getFramesRelativePos(KUI_BIN,backGroundFrameName,childFrameName,anchorPoint,relativePoint);
			pChildSprite:setPosition(relativePoint);
			button:getAnimationNode():addChild(pChildSprite,0,1);
		elseif itemState == 3 then
			-- Note: Frame Flag InBattle BackGround
			childFrameName = "map_ui_FRAME_FAIRY_ICON_INBATTLE";
			pChildSprite = AspriteManager:getInstance():getFramesRelativePos(KUI_BIN,backGroundFrameName,childFrameName,anchorPoint,relativePoint);
			pChildSprite:setPosition(relativePoint);
			button:getAnimationNode():addChild(pChildSprite,0,1);
		elseif itemState == 4 then
			-- Note: Frame Flag InBattle BackGround
			childFrameName = "map_ui_FRAME_FAIRY_ICON_LOCK";
			pChildSprite = AspriteManager:getInstance():getFramesRelativePos(KUI_BIN,backGroundFrameName,childFrameName,anchorPoint,relativePoint);
			pChildSprite:setPosition(relativePoint);
			button:getAnimationNode():addChild(pChildSprite,0,1);
		end		
		
		-- Note: 显示精灵精灵名称
		childFrameName = "map_ui_FRAME_FAIRY_TEXT_FAIRYNAME";
		local ElfName = GetOneElfName(elfId)
		ShowOneLabel(backGroundFrameName,childFrameName,ElfName,28,ccc3(238,166,26),anchorPoint,button:getAnimationNode())
		
		-- Note: 显示精灵潜能名称
		childFrameName = "map_ui_FRAME_FAIRY_TEXT_POTENTIAL";
		local tmpLabel = ShowOneLabel(backGroundFrameName,childFrameName,"潜能",18,ccc3(255,255,255),anchorPoint,button:getAnimationNode(),kCCTextAlignmentRight)
		
		-- Note: 显示精灵潜能数值
		childFrameName = "map_ui_FRAME_FAIRY_NUMBER_POTENTIAL";		
		local ElfPotential = GetOneElfPotential(elfId)
		ShowOneLabel(backGroundFrameName,childFrameName,"+" .. ElfPotential,18,ccc3(255,255,255),anchorPoint,button:getAnimationNode())		
		
		-- Note: 显示精灵精灵获取方式
		childFrameName = "map_ui_FRAME_FAIRY_TEXT_GETWAY";
		local ElfGetWayString = GetOneElfGetWayString(elfId)
		if "" ~= ElfGetWayString then
			--print ("Get Way" .. ElfGetWayString)
			ShowOneLabel(backGroundFrameName,childFrameName,ElfGetWayString,18,ccc3(255,255,255),anchorPoint,button:getAnimationNode())
		end
		
		--Note: 显示左侧头像
		childFrameName = "map_ui_FRAME_FAIRY_ICON_FAIRY";
		AspriteManager:getInstance():getFramesRelativePos(KUI_BIN,backGroundFrameName,childFrameName,anchorPoint,relativePoint);
		local iconName = GetOneElfIcon(elfId)
		childFrameName = "map_ui_system_icon_FRAME_" .. iconName
		local elfLeftIcon = AspriteManager:getInstance():getOneFrame(KICON_BIN,childFrameName)
		elfLeftIcon:setPosition(relativePoint);
		button:getAnimationNode():addChild(elfLeftIcon);		
end

--[[
Instruction : 显示一段文本
@param 
@result 
--]]
function ShowOneLabel(bgName,uiName,content,fontSize,color,anchorPoint,parentNode,HorAligment,VerAligment)
	local relativePoint = CCPoint(0,0);
	local pLabelSprite = AspriteManager:getInstance():getFramesRelativePos(KUI_BIN,bgName,uiName,anchorPoint,relativePoint);
	local labelSize = pLabelSprite:getContentSize();
	local contentSize = CCSize(labelSize.width,labelSize.height)
	if HorAligment == nil then
		HorAligment = kCCTextAlignmentLeft
	end
	if VerAligment == nil then
		VerAligment = kCCVerticalTextAlignmentCenter
	end
	local nameLabel = TXGUI.UILabelTTF:create(content, KJLinXin, fontSize,contentSize,HorAligment,VerAligment)
	nameLabel:setColor(color)
	nameLabel:setPosition(relativePoint)
	parentNode:addChild(nameLabel,5)
	return nameLabel
end

--Note: 显示技能图标
function ShowSkillLeftIcon(elfID)
	local iconName = GetOneElfSkillIcon(elfID)
	childFrameName = "map_ui_system_icon_FRAME_" .. iconName
	local skillIcon = g_layout:FindChildObjectByName("iconFairySkill").__UIPicture__
	if nil ~= skillIcon then
		local sprite = AspriteManager:getInstance():getOneFrame(KICON_BIN,childFrameName)
		skillIcon:setSprite(sprite)
	end
end

--[[
Instruction : ListItem Click Event Handler
@param 
@result 
--]]
function onListItemClick(sender)		
	--CCLuaLog("onListItemClick" .. sender)
	local tmpTag = sender+1

	if tmpTag == g_SelectItemIndex then
		local btn = g_ElfListTable[listItemIndex]
		btn:selected()
		return
	end

	g_SelectItemIndex = tmpTag
		
	local btn = g_ElfListTable[listItemIndex]
	if nil ~= g_selectedButton then
		g_selectedButton:unselected()
	end			
	btn:selected()
	g_selectedButton = btn
	
	local id = GetOneItemElfId(G_LuaElfDataTable,listItemIndex)
	ShowElfOnLayer(g_layout,id)
	ShowOneElfSkillInfo(id)
	ShowSkillLeftIcon(id)
	
	if listItemIndex == g_DisableItemIndex then
		g_fightBtn:setVisible(false)
		g_fightLable:setVisible(false)
	else
		g_fightBtn:setVisible(true)
		g_fightLable:setVisible(true)
		
		local elfState = GetOneItemElfState(G_LuaElfDataTable,listItemIndex)
	
		if elfState == 3 then
			g_fightLable:setString("取消出战")
		else
			g_fightLable:setString("出战")
		end
	end
end

--Note: 显示精灵技能信息
function ShowOneElfSkillInfo(elfId)
	g_skillNameLabel:setString(GetOneElfSkillName(elfId))
	g_skillDescriptionLabel:setString(GetOneElfSkillDescription(elfId))
end

--Note: 点击战斗点击战斗按钮按钮
function GoToFightBtnClick(pObj)
	--print "GoToFightBtnClick"
	if -1 ~= g_SelectItemIndex and g_SelectItemIndex ~= g_DisableItemIndex then
	
		local elfId = GetOneItemElfId(G_LuaElfDataTable,g_SelectItemIndex)
		local elfState = GetOneItemElfState(G_LuaElfDataTable,g_SelectItemIndex)
	
		--print ("fight elfId " .. elfId)
		
		if elfState == 3 then
			SpriteElfDataCenter:Get():SendSetElfStateMessage(elfId,1)
			SpriteFactory:sharedFactory():RemoveElfFromHero(SpriteElfDataCenter:Get():GetHeroUserId())
			
			g_fightLable:setString("出战")
		else
			if -1 ~= g_FightItemIndex and g_FightItemIndex ~= g_SelectItemIndex then
				local preFightItemId = GetOneItemElfId(G_LuaElfDataTable,g_FightItemIndex)
				print("preFightItemId " .. preFightItemId)
				SpriteElfDataCenter:Get():SendSetElfStateMessage(preFightItemId,1)
			end
			SpriteElfDataCenter:Get():SendSetElfStateMessage(elfId,3)
		end

	end
end

--Note: Close Btn Click
function OnCloseBtnClick(pObj)
	
end

--Note: recieve rqs state message from server
function HandleRsqStateMessageFromServer(elfId,stateId)

	--print("HandleRsqMessageFromServer " .. elfId .. stateId)
	
	if stateId == 2 then
		InsertNewItem(G_LuaElfDataTable,elfId,stateId)
		
		local Flag = "ELF_GET_NEW";
		local Content = Localization[Flag].SimpleChinese
		GameApi:showMessage(Content)
	elseif stateId == 1 then
		SetOneItemElfState(G_LuaElfDataTable,elfId,stateId)
		local itemIndex = GetListItemIndexByElfId(elfId)
		ShowListItemRightIconByState(itemIndex,stateId)
	elseif stateId == 3 then
		G_FightElfID = elfId
		SetOneItemElfState(G_LuaElfDataTable,elfId,stateId)
		SpriteElfDataCenter:Get():EquipOneElf(elfId)
		g_FightItemIndex = g_SelectItemIndex
		ShowListItemRightIconByState(g_FightItemIndex,stateId)
		g_fightLable:setString("取消出战")
	end

	return true
end

--Note: Get ListItem Index In List By SpriteID
function GetListItemIndexByElfId(elfId)
	for index,value in pairs(G_LuaElfDataTable) do
		local tmpElfId = value.ElfId
		if tmpElfId == elfId then
			return index
		end
	end
	return 0
end

--Note: Show Sprite Come on State
--Note: 1 waiting 2 new 3 fight
function ShowListItemRightIconByState(itemIndex,state)
	local btnItem = g_ElfListItemTable[itemIndex]
	local childFlagIcon = btnItem:getAnimationNode():getChildByTag(1)
	if nil ~= childFlagIcon then
		childFlagIcon:removeFromParentAndCleanup(true)
		childFlagIcon = nil
	end
		
	local anchorPoint = CCPoint(0.5,0.5)
	local relativePoint = CCPoint(0,0)

	if state == 1 then
		-- Note: nothing do
	elseif state == 2 then
		-- Note: Frame Flag New BackGround
		local childFrameName = "map_ui_FRAME_FAIRY_ICON_NEW";
		local pChildSprite = AspriteManager:getInstance():getFramesRelativePos(KUI_BIN,backGroundFrameName,childFrameName,anchorPoint,relativePoint);
		pChildSprite:setPosition(relativePoint);
		btnItem:getAnimationNode():addChild(pChildSprite,0,1);
	elseif state == 3 then
		-- Note: Frame Flag InBattle BackGround
		local childFrameName = "map_ui_FRAME_FAIRY_ICON_INBATTLE";
		local pChildSprite = AspriteManager:getInstance():getFramesRelativePos(KUI_BIN,backGroundFrameName,childFrameName,anchorPoint,relativePoint);
		pChildSprite:setPosition(relativePoint);
		btnItem:getAnimationNode():addChild(pChildSprite,0,1);
	end
	
end

--Note: Get Player SpriteList Info
function HandleRsqListMessageFromServer(roleId,elfId,stateId)
	print("HandleRsqListMessageFromServer " .. roleId .. "  " .. elfId .. "  " .. stateId)
	--Note: 判断是否为主角
	local heroId = SpriteElfDataCenter:Get():GetHeroUserId()
	if roleId == heroId then
		--print ("roleId == heroId " .. roleId)		
		InsertNewItem(G_LuaElfDataTable,elfId,stateId)
		--print ("count " .. table.getn(G_LuaElfDataTable))
		--Note: Fight State
		if stateId == 3 then
			--print("stateId == 3")
			G_FightElfID = elfId
			SpriteFactory:sharedFactory():AttachElfToOneHero(elfId,roleId)
		end
	else
		--Note: Fight State
		if stateId == 3 then
			SpriteFactory:sharedFactory():AttachElfToOneHero(elfId,roleId)
		end
	end

	return true
end

--Note: Select Default ListItem when Init Layer open
function SelectDefaultListItem()
	if g_FightItemIndex == -1 then
		if nil ~= G_LuaElfDataTable then
			local count = GetCount(G_LuaElfDataTable)
			if count >= 1 then
				--Note: 选中的一项
				onListItemClick(0)
			end
		end
	else
		onListItemClick(g_FightItemIndex-1)
	end	
end

--Note:获取获取英雄英雄战斗中战斗中精灵精灵
function GetHeroFightElfID()
	return G_FightElfID
end

---------------------------------------------------Chat Tool Bar UI Parts-------------------------------

function ChatToolTrainButtonClick(pObj)
	print("ChatToolTrainButtonClick")
	if nil ~= G_SpriteElfLayer then
		OnElfLayerCloseEvent(0)
	end
	--CCSpriteElfStrengthenLayer:CreateElfStengthenLayer(nil);
	SpriteFactory:sharedFactory():ShowElfPanelWithBackPackLayer()
end

function GetTotalPotential()
	local sumValue = 0;
	for index,value in pairs(G_LuaElfDataTable) do
		if index ~= g_DisableItemIndex then
			local tmpElfId = value.ElfId
			sumValue = sumValue + GetOneElfPotential(tmpElfId)
		end
	end
	return sumValue
end

function InitChatToolLayerPanel()
	local chatLayout = TXGUI.UIManager:sharedManager():getUILayout("chatToolbar");
	local trainBtn = chatLayout:FindChildObjectByName("trainButton").__UIButton__;
	local trainBtnMenuItem = trainBtn:getMenuItemSprite();
	local potentialLabel = chatLayout:FindChildObjectByName("trainNumPotentialLabel").__UILabel__;
	
	local sumPotential = GetTotalPotential()
	potentialLabel:setString("" .. sumPotential)
	
	local frameName = "map_ui_system_icon_FRAME_ICON_TRAIN"
	if nil ~= trainBtn then
		local sprite = AspriteManager:getInstance():getOneFrame(KICON_BIN,frameName)
		trainBtn:setIconSprite(sprite)
	end	
	
	trainBtnMenuItem:registerScriptTapHandler(ChatToolTrainButtonClick);
end

function IsOneElfExistInElfDataTable(elfId)
	
	for index,value in pairs(G_LuaElfDataTable) do
		local ElfId = value.ElfId
		local ElfState = value.ElfState
		if ElfId == elfId and 4 ~= ElfState then
			return true
		end
	end
	return false
end

--Note: 获取可用探索精灵列表
function GetExploreElfTabel()
	local resultTable = {}
	--Add : fairys排序
	for index,value in pairsByKeys(fairys) do
		getWay = tonumber(value.get_way)
		if 2 == getWay then
			local isAdd = false
			if nil == value.unlocklevel then
				isAdd = true
			else
				local unLockLevel = tonumber(value.unlocklevel)
				local userLevel = UserData:GetUserLevel()
				if userLevel >= unLockLevel then
					isAdd = true
				end
			end

			if isAdd then
				if IsOneElfExistInElfDataTable(index) then
					isAdd = false
				end
			end

			if isAdd then
				InsertOneItemToTable(resultTable,index)
			end
		end
	end
	return resultTable
end

--Note:获取通过兑换方式可以获取到的精灵
function GetExchangeAbleElfTabel()
	local resultTable = {}
	--Add : fairys排序
	for index,value in pairsByKeys(fairys) do
		getWay = tonumber(value.get_way)
		if 3 == getWay then
			local isAdd = true
			--if IsOneElfExistInElfDataTable(index) then
			--	isAdd = false
			--end

			if isAdd then
				InsertOneItemToTable(resultTable,index)
			end
		end
	end
	return resultTable
end

--------------------------------------------------------------------------------------------------------

local closeCallBackFun = NotificationCenter:defaultCenter():registerScriptObserver(closeLayerCallBack)