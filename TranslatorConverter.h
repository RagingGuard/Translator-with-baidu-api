#ifndef __TRANSLATORCONVERTER_H
#define __TRANSLATORCONVERTER_H

#include <iostream>
#include <cstring>
#include <string>
#include <openssl/md5.h>
#include "URLcode.h"

using namespace std;

class translatorConverter:public URLcode{
public:
protected:
    //拼接发送的内容
    string& sendMessageSplicing(void);
    //拆分接受的JSON字符串，并解析
    void recvMessageSplitting(string);

string sendMessage;
string recvMessage;

string m_PPID;
string m_PASSWD;
string m_FromMessage;
string m_FromText;
string m_ToText;
string m_FromTextSet;
string m_ToTextSet;
};

#endif //__TRANSLATORCONVERTER_H