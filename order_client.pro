QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myUtil.cpp

HEADERS += \
    mainwindow.h \
    myUtil.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    static.qrc

# 部署的默认规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
