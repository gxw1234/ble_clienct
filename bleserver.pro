QT       += core gui network printsupport
QT += multimedia
DESTDIR = $$PWD/bin
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#DESTDIR = $$PWD/bin
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += release
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_FILE =ico.rc

INCLUDEPATH += \
    ble_time_line/ \
    backpack/
    common/
     uncommon/
    keycfg/

SOURCES += \
    common/cmdanalyze.cpp \
    common/datetimeutil.cpp \
    common/iconpushbutton.cpp \
    common/mapfle.cpp \
    common/savexls.cpp \
    common/tips_widget.cpp \
    main.cpp \
    mainwindow.cpp \
    common/menubar.cpp \
    tcpserver/networkservice.cpp \
    tcpserver/tcpapp.cpp \
    ble_time_line/labeleditor.cpp \
    ble_time_line/caselinebucket.cpp \
    ble_time_line/caselineglobal.cpp \
    ble_time_line/caselineleadingdot.cpp \
    ble_time_line/caselinetextlabel.cpp \
    ble_time_line/caselinetimelabel.cpp \
    ble_time_line/caselineundocommands.cpp \
    ble_time_line/caselineundostack.cpp \
    ble_time_line/caselineundovirtual.cpp \
    ble_time_line/caselinewidget.cpp\
    uncommon/burn_qwidget.cpp \
    uncommon/disposition.cpp \
    uncommon/generate_case_qwidget.cpp \
    uncommon/mydragwidget.cpp \
    uncommon/subassembleqwidget.cpp \
    uncommon/test_case_qwidget.cpp\
    common/wechatnotifier.cpp \
    uncommon/selectionwindow.cpp \
    ble_time_line/caselineinputdialog.cpp \
    common/icon_config.cpp



HEADERS += \
    common/cmdanalyze.h \
    common/datetimeutil.h \
    common/fileutil.h \
    common/iconpushbutton.h \
    common/mapfle.h \
    common/savexls.h \
    common/tips_widget.h \
    mainwindow.h \
    common/menubar.h \
    tcpserver/networkservice.h \
    tcpserver/tcpapp.h \
    ble_time_line/labeleditor.h \
    ble_time_line/caselinebucket.h \
    ble_time_line/caselineglobal.h \
    ble_time_line/caselineleadingdot.h \
    ble_time_line/caselinetextlabel.h \
    ble_time_line/caselinetimelabel.h \
    ble_time_line/caselineundocommands.h \
    ble_time_line/caselineundostack.h \
    ble_time_line/caselineundovirtual.h \
    ble_time_line/caselinewidget.h\
    uncommon/burn_qwidget.h \
    uncommon/disposition.h \
    uncommon/generate_case_qwidget.h \
    uncommon/mydragwidget.h \
    uncommon/subassembleqwidget.h \
    uncommon/test_case_qwidget.h\
    common/wechatnotifier.h \
    uncommon/selectionwindow.h \
    ble_time_line/caselineinputdialog.h \
    keycfg/key_cfg.h \
    ble_time_line/controldata.h \
    common/icon_config.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
include(QXlsx/QXlsx.pri)
DISTFILES += \
    README.md \

RESOURCES += \
    images.qrc


