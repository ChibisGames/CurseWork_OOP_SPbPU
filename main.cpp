#include <QApplication>

#include"mainwindow.h"
#include "Methods.h"

using namespace std;


int main(int argc, char *argv[]) {
    #ifdef USE_GUI // смотерть в .pro
        QApplication app(argc, argv);
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    #else
        int opt = 0;
        mainMenu(opt);
        return 0;
    #endif
}

