QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    MyUtil.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp

HEADERS += \
    MyUtil.h \
    mainwindow.h \
    menu.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    static.qrc

# 部署的默认规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
