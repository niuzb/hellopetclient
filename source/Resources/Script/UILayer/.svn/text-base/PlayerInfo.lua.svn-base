LuaPlayerInfo =	{
	totalHp = 0,
	currentHp = 0,
	uiNode = nil,
	hpBar = nil,
	type = nil,
	name = "",
	id = nil
}

function LuaPlayerInfo:createPlayerInfo(extension)
	CCLuaLog("-------------------create new LuaPLayerInfo---------------");
	local playerinfo = setmetatable(extension or {},self);
	self.__index = self;
	return playerinfo;
end

function LuaPlayerInfo:getTotalHp()
	return self.totalHp;
end

function LuaPlayerInfo:setTotalHp(hp)
     CCLuaLog(string.format("LuaPlayerInfo:setTotalHp(%d)",hp));
	self.totalHp = hp;
end

function LuaPlayerInfo:getCurrentHp()
	return self.currentHp;
end

function LuaPlayerInfo:setCurrentHp(hp)
    CCLuaLog(string.format("LuaPlayerInfo:setCurrentHp(%d)",hp));
	self.currentHp = hp;
end

function LuaPlayerInfo:getUINode()
	return self.uiNode;
end

function LuaPlayerInfo:setUINode(node)
	self.uiNode = node;
end

function LuaPlayerInfo:getHpBar()
	return self.hpBar;
end

function LuaPlayerInfo:setHpBar(bar)
	self.hpBar = bar;
end

function LuaPlayerInfo:getPlayerType()
	return self.type;
end

function LuaPlayerInfo:setPlayerType(type)
	self.type = type;
	CCLuaLog(string.format("LuaPlayerInfo:setPlayerType(%d)",type));
end

function LuaPlayerInfo:getPlayerName()
	return self.name;
end

function LuaPlayerInfo:setPlayerName(str)
	CCLuaLog(string.format("LuaPlayerInfo:setPlayerName(%s)",str));
	self.name = str;
end

function LuaPlayerInfo:getPlayerId()
	return self.id;
end

function LuaPlayerInfo:setPlayerId(id)
	CCLuaLog(string.format("LuaPlayerInfo:setPlayerId(%d)",id));
	self.id = id;
end

function LuaPlayerInfo:playHpAni(hp)	
	if self.currentHp ~= hp then
		local uiScale =  TXGUI.UIManager:sharedManager():getScaleFactor();
		--CCLuaLog(string.format("LuaPlayerInfo:playHpAni: %d / %d,%f",hp,self.totalHp,uiScale));
		self.currentHp = hp;
		if 0 ~= self.totalHp then
			local scale = uiScale * hp / self.totalHp;
			local action = CCScaleTo:create(0.5,scale,uiScale);
			if self.hpBar ~= nil then
				self.hpBar:runAction(action);
			end
		end
	end
end