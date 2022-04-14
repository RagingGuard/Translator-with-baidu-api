#include "TranslatorConverter.h"

string& translatorConverter::sendMessageSplicing(void){
    //通过第一个字符判定是否为英文
    if ((m_FromMessage[0] <= 'Z' && m_FromMessage[0] >= 'A') || 
            (m_FromMessage[0] <= 'z' && m_FromMessage[0] >= 'a')) {
            m_FromTextSet = "en";
            m_ToTextSet = "zh";
    }
    else{
            m_FromTextSet = "zh";
            m_ToTextSet = "en";
    }
    //拼接发送的字符串
    sendMessage = "http://api.fanyi.baidu.com/api/trans/vip/translate?";
    sendMessage += "appid=";
    sendMessage += m_PPID;
    sendMessage += "&q=";
    sendMessage += UrlEncode(m_FromMessage);
    sendMessage += "&from=";
    sendMessage += m_FromTextSet;
    sendMessage += "&to=";
    sendMessage += m_ToTextSet;
    sendMessage += "&salt=";
    //此处拼接部分为随机数
    int a = rand();
    char salt[60];
    sprintf(salt,"%d",a);
    sendMessage += salt;
    sendMessage += "&sign=";
    //此处对密钥进行加密
    string signCode = "";
    signCode += m_PPID;
    signCode += m_FromMessage;
    signCode += salt;
    signCode += m_PASSWD;
    unsigned char md[16];
    char tmp[3]={'\0'},buf[33]={'\0'};
    MD5((unsigned char *)signCode.c_str(),signCode.size(),md);
    for (int i = 0; i < 16; i++){
        sprintf(tmp,"%2.2x",md[i]);
        strcat(buf,tmp);
    }
    sendMessage += buf;
    return sendMessage;
};

void translatorConverter::recvMessageSplitting(string buffer){
    string jsonMessage = buffer;
    //首先判断是否有错误
    if(jsonMessage.find("\"error_code\"") != (long unsigned int)-1){
        recvMessage = jsonMessage;
        m_FromText = "自动";
        m_ToText = "错误";
    }
    else {
        int i = 0;
        //由网络反馈得到翻译前类型
        i = jsonMessage.find("\"from\"");
        if(jsonMessage[i+8] == 'e' && jsonMessage[i+9] == 'n'){
            m_FromText = "英文";
        }else if(jsonMessage[i+8] == 'z' && jsonMessage[i+9] == 'h'){
            m_FromText = "中文";
        }else if(jsonMessage[i+8] == 'a' && jsonMessage[i+9] == 'u' && jsonMessage[i+10] == 't' && jsonMessage[i+11] == 'o'){
            m_FromText = "自动";
        }else{
            m_FromText = "其他语言";
        }
        //由网络反馈得到翻译后类型
        i = jsonMessage.find("\"to\"");
        if(jsonMessage[i+6] == 'e' && jsonMessage[i+7] == 'n'){
            m_ToText = "英文";
        }else if(jsonMessage[i+6] == 'z' && jsonMessage[i+7] == 'h'){
            m_ToText = "中文";
        }else{
            m_ToText = "其他语言";
        }
        //得到全部翻译后的原始字符串
        string recvMessageOriginal = "";
        char* tem_cstr = (char *)malloc(jsonMessage.size()+1);
        memcpy(tem_cstr,jsonMessage.c_str(),jsonMessage.size()+1);
        while(NULL != (tem_cstr = strstr(tem_cstr+1, "\"dst\""))){
            int i = 7;
            while(tem_cstr[i] != '\"'){
                recvMessageOriginal += tem_cstr[i];
                i++;
            }
            recvMessageOriginal += "\n";
        }
        recvMessage = recvMessageOriginal;
    }
}
