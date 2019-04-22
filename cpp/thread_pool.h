#include <iostream>
#include <pthread.h>
#include <vector>

typedef struct stTask
{
	int nNum
}tagTask;


class CThreadPool
{
public:
	CThreadPool():m_nMaxThreadCount(8)
	{
	};

	~CThreadPool()
	{
	};

	void threadpool_init(const int nCout)
	{
		this.m_nMaxThreadCount = nCount;

	}

	void threadpool_start()
	{
		for ( int i = 0 ; i < m_nMaxThreadCount ; i++ )
		{
			pthread_t thread_obj;
			pthread_create(&thread_obj, NULL, (void *)&)
		}
	}

	void daily_work()
	{
		
	}

	

private:
	int m_nMaxThreadCount;
	vector<pthread_t>;	
}
