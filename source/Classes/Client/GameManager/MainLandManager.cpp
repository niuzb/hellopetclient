#include "GameResourceManager.h"
#include "tinystr.h"
#include "LevelManager.h"
#include "MainLandManager.h"

#ifndef NULL
#define NULL 0
#endif

MainLandManager::MainLandManager()
{   
	mapCityIdAndBasicInfo = new std::map<unsigned int,CityBasicInfo*>();
	mIsDataLoad = false;
}

MainLandManager::~MainLandManager()
{
	for (std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->begin();
		 iter != mapCityIdAndBasicInfo->end();iter++)
	{
		CityBasicInfo * basic_info = (*iter).second;
		CC_SAFE_DELETE(basic_info);
	}
	mapCityIdAndBasicInfo->clear();
	CC_SAFE_DELETE(mapCityIdAndBasicInfo);
}

bool MainLandManager::LoadData()
{
	// Note: 避免数据重复加载
	if (false == mIsDataLoad)
	{
		mIsDataLoad = true;
	}
	else
	{
		return true;
	}

	std::string xmlFilePath = "Data/CityBasicInformation.xml";
	std::string fullFilePath = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(xmlFilePath.c_str());

	unsigned long	_size;
	char			*_pFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(fullFilePath.c_str() , "r", &_size);
	TiXmlDocument	*_document = new TiXmlDocument();
	_document->Parse(_pFileContent, 0, TIXML_ENCODING_UTF8);

	CC_SAFE_DELETE_ARRAY(_pFileContent);

	TiXmlElement *RootElement = _document->RootElement();
	if (RootElement)
	{
		TiXmlElement *childElement = RootElement->FirstChildElement();
		while(childElement)
		{
			CityBasicInfo *cityBasicInfo = new CityBasicInfo();

			unsigned int city_id = 0;
			TiXmlAttribute* pAttribute = childElement->FirstAttribute();
			while(pAttribute)
			{
				std::string strName(pAttribute->Name());
				if (strName == "CityID")
				{
					const char* city_id_str = childElement->Attribute("CityID");
					city_id = atoi(city_id_str);
				}
				else if (strName == "MapID")
				{
					std::string mapIdStr(childElement->Attribute("MapID"));
					cityBasicInfo->map_id = atoi(mapIdStr.c_str());
				}
				else if (strName == "CityName")
				{
					cityBasicInfo->city_name = childElement->Attribute("CityName");
				}
				else if (strName == "HeroBornCoordinate")
				{
					cityBasicInfo->heroBornPoint = getPointAttribute(childElement, "HeroBornCoordinate");
				}
				else if (strName == "NormalRaidTransmissionGate")
				{
					cityBasicInfo->normalRaidTransmissionGate = getPointAttribute(childElement, "NormalRaidTransmissionGate");
				}
				else if (strName == "NormalRaidTransmissionGate")
				{
					cityBasicInfo->normalRaidTransmissionGate = getPointAttribute(childElement, "NormalRaidTransmissionGate");
				}
				else if (strName == "EliteRaidTransmissionGate")
				{
					cityBasicInfo->eliteRaidTransmissionGate = getPointAttribute(childElement, "EliteRaidTransmissionGate");
				}
				else if (strName == "BGMID")
				{
					const char* city_bgm = childElement->Attribute("BGMID");
					cityBasicInfo->backgroundMusicID = atoi(city_bgm);
				}
				else
				{
					int pos = strName.find("TaskNPC");
					if (std::string::npos != pos)
					{
						pos = pos + 6;
						int endPos = strName.rfind("ID");
						int firstNpcId = atoi(strName.substr(pos+1,endPos-pos-1).c_str());

						char buffer[100];
						memset(buffer,0,sizeof(buffer)/sizeof(char));
						sprintf(buffer,"TaskNPC%dID",firstNpcId);
						int npc_id = atoi(childElement->Attribute(buffer));

						NpcBasicInfo npcBasicInfo;

						memset(buffer,0,sizeof(buffer)/sizeof(char));
						sprintf(buffer,"TaskNPC%dposition",firstNpcId);

						std::string npc_pos_str(childElement->Attribute(buffer));
						int midPos = npc_pos_str.find("/");
						float posX = atoi(npc_pos_str.substr(0,midPos).c_str()) * 16;
						float posY = atoi(npc_pos_str.substr(midPos+1,npc_pos_str.length()-midPos-1).c_str()) * 16;

						npcBasicInfo.pos.x = posX;
						npcBasicInfo.pos.y = posY;				

						memset(buffer,0,sizeof(buffer)/sizeof(char));
						sprintf(buffer,"TaskNPC%dflip",firstNpcId);
						const char* bFlip_str = childElement->Attribute(buffer);
						if (bFlip_str != 0)
						{
							int value = atoi(bFlip_str);
							if (value == 1)
							{
								npcBasicInfo.bFlip = true;
							}
						}

						cityBasicInfo->mapNpcIdAndPos->insert(std::make_pair(npc_id,npcBasicInfo));
					}
				}

				pAttribute = pAttribute->Next();
			}
			
			mapCityIdAndBasicInfo->insert(std::make_pair(city_id,cityBasicInfo));

			childElement = childElement->NextSiblingElement();
		}
	}

	delete _document;

	return true;
}

std::map<unsigned int,NpcBasicInfo>* MainLandManager::GetOneCityNpcInfos(unsigned int city_id)
{
	std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->find(city_id);
	if (iter == mapCityIdAndBasicInfo->end())
	{
		return 0;
	}
	return (*iter).second->mapNpcIdAndPos;
}

CCPoint MainLandManager::getCityCell(int cityId, string typeName)
{
	CCPoint cell = ccp(0, 0);
	std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->begin();
	while (iter != mapCityIdAndBasicInfo->end())
	{
		if ((*iter).second->map_id == cityId)
		{
			if (typeName == "born")
			{
				cell = (*iter).second->heroBornPoint;
			}
			else if (typeName == "normalGate")
			{
				cell = (*iter).second->normalRaidTransmissionGate;
			}
			else if (typeName == "eliteGate")
			{
				cell = (*iter).second->eliteRaidTransmissionGate;
			}
			
			break;
		}
		iter++;
	}	
	
	return cell;
}

string MainLandManager::getCityName(int cityId)
{
	string name;
	std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->begin();
	while (iter != mapCityIdAndBasicInfo->end())
	{
		if ((*iter).second->map_id == cityId)
		{
			name = (*iter).second->city_name;
			break;
		}
		iter++;
	}
	return name;
}

bool MainLandManager::isMainLand(int cityId)
{
	bool isMainLand = false;
	if (!cityId)
	{
		isMainLand = true;
	}
	else
	{
		std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->begin();
		while (iter != mapCityIdAndBasicInfo->end())
		{
			if ((*iter).second->map_id == cityId)
			{
				isMainLand = true;
				break;
			}
			iter++;
		}
	}

	return isMainLand;
}

vector<int> MainLandManager::getCityIdList()
{
	vector<int> cityIdList;
	std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->begin();
	while (iter != mapCityIdAndBasicInfo->end())
	{
		cityIdList.push_back((*iter).second->map_id);
		iter++;
	}
	return cityIdList;
}
	
CCPoint MainLandManager::getPointAttribute(TiXmlElement *element, string attStr)
{
	std::string pointStr(element->Attribute(attStr.c_str()));
	int midPos = pointStr.find("/");
	int cellX = atoi(pointStr.substr(0,midPos).c_str());
	int cellY = atoi(pointStr.substr(midPos+1,pointStr.length()-midPos-1).c_str());
	return ccp(cellX, cellY);
}

int MainLandManager::GetCityIdByMapId(int mapId)
{
	std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->begin();
	while(iter != mapCityIdAndBasicInfo->end())
	{
		if (mapId == (*iter).second->map_id)
		{
			return (*iter).first;
		}
		iter++;
	}
	return -1;
}

bool MainLandManager::GetCityIdByNpcId(int npc_id,int &city_Id,int &mapId)
{
	// Note: 首先在自己的城中查找NPC
	int CityIDValue = GetCityIdByMapId(this->curCityId);
	std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->find(CityIDValue);
	if (iter != mapCityIdAndBasicInfo->end())
	{
		CityBasicInfo* pCityInfo = (*iter).second;
		if (pCityInfo)
		{
			std::map<unsigned int,NpcBasicInfo>::iterator npcIter = pCityInfo->mapNpcIdAndPos->find(npc_id);
			if (npcIter != pCityInfo->mapNpcIdAndPos->end())
			{
				mapId = (*iter).second->map_id;
				city_Id = (*iter).first;
				return true;
			}
		}
	}

	//if (bFindNpc == false)
	{
		std::map<unsigned int,CityBasicInfo*>::reverse_iterator reversIter = mapCityIdAndBasicInfo->rbegin();
		while (reversIter != mapCityIdAndBasicInfo->rend())
		{
			int tmpCityId = (*reversIter).first;
			if (IsCityCanGo(tmpCityId))
			{
				CityBasicInfo* pCityInfo = (*reversIter).second;
				if (pCityInfo)
				{
					std::map<unsigned int,NpcBasicInfo>::iterator npcIter = pCityInfo->mapNpcIdAndPos->find(npc_id);
					if (npcIter != pCityInfo->mapNpcIdAndPos->end())
					{
						mapId = (*reversIter).second->map_id;
						city_Id = (*reversIter).first;
						return true;
					}
				}
			}	

			reversIter++;
		}
	}

	return false;
}

bool MainLandManager::GetOneCityNpcPos(int cityId,int npcId, CCPoint &targetPos)
{
	std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->find(cityId);
	if (iter != mapCityIdAndBasicInfo->end())
	{
		CityBasicInfo* pCityInfo = (*iter).second;
		if (pCityInfo)
		{
			std::map<unsigned int,NpcBasicInfo>::iterator npcIter = pCityInfo->mapNpcIdAndPos->find(npcId);
			if (npcIter != pCityInfo->mapNpcIdAndPos->end())
			{
				targetPos = (*npcIter).second.pos;
				return true;
			}
		}
	}

	return false;
}

int MainLandManager::GetCityBGM(int cityId)
{
	int musicId = 0;

	std::map<unsigned int,CityBasicInfo*>::iterator iter = mapCityIdAndBasicInfo->begin();
	while (iter != mapCityIdAndBasicInfo->end())
	{
		if ((*iter).second->map_id == cityId)
		{
			musicId = (*iter).second->backgroundMusicID;		
			break;
		}
		iter++;
	}

	return musicId;
}