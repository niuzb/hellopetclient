require("Script/GameConfig/Localization")

LanguageLocalization = {
	LanguageFlag = "SimpleChinese"
}

function LanguageLocalization:SetLocalization(szLanguageFlag)
	self.LanguageFlag = szLanguageFlag
end

function LanguageLocalization:GetLocalization(szFlag,szLanguageFlag)
	local curLanguage = self.LanguageFlag
	if nil ~= szLanguageFlag then
		curLanguage = szLanguageFlag
	end
	
	return Localization[szFlag][curLanguage]
end

function GetLuaLocalization(szFlag)
	return LanguageLocalization:GetLocalization(szFlag)
end