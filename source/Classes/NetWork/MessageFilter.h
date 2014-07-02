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
#include <vector>
#include <string>

using namespace std;


#include "Singleton_t.h"
#include "NetWorkUtil.h"




class Explorer;

class MessageFilter : public TSingleton<MessageFilter>
{
public:
	MessageFilter();

	virtual ~MessageFilter();

public:
	/// init 
	bool Init();

	void Uninit();

	/// tick every frame
	void clock();

	/// check current message must be filter by MessageFilter
	/// @note, true mean filter message otherwise false  
	bool	CheckFilterMessage(Message* body);

	/// process current message
	void	ProcessMessage(Message* body, MessageHeader* header);

	///@prototype, PickBufferData()
	// @ pbuffer, -void, buffer used to store 
	// @ nLen, buffer length
	// @ return, return the data copied
    int     PickBufferData(const void* pbuffer, int nLen);

	//// prepare 
	void	PrepareBattleLevel(int level, int map);

	void	ReleaseBattleLevel();

protected:
	/// encode message!
	bool encodeMessage(MessageHeader* headerMsg, Message* bodyMsg, byte_array_t& outBuffer);
	/// decode message!
	bool decodeMessage(char* inputBuffer, int bufferLen, 
		char*& headerBuffer, 
		int& headerLen,
		char*& bodyBuffer,
		int& bodyLen, 
		int& totalLen);

protected:
	vector<string>m_vecMessages;
	Explorer* m_pExploer;

	bool	m_bRunning;
};