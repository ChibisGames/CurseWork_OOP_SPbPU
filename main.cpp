#include "AllModuls.h"
#include "Methods.h"

#include<QApplication>
#include<QLabel>

using namespace std;


int main(int argc, char *argv[]) {
    int opt = 0;
    // console app
    //mainManu(opt);

    //Qt app
    QApplication app(argc, argv);
    //QLabel *label = new QLabel("Hello World!");
    QWidget *window = new QWidget;
    window->setWindowTitle("Phone Book");

    //label->show();
    window->show();
    return app.exec();
    return 0;

}

