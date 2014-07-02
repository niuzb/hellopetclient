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
#include "cocos2d.h"
#include "AdvPch.h"

#include <libxml/parser.h>

#include "SpriteDataManager.h"
#include "GameResourceManager.h"


GameSpriteDataManager* GameSpriteDataManager::pSharedManager = NULL;

GameSpriteDataManager::GameSpriteDataManager()
{   
	this->clearAllData();
}

GameSpriteDataManager::~GameSpriteDataManager()
{
	this->clearAllData();
}

GameSpriteDataManager* GameSpriteDataManager::sharedManager()
{
	if(!pSharedManager)
	{
		pSharedManager = new GameSpriteDataManager();

	}
	return pSharedManager;
}

//#pragma mark -- Private Functions

void GameSpriteDataManager::clearAllData() {

	this->m_monstersDic.clear();
}


void GameSpriteDataManager::loadMonsters()
{
	CCLOG("start load monster xml info");
	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml("Data/monsters.xml");

	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);


	xmlNodePtr pMonsterNode = pRoot->children;
	pMonsterNode = pMonsterNode->next;
	while (pMonsterNode != NULL)
	{
		if(xmlStrcmp(pMonsterNode->name, BAD_CAST"Monster")==0)
		{
			Monsters_t monster;

			//by benyang
#ifndef WIN32
			memset(&monster, 0, sizeof(Monsters_t));
#endif
			char *numbersID     = (char*)xmlGetProp(pMonsterNode, BAD_CAST"NumbersID");
			char *id            = (char*)xmlGetProp(pMonsterNode, BAD_CAST"ID");
			char *type          = (char*)xmlGetProp(pMonsterNode, BAD_CAST"Type");
			char *growthType    = (char*)xmlGetProp(pMonsterNode, BAD_CAST"GrowthType");
			char *hp            = (char*)xmlGetProp(pMonsterNode, BAD_CAST"HP");
			char *atk           = (char*)xmlGetProp(pMonsterNode, BAD_CAST"Atk");
			char *def           = (char*)xmlGetProp(pMonsterNode, BAD_CAST"Def");
			char *spAtk         = (char*)xmlGetProp(pMonsterNode, BAD_CAST"SpAtk");
			char *spDef         = (char*)xmlGetProp(pMonsterNode, BAD_CAST"SpDef");
			char *spd           = (char*)xmlGetProp(pMonsterNode, BAD_CAST"Spd");
			char *yieldingExp   = (char*)xmlGetProp(pMonsterNode, BAD_CAST"YieldingExp");
			char *catchRate     = (char*)xmlGetProp(pMonsterNode, BAD_CAST"CatchRate");
			char *yieldingEV    = (char*)xmlGetProp(pMonsterNode, BAD_CAST"YieldingEV");
			char *evolvesFrom   = (char*)xmlGetProp(pMonsterNode, BAD_CAST"EvolvesFrom");
			char *evolvesTo     = (char*)xmlGetProp(pMonsterNode, BAD_CAST"EvolvesTo");
			char *evolvingLv    = NULL;
			evolvingLv          = (char*)xmlGetProp(pMonsterNode, BAD_CAST"EvolvingLv");
			char *height        = (char*)xmlGetProp(pMonsterNode, BAD_CAST"Height");
			char *weight        = (char*)xmlGetProp(pMonsterNode, BAD_CAST"Weight");
			char *features      = (char*)xmlGetProp(pMonsterNode, BAD_CAST"Features");
			char *gender        = (char*)xmlGetProp(pMonsterNode, BAD_CAST"Gender");
			char *freeForbidden = (char*)xmlGetProp(pMonsterNode, BAD_CAST"FreeForbidden");

			monster.numbersID  = atoi(numbersID);
			monster.mID         = atoi(id);
			monster.type        = atoi(type);
			monster.growType    = atoi(growthType);
			monster.hp          = atoi(hp);
			monster.atk         = atoi(atk);
			monster.def         = atoi(def);
			monster.spAtk       = atoi(spAtk);
			monster.spDef       = atoi(spDef);
			monster.spd         = atoi(spd);
			monster.yieldingExp = atoi(yieldingExp);
			monster.catchRate   = atoi(catchRate);
			monster.yieldingEV  = atoi(yieldingEV);
			monster.evolvesFrom = atoi(evolvesFrom);
			monster.evolvesTo   = atoi(evolvesTo);
			if (evolvingLv != NULL) 
			{
				monster.evolvingLv  = atoi(evolvingLv);
				xmlFree(evolvingLv);
			}else
			{
				monster.evolvingLv = 0;
			}


			char *temp;
			temp                = strtok(height, " ");;
			monster.minHeight   = atoi(temp);
			temp                = strtok(NULL, " ");
			monster.maxHeight   = atoi(temp);

			temp                = strtok(weight, " ");
			monster.minWeight   = atoi(temp);
			temp                = strtok(NULL, " ");
			monster.maxWeight   = atoi(temp);


			monster.features    = atoi(features);

			temp                = strtok(gender, " ");
			monster.minGender   = atoi(temp);
			temp                = strtok(NULL, " ");
			monster.maxGender   = atoi(temp);
			monster.freeForbidden = atoi(freeForbidden);

			xmlFree(numbersID);
			xmlFree(id);
			xmlFree(type);
			xmlFree(growthType);
			xmlFree(hp);
			xmlFree(atk);
			xmlFree(def);
			xmlFree(spDef);
			xmlFree(spd);
			xmlFree(yieldingExp);
			xmlFree(catchRate);
			xmlFree(yieldingEV);
			xmlFree(evolvesFrom);
			xmlFree(evolvesTo);

			xmlFree(height);
			xmlFree(weight);
			xmlFree(features);
			xmlFree(gender);
			xmlFree(freeForbidden);
			xmlFree(spAtk);

			xmlNodePtr curNode = pMonsterNode->children;
			curNode = curNode->next;

			m_monstersDic.insert(make_pair(monster.mID, monster));
		}

		pMonsterNode = pMonsterNode->next;
	}
	free(xmlString);
	xmlFreeDoc(pDoc);
	xmlCleanupParser();

	CCLOG("end load monster xml info");
}

void GameSpriteDataManager::loadPets()
{
	CCLOG("start load pet xml dictionary");

	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml("Data/petDictionary.xml");
	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
	xmlNodePtr pMonster = pRoot->children;
	while ((pMonster = pMonster->next)) 
	{
		if (xmlStrcmp(pMonster->name, BAD_CAST"Monster")==0) 
		{
			Pets_t pPets;
			char *pNumbersID    = (char*) xmlGetProp(pMonster, BAD_CAST"NumbersID");
			char *pEmblemID     = (char*) xmlGetProp(pMonster, BAD_CAST"emblemID");
			char *pID           = (char*) xmlGetProp(pMonster, BAD_CAST"ID");

			pPets.numbersID     = atoi(pNumbersID);
			pPets.emblemID      = atoi(pEmblemID);
			pPets.petID         = atoi(pID);
			m_petsDic.insert(make_pair(pPets.petID, pPets));
			xmlFree(pNumbersID);
			xmlFree(pEmblemID);
			xmlFree(pID);
		}
	}

	free(xmlString);
	xmlFreeDoc(pDoc);
	xmlCleanupParser();

	CCLOG("end load pet xml dictionary");
}


void GameSpriteDataManager::loadCharacters()
{

	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml("Data/character.xml");

	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
	xmlNodePtr pCharacter = pRoot->children;
	while ((pCharacter = pCharacter->next)) 
	{
		if (xmlStrcmp(pCharacter->name, BAD_CAST"Character")==0) 
		{
			Characters_t bChar;
			memset(&bChar, 0, sizeof(Characters_t));
			char *bID             = (char*) xmlGetProp(pCharacter, BAD_CAST"ID");
			char *bM_attack       = (char*) xmlGetProp(pCharacter, BAD_CAST"Atk");
			char *bM_defence      = (char*) xmlGetProp(pCharacter, BAD_CAST"Def");
			char *bM_SA           = (char*) xmlGetProp(pCharacter, BAD_CAST"Satk");
			char *bM_SD           = (char*) xmlGetProp(pCharacter, BAD_CAST"Sdef");
			char *bM_speed        = (char*) xmlGetProp(pCharacter, BAD_CAST"Spd");
			bChar.cID             = atoi(bID);
			bChar.atk         = atof(bM_attack);
			bChar.def         = atof(bM_defence);
			bChar.spAtck         = atof(bM_SA);
			bChar.spDef         = atof(bM_SD);
			bChar.speed         = atof(bM_speed);

			m_characterDic.insert(make_pair(bChar.cID, bChar));
			xmlFree(bID);
			xmlFree(bM_attack);
			xmlFree(bM_defence);
			xmlFree(bM_SA);
			xmlFree(bM_SD);
			xmlFree(bM_speed);
		}
	}

	free(xmlString);
	xmlFreeDoc(pDoc);
	xmlCleanupParser();

	//get character name from character.plist,add by august
	const char* pszPath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(CHARACTER_PLIST);
	CCArray *aCharacter = CCFileUtils::arrayWithContentsOfFile(pszPath);
	aCharacter->retain();
	unsigned int size = aCharacter->count();
	for (int i = 0; i < (int)size; i++)
	{
		CCDictionary *character = (CCDictionary*)aCharacter->objectAtIndex(i);
		// read data

	}
	aCharacter->release();
}

Monsters_t* GameSpriteDataManager::getMonsterById(int monsterID) {
	Monsters_t *ret = NULL;
	if (!this->isHaveMonsterInfo(monsterID)) return ret;

	ret = &this->m_monstersDic[monsterID];
	return ret; 
}

int GameSpriteDataManager::getMonsterDicSize() { 
	if(this->m_monstersDic.empty())
	{
		this->loadMonsters();
	}

	return this->m_monstersDic.size();
}

Pets_t* GameSpriteDataManager::getPetById(const int petId) {
	Pets_t *ret = NULL;
	if (!this->isHavePetInfo(petId)) return ret;

	ret = &this->m_petsDic[petId]; 
	return ret; 
}

Characters_t* GameSpriteDataManager::getCharacterByCharacterId(const int characterId) {
	Characters_t *ret = NULL;
	if (!this->isHaveCharacterInfo(characterId)) return ret;

	ret = &this->m_characterDic[characterId];  
	return ret; 
}

size_t GameSpriteDataManager::characterCount() {
	if(this->m_characterDic.empty())
	{
		this->loadCharacters();
	}

    return this->m_characterDic.size();
}

MonstersDictionary& GameSpriteDataManager::getMonstersDic() {
	if (this->m_monstersDic.empty()) {
		this->loadMonsters();
	}

	return this->m_monstersDic;
}


PetsDictionary& GameSpriteDataManager::getPetsDic() {
	return this->m_petsDic;
}


bool GameSpriteDataManager::isHaveMonsterInfo(const int monsterID) {
	if (this->m_monstersDic.empty()) {
		this->loadMonsters();
	}

	return this->m_monstersDic.find(monsterID) != this->m_monstersDic.end();
}

bool GameSpriteDataManager::isHavePetInfo(const int petId) {
	if (this->m_petsDic.empty()) {
		this->loadPets();
	}

	return this->m_petsDic.find(petId) != this->m_petsDic.end();
}


bool GameSpriteDataManager::isHaveCharacterInfo(const int characterId) {
	if (this->m_characterDic.empty()) {
		this->loadCharacters();
	}

	return this->m_characterDic.find(characterId) != this->m_characterDic.end();
}

//const char* GameSpriteDataManager::getMonsterDefNameById(const int monsterId) {
//	return NULL;
//	//return GameConfigFromLuaManager::sharedManager()->getMonsterDefNameById(monsterId);
//}


const char* GameSpriteDataManager::getPetFoundinById(const int petId) {
	return NULL;
	//return GameConfigFromLuaManager::sharedManager()->getPetFoundinById(petId);
}

const char* GameSpriteDataManager::getPetTypeById(const int petId) {
	return NULL;
	//return GameConfigFromLuaManager::sharedManager()->getPetTypeById(petId);
}

const char* GameSpriteDataManager::getPetFeatureById(const int petId) {
	return NULL;
	//return GameConfigFromLuaManager::sharedManager()->getPetFeatureById(petId);
}

const char* GameSpriteDataManager::getPetIntroById(const int petId) {
	return NULL;
	//return GameConfigFromLuaManager::sharedManager()->getPetIntroById(petId);
}
