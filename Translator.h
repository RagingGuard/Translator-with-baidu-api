#ifndef __TRANSLATOR_H
#define __TRANSLATOR_H

#include "ui_TranslatorDialog.h"
#include "TranslatorConnecter.h"
#include "TranslatorConverter.h"

class translator:public QMainWindow, public Ui::TranslatorDialog, public translatorConnecter, public translatorConverter{
    Q_OBJECT
public:
    translator(void);
public slots:
    void clickLoginConfirmButton(void);
    void clickLoginClearButton(void);
    void clickTranslateButton(void);
protected:
    FILE* fp;
};

#endif //__TRANSLATOR_H
