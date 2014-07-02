--[[ 
@file:ppveUILayer.lua
@description 
    ppve game hall, show the list of all the rooms, click one room to join.

@author:
     jameshuang 
@date
     2013/2/21
--]]
-- bind create room button
require("Script/GameConfig/InstanceList")

local ppveLayout = TXGUI.UIManager:sharedManager():getUILayout("chatToolbar");
createBtn = ppveLayout:FindChildObjectByName("createButton").__UIButton__:getMenuItemSprite();
enterBtn  = ppveLayout:FindChildObjectByName("EnterButton").__UIButton__:getMenuItemSprite();
 
local topLayout = TXGUI.UIManager:sharedManager():getUILayout("ppveUI");
local timeLabel = topLayout:FindChildObjectByName("timeremain").__UILabel__;

g_PPveHostPlayer = false;
g_bInRoom = false;

function onCloseBtnClicked(pObj)
	TXGUI.UIManager:sharedManager():removeUILayout("ppveRoom");
	ShowPPVEHall();	
	MessageHandler:sShareInstance():exitRoom();
	MessageHandler:sShareInstance():getRoomList();
end

-----------------------------------------------------update function ------------------------------------------
local lastUpdateTime = 0;
local myRemain_time = 3600;
local myCountdown = 20;
function  ppveUILayerUpdate(dt)
    --print("update script now!!!!");
    if TXGUI.UIManager:sharedManager():getUILayout("ppveUI") == nil then
        onClose(nil);
        return;
    end
    
    myRemain_time = myRemain_time -1;

    --- update remain time 
    local h =math.floor(myRemain_time / 3600);
    local m = math.floor((myRemain_time - h * 3600) / 60);
    local s = myRemain_time - h * 3600 - m * 60;

    local timeStr = ""..h;
    if (m < 10) then
       timeStr = timeStr..":0"..m;
      else
       timeStr = timeStr..":"..m;
    end
    if (s < 10) then
       timeStr = timeStr..":0"..s;
      else
       timeStr = timeStr..":"..s;    
    end

    timeLabel:setString(timeStr);

    lastUpdateTime = lastUpdateTime + 1;   
     
    -- update list
    if (lastUpdateTime > 5) then
        -- query room list every 10 seconds
        MessageHandler:sShareInstance():getPPVERooms();
        lastUpdateTime = 0;
    end
end

--- register update function 
local updateFun = CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(ppveUILayerUpdate, 1.0, false);
--------------------------------------------------------------------------------------------------------------------

function onClose(pObj)
    CCDirector:sharedDirector():getScheduler():unscheduleScriptEntry(updateFun);
end

function onJoinRoomImmediate(pObj)
end

local closeButton = topLayout:FindChildObjectByName("closeBtn").__UIButton__:getMenuItemSprite();
closeButton:registerScriptTapHandler(onClose);

-- close currnet ui layerout
function gotoNewRoom()

    CCLuaLog("PPVE gotoNewRoom!");
    CCDirector:sharedDirector():getScheduler():unscheduleScriptEntry(updateFun);  

    g_bInRoom = true;
    -- set myself host
    g_PPveHostPlayer = true;

	-- get current UI Layout and remove it from the GUI system
    local pvpLayout = TXGUI.UIManager:sharedManager():createUILayoutFromParent("UIplist/ppveRoom.plist",topLayout,"ppveRoom",false);
    pvpLayout:setVisibleInStyle(true);                                                                            
    topLayout:setVisible(false);
    
    local closeBtn = pvpLayout:FindChildObjectByName("closeBtn").__UIButton__:getMenuItemSprite();
    closeBtn:registerScriptTapHandler(onCloseBtnClicked);
    
    HideChatToolLayerAllItems();
    MessageHandler:sShareInstance():createRoom();
    TXGUI.UIManager:sharedManager():removeUILayout("ppveMapListUI");
    
end

--- press the close button of select map gui
function onCloseSelectMap(pObj)
    topLayout:setVisibleInStyle(true);                                                                      
    TXGUI.UIManager:sharedManager():removeUILayout("ppveMapListUI");
    ShowPPVELayerItems();
end

function onCreateRoom(pObj)
    CCLuaLog("ppveUILayer onCreateRoom!");
    CCDirector:sharedDirector():getScheduler():unscheduleScriptEntry(updateFun);  
   	-- get current UI Layout and remove it from the GUI system
    local selectMap = TXGUI.UIManager:sharedManager():createUILayoutFromParent("UIplist/ppveMapListUI.plist", 
                                                                               topLayout,
                                                                               "ppveMapListUI",
                                                                                false);
    GameApi:PPVELayer_InitMap();                                                                            
    selectMap:setVisibleInStyle(true);
    topLayout:setVisible(false);

    --- register close message handler for Select map gui
    local closeBtn = selectMap:FindChildObjectByName("closeBtn").__UIButton__:getMenuItemSprite();
    closeBtn:registerScriptTapHandler(onCloseSelectMap);
    HideChatToolLayerAllItems();
end

function onEnterRoom(pObj)    
     MessageHandler:sShareInstance():joinRoom(0);
end

--- show current layout
function ShowPPVEHall()
    topLayout:setVisibleInStyle(true);   
    g_bInRoom = false;
    ShowPPVELayerItems();
    CCDirector:sharedDirector():getScheduler():unscheduleScriptEntry(updateFun);
    updateFun = CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(ppveUILayerUpdate, 1.0, false);
end 

CCLuaLog("ppveUILayer loaded!");
createBtn:registerScriptTapHandler(onCreateRoom);
enterBtn:registerScriptTapHandler(onEnterRoom);

-- query room list
MessageHandler:sShareInstance():getPPVERooms();

ppve_roomData = {};
ppve_roomData[0] ={ room_id = 1, top_level = 1, current_online = 2, max_online = 4};


------------------------------------------------------ called by C++--------------------------------------
function UpdatePPVEPage()
    -- update list
   	ppve_roomData = MessageHandler:sShareInstance():getRoomData();
    printTab(ppve_roomData);    
end

---- seat inforamtion, global
RoomSeat={};

RoomSeat[0]={seat_id= -1, level= 0, name="", Avatar=0, bReady=false,};
RoomSeat[1]={seat_id= -1, level= 0, name="", Avatar=0, bReady=false,};
RoomSeat[2]={seat_id= -1, level= 0, name="", Avatar=0, bReady=false,};
RoomSeat[3]={seat_id= -1, level= 0, name="", Avatar=0, bReady=false,};

function PlayerOnSeat(seatID, playerdata)
    print("PlayerOnSeat:"..seatID.."Avatar:".. playerdata['Avatar']);
    
    RoomSeat[seatID]['seat_id'] = playerdata['seat_id'];
    RoomSeat[seatID]['level'] = playerdata['level'];
    RoomSeat[seatID]['name'] = playerdata['name']; 
    RoomSeat[seatID]['Avatar'] = playerdata['Avatar']; 
    RoomSeat[seatID]['bReady'] = playerdata['bReady'];   
    
    print("name:"..RoomSeat[seatID]['name']);
    
end

function  PlayerLeaveSeat(seatID)
     print("PlayerLeaveSeat:"..seatID);
     RoomSeat[seatID]['seat_id'] = -1;    
     RoomSeat[seatID]['bReady'] = false;
end

--------------------------------------------------- called by c++ ----------------------------------------
---- when guest leave or set ready or not, this funciton will be called by C++
function EnterRoom(roomID, topLevel) 
    CCLuaLog("PPVE EnterRoom!");
    local pvpLayout;

    if g_bInRoom == false then
        g_bInRoom = true;
        CCDirector:sharedDirector():getScheduler():unscheduleScriptEntry(updateFun);
         
        -- set myself guest
   		g_PPveHostPlayer = false;

		-- get current UI Layout and remove it from the GUI system
    	pvpLayout = TXGUI.UIManager:sharedManager():createUILayoutFromParent("UIplist/ppveRoom.plist", 
                                                                               topLayout,
                                                                               "ppveRoom",
                                                                                false);
    	pvpLayout:setVisibleInStyle(true);
    	topLayout:setVisible(false);
    	HideChatToolLayerAllItems();  
    	InitRoomTitle(roomID, topLevel);
        
        CCLuaLog("PPVE EnterRoom! g_bInRoom == false");
    else
        print("UpdateGuestSeat!");
        UpdateGuestSeat();  
        InitRoomTitle(roomID, topLevel);  	
        
        CCLuaLog("PPVE EnterRoom! g_bInRoom == true");
    end
end

---- kick off by Host
function kickOffFromRoom()
     CCLuaLog("kic kOff From Room!");
     --- call close button logic
     onCloseBtnClicked("");
end

function PlayerBaseInfo(countdown, remain_times)
   print("countdown:"..countdown.."remain_times:"..remain_times);
   myRemain_time = remain_times;
   myCountdown = countdown;
end

---------------------------------
--
--  init all PPVE map
--
function InitAllInstance()
     local i, val
     for i,val in pairs(instances) do
       	if instances[i]['Type'] == '2' then	
       	    local reqLevel = instances[i]['RequiredLevel']
			GameApi:InsertPPVEInstance(i, reqLevel)
		end  
     end          
end

