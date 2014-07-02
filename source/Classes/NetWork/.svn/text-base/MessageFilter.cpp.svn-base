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
#include "MessageFilter.h"
#include "explorer.h"
#include "OnlineNetworkManager.h"
#include "UserData.h"

#define USE_LOCAL_SERVER   0

char* g_buffer = NULL;
int   g_curPos = 0;

/// handle data send from virtual server!
int VirtualDataReceive(const void* const data, int len)
{
	if (g_curPos + len < 4096)
	{
		memcpy((g_buffer + g_curPos), data, len);
		g_curPos += len;
		return len;
	}else
	{
		return 0;
	}
}


MessageFilter::MessageFilter() : 
m_pExploer(NULL)
,m_bRunning(false)
{
#if USE_LOCAL_SERVER
	/// 截获副本创建包
	m_vecMessages.push_back("CSBattleCreateReq");
	m_vecMessages.push_back("CSBattleLoadCompleteReq");
	m_vecMessages.push_back("CSBattleMoveReq");
	m_vecMessages.push_back("CSBattleLeaveReq");
	m_vecMessages.push_back("CSSkillBeginReq");
	m_vecMessages.push_back("CSPlayerAttackReq");
#endif


	/// init message cached buffer
	g_buffer = new char[4096];
	
}

bool MessageFilter::Init()
{
	/// construct explorer
	BasicUserInfo* pUserInf = (BasicUserInfo*)
		MessageUtil::sShareInstance()->createMessageInstance("BasicUserInfo");

	pUserInf->set_uid(UserData::getUserId());
	pUserInf->set_name(UserData::getUserName());
	pUserInf->set_type(UserData::GetUserType());
	pUserInf->set_gender(0);
	pUserInf->set_lv(UserData::GetUserLevel());
	pUserInf->set_xpos(UserData::GetUserXPos());
	pUserInf->set_ypos(UserData::GetUserYPos());
	pUserInf->set_orient(UserData::GetUserOrient());

	m_pExploer = new Explorer(*pUserInf, VirtualDataReceive);
	delete pUserInf;

	return NULL != m_pExploer;
}

void MessageFilter::Uninit()
{

}

MessageFilter::~MessageFilter()
{
	delete m_pExploer;
	delete g_buffer;
	g_buffer = NULL;
}

void MessageFilter::clock()
{
	if (g_curPos > 0)
	{
		int ret = MessageFilter::Get()->PickBufferData(g_buffer, g_curPos);
		CCAssert(ret > 0, "MessageFilter::PickBufferData Error!");
	}

	/// tick explorer 
	if (m_pExploer)
	{
		m_pExploer->clock();
	}
}


void MessageFilter::PrepareBattleLevel(int level, int map)
{
#if USE_LOCAL_SERVER
	m_pExploer->LoadConfigToMem(level, map);
	/// send message to server , get battle monster configuration from server!
	/// to do...
	m_bRunning = true;

#endif
}

void MessageFilter::ReleaseBattleLevel()
{
#if USE_LOCAL_SERVER
	m_bRunning = false;

	m_pExploer->FreeConfig();
#endif
}

bool MessageFilter::CheckFilterMessage(Message* bodyMsg)
{
	bool bRet = false;

	if (bodyMsg && true == m_bRunning)
	{
		string typeName = bodyMsg->GetTypeName();
		vector<string>::const_iterator itF = m_vecMessages.begin();
		vector<string>::const_iterator itE = m_vecMessages.end();
		while(itF != itE)
		{
			if (*itF == typeName)
			{
				/// existed in the filter messages
				bRet = true;
				break;
			}
			itF++;
		}
	}

	return bRet;
}

void MessageFilter::ProcessMessage(Message* bodyMsg, MessageHeader* headerMsg)
{
	static byte_array_t ba;
	ba.init_postion();

	//////////////////////////////////////////////////////////////////////////
	//encode message to binary stream
	//////////////////////////////////////////////////////////////////////////

	//set header cmd using body msg
	headerMsg->set_msg_name(bodyMsg->GetTypeName());

	if (encodeMessage(headerMsg, bodyMsg, ba) == false)
	{		
		return ;
	}

	//////////////////////////////////////////////////////////////////////////
	//write binary stream to server
	//////////////////////////////////////////////////////////////////////////
	uint32_t totalSize = ba.get_postion();    	
	if (m_pExploer)
	{
		m_pExploer->dispatch(ba.get_buf(), totalSize);
	}
}

//------------------------------------------------------------------------
bool MessageFilter::encodeMessage(MessageHeader* headerMsg, Message* bodyMsg, byte_array_t& outBuffer)
{
	if (headerMsg == NULL || bodyMsg == NULL)	
		return false;


	//write len(u32)
	uint32_t len = 4 + 4 + headerMsg->ByteSize() + bodyMsg->ByteSize();
	outBuffer.write_uint32(htonl(len));

	//write hlen(u32)
	uint32_t hlen = headerMsg->ByteSize() + 4;
	outBuffer.write_int32(htonl(hlen));

	//write header buffer
	char* headerBuffer = NULL;
	int headerLen = 0;
	bool result = MessageUtil::sShareInstance()->encodeMessage2Buffer(headerMsg, headerBuffer, headerLen);
	if (result)
	{
		outBuffer.write_buf(headerBuffer, headerLen);
		delete headerBuffer;
	}
	else
	{
		CCLog("encode header message to buffer error");
		MessageUtil::sShareInstance()->printMessage(headerMsg);

		delete headerBuffer;

		return false;
	}

	//write body buffer
	char* bodyBuffer = NULL;
	int bodyLen = 0;
	result = MessageUtil::sShareInstance()->encodeMessage2Buffer(bodyMsg, bodyBuffer, bodyLen);
	if (result)
	{
		outBuffer.write_buf(bodyBuffer, bodyLen);
		delete bodyBuffer;
	}
	else
	{
		CCLog("encode body message to buffer error");
		MessageUtil::sShareInstance()->printMessage(bodyMsg);

		delete bodyBuffer;

		return false;
	}

	return true;
}

//------------------------------------------------------------------------
bool MessageFilter::decodeMessage(char* inputBuffer, int bufferLen, 
	char*& headerBuffer, 
	int& headerLen,
	char*& bodyBuffer,
	int& bodyLen, 
	int& totalLen)
{
	//package length
	uint32_t* currPackageLen = (uint32_t*)inputBuffer;
	totalLen = ntohl(*currPackageLen);
	inputBuffer += 4;

	//invalid message package
	if (totalLen > bufferLen || totalLen < 12)
	{
		CCLog("invalid message package length : %d", totalLen);				
		return false;
	}

	//head length
	uint32_t* currHeadLen = (uint32_t*)inputBuffer;
	headerLen = ntohl(*currHeadLen) - 4;
	inputBuffer += 4;

	//invalid message header
	if (headerLen > totalLen || headerLen < 0)
	{
		CCLog("invalid message header length : %d", headerLen);	
		return false;
	}

	//head buffer
	headerBuffer = (char*)inputBuffer;	
	inputBuffer += headerLen;

	//body buffer
	bodyBuffer = (char*)inputBuffer;
	bodyLen = totalLen - 4 - 4 - headerLen;
	inputBuffer += bodyLen;

	//invalid message body
	if (bodyLen < 0)
	{
		CCLog("invalid message body length : %d", bodyLen);	
		return false;
	}	

	return true;
}


int MessageFilter::PickBufferData(const void* pbuffer, int nLen)
{
	char* headerBuffer = NULL;
	char* bodyBuffer= NULL;
	int headerLen = 0;
	int bodyLen = 0;
	int totalLen = 0;
	bool result = false;
	
	do{
		result = decodeMessage((char*)pbuffer, nLen, headerBuffer, headerLen, bodyBuffer, bodyLen, totalLen);
		if (result)
		{
			/// call online network manager dispatch message!
			OnlineNetworkManager::sShareInstance()->dispatchMessage(headerBuffer, headerLen, bodyBuffer, bodyLen, 0);
			if (g_curPos - totalLen > 0)
			{
				memmove(g_buffer, g_buffer + totalLen, g_curPos - totalLen);
			}

			g_curPos -= totalLen;
			if (g_curPos < 0)
			{
				CCAssert(0, "impossible!!! why this happen, aha!");
				g_curPos = 0;
			}
		}
	}while(result && g_curPos > 0);

	return nLen - g_curPos;
}