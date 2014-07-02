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
#include "NetWorkUtil.h"
#include "proto_encry.h"


#include "MessageHandler.h"
#include "MessageCache.h"


#include "UserData.h"
#include "XLogicManager.h"
#include "MainMenuLayer.h"
#include "cocos2d.h"

#include "MessageFilter.h"
#ifdef WIN32
#include "MessageLog.h"
#endif
#define		REPEAT_SEND_FREE_TIME			0.2f


NetWorkUtil::NetWorkUtil()
	:m_canSend(false)
	,m_tickTime(0.0)
	,m_repeatSendFreeTime(REPEAT_SEND_FREE_TIME)
	,m_bRecvQueueLen(0)
	,m_timeOutEventHandler(NULL)
	,m_timeOutCallBackFun(NULL)
	
{
	
	memset(&m_bSocketInfo, 0, sizeof(SocketInfo_t));
	memset(&m_bRecvQueue, 0, KRecvQueueLen);	
	resetTimeOut();

	m_pMessageCache = new MessageCache();
}


NetWorkUtil::~NetWorkUtil()
{
	delete m_pMessageCache;

	MessageHandler::Destroy();
	MessageUtil::Destroy();
	#ifdef _DEBUG_LOG
	MessageLog::Destroy();
	#endif
	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();
}



//------------------------------------------------------------------------
void NetWorkUtil::connect2Server(const char *ip,const int port,float timeout,int tag)
{	
	
	//	
	memset(&m_bRecvQueue, 0, KRecvQueueLen);

	//
	m_bScoketStatus = KSocketDisconnect;	
	strcpy(m_bSocketInfo.ip, ip);
	m_bSocketInfo.port = port;

	//	
	m_timeOut.tag        = tag;
	m_timeOut.cmd        = "connect2Server";
	m_timeOut.timeout    = timeout;
	
	if(m_bSocket.getSocketID() != -1)
	{
		m_bSocket.CancelSocket();
	}
	m_bSocket.CreateSocket();
	m_bSocket.SetBlockMode(1);
	int ret = m_bSocket.ConnectTo((char*)ip, port);
	//connect error
	if (ret == -1)
	{
		onSockectError(ES_ERR_CONNECT, tag);		
	}

	//
	m_canSend = false;
	tickRepeatSend(0.0, true);
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(NetWorkUtil::update),
		this, 
		0.01f,
		false);		
}

//------------------------------------------------------------------------
void NetWorkUtil::reconnect2Server(float timeout, int tag)
{
	if (strlen(m_bSocketInfo.ip) > 0 && m_bSocketInfo.port != 0) 
	{
		connect2Server(m_bSocketInfo.ip, m_bSocketInfo.port, timeout, tag);
	}
}


//------------------------------------------------------------------------
void NetWorkUtil::cleanServerConnect(bool needReconnect)
{
	CCLog("disconnect, clean data");

	//
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NetWorkUtil::update), this);

	//
	m_canSend = false;
	tickRepeatSend(0.0, true);

	//
	m_bRecvQueueLen = 0;
	memset(m_bRecvQueue, 0, KRecvQueueLen);	

	//
	m_bScoketStatus = KSocketDisconnect;
	m_bSocket.CancelSocket();
	
	//
	resetTimeOut();

	//reconnect later
	if(needReconnect)
	{
		CCLog("scheculed reconnect");
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(NetWorkUtil::scheduleReconnect), this, 10.0, false);
	}
	else
	{
		/// if not need to reconnect , so clean the message cached and reset 
		Reset();
	}
	
}

void NetWorkUtil::Reset()
{
	this->resetTimeOut();
	if (m_pMessageCache)
	{
		m_pMessageCache->clearCacheMessages();
	}
}


//------------------------------------------------------------------------
bool NetWorkUtil::encodeMessage(MessageHeader* headerMsg, Message* bodyMsg, byte_array_t& outBuffer)
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

	//write check sum
	//cur not used
	//outBuffer.write_uint32(htonl(0));

	return true;
}


//------------------------------------------------------------------------
bool NetWorkUtil::decodeMessage(char* inputBuffer, int bufferLen, char*& headerBuffer, int& headerLen,char*& bodyBuffer,
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

	//check sum	
	//uint32_t* checkSum = (uint32_t*)inputBuffer;
	//inputBuffer += 4;
	//check sum valid
	if (false)
	{
		CCLog("check sum failure, drop the package");	
		return false;
	}

	return true;
}



//------------------------------------------------------------------------
MessageHeader* NetWorkUtil::encodeMessageHeader(unsigned int userid, int userRoleTm)
{
	MessageHeader* msgHeader = MessageUtil::sShareInstance()->createMessageHeader();
	CCAssert(msgHeader != NULL, "create message header fail");

	// TODO: check this
	
	msgHeader->set_msg_name("Default");
	//msgHeader->set_uid(userid);
	//msgHeader->set_ret(0);
	//msgHeader->set_seq(0);

	return msgHeader;
}


//------------------------------------------------------------------------
KSendMessageResult NetWorkUtil::sendMessage(MessageHeader* headerMsg, Message* bodyMsg, float timeout, int tag)
{

	CCAssert(headerMsg != NULL, "message header is null");
	CCAssert(bodyMsg != NULL, "message header is null");
    
	/// step 1: filter message if necessary
	/// filter message if possible, this happened when Monster attack message happened!
	/// we just pick up the message and send it to the local Server
	if (MessageFilter::Get()->CheckFilterMessage(bodyMsg))
	{
		MessageFilter::Get()->ProcessMessage(bodyMsg, headerMsg);
		
		return KResultSuccess;
	}

	/// step 2: send it to the remote server
	if (!m_canSend) 
	{
		//CCLog("repeat send package, drop it",headerMsg->msg_type_name().c_str());		
		return KResultCannotSendNow;
	}


	int ret = m_bSocket.CanWrite(5000);	
	if (ret != 0)
	{
        m_canSend = false;
        
		cleanServerConnect(true);

		onSockectError(ES_ERR_SEND, tag);
		return KResultSocketError;
	}

	
	//
	m_canSend = false;
	tickRepeatSend(0.0, true);


	//CCLog("ret=%d ",ret);

	//
	static byte_array_t ba;
	ba.init_postion();

	//////////////////////////////////////////////////////////////////////////
	//encode message to binary stream
	//////////////////////////////////////////////////////////////////////////

	//set header cmd using body msg. 
	headerMsg->set_msg_name(bodyMsg->GetTypeName());

	if (encodeMessage(headerMsg, bodyMsg, ba) == false)
	{		
		return KResultEncodeBufferError;
	}

	//record the msg info into message.log
	//only enabled in win32 platform. jackniu
	#ifdef _DEBUG_LOG
		
		MessageLog::Get()->Write("%-3s %-40s", "In", bodyMsg->GetTypeName().c_str());
	#endif
	//////////////////////////////////////////////////////////////////////////
	//write binary stream to server
	//////////////////////////////////////////////////////////////////////////
	uint32_t totalSize = ba.get_postion();    

	ret = send(m_bSocket.getSocketID(), ba.get_buf(),totalSize, 0);

	//CCLog("error = %d| %s", errno, strerror(errno));

	if (ret == -1 || ret == 0)
	{
		cocos2d::CCLog("send message to server error");
		cleanServerConnect(true);

		onSockectError(ES_ERR_SEND, tag);
		return KResultSocketError;
	}

	//
	m_timeOut.tag        = tag;
	m_timeOut.cmd        = headerMsg->msg_name();
	m_timeOut.timeout    = timeout;

	return KResultSuccess;
}


//------------------------------------------------------------------------
KSendMessageResult NetWorkUtil::sendMessage(MessageHeader* headerMsg, Message* bodyMsg, float timeout, int tag, 
											bool isFailedCache,
											bool cleanUp)
{
	KSendMessageResult result = sendMessage(headerMsg, bodyMsg, timeout, tag);
	if (result != KResultSuccess && isFailedCache && cleanUp)
	{
		m_pMessageCache->addMessage(headerMsg, bodyMsg, timeout, tag);
	}
	else if(cleanUp)
	{
		//
		delete headerMsg;
		delete bodyMsg;
	}

	return result;
}



//------------------------------------------------------------------------
KSendMessageResult NetWorkUtil::sendMessage(Message* bodyMsg,float timeout, int tag, bool isFailedCache, bool cleanUp)
{
	MessageHeader* headerMsg = encodeMessageHeader(UserData::getUserId(), UserData::GetUserInfo().createdTime);

	KSendMessageResult result = sendMessage(headerMsg, bodyMsg, timeout, tag);

	if (result != KResultSuccess && isFailedCache && cleanUp)
	{
		m_pMessageCache->addMessage(headerMsg, bodyMsg, timeout, tag);
	}
	else if(cleanUp)
	{
		//
		delete headerMsg;
		delete bodyMsg;
	}




	return result;
}


//------------------------------------------------------------------------
void NetWorkUtil::dispatchMessage(char *headBuff,int headlen, char *bodyBuff,int bodylen,int tag)
{

	//------------------------------------------------------------------------
	//				parse message header
	//------------------------------------------------------------------------
	MessageHeader* msgHeader = MessageUtil::sShareInstance()->createMessageHeader();
	CCAssert(msgHeader != NULL, "create message header fail");
	MessageUtil::sShareInstance()->decodeBuffer2Message(msgHeader, headBuff, headlen);
		
	std::string cmd = msgHeader->msg_name();

	CCLog("NetWorkUtil::dispatchMessage: %s: ",cmd.c_str());
	//uint32_t uid = msgHeader->;
	uint32_t ret = msgHeader->errcode();
	//uint32_t seq = msgHeader->seq();
	//
	delete msgHeader;

	//------------------------------------------------------------------------
	//					parse message body
	//------------------------------------------------------------------------
	Message* msg = NULL;

	//msg = MessageUtil::sShareInstance()->createMessageInstance(cmd);
	//check error code
	if (ret == 0)
	{
		msg = MessageUtil::sShareInstance()->createMessageInstance(cmd);
	}
	else
	{
		NORMAL_MSG_PACKAGE package;
		package.msg = msg;
		package.header.cmd = cmd;
		//package.header.uid = uid;
		package.header.ret = ret;
		package.header.tag = tag;	
		MessageHandler::sShareInstance()->handleMessage(&package);
		return;
		//msg = MessageUtil::sShareInstance()->createMessageInstance("ErrorCode");
	}

	if (msg)
	{
		//decode buffer to message
		bool result = MessageUtil::sShareInstance()->decodeBuffer2Message(msg, bodyBuff, bodylen);
		if (result == false)
		{
			//fix me there is no err handling jackniu 
			CCLog("decode message buffer error");
		}
		
		//record the msg info into message.log
		//only enabled in win32 platform. jackniu
		#ifdef _DEBUG_LOG
		MessageLog::Get()->Write("%-3s %-40s", "Out", msg->GetTypeName().c_str());
		#endif
       
		//handle message
		NORMAL_MSG_PACKAGE package;
		package.msg = msg;
		package.header.cmd = cmd;
		//package.header.uid = uid;
		//package.header.ret = ret;
		package.header.tag = tag;	
		MessageHandler::sShareInstance()->handleMessage(&package);

		//free msg
		delete msg;
	}
	else
	{
		//handle message
		WILD_MSG_PACKAGE package;
		package.buffer = bodyBuff;
		package.length = bodylen;
		package.header.cmd = cmd;
		//package.header.uid = uid;
		package.header.ret = ret;
		package.header.tag = tag;	
		MessageHandler::sShareInstance()->handleMessage(&package);
	}
	
}


//------------------------------------------------------------------------

void NetWorkUtil::update(float dt)
{
	Timeout_t *timeout = &m_timeOut;
	if (m_bScoketStatus == KSocketDisconnect)
	{
		int ret = m_bSocket.CanWrite(5000);
		//success
		if(ret == 0)
		{
			CCLog("connect to server");

			m_bScoketStatus = KSocketConnecting;
			m_canSend = true;
			tickRepeatSend(0, true);

			onConnectResult(KSocketConnecting, timeout->tag);
		}
		//refuse
		else if(ret == ECONNREFUSED)
		{	

			CCLog("refused by server");			

			int tag = timeout->tag;			

			onConnectResult(KSocketTimeout, tag);
		}
		else if (timeout->timeout > 0.001)
		{
			timeout->timeout -= dt;
			if (timeout->timeout < 0)
			{

				CCLog("connect time out");
				std::string cmd = timeout->cmd;
				int tag = timeout->tag;
                onTimeOut(cmd,tag);
                
                /// send package timeout, so the connection is down, can't send package now!
                /// wait for reconnect!
				m_canSend = false;
				onConnectResult(KSocketTimeout,tag);
			}
		}
	}

	int len = 0;
	if (m_bScoketStatus == KSocketConnecting)
	{
		if (m_bSocket.DataArrival(5000) == 1) 
		{			
			do
			{
				m_bRecvQueueLen += len;
				len = recv(m_bSocket.getSocketID(), m_bRecvQueue + m_bRecvQueueLen , KRecvQueueLen, 0);

			} while (len != -1 && len != 0);
			
			//data read over
			if (len == -1)
			{
				filter();

				m_canSend = true;
				tickRepeatSend(0, true);
			}
			//disconnect
			else if(len == 0)
			{
				
				CCLog("disconnect to server");

				int tag = timeout->tag;
				cleanServerConnect(false);

				m_bScoketStatus = KSocketDisconnect;

				onConnectResult(KSocketTimeout, tag);
			}
		}

		// 先收，后发送，可以解决移动包堆集的问题
		m_pMessageCache->update(dt);

		tickRepeatSend(dt, false);
	}
	
	/////////////////////////////////////////////////////////////////////////////
	///  call clock function of messag filter, see MesssageFilter for more detail
	/// tick message filter!
	MessageFilter::Get()->clock();
}


//------------------------------------------------------------------------
//data format is "len(u32) + hlen(u32) + msghead + msgbody + checksum"
//len(u32) is the length from len(32) to checksum
//hen(u32) is the length from hen(32) to msghead
//------------------------------------------------------------------------
void NetWorkUtil::filter()
{
	while (m_bRecvQueueLen > 0)
	{		
		char* headerBuffer = NULL;
		char* bodyBuffer= NULL;
		int headerLen = 0;
		int bodyLen = 0;
		int totalLen = 0;

		bool result = decodeMessage((char*)m_bRecvQueue, m_bRecvQueueLen, headerBuffer, headerLen, bodyBuffer, bodyLen, totalLen);
		if (result)
		{			
			int tag = m_timeOut.tag;
			resetTimeOut();

			dispatchMessage(headerBuffer, headerLen, bodyBuffer, bodyLen, tag);

			memset(m_bRecvQueue, 0, totalLen);
			m_bRecvQueueLen  -= totalLen;

			if (m_bRecvQueueLen > 0)
				memmove(m_bRecvQueue, m_bRecvQueue + totalLen, m_bRecvQueueLen);						

		}
		else
		{
			CCLog("in-complete package received! continue to receive the data!");
			return;
		}
	}	
}




//------------------------------------------------------------------------
void NetWorkUtil::tickRepeatSend(float dt, bool reset)
{
	if (reset)
	{
		m_tickTime = 0.0;
	}
	else
	{
		if (m_canSend == false)
		{
			m_tickTime += dt;
			if (m_tickTime >= m_repeatSendFreeTime && m_bScoketStatus == KSocketConnecting)
			{
				m_canSend = true;
				m_tickTime = 0.0;
			}
		}
	}
}


//------------------------------------------------------------------------
void NetWorkUtil::registerTimeOutEventHandler(CCObject* handler, SEL_CallFuncND callBackfunc)
{
	m_timeOutEventHandler = NULL;
	m_timeOutCallBackFun = NULL;
}

void NetWorkUtil::onTimeOut(std::string cmd,int tag)
{
    resetTimeOut();
}

//------------------------------------------------------------------------
void NetWorkUtil::onConnectResult(KSocketStatus status, int tag)
{
	cocos2d::CCLog("NetWorkUtil::onConnectResult(%d)", status);
	if (KSocketDisconnect == status || KSocketConnecting == status)
	{
		/// connect to server failed!
		HideWaitingLayer();
	}
    
    if (status == KSocketTimeout)
    {
        resetTimeOut();
        
        /// socket error!
        m_bScoketStatus = KSocketNone;
      
        
        if (m_timeOutEventHandler != NULL && m_timeOutCallBackFun != NULL)
        {
            (m_timeOutEventHandler->*m_timeOutCallBackFun)(NULL, &m_timeOut);
        }
        
        ///没有收到相应的回包，认为收包超时, 网络异常
        FireEvent(&ISocketEvent::OnDisconnect);
    }
}

//------------------------------------------------------------------------
void NetWorkUtil::onSockectError(KSocketError error, int tag)
{
	cocos2d::CCLog("NetWorkUtil::onSockectError(%d)", error);
	
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID 
	CCLog("socket error! ");
	/// on android platform, receive socket error message in stead  of disconnect message
	resetTimeOut();

	/// socket error!
	m_bScoketStatus = KSocketNone;

	if (m_timeOutEventHandler != NULL && m_timeOutCallBackFun != NULL)
	{
		(m_timeOutEventHandler->*m_timeOutCallBackFun)(NULL, &m_timeOut);
	}

	///没有收到相应的回包，认为收包超时, 网络异常
	FireEvent(&ISocketEvent::OnDisconnect);
#endif
}


//------------------------------------------------------------------------
void NetWorkUtil::resetTimeOut()
{
	// CCLog("resetTimeOut: %s",m_timeOut.cmd.c_str());
	m_timeOut.timeout = 0;
	m_timeOut.tag = 0;
	m_timeOut.cmd = "Dummy";
}


//------------------------------------------------------------------------
void NetWorkUtil::scheduleReconnect(float dt)
{
	//
	reconnect2Server(2, 0);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NetWorkUtil::scheduleReconnect), this);	
}


//------------------------------------------------------------------------




//------------------------------------------------------------------------





//------------------------------------------------------------------------


