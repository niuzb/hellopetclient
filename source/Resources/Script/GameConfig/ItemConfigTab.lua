--[[
***
@file:ItemConfigTab.lua
@description 
     all the quest data configuration here!
keep all the configuration and some game logic here!-- enjoy yourself! , there is only one code here, just for test!
@author:
     jameshuang 
@date
     2013/2/21
*
--]]


require("Script/GameConfig/Item")
require("Script/GameConfig/EquipmentItem")
require("Script/GameConfig/characterString")
require("Script/GameConfig/ExchangeItem")
require("Script/GameConfig/SearchSpirit")
----------------------------- item configuration data-----------------
function getItemName(itemId)
	return Items[itemId]['Name']
end

function getItemDesc(itemId)
	return Items[itemId]['Description']
end

function getItemOverlapped(itemId)
	return Items[itemId]['Overlapped']
end

function getItemSource(itemId)
	return Items[itemId]['Source']
end

function getItemGetPrice(itemId)
	return Items[itemId]['GetPrice']
end

function getItemSellPrice(itemId)
	return Items[itemId]['SellPrice']
end

function getItemRequiredLevel(itemId)
	return Items[itemId]['RequiredLevel']
end

function getItemRequiredType(itemId)
	return Items[itemId]['Type']
end


--*******************************************************************
-- get equipment filed 
-- @param, itemId - item id
-- @param, field - field name
-- @note,
--        get equipment field value according to the given item id
--*******************************************************************
function getEquipmentField(itemId, field)
	return EquipmentItems[itemId][field]
end


--*******************************************************************
-- get item filed 
-- @param, itemId - item id
-- @param, field - field name
-- @note,
--        get item field value according to the given item id
--*******************************************************************
function getItemField(itemId, field)
	return Items[itemId][field]
end

function getCharacterField(characterId, field)
	return Characters[characterId][field]
end

ExchangeIds = {}

function getExchangeId(id)
	if table.getn(ExchangeIds) == 0 then
		for index,value in pairs(ExchangeItems) do
			table.insert(ExchangeIds,index);
		end
	end
	if ExchangeIds[id] ~= nil then
		return ExchangeIds[id];
	end
	return 0;
end

function getExchangeField(id,field)
	return ExchangeItems[id][field]
end

function getSearchSpiritField(id,field)
	CCLuaLog("getSearchSpiritField: " .. id .. " " .. field);
	return SearchSpirit[id][field]
end