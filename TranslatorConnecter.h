#ifndef __TRANSLATORCONNECTER_H
#define __TRANSLATORCONNECTER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <curl/curl.h>

using namespace std;

class translatorConnecter{
public:
//连接百度翻译api服务器，传入写好的指针字符串
void connecterSend(string&);

protected:
//接受服务器数据的函数
static size_t processRecv(void*, size_t, size_t, void*);
public:
static string recvData;
};

#endif //__TRANSLATORCONNECTER_H