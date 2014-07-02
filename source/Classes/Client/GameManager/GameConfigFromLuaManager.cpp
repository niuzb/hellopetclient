// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//


#include <libxml/parser.h>

#include "ItemManager.h"
#include "ItemBase.h"
#include "EquipmentItem.h"
#include "GameConfigFromLuaManager.h"
#include "GameResourceManager.h"
#include "NetWorkConfigure.h"
#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "tolua++.h"

static void EnumTableItem(lua_State *L, const char* lpszTableName,std::vector<unsigned int> &outVec)
{
	outVec.clear();

	lua_getglobal(L, lpszTableName); 
	int it = lua_gettop(L);  
	lua_pushnil(L);         
	while(lua_next(L, it))  
	{
		int value = (int)lua_tonumber(L, -2);
		printf("%d\n", value); 		
		outVec.push_back(value);
		lua_pop(L, 1);  
	}
	lua_pop(L, 1);
}

GameConfigFromLuaManager::GameConfigFromLuaManager()
{
	this->m_configLuaState = NULL;
	this->initLuaState();
	loadedFiles.clear();

	this->m_isLoadMapMusicData = false;
	//this->m_isLoadOsCommonMethodData = false;
	this->m_isLoadToolBarTableData = false;
	this->m_isLoadSkillConfigData = false;
	this->m_isLoadCommonDefineData = false;
}

GameConfigFromLuaManager::~GameConfigFromLuaManager() 
{

}

void GameConfigFromLuaManager::initLuaState() {

	// get global luad state
	this->m_configLuaState = CCLuaEngine::defaultEngine()->getLuaState();
}

bool GameConfigFromLuaManager::checkAnyLoadFile(string filePath)
{
	
	if (loadedFiles.find(filePath) == loadedFiles.end())
	{
		const char *path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(filePath.c_str());

		unsigned long fileSize = 0;
		unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path, "rt", &fileSize);
		int ret = luaL_dostringEx(this->m_configLuaState, (char*)buffer, fileSize);

		if (ret != 0) {
			CCLOG("load %s file error: %s", filePath.c_str(), lua_tostring(this->m_configLuaState, -1));
			lua_pop(this->m_configLuaState, 1);
			return false;
		}

		loadedFiles.insert(filePath);
		return true;
	}

	return true;
}

bool GameConfigFromLuaManager::checkConfigLoadFile(string fileName)
{
	string filePath = "Script/GameConfig/" + fileName + ".lua";
	return checkAnyLoadFile(filePath);
}

bool GameConfigFromLuaManager::getEquipmentItemFieldById(const int itemId, const char * field , const char* itemState, std::string& Val)
{
	if (false == this->checkConfigLoadFile("ItemConfigTab"))
		return false;

	const char *desc = "";

	lua_getglobal(this->m_configLuaState, itemState);
	lua_pushnumber(this->m_configLuaState, itemId);
	lua_pushstring(this->m_configLuaState, field);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) {
		//CCLOG("call getItemDesc error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return false;
	}

	if (lua_isstring(this->m_configLuaState, -1)) {
		desc = lua_tostring(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);

	Val = desc;
    return true;
}

bool GameConfigFromLuaManager::getEquipmentItemFieldById(const int itemId, const char * field , const char* itemState, int& Val)
{
	if (false == this->checkConfigLoadFile("ItemConfigTab"))
		return false;

	lua_getglobal(this->m_configLuaState, itemState);
	lua_pushnumber(this->m_configLuaState, itemId);
	lua_pushstring(this->m_configLuaState, field);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) {
		//CCLOG("call getItemDesc error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return false;
	}

	if (lua_isnumber(this->m_configLuaState, -1)) {
		Val = lua_tointeger(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);
    return true;
}

bool GameConfigFromLuaManager::getEquipmentItemFieldById(const int itemId, const char * field , const char* itemState, double& Val)
{
	if (false == this->checkConfigLoadFile("ItemConfigTab"))
		return false;

	lua_getglobal(this->m_configLuaState, itemState);
	lua_pushnumber(this->m_configLuaState, itemId);
	lua_pushstring(this->m_configLuaState, field);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) {
		//CCLOG("call getItemDesc error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return false;
	}

	if (lua_isnumber(this->m_configLuaState, -1)) {
		Val = lua_tonumber(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);
    return true;
}

bool GameConfigFromLuaManager::getEquipmentItemFieldById(const int itemId, const char * field , const char* itemState, bool& Val)
{
	if (false == this->checkConfigLoadFile("ItemConfigTab"))
		return false;

	lua_getglobal(this->m_configLuaState, itemState);
	lua_pushnumber(this->m_configLuaState, itemId);
	lua_pushstring(this->m_configLuaState, field);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) {
		//CCLOG("call getItemDesc error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return false;
	}

	if (lua_isnumber(this->m_configLuaState, -1)) {
		Val = lua_tonumber(this->m_configLuaState, -1) != 0;
	}

	lua_pop(this->m_configLuaState, 1);
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// get resource id
#include "TXGUIHeader.h"
#define UNKNOWN_ITEM_RESOURCE_ID   "map_ui_system_icon_FRAME_499999"

int GameConfigFromLuaManager::getItemResourceId(const int itemId) {
	char szKey[256] = "";
	sprintf(szKey, "map_ui_system_icon_FRAME_%d", itemId);
	int iVal = TXGUI::getResourceIDByName(szKey);
	if (iVal < 0)
	{
		/// can't find the resource from resources.h
		return TXGUI::getResourceIDByName(UNKNOWN_ITEM_RESOURCE_ID);
	}
	return iVal;
}

 bool GameConfigFromLuaManager::getEquipmentItem(const int itemId, EquipmentItem* item)
{
	if (false == this->checkConfigLoadFile("ItemConfigTab"))
		return false;

	string Name = "", InlayHole = "", Description = "";
	int Owner, Part,Character, Level, GetPrice, SellPrice, RequiredLevel, Attribute, AttributeFormula,Quality;

	/// get all the filed in the equipment table
	bool isExist = getEquipmentItemFieldById(itemId, "Name", "getEquipmentField", Name);
    isExist &= getEquipmentItemFieldById(itemId, "InlayHole", "getEquipmentField", InlayHole);
	isExist &= getEquipmentItemFieldById(itemId, "Description", "getEquipmentField", Description);
	isExist &= getEquipmentItemFieldById(itemId, "Owner", "getEquipmentField", Owner);
	isExist &= getEquipmentItemFieldById(itemId, "Part", "getEquipmentField", Part);	
	isExist &= getEquipmentItemFieldById(itemId, "Character", "getEquipmentField", Character);
	isExist &= getEquipmentItemFieldById(itemId, "Level", "getEquipmentField", Level);
	isExist &= getEquipmentItemFieldById(itemId, "GetPrice", "getEquipmentField", GetPrice);
	isExist &= getEquipmentItemFieldById(itemId, "SellPrice", "getEquipmentField", SellPrice);
	isExist &= getEquipmentItemFieldById(itemId, "Attribute", "getEquipmentField", Attribute);
	isExist &= getEquipmentItemFieldById(itemId, "AttributeFormula", "getEquipmentField", AttributeFormula);
	isExist &= getEquipmentItemFieldById(itemId, "Quality", "getEquipmentField", Quality);
    if(!isExist)
    {
        return false;
    }
    /// copy to the item
	item->m_attribute = Attribute;
	item->m_ownerType = Owner;
	item->m_equipPart = Part;
	item->m_type = Character;
	item->m_sellprice = SellPrice;
	item->m_byeprice = GetPrice;
	item->m_requiredLevel = Level;
	item->m_quality = Quality;

	sprintf(item->m_szDescription, "%s", Description.c_str());
	sprintf(item->m_name,  "%s", Name.c_str());
	sprintf(item->m_szInlayHole, "%s", InlayHole.c_str());

	return true;
}

bool  GameConfigFromLuaManager::getItem(const int itemId, ItemBase* item)
{
	if (false == this->checkConfigLoadFile("ItemConfigTab"))
		return false;

	string Name = "", InlayHole = "", Description = "";
	int  GetPrice, SellPrice, RequiredLevel, Quality,Type;

	/// get all the filed in the equipment table
	bool isExist = getEquipmentItemFieldById(itemId, "Name", "getItemField", Name);
	isExist &= getEquipmentItemFieldById(itemId, "Description", "getItemField", Description);
	isExist &= getEquipmentItemFieldById(itemId, "GetPrice", "getItemField", GetPrice);
	isExist &= getEquipmentItemFieldById(itemId, "SellPrice", "getItemField", SellPrice);
	isExist &= getEquipmentItemFieldById(itemId, "RequiredLevel", "getItemField", RequiredLevel);
	isExist &= getEquipmentItemFieldById(itemId, "Quality", "getItemField", Quality);
	isExist &= getEquipmentItemFieldById(itemId, "Type", "getItemField", Type);
    if(!isExist)
    {
        return false;
    }
    /// copy to the item
	item->m_type = Type;
	item->m_sellprice = SellPrice;
	item->m_byeprice = GetPrice;
	item->m_requiredLevel = RequiredLevel;
	item->m_quality = Quality;
	item->m_id = itemId;
	sprintf(item->m_szDescription, "%s", Description.c_str());
	sprintf(item->m_name,  "%s", Name.c_str());
	sprintf(item->m_szInlayHole, "%s", InlayHole.c_str());

	return true;
}

 ////////////////////////////////////////////////////////////////////////////////////////////
 ///    monster table
 ////
//const char* GameConfigFromLuaManager::getMonsterDefNameById(const int monsterId) {
//	if (false == this->checkConfigLoadFile("MonsterDefNameConfig"))
//		return 0;
//
//	const char *name = "";
//
//	lua_getglobal(this->m_configLuaState, "getMonsterDefName");
//	lua_pushnumber(this->m_configLuaState, monsterId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getMonsterDefName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return name;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		name = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return name;
//}

bool GameConfigFromLuaManager::checkToolBarTableContent()
{
	if (!this->m_isLoadToolBarTableData) {
		const char *path = GameResourceManager::sharedManager()
			->storedFullPathFromRelativePath("Script/ChatToolLayer.lua");

		unsigned long fileSize = 0;
		unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path, "rt", &fileSize);
		int ret = luaL_dostringEx(this->m_configLuaState, (char*)buffer, fileSize);

		if (ret != 0) {
			CCError("load ToolBar name config file error:%s", lua_tostring(this->m_configLuaState, -1));
			lua_pop(this->m_configLuaState, 1);

			return false;
		}
#ifndef RELOAD_LUA_FILES
		this->m_isLoadToolBarTableData = true;
#endif		
		return true;
	}

	return true;
}

bool GameConfigFromLuaManager::checkSkillUIContent()
{
	if (!this->m_isLoadSkillConfigData) {
		const char *path = GameResourceManager::sharedManager()
			->storedFullPathFromRelativePath("Script/Skill/SkillDataCenter.lua");
		//#ifndef ANDROID
		//		int ret = luaL_dofile(this->m_configLuaState, path);
		//#else
		unsigned long fileSize = 0;
		unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path, "rt", &fileSize);
		int ret = luaL_dostringEx(this->m_configLuaState, (char*)buffer, fileSize);
		//#endif
		if (ret != 0) {
			CCError("load SkillUIContent name config file error:%s", lua_tostring(this->m_configLuaState, -1));
			lua_pop(this->m_configLuaState, 1);

			return false;
		}
#ifndef RELOAD_LUA_FILES
		this->m_isLoadSkillConfigData = true;
#endif		
		return true;
	}

	return true;
}

bool GameConfigFromLuaManager::checkCommonDefineContent()
{
	if (!this->m_isLoadCommonDefineData) {
		const char *path = GameResourceManager::sharedManager()
			->storedFullPathFromRelativePath("Script/CommonDefine.lua");
		//#ifndef ANDROID
		//		int ret = luaL_dofile(this->m_configLuaState, path);
		//#else
		unsigned long fileSize = 0;
		unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path, "rt", &fileSize);
		int ret = luaL_dostringEx(this->m_configLuaState, (char*)buffer, fileSize);
		//#endif
		if (ret != 0) {
			CCError("load checkCommonDefineContent name config file error:%s", lua_tostring(this->m_configLuaState, -1));
			lua_pop(this->m_configLuaState, 1);

			return false;
		}
#ifndef RELOAD_LUA_FILES
		this->m_isLoadCommonDefineData = true;
#endif		
		return true;
	}

	return true;
}

//const char* GameConfigFromLuaManager::getCharacterNameById(const int id)
//{
//	if (false == this->checkConfigLoadFile("characterString"))
//		return NULL;
//
//	const char *name = "";
//
//	lua_getglobal(this->m_configLuaState, "getCharacterField");
//	lua_pushnumber(this->m_configLuaState, id);
//	lua_pushstring(this->m_configLuaState, "Name");
//	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getMonsterDefName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return name;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		name = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return name;
//}
//
//const char* GameConfigFromLuaManager::getCharacterDesById(const int id)
//{
//	if (false == this->checkConfigLoadFile("characterString"))
//		return NULL;
//
//	const char *name = "";
//
//	lua_getglobal(this->m_configLuaState, "getCharacterField");
//	lua_pushnumber(this->m_configLuaState, id);
//	lua_pushstring(this->m_configLuaState, "Description");
//	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getMonsterDefName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return name;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		name = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return name;
//}

/// <summary>
//	获取npc的配置信息
/// </summary>
//const char* GameConfigFromLuaManager::getNpcNameById(const int npcId)
//{
//	if (false == this->checkConfigLoadFile("NpcItemConfigTable"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getNpcName");
//	lua_pushnumber(this->m_configLuaState, npcId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}

//const char* GameConfigFromLuaManager::getNpcMottoById(const int npcId)
//{
//	if (false == this->checkConfigLoadFile("NpcItemConfigTable"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getNpcMotto");
//	lua_pushnumber(this->m_configLuaState, npcId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}

//int GameConfigFromLuaManager::getNpcTypeId(const int npcId)
//{
//	if (false == this->checkConfigLoadFile("NpcItemConfigTable"))
//		return 0;
//
//	unsigned short faceID = 0;
//
//	lua_getglobal(this->m_configLuaState, "getNpcType");
//	lua_pushnumber(this->m_configLuaState, npcId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcType error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return faceID;
//	}
//
//	if (lua_isnumber(this->m_configLuaState, -1)) {
//		faceID = lua_tonumber(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return faceID;
//}

//const char* GameConfigFromLuaManager::getNpcHeadIconName(const int npcId)
//{
//	if (false == this->checkConfigLoadFile("NpcItemConfigTable"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getNpcHeadIcon");
//	lua_pushnumber(this->m_configLuaState, npcId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcHeadIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}

//const char* GameConfigFromLuaManager::getNpcBodyIconName(const int npcId)
//{
//	if (false == this->checkConfigLoadFile("NpcItemConfigTable"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getNpcBodyIcon");
//	lua_pushnumber(this->m_configLuaState, npcId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcBodyIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}

//const char* GameConfigFromLuaManager::getNpcTypeFlagIconName(const int npcId)
//{
//	if (false == this->checkConfigLoadFile("NpcItemConfigTable"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getNpcTypeFlagIcon");
//	lua_pushnumber(this->m_configLuaState, npcId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcTypeFlagIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}

//const char*  GameConfigFromLuaManager::getCharacterHeadPicById(const int id)
//{
//	if (false == this->checkConfigLoadFile("characterString"))
//		return NULL;
//
//	const char *name = "";
//
//	lua_getglobal(this->m_configLuaState, "getCharacterField");
//	lua_pushnumber(this->m_configLuaState, id);
//	lua_pushstring(this->m_configLuaState, "HeadPicture");
//	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getMonsterDefName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return name;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		name = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return name;
//}

//const char* GameConfigFromLuaManager::getCharacterPicFileById(const int id)
//{
//	if (false == this->checkConfigLoadFile("characterString"))
//		return NULL;
//
//	const char *name = "";
//
//	lua_getglobal(this->m_configLuaState, "getCharacterField");
//	lua_pushnumber(this->m_configLuaState, id);
//	lua_pushstring(this->m_configLuaState, "PictureFile");
//	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getMonsterDefName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return name;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		name = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return name;
//}

bool GameConfigFromLuaManager::checkMapMusicContent()
{
	if (!this->m_isLoadMapMusicData)
	{
		const char *path = GameResourceManager::sharedManager()
			->storedFullPathFromRelativePath("Script/GameConfig/MapMusicTable.lua");

		unsigned long fileSize = 0;
		unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path, "rt", &fileSize);
		int ret = luaL_dostringEx(this->m_configLuaState, (char*)buffer, fileSize);
		if (ret != 0) {
			CCLog("load MapMusicTable.lua error:%s", lua_tostring(this->m_configLuaState, -1));
			lua_pop(this->m_configLuaState, 1);
		}

		if(initLuaMusicTable())
		{
			this->m_isLoadMapMusicData = true;
			return true;
		}
	}
	return true;
}

//int GameConfigFromLuaManager::getMusicIdByMapId(const int mapId)
//{
//	if (!this->checkMapMusicContent())
//		return 0;
//
//	int musicId = 0;
//
//	lua_getglobal(this->m_configLuaState, "getMusicId");
//	lua_pushnumber(this->m_configLuaState, mapId);
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getMonsterDefName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return musicId;
//	}
//
//	if (lua_isnumber(this->m_configLuaState, -1)) {
//		musicId = lua_tointeger(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return musicId;
//}

//int GameConfigFromLuaManager::getInstanceType( int mapId)
//{
//	if (false == this->checkConfigLoadFile("InstanceConfigTable"))
//		return NULL;
//
//	int musicId = 0;
//
//	lua_getglobal(this->m_configLuaState, "getMapType");
//	lua_pushnumber(this->m_configLuaState, mapId);
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getMapType error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return musicId;
//	}
//
//	if (lua_isnumber(this->m_configLuaState, -1)) {
//		musicId = lua_tointeger(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return musicId;
//}

//const char* GameConfigFromLuaManager::getInstanceIconName(const int instanceId)
//{
//	if (false == this->checkConfigLoadFile("InstanceConfigTable"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getInstanceIcon");
//	lua_pushnumber(this->m_configLuaState, instanceId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getInstanceIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}

//const char* GameConfigFromLuaManager::getInstanceName(const int instanceId)
//{
//	if (false == this->checkConfigLoadFile("InstanceConfigTable"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getInstanceName");
//	lua_pushnumber(this->m_configLuaState, instanceId);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getInstanceName error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}

/// <summary>
//	多语言本地化
/// </summary>
//const char* GameConfigFromLuaManager::getLocalizationSimpleChinese(const char * flag)
//{
//	if (false == this->checkConfigLoadFile("LocalizationItemGetter"))
//		return "";
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getItemSimpleChinese");
//	lua_pushstring(this->m_configLuaState,flag);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcTypeFlagIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}
//
//const char* GameConfigFromLuaManager::getLocalizationChinese(const char * flag)
//{
//	if (false == this->checkConfigLoadFile("LocalizationItemGetter"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getItemChinese");
//	lua_pushstring(this->m_configLuaState,flag);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcTypeFlagIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}
//
//const char* GameConfigFromLuaManager::getLocalizationEnglish(const char * flag)
//{
//	if (false == this->checkConfigLoadFile("LocalizationItemGetter"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getItemEnglish");
//	lua_pushstring(this->m_configLuaState,flag);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcTypeFlagIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}
//
//const char* GameConfigFromLuaManager::getLocalizationKorean(const char * flag)
//{
//	if (false == this->checkConfigLoadFile("LocalizationItemGetter"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getItemKorean");
//	lua_pushstring(this->m_configLuaState,flag);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcTypeFlagIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}
//
//const char* GameConfigFromLuaManager::getLocalizationJapanese(const char * flag)
//{
//	if (false == this->checkConfigLoadFile("LocalizationItemGetter"))
//		return 0;
//
//	const char *content = "";
//
//	lua_getglobal(this->m_configLuaState, "getItemJapanese");
//	lua_pushstring(this->m_configLuaState,flag);
//
//	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
//	if (ret != 0) {
//		CCLOG("call getNpcTypeFlagIcon error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return content;
//	}
//
//	if (lua_isstring(this->m_configLuaState, -1)) {
//		content = lua_tostring(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return content;
//}

//bool GameConfigFromLuaManager::checkOsCommondMethodContent()
//{
//	if (!this->m_isLoadOsCommonMethodData) {
//		const char *path = GameResourceManager::sharedManager()
//			->storedFullPathFromRelativePath("Script/OsCommonMethod.lua");
//
//		unsigned long fileSize = 0;
//		unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path, "rt", &fileSize);
//		int ret = luaL_dostringEx(this->m_configLuaState, (char*)buffer, fileSize);
//
//		if (ret != 0) {
//			CCLOG("load quest dialog file error:%s", lua_tostring(this->m_configLuaState, -1));
//			lua_pop(this->m_configLuaState, 1);
//		}
//
//		if (ret != 0) {
//			CCLOG("load OsCommondMethodContent file error:%s", lua_tostring(this->m_configLuaState, -1));
//			lua_pop(this->m_configLuaState, 1);
//			return false;
//		}
//
//		this->m_isLoadOsCommonMethodData = true;
//		return true;
//	}
//
//	return true;
//}

//long	GameConfigFromLuaManager::getOsTimeWithTicks()
//{
//	if (false == this->checkOsCommondMethodContent())
//		return NULL;
//
//	int time = 0;
//
//	lua_getglobal(this->m_configLuaState, "GetOSTimeWithMs");
//	int ret = lua_pcall(this->m_configLuaState, 0, 1, 0);
//	if (ret != 0) {
//		CCLOG("call GetOSTimeWithMs error:%s", lua_tostring(this->m_configLuaState, -1));
//		lua_pop(this->m_configLuaState, 1);
//
//		return time;
//	}
//
//	if (lua_isnumber(this->m_configLuaState, -1)) {
//		time = lua_tonumber(this->m_configLuaState, -1);
//	}
//
//	lua_pop(this->m_configLuaState, 1);
//
//	return time;
//}

lua_State* GameConfigFromLuaManager::getMainLuaState()
{
	lua_State* L_state = CCLuaEngine::defaultEngine()->getLuaState();
	std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Script/main.lua");

	unsigned long fileSize = 0;
	unsigned char* buffer = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rt", &fileSize);
	int ret = luaL_dostringEx(L_state, (char*)buffer, fileSize);

	if (ret != 0) {
		CCLOG("getMainLuaState error:%s", lua_tostring(L_state, -1));
		lua_pop(L_state, 1);
		return NULL;
	}
	return L_state;
}

//const char* GameConfigFromLuaManager::getVisionNum()
//{
//	lua_State* L_state = getMainLuaState();
//	const char *content = "";
//	if(L_state)
//	{
//		lua_getglobal(L_state, "getVisionNum");
//		
//		int ret = lua_pcall(L_state, 0, 1, 0);
//		if (ret != 0) {
//			CCLOG("call getVisionNum error:%s", lua_tostring(L_state, -1));
//			lua_pop(L_state, 1);
//			return content;
//		}
//		if (lua_isstring(L_state, -1)) {
//			content = lua_tostring(L_state, -1);
//		}
//		lua_pop(L_state, 1);
//	}
//	
//	return content;	
//}

void GameConfigFromLuaManager::getOneMapMonsterIds(unsigned int mapId,std::vector<unsigned int> &monsterIdVec)
{
	if (false == this->checkConfigLoadFile("MapDataTable"))
		return ;

	monsterIdVec.clear();

	lua_getglobal(this->m_configLuaState, "GetOneMapMonsterIds");
	lua_pushnumber(this->m_configLuaState, mapId);

	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
	if (ret != 0) {
		CCLOG("call getOneMapMonsterIds error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return ;
	}

	if (lua_isboolean(this->m_configLuaState, -1)) {
		bool bSuc = lua_toboolean(this->m_configLuaState, -1);
		if (bSuc == false)
		{
			lua_pop(m_configLuaState, 1);
			return;
		}
	}

	lua_pop(m_configLuaState, 1);

	lua_getglobal(this->m_configLuaState,"G_MonsterTable");
	int nIndex = lua_gettop( m_configLuaState );
	bool bTable = lua_istable(m_configLuaState, -1);
	if (!bTable)
	{
		lua_pop(m_configLuaState, 1);
		return ;
	}
	lua_pushnil( m_configLuaState );
	while( 0 != lua_next( m_configLuaState, -2 ) )
	{
		unsigned int monsterId = (unsigned int)lua_tonumber(m_configLuaState, -1);
		monsterIdVec.push_back(monsterId);
		lua_pop( m_configLuaState, 1 );
	}		
}

int GameConfigFromLuaManager::getExchangeId(int num)
{
	if (!this->checkConfigLoadFile("ItemConfigTab"))
		return 0;

	lua_getglobal(this->m_configLuaState, "getExchangeId");
	lua_pushnumber(this->m_configLuaState, num);
	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
	if (ret != 0) {
		CCLOG("call getExchangeId error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return 0;
	}

	int id = 0;
	if (lua_isnumber(this->m_configLuaState, -1)) {
		id = lua_tointeger(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);
	return id;
}

void GameConfigFromLuaManager::getExchangeItems()
{
	int i = 1;

	string fromItems,toItems;
	int type;

	bool success = true;
	while(success)
	{
		int num = getExchangeId(i);
		success = getExchangeItemFieldById(num, "FromItems", fromItems);
		success &= getExchangeItemFieldById(num, "ToItems", toItems);
		success &= getExchangeItemFieldById(num, "Type",type);	
		
		if(success)
		{
			ItemManager::Get()->addExchangeItem(num,fromItems,toItems,type);
		}
		i++;
	}
	
}

bool GameConfigFromLuaManager::getExchangeItemFieldById(const int itemId, const char* field ,std::string& Val)
{
	if (!this->checkConfigLoadFile("ItemConfigTab"))
		return false;

	lua_getglobal(this->m_configLuaState, "getExchangeField");
	lua_pushnumber(this->m_configLuaState, itemId);
	lua_pushstring(this->m_configLuaState, field);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) {
		CCLOG("call getExchangeItemDesc error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return false;
	}

	if (lua_isstring(this->m_configLuaState, -1)) {
		Val = lua_tostring(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);
	return true;
}

bool GameConfigFromLuaManager::getExchangeItemFieldById(const int itemId, const char* field , int& Val)
{
	if (!this->checkConfigLoadFile("ItemConfigTab"))
		return false;

	lua_getglobal(this->m_configLuaState, "getExchangeField");
	lua_pushnumber(this->m_configLuaState, itemId);
	lua_pushstring(this->m_configLuaState, field);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) {
		CCLOG("call getExchangeItemDesc error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return false;
	}

	if (lua_isnumber(this->m_configLuaState, -1)) {
		Val = lua_tointeger(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);
	return true;
}

TXGUI::UILayout* GameConfigFromLuaManager::InitLayer(CCNode* parentLayer,const char* initFunName)
{
	if (!this->checkToolBarTableContent())
		return false;

	TXGUI::UILayout* pResult = 0;

	lua_getglobal(this->m_configLuaState, initFunName);
	tolua_pushusertype(this->m_configLuaState,(void*)parentLayer,"CCNode");

	int ret = lua_pcall(this->m_configLuaState, 1, 1, 0);
	if (ret != 0) {
		CCLOG("call InitLayer error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return false;
	}

	if (lua_isuserdata(this->m_configLuaState, -1)) {
		pResult = (TXGUI::UILayout*)lua_touserdata(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);
	return pResult;
}

int GameConfigFromLuaManager::getSearchSpiritNpcCost(int npcId)
{
	int result = -1;
	if (!this->checkConfigLoadFile("ItemConfigTab"))
		return result;
	lua_getglobal(this->m_configLuaState, "getSearchSpiritField");
	lua_pushnumber(this->m_configLuaState, npcId);
	lua_pushstring(this->m_configLuaState, "Money");

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) {
		CCLOG("call getSearchSpiritField error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return result;
	}

	if (lua_isnumber(this->m_configLuaState, -1)) {
		result = lua_tointeger(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);
	return result;
}

void GameConfigFromLuaManager::PushSkillItemToLua(unsigned int skillId,unsigned int levelId,unsigned int maxLevel)
{
	if (!this->checkSkillUIContent())
		return ;

	lua_getglobal(this->m_configLuaState, "PushSkillItemToDataCenter");
	lua_pushnumber(this->m_configLuaState, skillId);
	lua_pushnumber(this->m_configLuaState, levelId);
	lua_pushnumber(this->m_configLuaState, maxLevel);

	int ret = lua_pcall(this->m_configLuaState, 3, 1, 0);
	if (ret != 0) {
		CCLOG("call PushSkillItemToLua error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return ;
	}

	lua_pop(this->m_configLuaState, 1);
}

void GameConfigFromLuaManager::InitSkillUIDataCenter()
{
	if (!this->checkSkillUIContent())
		return ;

	lua_getglobal(this->m_configLuaState, "SkillDataCenterInitData");

	int ret = lua_pcall(this->m_configLuaState, 0, 1, 0);
	if (ret != 0) {
		CCLOG("call InitSkillUIDataCenter error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return ;
	}

	lua_pop(this->m_configLuaState, 1);
}

void GameConfigFromLuaManager::PushDiffInfoToLua(unsigned int skill_id,unsigned int skill_level,
	unsigned int next_money,unsigned int next_exploit,unsigned int next_lv,float diff_own_cd,float continue_time_cd,unsigned int diff_hurt,
	unsigned int physical_attack,unsigned int magic_attack,unsigned int skill_attack,unsigned int physical_defence,
	unsigned int magic_defence,unsigned int skill_defence,unsigned int health_point,
	unsigned int accurate,unsigned int dodge,unsigned int wreck,unsigned int parry,unsigned int critical_strike,
	unsigned int tenacity,unsigned int slay,unsigned int speed,unsigned int proficiency)
{
	if (!this->checkSkillUIContent())
		return ;

	lua_getglobal(this->m_configLuaState, "PushDiffInfoToLua");
	lua_pushnumber(this->m_configLuaState, skill_id);
	lua_pushnumber(this->m_configLuaState, skill_level);

	lua_pushnumber(this->m_configLuaState, next_money);
	lua_pushnumber(this->m_configLuaState, next_exploit);
	lua_pushnumber(this->m_configLuaState, next_lv);
	lua_pushnumber(this->m_configLuaState, diff_own_cd);
	lua_pushnumber(this->m_configLuaState, continue_time_cd);
	lua_pushnumber(this->m_configLuaState, diff_hurt);

	lua_pushnumber(this->m_configLuaState, physical_attack);
	lua_pushnumber(this->m_configLuaState, magic_attack);
	lua_pushnumber(this->m_configLuaState, skill_attack);
	lua_pushnumber(this->m_configLuaState, physical_defence);
	lua_pushnumber(this->m_configLuaState, magic_defence);
	lua_pushnumber(this->m_configLuaState, skill_defence);
	lua_pushnumber(this->m_configLuaState, health_point);
	lua_pushnumber(this->m_configLuaState, accurate);
	lua_pushnumber(this->m_configLuaState, dodge);
	lua_pushnumber(this->m_configLuaState, wreck);
	lua_pushnumber(this->m_configLuaState, parry);
	lua_pushnumber(this->m_configLuaState, critical_strike);
	lua_pushnumber(this->m_configLuaState, tenacity);
	lua_pushnumber(this->m_configLuaState, slay);
	lua_pushnumber(this->m_configLuaState, speed);
	lua_pushnumber(this->m_configLuaState, proficiency);

	int ret = lua_pcall(this->m_configLuaState, 24, 1, 0);
	if (ret != 0) 
	{
		CCLOG("call PushDiffInfoToLua error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return ;
	}

	lua_pop(this->m_configLuaState, 1);
}

void GameConfigFromLuaManager::AddUserSkillRspToLua(unsigned int skill_id,unsigned int skill_level)
{
	if (!this->checkSkillUIContent())
		return ;

	lua_getglobal(this->m_configLuaState, "handleMsgAddUserSkillRsp");
	lua_pushnumber(this->m_configLuaState, skill_id);
	lua_pushnumber(this->m_configLuaState, skill_level);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) 
	{
		CCLOG("call AddUserSkillRspToLua error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return ;
	}

	lua_pop(this->m_configLuaState, 1);
}

void GameConfigFromLuaManager::PushSkillSlotInfoToLua(unsigned int slotIndex,unsigned int value)
{
	if (!this->checkSkillUIContent())
		return ;

	lua_getglobal(this->m_configLuaState, "PushSkillSlotInfoToLua");
	lua_pushnumber(this->m_configLuaState, slotIndex - SKILL_SLOT_1 + 1);
	lua_pushnumber(this->m_configLuaState, value);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) 
	{
		CCLOG("call AddUserSkillRspToLua error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return ;
	}

	lua_pop(this->m_configLuaState, 1);
}

void GameConfigFromLuaManager::ListItemDragToSLotItem(unsigned int skillItemIndex,unsigned int slotIndex)
{
	lua_getglobal(this->m_configLuaState, "ListItemDragToSLotItem");
	lua_pushnumber(this->m_configLuaState, skillItemIndex);
	lua_pushnumber(this->m_configLuaState, slotIndex);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) 
	{
		CCLOG("call ListItemDragToSLotItem error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return ;
	}

	lua_pop(this->m_configLuaState, 1);
}

void GameConfigFromLuaManager::SlotItemToSelf(unsigned int preSlotIndex,unsigned int toSlotIndex)
{
	lua_getglobal(this->m_configLuaState, "SlotItemToSelf");
	lua_pushnumber(this->m_configLuaState, preSlotIndex);
	lua_pushnumber(this->m_configLuaState, toSlotIndex);

	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) 
	{
		CCLOG("call SlotItemToSelf error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return ;
	}

	lua_pop(this->m_configLuaState, 1);
}

void GameConfigFromLuaManager::SkillLevelUpSucMessage()
{
	lua_getglobal(this->m_configLuaState, "SkillLevelUpSucMessage");

	int ret = lua_pcall(this->m_configLuaState, 0, 1, 0);
	if (ret != 0) 
	{
		CCLOG("call SkillLevelUpSucMessage error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
		return ;
	}

	lua_pop(this->m_configLuaState, 1);
}

int GameConfigFromLuaManager::getInstanceMusicId(const int raidId,const int mapId)
{
	if(!checkMapMusicContent())
		return 0;

	int musicId = 0;
	lua_getglobal(this->m_configLuaState, "getInstanceMusicId");
	lua_pushnumber(this->m_configLuaState, raidId);
	lua_pushnumber(this->m_configLuaState, mapId);
	int ret = lua_pcall(this->m_configLuaState, 2, 1, 0);
	if (ret != 0) {
		CCLOG("call getInstanceMusicId error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);

		return musicId;
	}

	if (lua_isnumber(this->m_configLuaState, -1)) {
		musicId = lua_tointeger(this->m_configLuaState, -1);
	}

	lua_pop(this->m_configLuaState, 1);

	return musicId;
}

void GameConfigFromLuaManager::PushLayerInstanceToLua(cocos2d::CCLayer* pLayer)
{
	if(!checkCommonDefineContent())
		return ;

	lua_getglobal(this->m_configLuaState, "SetLayerInstance");
	tolua_pushusertype(this->m_configLuaState,(void*)pLayer,"CCLayer");

	int ret = lua_pcall(this->m_configLuaState, 1, 0, 0);
	if (ret != 0) {
		CCLOG("call PushLayerInstanceToLua error:%s", lua_tostring(this->m_configLuaState, -1));
		lua_pop(this->m_configLuaState, 1);
	}
}

bool GameConfigFromLuaManager::initLuaMusicTable()
{
	lua_getglobal(this->m_configLuaState, "initInstanceMusic");
	int ret = lua_pcall(this->m_configLuaState, 0, 0, 0);
	if(ret != 0)
	{
		CCLOG("call initInstanceMusic error:%s", lua_tostring(this->m_configLuaState, -1));
		return false;
	}
	return true;

}

int GameConfigFromLuaManager::table_next(lua_State *L, int i,char **k, char **v)
{
	if ( lua_next(L, i) !=0 )
	{
		*k = (char *)lua_tostring(L, -2);
		*v = (char *)lua_tostring(L, -1);
		lua_pop(L, 1);
		return 1;
	}
	else
	{
		return 0;
	}	
}