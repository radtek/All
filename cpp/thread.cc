#include "thread.h"
Thread::Thread(const char* name)
{
	m_strName = name;
	m_hThread = NULL;
	
	ASSIGN_BOOL(itsRunningFlag,false);
	ASSIGN_BOOL(itsSuspendedFlag,false);
	ASSIGN_LONG(itsThreadID,0);
#ifdef WIN32
	InitializeCriticalSection(&m_hMutex);
#else
	pthread_init(&m_hMutex);
#endif
};

Thread::~Thread()
{
	if (m_hThread != NULL)
		stop(true);
#ifdef WIN32
	DeleteCriticalSection(&m_hMutex);
#else
	pthread_exit(&m_hMutex);
#endif
}

const char *Thread::getName()
{
	return m_strName.c_str();
};
	
void Thread::start()
{
	ASSIGN_BOOL(itsRunningFlag, true);
	
#ifdef WIN32
	DWORD tid = 0;
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTIME)_thread_func, (Thread*)this, 0, &tid );
#else
#endif
};

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
