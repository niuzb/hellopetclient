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
#pragma once
#include "AdvPch.h"
#include "PetInfo.h"
#include "MonsterInfo.h"
#include "CharacterInfo.h"


class GameSpriteDataManager 
{
public:
	GameSpriteDataManager();
	virtual ~GameSpriteDataManager();

	static GameSpriteDataManager *sharedManager();

	Monsters_t* getMonsterById(const int monsterID);
	int getMonsterDicSize();
	Pets_t* getPetById(const int petId);
	Characters_t* getCharacterByCharacterId(const int characterId);
	size_t characterCount();

	MonstersDictionary& getMonstersDic();
	PetsDictionary& getPetsDic();

	bool isHaveBossInfo(const int bossId);
	bool isHaveMonsterInfo(const int monsterID);
	bool isHavePetInfo(const int petId);
	bool isHaveFeatureInfo(const int featureId);
	bool isHaveCharacterInfo(const int characterId);

	//const char* getMonsterDefNameById(const int monsterId);

	const char* getFeatureNameById(const int featureId);
	const char* getFeatureDescById(const int featureId);

	const char* getPetFoundinById(const int petId);
	const char* getPetTypeById(const int petId);
	const char* getPetFeatureById(const int petId);
	const char* getPetIntroById(const int petId);

private:
	void clearAllData();

	void loadMonsters();
	void loadPets();
	
	void loadCharacters();

private:
	static GameSpriteDataManager* pSharedManager;

	MonstersDictionary m_monstersDic;
	PetsDictionary m_petsDic;
	CharactersDictionary m_characterDic;
};