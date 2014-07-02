--[[****--------------------------------------------------------------------------------------------------------------
/***
@file:main.lua
@description 
     Enterpoint of all the script project
 keep all the configuration and some game logic here!-- enjoy yourself! , there is only one code here, just for test!
@author:
      jameshuang 
@date
    2013/2/21
        1. 
	install package
***
-------------------------------------------------------------------------------------------------------------------]]-- 

--[[for debug usage!]]--
function printTab(tab)
  for i,v in pairs(tab) do
    if type(v) == "table" then
      print("table",i,"{")
      printTab(v)
      print("}")
    else
      print(v)
    end
  end
end

function currDir()  
  os.execute("cd > cd.tmp")  
  local f = io.open("cd.tmp", r)  
  local cwd = f:read("*a")  
  f:close()  
  os.remove("cd.tmp")  
  return cwd  
end



------------------------------------------[[init the script system!]]-------------------------------------------


package.path = "../?.lua;../Resources/Script/?.lua;../Resources/?.lua;./Resources/?.lua;?.lua;Script/?.lua;"..package.path 
---CCLuaLog("package_path : "..package.path)

-- load ItemConfigTab module
require("Script/GameConfig/ItemConfigTab")

local appName="Adventure"


function trace (event, line)
   local s = debug.getinfo(2).short_src
   print(s..":"..line)
end 

function testItemConfig()
	local i_name = getItemName(430000)
	local get_price = getItemGetPrice(430000)
	CCLuaLog("Test Item 430000, Name["..i_name .."]".."GetPrice="..get_price)
end

local visionNum = "0.0.0.14";
function getVisionNum()
	return visionNum;
end

CCLuaLog("the App is running the script system...")
--testItemConfig()
