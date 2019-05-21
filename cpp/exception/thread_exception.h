#ifndef _PLAT_THREAD_EXCEPTION_
#define _PLAT_THREAD_EXCEPTION_

#include "exception.h"
class ThreadException : Exception
{
public:
	ThreadException()
	{};

	ThreadException(char *msg)
	{
		m_strMsg = msg;
	};

	~ThreadException()
	{};

	string getMsg()
	{
		return	m_strMsg;
	}

public:
	string m_strMsg;
}

#endiif
