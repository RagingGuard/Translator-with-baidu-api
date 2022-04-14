#include "TranslatorConnecter.h"

void translatorConnecter::connecterSend(string& to){
    //建立curl连接
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, to.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, processRecv);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s", curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
    }

size_t translatorConnecter::processRecv(void* buffer, size_t size, size_t nmemb, void* userp){
    char* a = (char* )malloc(sizeof(char) * size * nmemb +1);
    a[sizeof(char) * size * nmemb] = (char)0;
    memcpy(a, buffer, size * nmemb);
    recvData = a;
    free(a);
    a = NULL;
    return size * nmemb;
}

string translatorConnecter::recvData = "";