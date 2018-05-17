#ifndef  _TRANSLATE_MODULE_
#define  _TRANSLATE_MODULE_

#include <stdio.h>
#include "kdt_translate_head.h"
#include "string.h"

#ifdef  _MSC_VER
#include<string.h>
#include<windows.h>
#include<winhttp.h>
#pragma comment(lib,"winhttp.lib")
#include "md5.h" 
#else
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#endif //_MSC_VER



typedef struct
{
	void init(trans_param *ptr)
	{
		appid = ptr->m_szAppId;
		from = ptr->m_szLanguageFrom;
		to = ptr->m_szLanguageTo;
		secret_key = ptr->m_szSecret_key;
	}
	

	void getUrl(char* szTarget,char *szUrl,int nSize)
	{
		if (nSize < 256)
			return;

		strcpy(szUrl, "http://api.fanyi.baidu.com/api/trans/vip/translate?");
		char *q = szTarget;
		char salt[60];
		int a = rand();
		sprintf(salt, "%d", a);
		char sign[120] = "";
		strcat(sign, appid);
		strcat(sign, q);
		strcat(sign, salt);
		strcat(sign, secret_key);

		char * utf_8_sign;
		utf_8_sign = G2U(sign);
		unsigned char md[16];
		char tmp[3] = { '\0' }, buf[33] = { '\0' };

#ifdef _MSC_VER
		wheel::MD5Context mdContext;
		wheel::MD5Init(&mdContext);
		wheel::MD5Update(&mdContext, (unsigned char*)utf_8_sign, strlen(utf_8_sign));
		wheel::MD5Final(md,&mdContext);

		delete[]utf_8_sign;
		for (int i = 0; i < 16; i++)
		{
			sprintf(tmp, "%2.2x", md[i]);
			strcat(buf, tmp);
		}
#else
		MD5((unsigned char *)sign, strlen((unsigned char *)sign), md);
		for (i = 0; i < 16; i++)
		{
			sprintf(tmp, "%2.2x", md[i]);
			strcat(buf, tmp);
		}
#endif
		

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
} bd_trans_param;

typedef struct _URL_INFO
{
	WCHAR szScheme[512];
	WCHAR szHostName[512];
	WCHAR szUserName[512];
	WCHAR szPassword[512];
	WCHAR szUrlPath[512];
	WCHAR szExtraInfo[512];
}URL_INFO, *PURL_INFO;

bool separate_url(LPCWSTR url,const int nSize,URL_INFO &lpUrlInfo,URL_COMPONENTSW &lpUrlComponents)
{
	lpUrlComponents.dwStructSize = sizeof(lpUrlComponents);
	lpUrlComponents.lpszExtraInfo = lpUrlInfo.szExtraInfo;
	lpUrlComponents.lpszHostName = lpUrlInfo.szHostName;
	lpUrlComponents.lpszPassword = lpUrlInfo.szPassword;
	lpUrlComponents.lpszScheme = lpUrlInfo.szScheme;
	lpUrlComponents.lpszUrlPath = lpUrlInfo.szUrlPath;
	lpUrlComponents.lpszUserName = lpUrlInfo.szUserName;

	lpUrlComponents.dwExtraInfoLength =
		lpUrlComponents.dwHostNameLength =
		lpUrlComponents.dwPasswordLength =
		lpUrlComponents.dwSchemeLength =
		lpUrlComponents.dwUrlPathLength =
		lpUrlComponents.dwUserNameLength = 512;

	return WinHttpCrackUrl(url, nSize, ICU_ESCAPE, &lpUrlComponents);
}

bool parseResult(char *Resourcestr,char *destStr)
{
	char *src  = strstr(Resourcestr, "\"dst\":\"");
	char *dest = destStr;

	if (src)
	{
		src += 7;
		while (*src != '\"')
			*dest++ = *src++;
		*dest = '\0';
		return true;
	}
	return false;
}

void kdt_trans_func(trans_param *ptr_param)
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
	HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;


#endif // !_MSC_VER

#ifndef _MSC_VER
	if (curl) 
	{
#else
	{

#endif
		bd_trans_param bd_param;
		bd_param.init(ptr_param);

		for (std::vector<std::string>::iterator iter = ptr_param->m_vcTarget.begin(); iter != ptr_param->m_vcTarget.end(); iter++)
		{
			dt_vchar2048 myurl;
			dt_vchar512  szTarget;
			strcpy(szTarget, iter->c_str());
			bd_param.getUrl(szTarget, myurl, sizeof(myurl));

#ifdef _MSC_VER

			URL_INFO url_info = { 0 };
			URL_COMPONENTSW lpUrlComponents = { 0 };

			WCHAR wszStr[2049];
			memset(wszStr, 0, sizeof(wszStr));
			MultiByteToWideChar(CP_ACP, 0, myurl, strlen(myurl) + 1, wszStr,
				sizeof(wszStr) / sizeof(wszStr[0]));

			if (!separate_url(wszStr, sizeof(wszStr), url_info, lpUrlComponents))
				return;

			//此处可以优化，把建立连接放到外层
			hSession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
			if (hSession)
				hConnect = WinHttpConnect(hSession, lpUrlComponents.lpszHostName, lpUrlComponents.nPort, 0);
			if (hConnect)
			{
				std::wstring wstrUrl = lpUrlComponents.lpszUrlPath;
				wstrUrl += lpUrlComponents.lpszExtraInfo;
				//WINHTTP_FLAG_SECURE HTTPS
				hRequest = WinHttpOpenRequest(hConnect, L"GET", wstrUrl.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
				
				/*
				DWORD dwFlags;
				DWORD dwBuffLen = sizeof(dwFlags);
				WinHttpQueryOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS,(LPVOID)&dwFlags, &dwBuffLen);
				dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
				dwFlags |= SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
				dwFlags |= SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
				
				WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS,&dwFlags, sizeof(dwFlags));*/
			}
			if (hRequest)
				bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
			if (bResults)
				bResults = WinHttpReceiveResponse(hRequest, NULL);
			else
				ptr_param->m_nErrorCode = GetLastError();

			if (bResults)
			{
				do
				{
					dwSize = 0;
					if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
						ptr_param->m_nErrorCode = GetLastError();

					if (dwSize == 0)
						break;

					pszOutBuffer = new char[dwSize + 1];
					ZeroMemory(pszOutBuffer, dwSize + 1);

					if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
						ptr_param->m_nErrorCode = GetLastError();
					else
					{
						dt_vchar2048 strResult;
						memset(strResult, 0, sizeof(strResult));
						parseResult(pszOutBuffer, strResult);
						ptr_param->m_vcResult.push_back(std::string(strResult));
					}

					delete[] pszOutBuffer;
				} while (dwSize > 0);
			}

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
	}
}

#endif