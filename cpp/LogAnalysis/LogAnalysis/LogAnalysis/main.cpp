#include<iostream>
#include<List>
#include<fstream>
#include<windows.h>
#include<string>
#include<assert.h>
#include<time.h>
using namespace std;

class LogDetail
{
public:
	LogDetail()
	{
		clear();
	}
	LogDetail(const char* szBeginTime,const char* szThreadId)
	{	
		clear();
		strcpy_s(m_szBeginTime,sizeof(m_szBeginTime),szBeginTime);
		strcpy_s(m_szThreadId,sizeof(m_szThreadId),szThreadId);
	}
	LogDetail(const string& szBeginTime,const string& szThreadId)
	{
		clear();
		strcpy_s(m_szBeginTime,sizeof(m_szBeginTime),szBeginTime.c_str());
		strcpy_s(m_szThreadId,sizeof(m_szThreadId),szThreadId.c_str());
		
	}
	LogDetail(const LogDetail& C)
    {
		m_cRiskPoint = C.m_cRiskPoint;
		strcpy_s(m_szFundid,sizeof(m_szFundid),C.m_szFundid);
		strcpy_s(m_szProjectid,sizeof(m_szProjectid),C.m_szProjectid);
		strcpy_s(m_szCombid,sizeof(m_szCombid),C.m_szCombid);
		strcpy_s(m_szStkid,sizeof(m_szStkid),C.m_szStkid);
		strcpy_s(m_szBsflag,sizeof(m_szBsflag),C.m_szBsflag);
		strcpy_s(m_szTimeCosum,sizeof(m_szTimeCosum),C.m_szTimeCosum);
		strcpy_s(m_szThreadId,sizeof(m_szThreadId),C.m_szThreadId);
		strcpy_s(m_szBeginTime,sizeof(m_szBeginTime),C.m_szBeginTime);
		m_cStatus = C.m_cStatus;
    }
	LogDetail & operator = (const LogDetail& C)
    {
		m_cRiskPoint = C.m_cRiskPoint;
		strcpy_s(m_szFundid,sizeof(m_szFundid),C.m_szFundid);
		strcpy_s(m_szProjectid,sizeof(m_szProjectid),C.m_szProjectid);
		strcpy_s(m_szCombid,sizeof(m_szCombid),C.m_szCombid);
		strcpy_s(m_szStkid,sizeof(m_szStkid),C.m_szStkid);
		strcpy_s(m_szBsflag,sizeof(m_szBsflag),C.m_szBsflag);
		strcpy_s(m_szTimeCosum,sizeof(m_szTimeCosum),C.m_szTimeCosum);
		strcpy_s(m_szThreadId,sizeof(m_szThreadId),C.m_szThreadId);
		strcpy_s(m_szBeginTime,sizeof(m_szBeginTime),C.m_szBeginTime);
		m_cStatus = C.m_cStatus;
		return *this;
    }
	bool operator == (const LogDetail& d)//重载 ==  
    {  
		return (strcmp(this->m_szThreadId,d.m_szThreadId) == 0);
    }
	void insert(const char*szPath)
	{
		string sql = "insert into loganalysis(threadid,begintime,file,riskpoint,fundid,projectid,combid,stkid,bsflag,timecosum,status) 
			value()";
	}

	void clear()
	{
		m_cRiskPoint = ' ';
		m_szFundid[0] = 0x00;
		m_szProjectid[0] = 0x00;
		m_szCombid[0] = 0x00;
		m_szStkid[0] = 0x00;
		m_szBsflag[0] = 0x00;
		m_szTimeCosum[0] = 0x00;
		m_szThreadId[0] = 0x00;
		m_szBeginTime[0] = 0x00;
		m_cStatus = ' ';
	}
public:
	char m_cRiskPoint;
	char m_szFundid[128];
	char m_szProjectid[128];
	char m_szCombid[128];
	char m_szStkid[128];
	char m_szBsflag[5];
	char m_szTimeCosum[20];
	char m_szThreadId[12];
	char m_szBeginTime[24];
	char m_cStatus;
};

typedef struct st
{
	st()
	{
		m_szPath[0] = 0x00;
		m_cEndFlag = '0';
	};
	char m_szPath[1024];
	char m_cEndFlag;//分析完毕标志
	CRITICAL_SECTION mutex_file;
	CRITICAL_SECTION mutex_mid;
	CRITICAL_SECTION mutex_res;
	CRITICAL_SECTION mutex_flag;
	list<string> ls_file;
	list<LogDetail> ls_mid;
	list<LogDetail> ls_res;
} st_param;

DWORD WINAPI ReadLog(LPVOID _ptr)
{
	st_param *ptr = (st_param*)_ptr;

	ifstream instream(ptr->m_szPath,ios::in);
	if (instream.eof())
	{
		assert("FILE_OPEN_ERROR");
	}
	string line;
	while(getline(instream,line))
	{
		EnterCriticalSection(&ptr->mutex_file);
		ptr->ls_file.push_back(line);
		LeaveCriticalSection(&ptr->mutex_file);
	}
	EnterCriticalSection(&ptr->mutex_file);
	ptr->ls_file.push_back(string("END"));
	LeaveCriticalSection(&ptr->mutex_file);

	return 0;
}
void set(st_param *ptr,const string& sz,const string& szThreadId ,const int &flag)
{
	EnterCriticalSection(&ptr->mutex_mid);
	for (list<LogDetail>::iterator iter = ptr->ls_mid.begin() ;iter!= ptr->ls_mid.end(); iter++)
	{
		if (strcmp(iter->m_szThreadId,szThreadId.c_str()) == 0)
		{
			switch(flag)
			{
				case 1:
					iter->m_cRiskPoint = sz.c_str()[0];
					break;
				case 2:
					strcpy_s(iter->m_szFundid,sizeof(iter->m_szFundid),sz.c_str());
					break;
				case 3:
					strcpy_s(iter->m_szProjectid,sizeof(iter->m_szProjectid),sz.c_str());
					break;
				case 4:
					strcpy_s(iter->m_szCombid,sizeof(iter->m_szCombid),sz.c_str());
					break;
				case 5:
					strcpy_s(iter->m_szStkid,sizeof(iter->m_szStkid),sz.c_str());
					break;
				case 6:
					strcpy_s(iter->m_szBsflag,sizeof(iter->m_szBsflag),sz.c_str());
					break;
				case 7:
					strcpy_s(iter->m_szTimeCosum,sizeof(iter->m_szTimeCosum),sz.c_str());
					break;
				default:
					break;
			}
			break;
		}
	}
	LeaveCriticalSection(&ptr->mutex_mid);

}

DWORD WINAPI Analysis(LPVOID _ptr)
{
	int i = 0;
	st_param *ptr = (st_param*)_ptr;
	
	while (ptr->ls_file.empty())
		;

	EnterCriticalSection(&ptr->mutex_file);
	string line = ptr->ls_file.front();
	LeaveCriticalSection(&ptr->mutex_file);
	//cout<<i<<endl;
	while(line!= string("END"))
	{
		//cout<<i++<<endl;
		string::size_type base_point;
		string szThreadId;
		string temp;
		bool stopFlag = false;

		if (line.find("[821004]: riskid") != string.npos ||
			(base_point = line.find("[821004]")) == string::npos ||
			line.find("[821004]: TryGetValue") != string::npos ||
			line.find("[821004]: exec") != string::npos )
		{
			EnterCriticalSection(&ptr->mutex_file);
			ptr->ls_file.pop_front();		
			LeaveCriticalSection(&ptr->mutex_file);

			while (ptr->ls_file.empty())
			;
			EnterCriticalSection(&ptr->mutex_file);
			line = ptr->ls_file.front();
			LeaveCriticalSection(&ptr->mutex_file);
			stopFlag = true;
		}

		if (!stopFlag)
		{

			szThreadId = line.substr(base_point-5,4);

			//cout<<"test"<<endl;
			if (line.find("Init(XANAME=tradedb, TYPE=DB)") != string::npos)
			{
				string szBeginTime;
				szBeginTime = line.substr(base_point-19,12);

				EnterCriticalSection(&ptr->mutex_mid);
				for (list<LogDetail>::iterator iter = ptr->ls_mid.begin() ;iter!= ptr->ls_mid.end(); iter++)
				{
					if (strcmp(iter->m_szThreadId,szThreadId.c_str()) == 0)
					{
						LogDetail tempObj; 
						
						iter->m_cStatus = '2'; //异常结束
						tempObj = *iter;
						ptr->ls_mid.remove(*iter);
						

						EnterCriticalSection(&ptr->mutex_res);
						ptr->ls_res.push_back(tempObj);
						LeaveCriticalSection(&ptr->mutex_res);
						
						break;
					}
				}
				LeaveCriticalSection(&ptr->mutex_mid);

				LogDetail objLogDetail(szBeginTime,szThreadId);

				EnterCriticalSection(&ptr->mutex_mid);
				ptr->ls_mid.push_back(objLogDetail);
				LeaveCriticalSection(&ptr->mutex_mid);
			}
			else if(line.find("GetValue(riskpoint)") != string::npos)
			{
				temp = line.substr(base_point+33,1);
				set(ptr,temp,szThreadId,1);
			}
			else if(line.find("KpmsRsGetCol(fundid)") != string::npos)
			{
				temp = line.substr(base_point+33);
				set(ptr,temp,szThreadId,2);
			}
			else if(line.find("KpmsRsGetCol(projectid)") != string::npos)
			{
				temp = line.substr(base_point+36);
				set(ptr,temp,szThreadId,3);
			}
			else if(line.find("KpmsRsGetCol(combid)") != string::npos)
			{
				temp = line.substr(base_point+33);
				set(ptr,temp,szThreadId,4);
			}
			else if(line.find("KpmsRsGetCol(stkid)") != string::npos)
			{
				string::size_type pos = line.rfind("'");
				temp = line.substr(base_point+33,pos-base_point+33-1);
				set(ptr,temp,szThreadId,5);
			}
			else if(line.find("KpmsRsGetCol(bsflag)") != string::npos)
			{
				string::size_type pos = line.rfind("'");
				temp = line.substr(base_point+34,pos-base_point+34-1);
				set(ptr,temp,szThreadId,6);
			}
			else if(line.find("[821004]: Runtime") != string::npos)
			{
				temp = line.substr(base_point+18);
				set(ptr,temp,szThreadId,2);
			}
			else if(line.find("[821004]: Exit()") != string::npos)
			{
				//cout << "test"<<endl;
				EnterCriticalSection(&ptr->mutex_mid);
				for (list<LogDetail>::iterator iter = ptr->ls_mid.begin() ;iter!= ptr->ls_mid.end(); iter++)
				{
					//cout<< iter->m_szThreadId << "--------"<<szThreadId.c_str()<<endl;
					if (strcmp(iter->m_szThreadId,szThreadId.c_str()) == 0)
					{
						LogDetail tempObj; 
						
						iter->m_cStatus = '1'; //正常结束
						ptr->ls_mid.remove(*iter);
						
						EnterCriticalSection(&ptr->mutex_res);
						ptr->ls_res.push_back(tempObj);
						LeaveCriticalSection(&ptr->mutex_res);

						/*cout<<"["<<iter->m_cRiskPoint<< "]["<<
							iter->m_szFundid<< "]["<<
							iter->m_szProjectid<< "]["<<
							iter->m_szCombid<< "]["<<
							iter->m_szStkid<< "]["<<
							iter->m_szBsflag<< "]["<<
							iter->m_szTimeCosum<< "]["<<
							iter->m_szThreadId<< "]["<<
							iter->m_szBeginTime<< "]["<<
							iter->m_cStatus<<"]"<<endl;*/
						break;
					}
				}
				LeaveCriticalSection(&ptr->mutex_mid);
			}

			EnterCriticalSection(&ptr->mutex_file);
			ptr->ls_file.pop_front();		
			LeaveCriticalSection(&ptr->mutex_file);

			while (ptr->ls_file.empty())
			;
			EnterCriticalSection(&ptr->mutex_file);
			line = ptr->ls_file.front();
			LeaveCriticalSection(&ptr->mutex_file);
		}
	}
	EnterCriticalSection(&ptr->mutex_flag);
	ptr->m_cEndFlag = '1';
	LeaveCriticalSection(&ptr->mutex_flag);
	return 0;
};


DWORD WINAPI output(LPVOID _ptr)
{
	st_param *ptr = (st_param*)_ptr;

	while(1)
	{
		EnterCriticalSection(&ptr->mutex_flag);
		cEndflag = ptr->m_cEndFlag;
		LeaveCriticalSection(&ptr->mutex_flag);

		while (ptr->ls_res.empty() && cEndflag = '0')
			;

		EnterCriticalSection(&ptr->mutex_res);
		LogDetail obj = ptr->ls_res.front();
		LeaveCriticalSection(&ptr->mutex_res);


		if (ptr->ls_res.empty() && cEndflag == '1')
		{
			break;
		}	
	}
	
	return 0;
}

void main()
{
	st_param param;
	strcpy_s(param.m_szPath,sizeof(param.m_szPath),"test.log");
	InitializeCriticalSection(&param.mutex_file);
	InitializeCriticalSection(&param.mutex_mid);
	InitializeCriticalSection(&param.mutex_res);

	clock_t start, finish;  
	double duration;  


	start = clock();  
	DWORD tid_1,tid_2,tid_3;
	HANDLE m_thread_1 = CreateThread(0,0,ReadLog,(LPVOID)&param,0,&tid_1);

	HANDLE m_thread_2 = CreateThread(0,0,Analysis,(LPVOID)&param,0,&tid_2);

	WaitForSingleObject(m_thread_1,INFINITE);
	WaitForSingleObject(m_thread_2,INFINITE);

	finish = clock();  
	duration = (double)(finish - start) / CLOCKS_PER_SEC;  
	printf( "%f seconds/n", duration ); 

	DeleteCriticalSection(&param.mutex_file);
	DeleteCriticalSection(&param.mutex_mid);
	DeleteCriticalSection(&param.mutex_res);
	system("pause");
}