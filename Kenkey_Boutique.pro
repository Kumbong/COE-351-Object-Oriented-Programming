#-------------------------------------------------
#
# Project created by QtCreator 2018-10-12T03:05:55
#
#-------------------------------------------------

QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kenkey_Boutique
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Mainwindow/mainwindow.cpp \
    Initialisation/loginscreen.cpp \
    Initialisation/createaccountscreen.cpp \
    Models/salestablemodel.cpp \
    Models/inventorytablemodel.cpp \
    Types/fooditem.cpp \
    Dialogs/editmenudialog.cpp \
    Dialogs/changemenuitemdialog.cpp \
    Types/inventoryitem.cpp \
    Types/themewidget.cpp \
    Dialogs/changepassworddialog.cpp \
    Types/user.cpp \
    Types/transaction.cpp

HEADERS += \
    Mainwindow/mainwindow.h \
    Initialisation/loginscreen.h \
    Initialisation/createaccountscreen.h \
    Models/salestablemodel.h \
    Models/inventorytablemodel.h \
    Types/typedefinitions.h \
    Types/fooditem.h \
    Dialogs/editmenudialog.h \
    Dialogs/changemenuitemdialog.h \
    Types/inventoryitem.h \
    Types/themewidget.h \
    Dialogs/changepassworddialog.h \
    Types/user.h \
    Types/transaction.h

FORMS += \
    Mainwindow/mainwindow.ui \
    Initialisation/loginscreen.ui \
    Initialisation/createaccountscreen.ui \
    Dialogs/editmenudialog.ui \
    Dialogs/changemenuitemdialog.ui \
    Dialogs/changepassworddialog.ui

RESOURCES += \
    Resources/pictures.qrc
