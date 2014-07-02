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
#ifndef MESSAGE_UTIL_H
#define MESSAGE_UTIL_H

#include <map>
#include "message.h"
#include "cs_basic.pb.h"

using namespace google::protobuf;

//////////////////////////////////////////////////////////////////////////

typedef CSMessageHeader MessageHeader;

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//Message Util
//////////////////////////////////////////////////////////////////////////


class MessageUtil
{

public:

	//////////////////////////////////////////////////////////////////////////
	static MessageUtil*				sShareInstance();
	static void Destroy();
		

	//////////////////////////////////////////////////////////////////////////
	//Message creator
	//////////////////////////////////////////////////////////////////////////	
	Message*						createMessageInstance(const std::string typeName);

	MessageHeader*					createMessageHeader();

	//////////////////////////////////////////////////////////////////////////
	//message encode/decode
	//////////////////////////////////////////////////////////////////////////
	bool							decodeString2Message(Message* msg, const std::string& msgStr);
	bool							decodeBuffer2Message(Message* msg, const char* buffer, const int length);
			

	bool							encodeMessage2Buffer(Message* msg, char*& outBuffer,int& length);
	bool							encodeMessage2String(Message* msg, std::string& str);	

	//////////////////////////////////////////////////////////////////////////
	//Message debug
	//////////////////////////////////////////////////////////////////////////
	void							printMessage(Message* msg);					
	

protected:

	MessageUtil();
	~MessageUtil();
		

private:

	static MessageUtil*				sInstance;	

};


#endif