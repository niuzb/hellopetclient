#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#ifndef WIN32
#  include <unistd.h>
#  include <sys/errno.h>
#endif
//#define  DEBUG_SGIP

#ifndef DEF_HP
#ifndef WIN32
#	include  <sys/select.h>
#	include  <sys/socket.h>
#else
#	include "Win32Platform/socket_win32.h"
#endif
#endif
#include "cocos2d.h"
#include "CSocketUtil.h"

CSocketUtil::CSocketUtil()
{
	m_iSocketID = -1;
	//socket创建时间
	time(&m_btim);
	m_iSocketState = 1;
	m_iReadWriteMode = 0;
	memset(m_sLocalIP, 0, sizeof(m_sLocalIP));
	memset(m_sPeerIP, 0, sizeof(m_sPeerIP));
	memset(&m_strAddrIn, 0, sizeof(m_strAddrIn));

#ifdef WIN32
	WSADATA  Ws;

	if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
    {
#ifdef DEBUG_SGIP
		CLogPlus::getInstance()->Log("Init Windows Socket Failed.\n");
#endif
	}
    
#else
    signal(SIGPIPE, SIG_IGN);
    
#endif
}

CSocketUtil::~CSocketUtil()
{
	CancelSocket();
}

/******************************************************************************************************************
 *       函数名称:     CreateSocket
 *       函数描述:     创建一个socket
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     socket句柄
 ******************************************************************************************************************/
int CSocketUtil::CreateSocket()
{
	m_iSocketID = socket(AF_INET, SOCK_STREAM, 0);
	return m_iSocketID;
}
/******************************************************************************************************************
 *       函数名称:     getSocketID
 *       函数描述:      返回socket句柄
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:      socket句柄
 ******************************************************************************************************************/
int CSocketUtil::getSocketID()
{
	return m_iSocketID;
}
/******************************************************************************************************************
 *       函数名称:     CancelSocket
 *       函数描述:     关闭socket连接
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     无
 ******************************************************************************************************************/
void CSocketUtil::CancelSocket()
{
	if (m_iSocketID != -1)
	{
		close(m_iSocketID);
	}
	m_iSocketID = -1;
}

/******************************************************************************************************************
 *       函数名称:     IsSocketClosed
 *       函数描述:     关闭socket连接
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     0表示断开　非０成功
 ******************************************************************************************************************/
int CSocketUtil::IsSocketClosed()
{
    //select
    int iRet=1;
    char sReadBuff[100];
    if (DataArrival()==1) 
    {
         iRet = read(m_iSocketID, sReadBuff, 100);
//        printf("iret=%d",iRet);
    }
    return iRet;
}


/******************************************************************************************************************
 *       函数名称:     ListenOn
 *       函数描述:     设置socket, 在指定的地址和端口上监听
 *       输入参数:     sListenAddr  监听地址
 *                     iPort   监听端口
 *                     iRange  排队数量
 *       输出参数:     无
 *       返 回 值:     0--成功,非0--失败
 ******************************************************************************************************************/
int CSocketUtil::ListenOn(char *sListenAddr, int iPort, int iRange)
{
	int iTemp;
	int optval = 1;
	m_strAddrIn.sin_family = AF_INET;
	m_strAddrIn.sin_port = htons((unsigned short) iPort);

	if ((inet_aton(sListenAddr, &(m_strAddrIn.sin_addr))) == 0)
	{
		return -1;
	}

	if (setsockopt(m_iSocketID, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(optval)) != 0)
	{
        printf("setsockopt SO_REUSEADDR error!\n");
		return -1;
	}

	if (bind(m_iSocketID, (struct sockaddr*) &m_strAddrIn, (int) sizeof(m_strAddrIn)) == -1)
	{
		iTemp = errno;
		printf("Socket bind (%s:%d) error:%s\n", sListenAddr, iPort, strerror(iTemp));
		return -1;
	}

	if (listen(m_iSocketID, iRange) == -1)
	{
		return -2;
	}
	else
	{
		return 0;
	}
}

/******************************************************************************************************************
 *       函数名称:     SetBlockMode
 *       函数描述:     设置socket的阻塞模式
 *       输入参数:     iSyncState   阻塞模式 (0--阻塞,非0--非阻塞)
 *       输出参数:     无
 *       返 回 值:     0--成功,非0--失败
 ******************************************************************************************************************/
int CSocketUtil::SetBlockMode(int iSyncState)
{
	int r = 0; long o = 1; socklen_t ol = sizeof(long);
	r = setsockopt(m_iSocketID, IPPROTO_TCP, TCP_NODELAY, (char*)&o, ol);


	int iBlockFlag;
	// Blocking or not
	if ((iBlockFlag = fcntl(m_iSocketID, F_GETFL, NULL)) == -1)
	{
		return -1;
	}

	if (iSyncState == 0)
		// 同步, 等待返回
		iBlockFlag = iBlockFlag & (~O_NDELAY);
	else
		// 异步, 继续执行
		iBlockFlag = iBlockFlag | O_NDELAY;
	if (fcntl(m_iSocketID, F_SETFL, iBlockFlag) == -1)
		return -1;
	else
		return 0;
}

/******************************************************************************************************************
 *       函数名称:     AcceptSocket
 *       函数描述:     接收请求返回一个对象
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     对象指针
 ******************************************************************************************************************/
CSocketUtil* CSocketUtil::AcceptSocket()
{
	CSocketUtil *sckAccept;
//	int iNewSocketID, iSocketID;

#ifdef _SCO_
	int iLen;
#else
#ifdef DEF_HP
	int iLen;
#else
	socklen_t iLen;
#endif
#endif

	sckAccept = new CSocketUtil();
	if (sckAccept != NULL)
	{
		sckAccept->m_iSocketID = accept(m_iSocketID, (struct sockaddr*) &(m_strAddrIn), &iLen);
	}
	return sckAccept;
}

/******************************************************************************************************************
 *       函数名称:     ReadSocket
 *       函数描述:     读socket数据
 *       输入参数:     sReadData  数据缓冲区地址
 *                     iTimeOut   超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:     读取的长度
 ******************************************************************************************************************/
int CSocketUtil::ReadSocket(char *sReadData, int iLen, int iTimeOut)
{
	if (m_iReadWriteMode == 0 || iTimeOut == 0)
		return ReadByNoTime(sReadData, iLen);
	else if (m_iReadWriteMode == 1)
		return ReadBySelect(sReadData, iLen, iTimeOut);
	else if (m_iReadWriteMode == 2)
		return ReadByAlarm(sReadData, iLen, iTimeOut);
	else
		return ReadByNoTime(sReadData, iLen);
}

/******************************************************************************************************************
 *       函数名称:     SendSocket
 *       函数描述:     发送数据到socket
 *       输入参数:     sWriteData 数据缓冲区地址
 *                     iCount   长度
 *                     iTimeOut  超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:     >0(发送长度)--成功, <0--失败
 ******************************************************************************************************************/
int CSocketUtil::SendSocket(char *sSendData, int iCount, int iTimeOut)
{
	if (m_iReadWriteMode == 0 || iTimeOut == 0)
		return WriteByNoTime(sSendData, iCount);
	else if (m_iReadWriteMode == 1)
		return WriteBySelect(sSendData, iCount, iTimeOut);
	else if (m_iReadWriteMode == 2)
		return WriteByAlarm(sSendData, iCount, iTimeOut);
	else
		return WriteByNoTime(sSendData, iCount);
}

/******************************************************************************************************************
 *       函数名称:     ReadByNoTime
 *       函数描述:     读socket数据
 *       输入参数:     sReadData
 *       输出参数:     无
 *       返 回 值:     读取的长度
 ******************************************************************************************************************/
int CSocketUtil::ReadByNoTime(char *sReadData, int iLen)
{
	int iRet = 0, iCurrRet = 0;
	int iReaded = 0, iLeft = 0;

	iLeft = iLen;

	if (m_iSocketID <= 0)
	{

		return -1;
	}

	while (iLeft > 0)
	{
//        printf("ReadByNoTime");
		//do
		//{
		iRet = read(m_iSocketID, sReadData + iReaded, iLeft);
		//} while (iRet == -1 && errno == EINTR);

		iCurrRet = iRet;

		if (iRet < 0)
		{
			if (errno == EINTR)
			{//超时
				iRet = -3;
				break;
			}
			else
			{//读错
				iRet = -4;
				break;
			}
		}
		else if (iRet == 0)
		{//端口关闭
			iRet = -5;
			break;
		}

		iReaded = iReaded + iRet;
		iLeft = iLeft - iRet;

	}

//	sReadData[iReaded] = '\0';
//    if(iReaded>0)
//        m_delegate->didRecieveData(sReadData);


	//设置返回值

	if (iRet <= 0)
		return iRet;
	else
		return iReaded;
}

/******************************************************************************************************************
 *       函数名称:     WriteByNoTime
 *       函数描述:     发送数据到socket
 *       输入参数:     sWriteData 数据缓冲区地址
 *                     iCount   长度
 *       输出参数:     无
 *       返 回 值:     >0(发送长度)--成功, <0--失败
 ******************************************************************************************************************/
int CSocketUtil::WriteByNoTime(char *sWriteData, int iCount)
{
	int iRet = 0, iCurrRet = 0;
	int iLeft = 0, iWrited = 0;

	iLeft = iCount;

	if (m_iSocketID <= 0)
	{
#ifdef DEBUG_SGIP
		CLogPlus::getInstance()->Log("Socket not connected.\n");
#endif
		return -1;
	}

	while (iLeft > 0)
	{
		iRet = write(m_iSocketID, sWriteData + iWrited, iLeft);

		iCurrRet = iRet;

		if (iRet < 0)
		{
			if (errno == EINTR)
			{/*超时*/
				iRet = -3;
				break;
			}
			else
			{/*写错*/
				iRet = -2;
				break;
			}
		}

		iWrited = iWrited + iRet;
		iLeft = iLeft - iRet;
	}

#ifdef DEBUG_SGIP
	CLogPlus::getInstance()->setPrintDateTime(false);
	CLogPlus::getInstance()->Log("WriteByNoTime Write to:[length = %d][iRet = %d][iCurrRet = %d]\n",iWrited,iRet,iCurrRet);
	CLogPlus::getInstance()->Log("<--------------------------------------------------->.\n");
	for(int i=0; i<iWrited; i++)
	{
		CLogPlus::getInstance()->Log("%u,",sWriteData[i]);
	}
	CLogPlus::getInstance()->Log("\n<--------------------------------------------------->.\n");
	CLogPlus::getInstance()->setPrintDateTime(true);
#endif

	if (iRet <= 0)
		return iRet;
	else
		return iWrited;
}

/******************************************************************************************************************
 *       函数名称:     BindTo
 *       函数描述:     绑定到某IP及端
 *       输入参数:     sConnAddr   连接地址
 *                     iPort       端口
 *       输出参数:     无
 *       返 回 值:     0--成功, 非0--失败
 ******************************************************************************************************************/
int CSocketUtil::BindTo(char *sConnAddr, int iPort)
{
	struct sockaddr_in m_strBindAddr;

	m_strBindAddr.sin_family = AF_INET;
	m_strBindAddr.sin_port = htons((unsigned short) iPort);
	m_strBindAddr.sin_addr.s_addr = inet_addr(sConnAddr);

	if (bind(m_iSocketID, (struct sockaddr*) &(m_strBindAddr), sizeof(m_strBindAddr)) == -1)
		return -1;
	return m_iSocketID;
}

/******************************************************************************************************************
 *       函数名称:     ConnectTo
 *       函数描述:     连接到服务器监听socket
 *       输入参数:     sConnAddr   连接地址
 *                     iPort       端口
 *       输出参数:     无
 *       返 回 值:     0--成功, 非0--失败
 ******************************************************************************************************************/
int CSocketUtil::ConnectTo(char *sConnAddr, int iPort)
{

	m_strAddrIn.sin_family = AF_INET;
	m_strAddrIn.sin_port = htons((unsigned short) iPort);
	m_strAddrIn.sin_addr.s_addr = inet_addr(sConnAddr);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID 
	int set =1 ;
	setsockopt(m_iSocketID, SOL_SOCKET, MSG_NOSIGNAL, &set, sizeof(int));
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    int set =1 ;
    setsockopt(m_iSocketID, SOL_SOCKET, SO_NOSIGPIPE, &set, sizeof(int));
#endif

	if (connect(m_iSocketID, (struct sockaddr*) &(m_strAddrIn), sizeof(m_strAddrIn)) == -1)
	{
		int iError = errno;
		if (iError != EINPROGRESS)
			return -1;
	}
    
	return m_iSocketID;
}

/******************************************************************************************************************
 *       函数名称:     ConnectTo
 *       函数描述:     连接到服务器监听socket(在指定超时时间内)
 *       输入参数:     sConnAddr   连接地址
 *                     iPort       端口
 *                     iOutTime    超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:     0:成功, -1:连接出错,-2:连接超时,-3:系统错
 ******************************************************************************************************************/
int CSocketUtil::ConnectTo(char *sConnAddr, int iPort, int iOutTime)
{
	unsigned long non_blocking = 1;
	unsigned long blocking = 0;
	int error;
	int iResult = 0;

	m_strAddrIn.sin_family = AF_INET;
	m_strAddrIn.sin_port = htons((unsigned short) iPort);
	m_strAddrIn.sin_addr.s_addr = inet_addr(sConnAddr);

	ioctl(m_iSocketID, FIONBIO, &non_blocking);
	//fcntl(m_iSocketID,F_SETFL, O_NONBLOCK);

	iResult = 0;

	if (connect(m_iSocketID, (struct sockaddr*) &(m_strAddrIn), sizeof(m_strAddrIn)) == -1)
	{
		if (errno == EINPROGRESS)
		{// it is in the connect process
			struct timeval timeout;
			fd_set writefds;

			//设置连接超时时间
			timeout.tv_sec = iOutTime; //秒数
			timeout.tv_usec = 0; //毫秒

			FD_ZERO(&writefds);
			FD_SET(m_iSocketID, &writefds);

			if (select(m_iSocketID + 1, NULL, &writefds, NULL, &timeout) > 0)
			{

#ifndef DEF_HP
				socklen_t len = sizeof(int);
#else
				int len = sizeof(int);
#endif
				//下面的一句一定要，主要针对防火墙
				getsockopt(m_iSocketID, SOL_SOCKET, SO_ERROR, (char*)&error, &len);

				if (error == 0)
					iResult = 0; //connect success
				else
					iResult = -1; //error happen
			}
			else
			{
				iResult = -2; //timeout or error happen
			}
		}
		else
		{
			this->CancelSocket();
			iResult = -3; //error happen
		}
	}

	ioctl(m_iSocketID, FIONBIO, &blocking);
	//fcntl(m_iSocketID,F_SETFL, ~O_NONBLOCK);

	return iResult;
}

/******************************************************************************************************************
 *       函数名称:     DataArrival
 *       函数描述:     是否有数据到达
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     1--到达, 0--还没到达
 ******************************************************************************************************************/
int CSocketUtil::DataArrival(int T)
{
	fd_set fdsck;
	struct timeval timeout;

	FD_ZERO(&fdsck);
	//FD_SET((unsigned long)m_iSocketID, &fdsck);
	FD_SET(m_iSocketID, &fdsck);

	timeout.tv_sec = 0;
	timeout.tv_usec = T;
	int nError = select(m_iSocketID + 1, &fdsck, NULL, NULL, &timeout);
    
    /// socket error!
    if (-1 == nError || 0 == nError)
        return -1;


	if (FD_ISSET(m_iSocketID, &fdsck))
		return 1;
	else
		return 0;
}

//@return 61 connected refuse
//        0  success
int  CSocketUtil::CanWrite(int T)
{
    fd_set fdsck;
	struct timeval timeout;
    
	FD_ZERO(&fdsck);
	//FD_SET((unsigned long)m_iSocketID, &fdsck);
	FD_SET(m_iSocketID, &fdsck);
    
	timeout.tv_sec = 0;
	timeout.tv_usec = T;
	select(m_iSocketID + 1,NULL , &fdsck, NULL, &timeout);
	//if (FD_ISSET((unsigned long)m_iSocketID, &fdsck))
	if (FD_ISSET(m_iSocketID, &fdsck))
    {

        int error;
        
        socklen_t len = sizeof(int);

        //下面的一句一定要，主要针对防火墙
        getsockopt(m_iSocketID, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
        
        return error;
    }else
    {
		return -1;
    }
}
/******************************************************************************************************************
 *       函数名称:     SocketBusy
 *       函数描述:     是否可以向socket发送数据
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     1--可以发送, 0--不能发送
 ******************************************************************************************************************/
int CSocketUtil::SocketBusy()
{
	fd_set fdsck;
	struct timeval timeout;

	FD_ZERO(&fdsck);
	//FD_SET((unsigned long)m_iSocketID, &fdsck);
	FD_SET(m_iSocketID, &fdsck);

	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	select(m_iSocketID + 1, NULL, &fdsck, NULL, &timeout);
	//if (FD_ISSET((unsigned long)m_iSocketID, &fdsck))
	if (FD_ISSET(m_iSocketID, &fdsck))
		return 1;
	else
		return 0;
}

/******************************************************************************************************************
 *       函数名称:     TimeOut
 *       函数描述:     socket连接是否超时
 *       输入参数:     iOutTime  超时时间
 *                     iFlag (0--开始时间不变,>0--开始时间从现在开始)
 *       输出参数:     无
 *       返 回 值:     1--超时, 0--不超时
 ******************************************************************************************************************/
int CSocketUtil::TimeOut(int iOutTime, int iFlag)
{
	int iStat = 0;
	time_t nowtim;

	time(&nowtim);
	if ((nowtim - m_btim >= iOutTime) && iFlag == 0)
		iStat = 1;
	if (iFlag > 0)
		m_btim = nowtim;

	return iStat;
}

/******************************************************************************************************************
 *       函数名称:     SendSocketError
 *       函数描述:     发送连接错误信息
 *       输入参数:     sHeadInfo
 *                     iRetCode
 *       输出参数:     无
 *       返 回 值:     无
 ******************************************************************************************************************/
void CSocketUtil::SendSocketError(char *sHeadInfo, int iRetCode)
{
	char sLen[11];

	memset(sLen, 0, sizeof(sLen));

	sprintf(sLen, "%-10d", 3);
	strncpy(sHeadInfo + 10, sLen, 10);
	sprintf(sLen, "%-3d", iRetCode);
	strncpy(sHeadInfo + MSG_HEAD_LEN, sLen, 3);
	sHeadInfo[MSG_HEAD_LEN + 3] = '#';
	sHeadInfo[MSG_HEAD_LEN + 4] = '\0';
	WriteByNoTime(sHeadInfo, strlen(sHeadInfo));

	return;
}

/******************************************************************************************************************
 *       函数名称:     GetSocketLocalIP
 *       函数描述:      取得本地IP:port
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     sLocalIP  本地IP:port
 ******************************************************************************************************************/
char * CSocketUtil::GetSocketLocalIP()
{
#ifdef _SCO_
	int iLen;
#else
#ifdef DEF_HP
	int iLen;
#else
	socklen_t iLen;
#endif
#endif
	char *sTemp;

	if (m_iSocketID <= 0)
		return NULL;

	iLen = sizeof(m_strAddrIn);
	if (getsockname(m_iSocketID, (struct sockaddr*) &m_strAddrIn, &iLen) != 0)
		return NULL;
	sTemp = inet_ntoa(m_strAddrIn.sin_addr);

	sprintf(m_sLocalIP, "%s:%d", sTemp, ntohs(m_strAddrIn.sin_port));

	return m_sLocalIP;
}

/******************************************************************************************************************
 *       函数名称:     GetSocketPeerIP
 *       函数描述:     取得对端IP:port
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     sPeerIP  对端IP:port
 ******************************************************************************************************************/
char * CSocketUtil::GetSocketPeerIP()
{
#ifdef _SCO_
	int iLen;
#else
#ifdef DEF_HP
	int iLen;
#else
	socklen_t iLen;
#endif
#endif
	char *sTemp;

	if (m_iSocketID <= 0)
		return NULL;

	iLen = sizeof(m_strAddrIn);
	if (getpeername(m_iSocketID, (struct sockaddr*) &m_strAddrIn, &iLen) != 0)
		return NULL;
	sTemp = inet_ntoa(m_strAddrIn.sin_addr);

	sprintf(m_sPeerIP, "%s:%d", sTemp, ntohs(m_strAddrIn.sin_port));
	return m_sPeerIP;
}

/******************************************************************************************************************
 *       函数名称:     setReadWriteMode
 *       函数描述:     设置socket读取模式(0--不限时,1--select方式超时,2--alarm方式超时)
 *       输入参数:     iReadWriteMode
 *       输出参数:     无
 *       返 回 值:     无
 ******************************************************************************************************************/
void CSocketUtil::SetReadWriteMode(int iReadWriteMode)
{
	this->m_iReadWriteMode = (iReadWriteMode < 0 || iReadWriteMode > 2) ? 0 : iReadWriteMode;
	return;
}

/******************************************************************************************************************
 *       函数名称:     GetReadWriteMode
 *       函数描述:     返回设置socket读取模式(0--不限时,1--select方式超时,2--alarm方式超时)
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:     socket读取模式
 ******************************************************************************************************************/
int CSocketUtil::GetReadWriteMode()
{
	return this->m_iReadWriteMode;
}

/******************************************************************************************************************
 *       函数名称:     selectTest
 *       函数描述:
 *       输入参数:     iWaitfor
 *                     iMaxTime 超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::selectTest(int iWaitfor, int iMaxTime)
{
	fd_set fdset;
	fd_set *rd = NULL, *wr = NULL;
	struct timeval tmout;
	int iResult;

	FD_ZERO(&fdset);
	FD_SET(m_iSocketID, &fdset);
	if (iWaitfor & WAIT_FOR_READ)
		rd = &fdset;
	if (iWaitfor & WAIT_FOR_WRITE)
		wr = &fdset;

	tmout.tv_sec = iMaxTime;
	tmout.tv_usec = 0;

	do
	{
		iResult = select(m_iSocketID + 1, rd, wr, NULL, &tmout);
	} while (iResult < 0 && errno == EINTR);

	return iResult;
}

/******************************************************************************************************************
 *       函数名称:     pollInterval
 *       函数描述:
 *       输入参数:     iWf
 *                     iTimeOut 超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::pollInterval(int iWf, int iTimeOut)
{
	int iTest;

	if (iTimeOut > 0)
	{
		iTest = this->selectTest(iWf, iTimeOut);
		if (iTest == 0)
			errno = ETIMEDOUT;
		if (iTest <= 0)
			return 0;
	}
	return 1;
}

/******************************************************************************************************************
 *       函数名称:     ReadBySelect
 *       函数描述:
 *       输入参数:     sReadBuff
 *                     iTimeOut  超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::ReadBySelect(char *sReadBuff, int iLen, int iTimeOut)
{
	int iRet = 0, iCurrRet = 0;
	int iReaded = 0, iLeft = 0;

	iLeft = iLen;

	if (m_iSocketID <= 0)
	{
#ifdef DEBUG_SGIP
		CLogPlus::getInstance()->Log("Socket not connected.\n");
#endif
		return -1;
	}

	if (!pollInterval(WAIT_FOR_READ, iTimeOut))
	{
		return 1;
	}

	while (iLeft > 0)
	{
		do
		{
			iRet = read(m_iSocketID, sReadBuff + iReaded, iLeft);
		} while (iRet == -1 && errno == EINTR);

		iCurrRet = iRet;

		if (iRet < 0)
		{
			if (errno == EINTR)
			{//超时
				iRet = -3;
				break;
			}
			else
			{//读错
				iRet = -4;
				break;
			}
		}
		else if (iRet == 0)
		{//端口关闭
			iRet = -5;
			break;
		}

		iReaded = iReaded + iRet;
		iLeft = iLeft - iRet;
	}

	sReadBuff[iReaded] = '\0';

#ifdef DEBUG_SGIP
	CLogPlus::getInstance()->setPrintDateTime(false);
	CLogPlus::getInstance()->Log("ReadBySelect Read from:[length = %d][iRet = %d][iCurrRet = %d]\n",iReaded,iRet,iCurrRet);
	CLogPlus::getInstance()->Log("<--------------------------------------------------->.\n");
	for(int i=0; i<iReaded; i++)
	{
		CLogPlus::getInstance()->Log("%u,",sReadBuff[i]);
	}
	CLogPlus::getInstance()->Log("\n<--------------------------------------------------->.\n");
	CLogPlus::getInstance()->setPrintDateTime(true);
#endif

	//设置返回值
	if (iRet <= 0)
		return iRet;
	else
		return iReaded;
}

/******************************************************************************************************************
 *       函数名称:     WriteBySelect
 *       函数描述:
 *       输入参数:     sWriteBuff
 *                     iBuffSize
 *                     iTimeOut  超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::WriteBySelect(char *sWriteBuff, int iCount, int iTimeOut)
{
	int iRet = 0, iCurrRet = 0;
	int iLeft = 0, iWrited = 0;

	iLeft = iCount;

	if (m_iSocketID <= 0)
	{
#ifdef DEBUG_SGIP
		CLogPlus::getInstance()->Log("Socket not connected.\n");
#endif
		return -1;
	}

	while (iLeft > 0)
	{
		if (!pollInterval(WAIT_FOR_WRITE, iTimeOut))
			return -1;

		do
		{
			iRet = write(m_iSocketID, sWriteBuff + iWrited, iLeft);
		} while (iRet == -1 && errno == EINTR);

		iCurrRet = iRet;

		if (iRet <= 0)
			break;

		iWrited = iWrited + iRet;
		iLeft = iLeft - iRet;
	}

#ifdef DEBUG_SGIP
	CLogPlus::getInstance()->setPrintDateTime(false);
	CLogPlus::getInstance()->Log("WriteBySelect Write to:[length = %d][iRet = %d][iCurrRet = %d]\n",iWrited,iRet,iCurrRet);
	CLogPlus::getInstance()->Log("<--------------------------------------------------->.\n");
	for(int i=0; i<iWrited; i++)
	{
		CLogPlus::getInstance()->Log("%u,",sWriteBuff[i]);
	}
	CLogPlus::getInstance()->Log("\n<--------------------------------------------------->.\n");
	CLogPlus::getInstance()->setPrintDateTime(true);
#endif

	if (iRet <= 0)
		return iRet;
	else
		return iWrited;
}

/******************************************************************************************************************
 *       函数名称:     ReadByAlarm
 *       函数描述:
 *       输入参数:     sReadBuff
 *                     iTimeOut  超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::ReadByAlarm(char *sReadBuff, int iLen, int iTimeOut)
{
	int iRet = 0, iCurrRet = 0;
	int iReaded = 0, iLeft = 0;

	iLeft = iLen;

	if (m_iSocketID <= 0)
	{
#ifdef DEBUG_SGIP
		CLogPlus::getInstance()->Log("Socket not connected.\n");
#endif
		return -1;
	}

// by benyang:need find replacement
#ifndef WIN32
	alarm(iTimeOut);
#endif
	errno = 0;

	while (iLeft > 0)
	{
		do
		{
			iRet = read(m_iSocketID, sReadBuff + iReaded, iLeft);
		} while (iRet == -1 && errno == EINTR);

		iCurrRet = iRet;

		if (iRet < 0)
		{
			if (errno == EINTR)
			{//超时
				iRet = -3;
				break;
			}
			else
			{//读错
				iRet = -4;
				break;
			}
		}
		else if (iRet == 0)
		{//端口关闭
			iRet = -5;
			break;
		}

		iReaded = iReaded + iRet;
		iLeft = iLeft - iRet;
	}

	sReadBuff[iReaded] = '\0';

// by benyang:need find replacement
#ifndef WIN32
	alarm(0);
#endif

#ifdef DEBUG_SGIP
	CLogPlus::getInstance()->setPrintDateTime(false);
	CLogPlus::getInstance()->Log("ReadByAlarm Read from:[length = %d][iRet = %d][iCurrRet = %d]\n",iReaded,iRet,iCurrRet);
	CLogPlus::getInstance()->Log("<--------------------------------------------------->.\n");
	for(int i=0; i<iReaded; i++)
	{
		CLogPlus::getInstance()->Log("%u,",sReadBuff[i]);
	}
	CLogPlus::getInstance()->Log("\n<--------------------------------------------------->.\n");
	CLogPlus::getInstance()->setPrintDateTime(true);
#endif

	//设置返回值
	if (iRet <= 0)
		return iRet;
	else
		return iReaded;
}

/******************************************************************************************************************
 *       函数名称:     WriteByAlarm
 *       函数描述:
 *       输入参数:     sWriteBuff
 *                     iBuffSize
 *                     iTimeOut  超时时间(单位:秒)
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::WriteByAlarm(char *sWriteBuff, int iCount, int iTimeOut)
{
	int iRet = 0, iCurrRet = 0;
	int iLeft = 0, iWrited = 0;

	iLeft = iCount;

	if (m_iSocketID <= 0)
	{
#ifdef DEBUG_SGIP
		CLogPlus::getInstance()->Log("Socket not connected.\n");
#endif
		return -1;
	}

// by benyang:need find replacement
#ifndef WIN32
	alarm(iTimeOut);
#endif
	errno = 0;

	while (iLeft > 0)
	{
		iRet = write(m_iSocketID, sWriteBuff + iWrited, iLeft);

		iCurrRet = iRet;

		if (iRet < 0)
		{
			if (errno == EINTR)
			{/*超时*/
				iRet = -3;
				break;
			}
			else
			{/*写错*/
				iRet = -2;
				break;
			}
		}

		iWrited = iWrited + iRet;
		iLeft = iLeft - iRet;
	}
	
// by benyang:need find replacement
#ifndef WIN32
	alarm(0);
#endif

#ifdef DEBUG_SGIP
	CLogPlus::getInstance()->setPrintDateTime(false);
	CLogPlus::getInstance()->Log("WriteByAlarm Write to:[length = %d][iRet = %d][iCurrRet = %d]\n",iWrited,iRet,iCurrRet);
	CLogPlus::getInstance()->Log("<--------------------------------------------------->.\n");
	for(int i=0; i<iWrited; i++)
	{
		CLogPlus::getInstance()->Log("%u,",sWriteBuff[i]);
	}
	CLogPlus::getInstance()->Log("\n<--------------------------------------------------->.\n");
	CLogPlus::getInstance()->setPrintDateTime(true);
#endif

	if (iRet <= 0)
		return iRet;
	else
		return iWrited;
}

/******************************************************************************************************************
 *       函数名称:     GetMsgBodySize
 *       函数描述:     返回消息体长度
 *       输入参数:     sDataBuff 数据缓冲区地址
 *       输出参数:     无
 *       返 回 值:     消息体长度
 ******************************************************************************************************************/
long CSocketUtil::GetMsgBodySize(char *sDataBuff)
{
	char sLength[MSG_HEAD_LEN + 1];

	memset(sLength, 0, sizeof(sLength));
	strncpy(sLength, sDataBuff, MSG_HEAD_LEN);
	sLength[MSG_HEAD_LEN] = '\0';

	//try
	{
		return atol(sLength);
	}
	//catch(...)
	//{
	//	return (-1);
	//}
}

/******************************************************************************************************************
 *       函数名称:     GetReadBuffSize
 *       函数描述:
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::GetReadBuffSize()
{
	int iSendbuf;

#ifndef DEF_HP
	socklen_t iSendbufSize = sizeof(int);
#else
	int iSendbufSize = sizeof(int);
#endif

	if (getsockopt(m_iSocketID, SOL_SOCKET, SO_SNDBUF, (char*) &iSendbuf, &iSendbufSize) != -1)
		return iSendbuf;
	else
		return -1;
}

/******************************************************************************************************************
 *       函数名称:     SetReadBuffSize
 *       函数描述:
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::SetReadBuffSize(int iBuffsize)
{
	int iSendbuf;

#ifndef DEF_HP
	socklen_t iSendbufSize = sizeof(int);
#else
	int iSendbufSize = sizeof(int);
#endif

	if (getsockopt(m_iSocketID, SOL_SOCKET, SO_SNDBUF, (char*) &iSendbuf, &iSendbufSize) != -1)
	{
		iSendbuf = iBuffsize;
		setsockopt(m_iSocketID, SOL_SOCKET, SO_SNDBUF, (char*) &iSendbuf, iSendbufSize);
	}
	return 0;
}

/******************************************************************************************************************
 *       函数名称:     GetWriteBuffSize
 *       函数描述:
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::GetWriteBuffSize()
{
	int iWritebuf;

#ifndef DEF_HP
	socklen_t iWritebufSize = sizeof(int);
#else
	int iWritebufSize = sizeof(int);
#endif

	if (getsockopt(m_iSocketID, SOL_SOCKET, SO_RCVBUF, (char*) &iWritebuf, &iWritebufSize) != -1)
		return iWritebuf;
	else
		return -1;
}

/******************************************************************************************************************
 *       函数名称:     SetWriteBuffSize
 *       函数描述:
 *       输入参数:     无
 *       输出参数:     无
 *       返 回 值:
 ******************************************************************************************************************/
int CSocketUtil::SetWriteBuffSize(int iBuffsize)
{
	int iWritebuf;

#ifndef DEF_HP
	socklen_t iWritebufSize = sizeof(int);
#else
	int iWritebufSize = sizeof(int);
#endif

	if (getsockopt(m_iSocketID, SOL_SOCKET, SO_RCVBUF, (char*) &iWritebuf, &iWritebufSize) != -1)
	{
		iWritebuf = iBuffsize;
		setsockopt(m_iSocketID, SOL_SOCKET, SO_RCVBUF, (char*) &iWritebuf, iWritebufSize);
	}
	return 0;
}

