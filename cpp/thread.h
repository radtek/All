#ifndef _PLAT_THREAD_
#define _PLAT_THREAD_

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <sys/errno.h>
#endif

class Thread
{
public:
	Thread(const char* name)
	{};

	virtual ~Thread()
	{};

	const char * getName()
	{};
	
	void start();

	virtual void run();

	void suspend();

	void resume();

	void stop(bool cancel=true);

	void running();

	void isRunning();

	bool isSuspended();

	static void sleep(long ms);

	static void shutdownInProgress();

	static bool isShuttingDown();

	static unsigned long threadID();
	
protected:
	void *m_hThread;
	std::string m_strName;
	bool itsRunningFlag;
	bool itsSuspendedFlag;
	long itsThreadID;
}

#endif
