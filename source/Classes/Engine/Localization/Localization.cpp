#include "Localization.h"
#include "LuaTinkerManager.h"

//bool Localizatioin::m_bCheckLanguageEnv = false;
//LANGUAGE_TYPE Localizatioin::m_languageType = kType_Language_SimpleChinese;

Localizatioin::Localizatioin()
{
}

Localizatioin::~Localizatioin()
{
}

const char* Localizatioin::getLocalization(const char* szFlag)
{
	if (szFlag == 0)
	{
		return "";
	}
	//if (false == m_bCheckLanguageEnv)
	//{
	//	CheckLanguageEnv();
	//	m_bCheckLanguageEnv = true;
	//}

	return LuaTinkerManager::Get()->callLuaFunc<char *>("Script/Language.lua", "GetLuaLocalization", szFlag);

	//switch(m_languageType)
	//{
	//case kType_Language_SimpleChinese:
	//	{
	//		return GameConfigFromLuaManager::Get()->getLocalizationSimpleChinese(szFlag);
	//	}
	//	break;
	//case kType_Language_Chinese:
	//	{
	//		return GameConfigFromLuaManager::Get()->getLocalizationChinese(szFlag);
	//	}
	//	break;
	//case kType_Language_Korean:
	//	{
	//		return GameConfigFromLuaManager::Get()->getLocalizationKorean(szFlag);
	//	}
	//	break;
	//case kType_Language_English:
	//	{
	//		return GameConfigFromLuaManager::Get()->getLocalizationEnglish(szFlag);
	//	}
	//	break;
	//case kType_Language_Japanese:
	//	{
	//		return GameConfigFromLuaManager::Get()->getLocalizationJapanese(szFlag);
	//	}
	//	break;
	//case kType_Language_UnKnow:
	//	{
	//		return GameConfigFromLuaManager::Get()->getLocalizationSimpleChinese(szFlag);
	//	}
	//	break;
	//}
}

// Note: 根据不同的平台实现获取当前语言类型的代码
//以后设置环境到lua并读取
//void Localizatioin::CheckLanguageEnv()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID 
//	m_languageType = kType_Language_SimpleChinese;
//#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//	m_languageType = kType_Language_SimpleChinese;
//#else
//	m_languageType = kType_Language_SimpleChinese;
//#endif	
//}