#include <libxml/parser.h>
#include "TutorialsDataCenter.h"
#include "GameResourceManager.h"

TutorialDataCenter::TutorialDataCenter()
{
	mIsLoadData = false;
}

TutorialDataCenter::~TutorialDataCenter()
{
	mIdAndTutorialData.clear();
}

void TutorialDataCenter::InitXMLData()
{
	if (mIsLoadData)
	{
		return ;
	}
	mIsLoadData = true;

	const char* pFile = "Data/Tutorials.bin";
	char *xmlString =(char*) GameResourceManager::sharedManager()->loadXml(pFile);
	xmlDocPtr pDoc = xmlReadMemory(xmlString, strlen(xmlString), NULL, "UTF-8", XML_PARSE_RECOVER);
	xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);

	if(pRoot != NULL)
	{
		xmlNodePtr pChildrenNode = pRoot->children;
		while (pChildrenNode != NULL)
		{
			unsigned int id = 0;
			bool isExpansionMainMenu = false;
			OneTutorialData oneTutorialData;

			if(xmlStrcmp(pChildrenNode->name, BAD_CAST"Tutorial") == 0)
			{
				xmlAttrPtr attrPtr = pChildrenNode->properties;

				while (attrPtr != NULL)
				{
					if (!xmlStrcmp(attrPtr->name, BAD_CAST "ID"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "ID");

						id = atoi((const char*)szAttr);
						oneTutorialData.nId = id;

						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "UILayout"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "UILayout");

						oneTutorialData.szUiLayoutName = (const char*)szAttr;
												
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "ControlType"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "ControlType");

						oneTutorialData.szControlType = (const char*)szAttr;

						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "ControlName"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "ControlName");

						oneTutorialData.szControlName = (const char*)szAttr;

						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "ControlTipType"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "ControlTipType");

						oneTutorialData.nTipType = atoi((const char*)szAttr);

						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "ControlTipContent"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "ControlTipContent");

						oneTutorialData.szControlContent = (const char*)szAttr;

						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "ControlTipRelativePt"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "ControlTipRelativePt");

						CCPoint pt;
						std::string tmpStr((const char*)szAttr);
						int endPos = tmpStr.find("/");
						pt.x = atoi(tmpStr.substr(0,endPos).c_str());
						pt.y = atoi(tmpStr.substr(endPos+1,tmpStr.length()-endPos-1).c_str());

						oneTutorialData.relativePoint = pt;
						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "TutorialType"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "TutorialType");

						oneTutorialData.nType = atoi((const char*)szAttr);

						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "nextTutorial"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "nextTutorial");

						oneTutorialData.nNextId = atoi((const char*)szAttr);

						xmlFree(szAttr);
					}
					else if (!xmlStrcmp(attrPtr->name, BAD_CAST "IsExpansionMainMenu"))
					{
						xmlChar* szAttr = xmlGetProp(pChildrenNode,BAD_CAST "IsExpansionMainMenu");

						if (strcmp((const char*)szAttr,"true") == 0)
						{
							isExpansionMainMenu = true;
						}

						xmlFree(szAttr);
					}

					attrPtr = attrPtr->next;
				}

			}

			if (id != 0)
			{
				oneTutorialData.isExpansionMainMenu = isExpansionMainMenu;
				mIdAndTutorialData.insert(std::make_pair(id,oneTutorialData));
			}

			pChildrenNode = pChildrenNode->next;
		}
	}

	free(xmlString);
	xmlFreeDoc(pDoc);

	return ;
}

unsigned int TutorialDataCenter::GetOneTutorialType(unsigned int id)
{
	std::map<unsigned int ,OneTutorialData>::iterator iter = mIdAndTutorialData.find(id);
	if (iter == mIdAndTutorialData.end())
	{
		return 0;
	}

	return (*iter).second.nType;
}