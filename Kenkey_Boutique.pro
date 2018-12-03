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
        mainwindow.cpp \
    Initialisation/loginscreen.cpp \
    Initialisation/createaccountscreen.cpp \
    salestablemodel.cpp \
    inventorytablemodel.cpp \
    fooditem.cpp \
    Dialogs/editmenudialog.cpp \
    Dialogs/changemenuitemdialog.cpp \
    inventoryitem.cpp \
    themewidget.cpp \
    Dialogs/changepassworddialog.cpp \
    user.cpp \
    transaction.cpp

HEADERS += \
        mainwindow.h \
    Initialisation/loginscreen.h \
    Initialisation/createaccountscreen.h \
    salestablemodel.h \
    inventorytablemodel.h \
    typedefinitions.h \
    fooditem.h \
    Dialogs/editmenudialog.h \
    Dialogs/changemenuitemdialog.h \
    inventoryitem.h \
    themewidget.h \
    Dialogs/changepassworddialog.h \
    user.h \
    transaction.h

FORMS += \
        mainwindow.ui \
    Initialisation/loginscreen.ui \
    Initialisation/createaccountscreen.ui \
    Dialogs/editmenudialog.ui \
    Dialogs/changemenuitemdialog.ui \
    Dialogs/changepassworddialog.ui

RESOURCES += \
    Resources/pictures.qrc
