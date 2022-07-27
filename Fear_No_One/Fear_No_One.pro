QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += ./Data/Arms
INCLUDEPATH += ./Data/Character
INCLUDEPATH += ./Data/Ground
INCLUDEPATH += ./Data/Map
INCLUDEPATH += ./System/GameSystem
INCLUDEPATH += ./System/Interface
INCLUDEPATH += ./System


SOURCES += \
    Data/Arms/Arms.cpp \
    Data/Character/Character.cpp \
    Data/Ground/Ground.cpp \
    Data/Map/Map.cpp \
    System/GameSystem/CGameSystem.cpp \
    System/Interface/game.cpp \
    System/Interface/gamechoice.cpp \
    System/Interface/gamechoice2.cpp \
    System/Interface/gamemap.cpp \
    System/Interface/gamestart.cpp \
    System/Interface/gethit_exp.cpp \
    System/Interface/gethit_hp.cpp \
    System/Interface/groundtypeinfo.cpp \
    System/Interface/mybuttongamechoice.cpp \
    System/Interface/mybuttongamestart.cpp \
    System/Interface/peoplehpinfo.cpp \
    System/main.cpp \
    System/Interface/actionlistitem.cpp \
    System/Interface/actionlist.cpp \
    System/Interface/arminfo.cpp \
    System/Interface/armlist.cpp \
    System/Interface/armlistitem.cpp \
    System/Interface/gamechoiceitem.cpp \
    System/Interface/gamechoice2item.cpp \
    System/Interface/attackreadyinfo.cpp \
    System/Interface/tufeilistitem.cpp \
    System/Interface/tufeilist.cpp \
    System/Interface/changepeoplelist.cpp \
    System/Interface/changepeoplelistitem.cpp

HEADERS += \
    Data/Arms/Arms.h \
    Data/Character/Character.h \
    Data/Ground/Ground.h \
    Data/Map/Map.h \
    System/GameSystem/CGameSystem.h \
    System/Interface/game.h \
    System/Interface/gamechoice.h \
    System/Interface/gamechoice2.h \
    System/Interface/gamemap.h \
    System/Interface/gamestart.h \
    System/Interface/gethit_exp.h \
    System/Interface/gethit_hp.h \
    System/Interface/groundtypeinfo.h \
    System/Interface/mybuttongamechoice.h \
    System/Interface/mybuttongamestart.h \
    System/Interface/peoplehpinfo.h \
    System/packdef.h \
    System/Interface/actionlistitem.h \
    System/Interface/actionlist.h \
    System/Interface/arminfo.h \
    System/Interface/armlist.h \
    System/Interface/armlistitem.h \
    System/Interface/gamechoiceitem.h \
    System/Interface/gamechoice2item.h \
    System/Interface/attackreadyinfo.h \
    System/Interface/tufeilistitem.h \
    System/Interface/tufeilist.h \
    System/Interface/changepeoplelist.h \
    System/Interface/changepeoplelistitem.h

FORMS += \
    System/Interface/game.ui \
    System/Interface/gamechoice.ui \
    System/Interface/gamechoice2.ui \
    System/Interface/gamemap.ui \
    System/Interface/gamestart.ui \
    System/Interface/gethit_exp.ui \
    System/Interface/gethit_hp.ui \
    System/Interface/groundtypeinfo.ui \
    System/Interface/peoplehpinfo.ui \
    System/Interface/actionlistitem.ui \
    System/Interface/actionlist.ui \
    System/Interface/arminfo.ui \
    System/Interface/armlist.ui \
    System/Interface/armlistitem.ui \
    System/Interface/gamechoiceitem.ui \
    System/Interface/gamechoice2item.ui \
    System/Interface/attackreadyinfo.ui \
    System/Interface/tufeilistitem.ui \
    System/Interface/tufeilist.ui \
    System/Interface/changepeoplelist.ui \
    System/Interface/changepeoplelistitem.ui
