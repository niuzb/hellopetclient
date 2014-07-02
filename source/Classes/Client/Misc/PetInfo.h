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
#include <stdlib.h>
#include "cocos2d.h"


#define PET_PLIST "Data/petDictionary.plist"

using namespace std;


typedef struct stPets_t{
	int numbersID;
	int emblemID;
	int petID;
	char type[KMAX_TYPE_LEN];
}Pets_t;


typedef std::map<int, Pets_t> PetsDictionary;
