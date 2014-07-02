G_IsUseLuaLocal = false

KUI_BIN = "UI/ui.bin"
KUI_BIN_2 = "UI/ui2.bin"
KICON_BIN = "UI/ui_system_icon.bin"
KJLinXin = "STHeitiSC-Medium"

G_CurLayerInstance = nil

G_PvAILayerTag = 10001

function SetLayerInstance(instance)
	print("function SetLayerInstance(instance)")
	G_CurLayerInstance = instance
end