#ifndef  _TRANSLATE_MODULE_
#define  _TRANSLATE_MODULE_
#include <stdio.h>
#include "kdt_translate_head.h"

#ifdef  _MSC_VER
#include<string.h>
#include<winhttp.h>
#include "WinhHttpClient.h"
#else
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#endif //_MSC_VER



typedef struct
{
	void init()
	{
		appid = ptr->m_szAppId;
		from = ptr->m_szLanguageFrom;
		to = ptr->m_szLanguageTo;
		secret_key = ptr->m_szSecret_key;
	}
	

	void getUrl(const char* szTarget,char *szUrl,int nSize)
	{
		if (nSize < 256)
			return;

		strcpy(szUrl, "http://api.fanyi.baidu.com/api/trans/vip/translate?")
		char *q = szTarget;
		char salt[60];
		int a = rand();
		sprintf(salt, "%d", a);
		char sign[120] = "";
		strcat(sign, appid);
		strcat(sign, q);
		strcat(sign, salt);
		strcat(sign, secret_key);

		unsigned char md[16];
		int i;
		char tmp[3] = { '\0' }, buf[33] = { '\0' };
		MD5((unsigned char *)sign, strlen((unsigned char *)sign), md);
		for (i = 0; i < 16; i++){
			sprintf(tmp, "%2.2x", md[i]);
			strcat(buf, tmp);
		}
		printf("%s\n", buf);
		strcat(szUrl, "appid=");
		strcat(szUrl, appid);
		strcat(szUrl, "&q=");
		strcat(szUrl, q);
		strcat(szUrl, "&from=");
		strcat(szUrl, from);
		strcat(szUrl, "&to=");
		strcat(szUrl, to);
		strcat(szUrl, "&salt=");
		strcat(szUrl, salt);
		strcat(szUrl, "&sign=");
		strcat(szUrl, buf);
	}
	

	char *appid;
	char *from;
	char *to;
	char *secret_key;
	char 
}bd_trans_param;

typedef struct _URL_INFO
{
	WCHAR szScheme[512];
	WCHAR szHostName[512];
	WCHAR szUserName[512];
	WCHAR szPassword[512];
	WCHAR szUrlPath[512];
	WCHAR szExtraInfo[512];
}URL_INFO, *PURL_INFO;

bool separate_url(const char* url, URL_COMPONENTSW &lpUrlComponents)
{
	URL_INFO url_info = { 0 };
	lpUrlComponents.dwStructSize = sizeof(lpUrlComponents);
	lpUrlComponents.lpszExtraInfo = url_info.szExtraInfo;
	lpUrlComponents.lpszHostName = url_info.szHostName;
	lpUrlComponents.lpszPassword = url_info.szPassword;
	lpUrlComponents.lpszScheme = url_info.szScheme;
	lpUrlComponents.lpszUrlPath = url_info.szUrlPath;
	lpUrlComponents.lpszUserName = url_info.szUserName;

	lpUrlComponents.dwExtraInfoLength =
		lpUrlComponents.dwHostNameLength =
		lpUrlComponents.dwPasswordLength =
		lpUrlComponents.dwSchemeLength =
		lpUrlComponents.dwUrlPathLength =
		lpUrlComponents.dwUserNameLength = 512;

	return WinHttpCrackUrl(url, 0, ICU_ESCAPE, &lpUrlComponents);
}


int kdt_trans_func(trans_param *ptr_param)
{

#ifndef _MSC_VER
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
#else
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	BOOL  bResults = FALSE;
	HINTERNET  hSession = NULL,hConnect = NULL,hRequest = NULL;


#endif // !_MSC_VER

#ifndef _MSC_VER
	if (curl) 
	{
#else
	{
#endif

		
		bd_trans_param bd_param;
		bd_param.init(ptr_param)
	
		for (vector<std::string>::iterator iter = ptr_param->m_vcTarget.begin(); iter != ptr_param->m_vcTarget.end(); iter++)
		{
			dt_vchar2048 myurl;
			bd_param.getUrl(iter->c_str(), myurl, sizeof(myurl));

#ifdef _MSC_VER
			URL_COMPONENTSW lpUrlComponents = { 0 };
			if (!separate_url(myurl, lpUrlComponents))
				return;

			hSession = WinHttpOpen(L"WinHTTP Example/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
			if (hSession)
				hConnect = WinHttpConnect(hSession, lpUrlComponents.lpszHostName, lpUrlComponents.nPort, 0);
			if (hConnect)
				hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
			if (hRequest)
				bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
			if (bResults)
				bResults = WinHttpReceiveResponse(hRequest, NULL);

			if (bResults)
			{
				do
				{
					dwSize = 0;
					if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
						printf("Error %u in WinHttpQueryDataAvailable.\n",
						GetLastError());
					pszOutBuffer = new char[dwSize + 1];
					if (!pszOutBuffer)
					{
						printf("Out of memory\n");
						dwSize = 0;
					}
					else
					{
						ZeroMemory(pszOutBuffer, dwSize + 1);
						if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
							dwSize, &dwDownloaded))
							printf("Error %u in WinHttpReadData.\n", GetLastError());
						else
							printf("%s", pszOutBuffer);
						delete[] pszOutBuffer;
					}
				} while (dwSize > 0);
			}

			if (!bResults)
				printf("Error %d has occurred.\n", GetLastError());
			if (hRequest) WinHttpCloseHandle(hRequest);
			if (hConnect) WinHttpCloseHandle(hConnect);
			if (hSession) WinHttpCloseHandle(hSession);
#else
			curl_easy_setopt(curl, CURLOPT_URL, myurl);
			res = curl_easy_perform(curl);
			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

			curl_easy_cleanup(curl);
#endif // !_MSC_VER


		
	}
	
	

	return 0;
}

#endif