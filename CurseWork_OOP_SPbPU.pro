# Подключаем необходимые модули Qt (по крутому - в столбик)
QT += core gui widgets

TARGET = CurseWork_OOP_SPbPU
TEMPLATE = app

# Потому что я неадыкват (пишу с беты MacOs)
CONFIG += sdk_no_version_check

# Для GUI
CONFIG += c++14

# Для консольного приложения
CONFIG += console c++14
CONFIG -= app_bundle


# Для GUI приложения
DEFINES += USE_GUI

# Добавляем файл c записями в "конфигурацию"
DISTFILES += data.txt

# Файлы проекта
SOURCES += \
    findwidget.cpp \
    main.cpp \
    BookUnit.cpp \
    Methods.cpp \
    FullName.cpp \
    Email.cpp \
    BirthDate.cpp \
    Address.cpp \
    PhoneNumbers.cpp \
    mainwindow.cpp \
    subwindow.cpp

HEADERS += \
    BookUnit.h \
    Methods.h \
    AllModuls.h \
    FullName.h \
    Email.h \
    BirthDate.h \
    Address.h \
    PhoneNumbers.h \
    findwidget.h \
    mainwindow.h \
    subwindow.h

INCLUDEPATH += .

# Для macOS
macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 14
}
