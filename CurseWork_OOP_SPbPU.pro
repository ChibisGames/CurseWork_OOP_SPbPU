# Подключаем необходимые модули Qt
QT += core gui widgets

TARGET = CurseWork_OOP_SPbPU
TEMPLATE = app

# Для GUI приложения (если используете QApplication)
CONFIG += c++14

# Для консольного приложения (если не используете GUI)
# CONFIG += console c++14
# CONFIG -= app_bundle

# Файлы проекта
SOURCES += \
    main.cpp \
    BookUnit.cpp \
    Methods.cpp \
    FullName.cpp \
    Email.cpp \
    BirthDate.cpp \
    Address.cpp \
    PhoneNumbers.cpp

HEADERS += \
    BookUnit.h \
    Methods.h \
    AllModuls.h \
    FullName.h \
    Email.h \
    BirthDate.h \
    Address.h \
    PhoneNumbers.h

INCLUDEPATH += .

# Для macOS
macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.13
}
