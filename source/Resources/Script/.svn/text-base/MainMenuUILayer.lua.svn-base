function GetMainMenuLayerNode()
	local node =  SpriteFactory:sharedFactory():GetMainMenuLayerNode()
	return node
end

function HideOneLayerByTag(tag)
	local ret = false
	local node =  SpriteFactory:sharedFactory():GetMainMenuLayerNode()
	local layer = node:getChildByTag(tag)
	if layer ~= nil then
		layer:setVisible(false)
		ret = true
	end
	return ret
end