require("Script/GameConfig/RaidBasic")
--dofile("E:/cocos2d-x/Adventure/source/Resources/Script/GameConfig/RaidBasic.lua")

G_MonsterTable = {}

function GetOneMapMonsterIds(mapId)
	local monsterTable = MapMonsterInformation[mapId]
	if nil == monsterTable then
		return false
	else
		G_MonsterTable = MapMonsterInformation[mapId]
		return true
	end	
end

--GetOneMapMonsterIds(1001010)
--
--for key, value in pairs(monsterTable) do  
--	print(key)
--    print(value)
--end 