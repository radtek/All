#pragma once
#include<iostream>
#include<sys/socket.h>

typedef struct stUrlInfo
{
	string path;
	string domain;
	string protocol;
	string port;
	string query;	
}tagUrlInfo;

void parse_url(const string& raw_url, tagUrlInfo &info)
{
	int offset = 0;
	size_t pos1, pos2, pos3, pos4;
	x = _trim(raw_url);
	offset = offset == 0 && x.compare(0, 8, "https://") == 0 ? 8 : offset;
	offset = offset == 0 && x.compare(0, 7, "http://") == 0 ? 7 : offset;
	pos1 = x.find_first_of('/', offset + 1);
	info.path = pos1 == string::npos ? "" : x.substr(pos1);
	info.domain = string(x.begin() + offset, pos1 != string::npos ? x.begin() + pos1 : x.end());
	info.path = (pos2 = info.path.find("#")) != string::npos ? info.path.substr(0, pos2) : info.path;
	info.port = (pos3 = info.domain.find(":")) != string::npos ? info.domain.substr(pos3 + 1) : "";
	info.domain = info.domain.substr(0, pos3 != string::npos ? pos3 : info.domain.length());
	info.protocol = offset > 0 ? x.substr(0, offset - 3) : "";
	info.query = (pos4 = info.path.find("?")) != string::npos ? info.path.substr(pos4 + 1) : "";
	info.path = pos4 != string::npos ? info.path.substr(0, pos4) : info.path;
	cout << "[" << raw_url << "]" << endl;
	cout << "protocol: " << info.protocol << endl;
	cout << "domain: " << info.domain << endl;
	cout << "port: " << info.port << endl;
	cout << "path: " << info.path << endl;
	cout << "query: " << info.query << endl;
}


void parseUrl(const char *url)
{
	URLINFO info = ParseURL(url);
	socket sock = Socket
}
