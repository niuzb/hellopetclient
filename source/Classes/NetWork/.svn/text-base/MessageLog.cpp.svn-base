#include "MessageLog.h"

#ifdef _DEBUG_LOG


#include <direct.h>
#include <stdio.h>


void MessageLog::OpenFile(const char * strFile, bool bAppend, long lTruncate)
{

	m_lTruncate = lTruncate;
	m_filename = strFile;

	if (!(m_pLogFile = fopen(m_filename, bAppend ? "a" : "w")))
	{
		printf("Failed to open message log file\n");
	}
}

MessageLog::MessageLog()
{
	OpenFile("./message.log", false);
}

/////////////////////////////////
//	Destructor, close if logfile if opened
MessageLog::~MessageLog()
{
	CloseFile();
}
	
void MessageLog::Write(const char * pszFormat, ...)
{

		if (!m_pLogFile)
			return;

		//Trancate if the file grow too large
		long lLength = ftell(m_pLogFile);
		if (lLength > m_lTruncate)
			rewind(m_pLogFile);

		//write the formated log string to szLog
		char szLog[256];
		va_list argList;
		va_start( argList, pszFormat );
		vsnprintf( szLog, 256, pszFormat, argList );
		va_end( argList );

		//Get current time
		time_t timep;
		time (&timep);
		char szLine[1024];
		sprintf(szLine, "%s %s",  szLog, ctime(&timep));		
		fputs(szLine, m_pLogFile);
		fflush(m_pLogFile);

}

void MessageLog::CloseFile()
{
	if (m_pLogFile)
	{
		fputs("\n===============Finish Loging================\n\n", m_pLogFile);

		fclose(m_pLogFile);
	}

	
}

#endif //end of _DEBUG_LOG