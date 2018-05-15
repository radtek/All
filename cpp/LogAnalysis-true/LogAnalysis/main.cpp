#include<iostream>
#include<afx.h>
#include<List>
#include<fstream>
#include<windows.h>
#include<string>
#include<assert.h>
#include<time.h>
#include<exception>
#include"ocilib.h"
using namespace std;

#define MT(x)           x

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
	void insert(const char*szPath,OCI_Connection *cn ,OCI_Statement  *st)
	{
		OCI_Prepare(st, MT("insert into loganalysis ")
			MT("( ")
			MT("   threadid,  begintime, filepath, riskpoint, ")
			MT( "   fundid, projectid,combid,stkid,bsflag,timecosum,status ")
			//MT("   threadid,  begintime, filepath, ")
			//MT( "   fundid, projectid,combid,stkid,bsflag,timecosum ")
			MT( ") " )
			MT( "values ")
			MT( "( ")
			MT( "   :val_threadid, :val_begintime, :val_file, :val_riskpoint, ")
			MT( "   :val_fundid, :val_projectid, :val_combid, :val_stkid, :val_bsflag, :val_timecosum,:val_status")
			//MT( "   :val_threadid, :val_begintime, :val_file, ")
			//MT( "   :val_fundid, :val_projectid, :val_combid, :val_stkid, :val_bsflag, :val_timecosum ")
			MT(") "));

		int num_1,num_2,num_3;
		sscanf( m_szFundid, "%d", &num_1 );        
		sscanf( m_szProjectid, "%d", &num_2 );    
		sscanf( m_szCombid, "%d", &num_3 ); 

		char arr_1[2],arr_2[2];
		sprintf_s(arr_1,sizeof(arr_1),"%c",m_cRiskPoint);
		sprintf_s(arr_2,sizeof(arr_2),"%c",m_cStatus);

		OCI_BindString(st, MT(":val_threadid"), (dtext*) m_szThreadId, 8);
		OCI_BindString(st, MT(":val_begintime"), (dtext*) m_szBeginTime, 32);
		OCI_BindString(st, MT(":val_file"), (dtext*) szPath, 1024);
		OCI_BindString(st, MT(":val_riskpoint"), (dtext*) arr_1, 0);
		OCI_BindInt(st, MT(":val_fundid"), &num_1 );
		OCI_BindInt(st, MT(":val_projectid"), &num_2 );
		OCI_BindInt(st, MT(":val_combid"), &num_3 );
		OCI_BindString(st, MT(":val_stkid"), (dtext*) m_szStkid, 32);
		OCI_BindString(st, MT(":val_bsflag"), (dtext*) m_szBsflag, 8);
		OCI_BindString(st, MT(":val_timecosum"), (dtext*) m_szTimeCosum, 32);
		OCI_BindString(st, MT(":val_status"), (dtext*) arr_2, 0);

		try
		{
			OCI_Execute(st);
		}
		catch (CException* e)
		{
			printf("[oci]%s",OCI_ErrorGetString(OCI_GetLastError()));
		}

		OCI_Commit(cn);



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
	if (!instream)
	{
		printf("打开文件失败\n");
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

	Sleep(0);

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


	while (1)
	{
		EnterCriticalSection(&ptr->mutex_file);
		if (!ptr->ls_file.empty())
		{
			LeaveCriticalSection(&ptr->mutex_file);
			break;
		}
		LeaveCriticalSection(&ptr->mutex_file);
	};

	EnterCriticalSection(&ptr->mutex_file);
	string line = ptr->ls_file.front();
	LeaveCriticalSection(&ptr->mutex_file);

	while(line!= string("END"))
	{
		//cout<<i++<<endl;

		//printf("ls_file.size:%d",ptr->ls_file.size());
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

			while (1)
			{
				EnterCriticalSection(&ptr->mutex_file);
				if (!ptr->ls_file.empty())
				{
					LeaveCriticalSection(&ptr->mutex_file);
					break;
				}
				LeaveCriticalSection(&ptr->mutex_file);
			}

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
						//printf("tempobj-->%s,%s",tempObj.m_szThreadId,tempObj.m_szBeginTime);
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
				temp = line.substr(base_point+33,pos-base_point-33);
				set(ptr,temp,szThreadId,5);
			}
			else if(line.find("KpmsRsGetCol(bsflag)") != string::npos)
			{
				string::size_type pos = line.rfind("'");
				temp = line.substr(base_point+34,pos-base_point-34);
				set(ptr,temp,szThreadId,6);
			}
			else if(line.find("[821004]: Runtime") != string::npos)
			{
				temp = line.substr(base_point+18);
				set(ptr,temp,szThreadId,7);
			}
			else if(line.find("[821004]: Exit()") != string::npos)
			{

				//printf("ls_file.size:%d",ptr->ls_file.size());
				//printf("ls_mid.size:%d",ptr->ls_file.size());
				//printf("ls_output.size:%d",ptr->ls_file.size());
				//cout << "test"<<endl;
				EnterCriticalSection(&ptr->mutex_mid);
				for (list<LogDetail>::iterator iter = ptr->ls_mid.begin() ;iter!= ptr->ls_mid.end(); iter++)
				{
					//cout<< iter->m_szThreadId << "--------"<<szThreadId.c_str()<<endl;
					if (strcmp(iter->m_szThreadId,szThreadId.c_str()) == 0)
					{
						LogDetail tempObj; 

						iter->m_cStatus = '1'; //正常结束
						tempObj = *iter;
						ptr->ls_mid.remove(*iter);

						EnterCriticalSection(&ptr->mutex_res);
						//printf("tempobj-->%s,%s",tempObj.m_szThreadId,tempObj.m_szBeginTime);
						ptr->ls_res.push_back(tempObj);
						LeaveCriticalSection(&ptr->mutex_res);
						break;
					}
				}
				LeaveCriticalSection(&ptr->mutex_mid);
			}

			EnterCriticalSection(&ptr->mutex_file);
			ptr->ls_file.pop_front();		
			LeaveCriticalSection(&ptr->mutex_file);

			while (1)
			{
				EnterCriticalSection(&ptr->mutex_file);
				if (!ptr->ls_file.empty())
				{
					LeaveCriticalSection(&ptr->mutex_file);
					break;
				}
				LeaveCriticalSection(&ptr->mutex_file);
			}

			EnterCriticalSection(&ptr->mutex_file);
			line = ptr->ls_file.front();
			LeaveCriticalSection(&ptr->mutex_file);
		}
	}

	//将ls_mid中剩余的置为非正常结束状态插入ls_res
	EnterCriticalSection(&ptr->mutex_mid);
	for (list<LogDetail>::iterator iter = ptr->ls_mid.begin() ;iter!= ptr->ls_mid.end(); iter++)
	{
		LogDetail tempObj; 
		iter->m_cStatus = '2'; //日志不完整,没有找到exit
		ptr->ls_mid.remove(*iter);

		EnterCriticalSection(&ptr->mutex_res);
		ptr->ls_res.push_back(tempObj);
		LeaveCriticalSection(&ptr->mutex_res);
	}
	LeaveCriticalSection(&ptr->mutex_mid);

	//将结束标志置为1，控制输出线程结束
	EnterCriticalSection(&ptr->mutex_flag);
	ptr->m_cEndFlag = '1';
	LeaveCriticalSection(&ptr->mutex_flag);

	return 0;
};

void err_handler(OCI_Error *err)
{
}

DWORD WINAPI output(LPVOID _ptr)
{
	st_param *ptr = (st_param*)_ptr;

	if (!OCI_Initialize(err_handler, NULL, OCI_ENV_DEFAULT))
	{
		printf("oci初始化失败\n");
		return 1;
	}

	OCI_Connection *cn = NULL;
	OCI_Statement  *st = NULL;
	OCI_Resultset  *rs = NULL;

	OCI_EnableWarnings(TRUE);
	cn = OCI_ConnectionCreate("192.168.123.250/orcl", "oci", "oci", OCI_SESSION_DEFAULT);

	if (cn){
		st = OCI_StatementCreate(cn);
	}
	else
	{
		printf("[error]%s",OCI_ErrorGetString(OCI_GetLastError()));
	}

	OCI_ExecuteStmt(st, "select count(*) from user_tables where table_name = 'LOGANALYSIS'");  

	rs = OCI_GetResultset(st);  

	while (OCI_FetchNext(rs))  
	{
		int res = OCI_GetInt(rs, 1);
		if (res == 0)
		{
			OCI_ExecuteStmt(st, 	MT("CREATE TABLE LOGANALYSIS  ( ")
				MT("THREADID           VARCHAR2(8)                    DEFAULT '' NOT NULL,")
				MT("BEGINTIME          VARCHAR2(32)                   DEFAULT '' NOT NULL,")
				MT("FILEPATH           VARCHAR2(1024)                 DEFAULT ' ' ,")
				MT("RISKPOINT          CHAR(1)                        ,")
				MT("FUNDID             INTEGER                        ,")
				MT("PROJECTID          INTEGER                        ,")
				MT("COMBID             INTEGER                        ,")
				MT("STKID              VARCHAR2(32)                   ,")
				MT("BSFLAG             VARCHAR2(8)                    ,")
				MT("TIMECOSUM          VARCHAR2(32)                   ,")
				MT("STATUS             CHAR(1)                        ,")
				MT("CONSTRAINT PK_LOGANALYSIS PRIMARY KEY (THREADID, BEGINTIME, FILEPATH))"));
			OCI_Commit(cn);
		}
	}

	while(1)
	{
		EnterCriticalSection(&ptr->mutex_flag);
		char cEndflag = ptr->m_cEndFlag;
		LeaveCriticalSection(&ptr->mutex_flag);

		EnterCriticalSection(&ptr->mutex_res);
		if (ptr->ls_res.empty() && cEndflag == '1')
		{
			LeaveCriticalSection(&ptr->mutex_res);
			break;
		}
		else 
			LeaveCriticalSection(&ptr->mutex_res);

		EnterCriticalSection(&ptr->mutex_res);
		if (!ptr->ls_res.empty())
		{
			LogDetail obj = ptr->ls_res.front();
			ptr->ls_res.pop_front();
			LeaveCriticalSection(&ptr->mutex_res);

			obj.insert(ptr->m_szPath,cn ,st);
		}
		else
			LeaveCriticalSection(&ptr->mutex_res);
	}

	OCI_Cleanup();

	return 0;
}

void main(int argc,char *argv[])
{
	st_param param;
	strcpy_s(param.m_szPath,sizeof(param.m_szPath),argv[1]);
	InitializeCriticalSection(&param.mutex_file);
	InitializeCriticalSection(&param.mutex_mid);
	InitializeCriticalSection(&param.mutex_res);
	InitializeCriticalSection(&param.mutex_flag);

	clock_t start, finish;  
	double duration;  

	start = clock();  
	DWORD tid_1,tid_2,tid_3;
	HANDLE m_thread_1 = CreateThread(0,0,ReadLog,(LPVOID)&param,0,&tid_1);
	printf("【文件读取线程】已经启动\n");
	HANDLE m_thread_2 = CreateThread(0,0,Analysis,(LPVOID)&param,0,&tid_2);
	printf("【数据分析线程】已经启动\n");
	HANDLE m_thread_3 = CreateThread(0,0,output,(LPVOID)&param,0,&tid_3);
	printf("【数据写入线程】已经启动\n");


	//printf("ls_file:%d,ls_mid:%d,ls_res:%d",param.ls_file.size(),param.ls_mid.size(),param.ls_res.size());
	//Sleep(10);
	//printf("ls_file:%d,ls_mid:%d,ls_res:%d",param.ls_file.size(),param.ls_mid.size(),param.ls_res.size());

	WaitForSingleObject(m_thread_1,INFINITE);
	printf("【文件读取线程】已经结束\n");

	WaitForSingleObject(m_thread_2,INFINITE);
	printf("【数据分析线程】已经结束\n");

	WaitForSingleObject(m_thread_3,INFINITE);
	printf("【数据写入线程】已经结束\n");

	finish = clock();  
	duration = (double)(finish - start) / CLOCKS_PER_SEC;  
	printf( "整体耗时%f seconds/n", duration ); 

	DeleteCriticalSection(&param.mutex_file);
	DeleteCriticalSection(&param.mutex_mid);
	DeleteCriticalSection(&param.mutex_res);
	DeleteCriticalSection(&param.mutex_flag);
	system("pause");
}