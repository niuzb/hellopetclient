--Note: 通用ChatToolLayer 用户需要自己定义隐藏隐藏代码代码和和显示显示代码代码

G_ChatToolLayerItems = {}

function CreateChatToolLayer(parentNode)
	if nil ~= parentNode then
		local uiLayout = TXGUI.UIManager:sharedManager():getUILayout("chatToolbar");
		--local uiLayout = TXGUI.UIManager:sharedManager():createUILayoutFromFile("UIplist/chatToolbar.plist",parentNode, "chatToolbar", true);
		HideChatToolLayerAllItems()
		return uiLayout
	end
	return nil
end

function SetChatBar(isExtraVisible,order)
	SetChatToolLayer(true,true,isExtraVisible,order)
end

function SetChatToolLayer(isChatVisible,isFuncVisible,isExtraVisible,order)
	local mainLayer = MainMenuLayer:getMainMenuLayer()
	if mainLayer ~= nil then
		mainLayer:setChatToolbar(isChatVisible,isFuncVisible,isExtraVisible,order)
		HideChatToolLayerAllItems()
	end
end	

function InitChatToolLayer()
	local chatToolbarLayerOut = TXGUI.UIManager:sharedManager():getUILayout("chatToolbar");
	
	G_ChatToolLayerItems = {}
	--if chatToolbarLayerOut ~= nil then
		--Note:PPVE Layer
		g_createButton = chatToolbarLayerOut:FindChildObjectByName("createButton").__UIButton__;
		InsertOneItemToChatToolLayer(g_createButton)
		g_EnterButton = chatToolbarLayerOut:FindChildObjectByName("EnterButton").__UIButton__;
		InsertOneItemToChatToolLayer(g_EnterButton)
		g_createBtnLabel = chatToolbarLayerOut:FindChildObjectByName("createLabel").__UILabel__;
		InsertOneItemToChatToolLayer(g_createBtnLabel)
		g_enterBtnLabel = chatToolbarLayerOut:FindChildObjectByName("joinLabel").__UILabel__;
		InsertOneItemToChatToolLayer(g_enterBtnLabel)
		--Note:Elf Layer
		g_TrainButton = chatToolbarLayerOut:FindChildObjectByName("trainButton").__UIButton__;
		InsertOneItemToChatToolLayer(g_TrainButton)
		g_TrainLabel = chatToolbarLayerOut:FindChildObjectByName("trainTextLabel").__UILabel__;
		InsertOneItemToChatToolLayer(g_TrainLabel)
		g_TrainAllPotentialLabel = chatToolbarLayerOut:FindChildObjectByName("trainTextAllPotentialLabel").__UILabel__;
		InsertOneItemToChatToolLayer(g_TrainAllPotentialLabel)
		g_TrainNumLabel = chatToolbarLayerOut:FindChildObjectByName("trainNumPotentialLabel").__UILabel__;
		InsertOneItemToChatToolLayer(g_TrainNumLabel)
	--end
end

function InsertOneItemToChatToolLayer(oneItem)
	if nil~= oneItem then
		local tableCount = table.getn(G_ChatToolLayerItems)
		G_ChatToolLayerItems[tableCount+1] = oneItem
	end
end

function HideChatToolLayerAllItems()
	InitChatToolLayer()
	
	for index,value in pairs(G_ChatToolLayerItems) do 
		value:setVisible(false)
	end
end

function ShowPPVELayerItems()
	g_EnterButton:setVisible(true)
	g_createButton:setVisible(true)
	g_createBtnLabel:setVisible(true)
	g_enterBtnLabel:setVisible(true)
end


function ShowElfLayerItems()
	g_TrainButton:setVisible(true)
	g_TrainLabel:setVisible(true)
	g_TrainAllPotentialLabel:setVisible(true)
	g_TrainNumLabel:setVisible(true)
end

function ShowMoneyConfigLayer()

end

-----------------------------------------------------Init UI Layer---------------------------------------------
function InitPPVELayer(layerParent)	
	print("InitPPVELayer")
	--CreateChatToolLayer(layerParent)
	SetChatBar(false,10)
	ShowPPVELayerItems()
end

function InitElfLayer(layerParent)
	print("InitElfLayer")
	--CreateChatToolLayer(layerParent)
	SetChatBar(false,-1)
	ShowElfLayerItems()
end

function InitMoneyConfigLayer(layerParent)
	--CreateChatToolLayer(layerParent)
	SetChatBar(false,-1)
	ShowMoneyConfigLayer()
end

---------------------------------------------------------------------------------------------------------------