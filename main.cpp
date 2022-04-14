#include <QApplication>
#include "Translator.h"

int main(int argc, char** argv){
    QApplication app(argc,argv);
    
    translator trans;
    trans.show();

    return app.exec();
}