#include <Translator.h>
#include <unistd.h>
#include <QTextCodec>

#define loginFileAddress "/home/tronlong/.login"

translator::translator(void){
    setupUi(this);
    translatorToMessage->setText(QString::fromStdString(recvMessage));
    char test_str[38] = {0};
	if(access(loginFileAddress, F_OK))
		fp = fopen(loginFileAddress, "w+");
	else
		fp = fopen(loginFileAddress, "r+");
    if(fp == nullptr){
		perror("fopen");
		exit(-1);
	}
    unsigned long number = fread(test_str, 1, 37, fp);
    fclose(fp);
    if( number == 37){
        int i = 0;
        m_PPID = "";
        for(; i < 17; i++){
            m_PPID += test_str[i];
        }
        m_PASSWD = "";
        for(; i < 37; i++){
            m_PASSWD += test_str[i];
        }
    }
    else{
        m_PPID = "";
        m_PASSWD = "";
    }
    translatorLogin->setText(QString::fromStdString(m_PPID));
    translatorPasswd->setText(QString::fromStdString(m_PASSWD));
    connect(translatorConfirmButton,SIGNAL(clicked(void)),this,SLOT(clickLoginConfirmButton(void)));
    connect(translatorClearButton,SIGNAL(clicked(void)),this,SLOT(clickLoginClearButton(void)));
    connect(translatorTranslateButton,SIGNAL(clicked(void)),this,SLOT(clickTranslateButton(void)));
//  connect(translatorFromMessage,SIGNAL(textChanged(void)),this,SLOT(clickTranslateButton(void)));
}

void translator::clickLoginConfirmButton(void){
    m_PPID = translatorLogin->displayText().toStdString();
    m_PASSWD = translatorPasswd->displayText().toStdString();
    if(access(loginFileAddress, F_OK))
		fp = fopen(loginFileAddress, "w+");
	else
		fp = fopen(loginFileAddress, "r+");
    if(fp == nullptr){
		perror("fopen");
		exit(-1);
	}
	fseek( fp, 0, SEEK_SET);
    fwrite(m_PPID.c_str(), 1, m_PPID.size(), fp);
    fwrite(m_PASSWD.c_str(), 1, m_PASSWD.size(), fp);
    //test code begin
    cout << m_PPID << endl << m_PASSWD << endl;
    //test code end
    fclose(fp);
}

void translator::clickLoginClearButton(void){
    m_PPID = "";
    m_PASSWD ="";
    translatorLogin->clear();
    translatorPasswd->clear();
}

void translator::clickTranslateButton(void){
    m_FromMessage = translatorFromMessage->toPlainText().toStdString();
    if(m_FromMessage != string("")){
        connecterSend(sendMessageSplicing());
        usleep(500000);
        recvMessageSplitting(translatorConnecter::recvData);

        //将utf-16代码转换为utf-8的代码
        unsigned long num = recvMessage.size();
        unsigned char* cstr = (unsigned char*)malloc(num+1);
        cstr[num] = '\0';
        memcpy(cstr, recvMessage.c_str(), num);
        recvMessage = "";
        string zhongjian = "";
        for(int i = 0; i < (int)num;){
            if(cstr[i] == '\\' && cstr[i+1] == 'u' && cstr[i+6] == '\\' && cstr[i+7] == 'u' ){
                for(int j=2; j < 6; j+=4){
                    unsigned char a1 = 0;
                    unsigned char a2 = 0;
                    unsigned char a3 = 0;
                    unsigned char a4 = 0;
                    if(cstr[i+j] <= '9' && cstr[i+j] >= '0')
                        a1 += (cstr[i+j] - 48);
                    else if(cstr[i+j] <= 'f' && cstr[i+j] >= 'a')
                        a1 += (cstr[i+j] - 87);
                    else if(cstr[i+j] <= 'F' && cstr[i+j] >= 'F')
                        a1 += (cstr[i+j] - 55);
                    else{}
                    if(cstr[i+j+1] <= '9' && cstr[i+j+1] >= '0')
                        a2 += (cstr[i+j+1] - 48);
                    else if(cstr[i+j+1] <= 'f' && cstr[i+j+1] >= 'a')
                        a2 += (cstr[i+j+1] - 87);
                    else if(cstr[i+j+1] <= 'F' && cstr[i+j+1] >= 'F')
                        a2 += (cstr[i+j+1] - 55);
                    else{}
                    if(cstr[i+j+2] <= '9' && cstr[i+j+2] >= '0')
                        a3 += (cstr[i+j+2] - 48);
                    else if(cstr[i+j+2] <= 'f' && cstr[i+j+2] >= 'a')
                        a3 += (cstr[i+j+2] - 87);
                    else if(cstr[i+j+2] <= 'F' && cstr[i+j+2] >= 'F')
                        a3 += (cstr[i+j+2] - 55);
                    else{}
                    if(cstr[i+j+3] <= '9' && cstr[i+j+3] >= '0')
                        a4 += (cstr[i+j+3] - 48);
                    else if(cstr[i+j+3] <= 'f' && cstr[i+j+3] >= 'a')
                        a4 += (cstr[i+j+3] - 87);
                    else if(cstr[i+j+3] <= 'F' && cstr[i+j+3] >= 'F')
                        a4 += (cstr[i+j+3] - 55);
                    else{}
                    zhongjian += (char)((unsigned char)a3 * 16 + (unsigned char)a4);
                    zhongjian += (char)((unsigned char)a1 * 16 + (unsigned char)a2);
                    i += 6;
                }
            }else if(cstr[i] == '\\' && cstr[i+1] == 'u' ){
                for(int j=2; j < 6; j+=4){
                    unsigned char a1 = 0;
                    unsigned char a2 = 0;
                    unsigned char a3 = 0;
                    unsigned char a4 = 0;
                    if(cstr[i+j] <= '9' && cstr[i+j] >= '0')
                        a1 += (cstr[i+j] - 48);
                    else if(cstr[i+j] <= 'f' && cstr[i+j] >= 'a')
                        a1 += (cstr[i+j] - 87);
                    else if(cstr[i+j] <= 'F' && cstr[i+j] >= 'F')
                        a1 += (cstr[i+j] - 55);
                    else{}
                    if(cstr[i+j+1] <= '9' && cstr[i+j+1] >= '0')
                        a2 += (cstr[i+j+1] - 48);
                    else if(cstr[i+j+1] <= 'f' && cstr[i+j+1] >= 'a')
                        a2 += (cstr[i+j+1] - 87);
                    else if(cstr[i+j+1] <= 'F' && cstr[i+j+1] >= 'F')
                        a2 += (cstr[i+j+1] - 55);
                    else{}
                    if(cstr[i+j+2] <= '9' && cstr[i+j+2] >= '0')
                        a3 += (cstr[i+j+2] - 48);
                    else if(cstr[i+j+2] <= 'f' && cstr[i+j+2] >= 'a')
                        a3 += (cstr[i+j+2] - 87);
                    else if(cstr[i+j+2] <= 'F' && cstr[i+j+2] >= 'F')
                        a3 += (cstr[i+j+2] - 55);
                    else{}
                    if(cstr[i+j+3] <= '9' && cstr[i+j+3] >= '0')
                        a4 += (cstr[i+j+3] - 48);
                    else if(cstr[i+j+3] <= 'f' && cstr[i+j+3] >= 'a')
                        a4 += (cstr[i+j+3] - 87);
                    else if(cstr[i+j+3] <= 'F' && cstr[i+j+3] >= 'F')
                        a4 += (cstr[i+j+3] - 55);
                    else{}
                    zhongjian += (char)((unsigned char)a3 * 16 + (unsigned char)a4);
                    zhongjian += (char)((unsigned char)a1 * 16 + (unsigned char)a2);
                    i += 6;
                    QTextCodec* coder = QTextCodec::codecForName("UTF-16");
                    recvMessage += coder->toUnicode(zhongjian.c_str()).toStdString();
                    zhongjian = "";
                }
            }
            else{
                recvMessage += cstr[i];
                ++i;
            }

        }
        free(cstr);
        translatorToMessage->setText(QString::fromStdString(recvMessage)); 
/*
        if(!strcmp(m_ToText.c_str(), "中文")){
            int num = recvMessage.size();
            unsigned char* cstr = (unsigned char*)malloc(num+1);
            memcpy(cstr, recvMessage.c_str(), num);
            recvMessage = "";
            for(int i = 0; i < num; ){
                if(cstr[i] == '\\' && cstr[i+1] == 'u'){
                    for(int j=2; j < 6; j+=4){
                        unsigned char a1 = 0;
                        unsigned char a2 = 0;
                        unsigned char a3 = 0;
                        unsigned char a4 = 0;
                        if(cstr[i+j] <= '9' && cstr[i+j] >= '0')
                            a1 += (cstr[i+j] - 48);
                        else if(cstr[i+j] <= 'f' && cstr[i+j] >= 'a')
                            a1 += (cstr[i+j] - 87);
                        else if(cstr[i+j] <= 'F' && cstr[i+j] >= 'F')
                            a1 += (cstr[i+j] - 55);
                        else{}
                        if(cstr[i+j+1] <= '9' && cstr[i+j+1] >= '0')
                            a2 += (cstr[i+j+1] - 48);
                        else if(cstr[i+j+1] <= 'f' && cstr[i+j+1] >= 'a')
                            a2 += (cstr[i+j+1] - 87);
                        else if(cstr[i+j+1] <= 'F' && cstr[i+j+1] >= 'F')
                            a2 += (cstr[i+j+1] - 55);
                        else{}
                        if(cstr[i+j+2] <= '9' && cstr[i+j+2] >= '0')
                            a3 += (cstr[i+j+2] - 48);
                        else if(cstr[i+j+2] <= 'f' && cstr[i+j+2] >= 'a')
                            a3 += (cstr[i+j+2] - 87);
                        else if(cstr[i+j+2] <= 'F' && cstr[i+j+2] >= 'F')
                            a3 += (cstr[i+j+2] - 55);
                        else{}
                        if(cstr[i+j+3] <= '9' && cstr[i+j+3] >= '0')
                            a4 += (cstr[i+j+3] - 48);
                        else if(cstr[i+j+3] <= 'f' && cstr[i+j+3] >= 'a')
                            a4 += (cstr[i+j+3] - 87);
                        else if(cstr[i+j+3] <= 'F' && cstr[i+j+3] >= 'F')
                            a4 += (cstr[i+j+3] - 55);
                        else{}
                        recvMessage += (char)((unsigned char)a3 * 16 + (unsigned char)a4);
                        recvMessage += (char)((unsigned char)a1 * 16 + (unsigned char)a2);
                    }  
                    i += 6;
                }
                else{
                    recvMessage += cstr[i];
                    i += 1;
                }
            }
            QTextCodec* coder = QTextCodec::codecForName("UTF-16");
            translatorToMessage->setText(coder->toUnicode(recvMessage.c_str()));
            free(cstr)
        }
        else
            translatorToMessage->setText(QString::fromStdString(recvMessage));
*/    
        translatorFromText->setText(QString::fromStdString(m_FromText));
        translatorToText->setText(QString::fromStdString(m_ToText));
    }
}
