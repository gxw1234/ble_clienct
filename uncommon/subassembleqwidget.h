#ifndef SUBASSEMBLEQWIDGET_H
#define SUBASSEMBLEQWIDGET_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QFrame>
#include <QProgressBar>
#include <QStackedWidget>
#include <QTextCursor>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QFrame>
#include <QLineEdit>
#include<QComboBox>
#include <QToolBar>
#include <QAction>
#include <QToolBox>
#include "common/menubar.h"
#include "uncommon/generate_case_qwidget.h"
#include "uncommon/test_case_qwidget.h"
#include "tcpserver/networkservice.h"
#include "uncommon/burn_qwidget.h"
#include "uncommon/disposition.h"
#include <QSettings>

#include "tcpserver/tcpdebug.h"

class subassembleqwidget:  public QMainWindow
{
     Q_OBJECT
public:
    subassembleqwidget(const QString &title, const QString &ip, const QString &mac,QMainWindow *parent = nullptr);
    ~subassembleqwidget();
    void ui_init();
    void addToolBar();
    QPushButton *close_ui =nullptr;
    QLineEdit *show_title =nullptr;
    QFrame *top_qframe =nullptr;
    Generate_case_qwidget *Generate_test_files;
    Test_case_qwidget *test_case_widget;
    burn_qwidget * my_burn_qwidget;
    Disposition * my_disposition_qwidget;
    Tcpapp *tcpaap;

private:
    QPushButton *test;
    QStackedWidget *host_qstackedWidget;
    QString testFilePath;
    QFrame *show_tcp_state_qframe = nullptr;


    QLineEdit *tcpip_show= nullptr;


    QStringList inilist;
    QString ipValue;
    QString macValue;
    QSettings settings;
    QAction *currentSelectedAction = nullptr;
    void tcpinit();
    QStringList iniInit();
    QString _title;
    void settitle( QString pagename  );
    void updateButtonStyle(QAction *action, bool isSelected);

    NetworkThread * _NetworkThread;

    QPushButton *testStatusButton = nullptr;
    QPushButton *networkStatusButton = nullptr;


private slots:
    void onMenuActionTriggered(QAction *action);
    void closeApplication();
    void handleDataReceivedmain(quint8 dataType, const QByteArray& buffer,bool islen_, bool ismd5_);
    void get_connected_state(bool state);
    void onTestActionTriggered();
    void onDebugActionTriggered();
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();

};

#endif // SUBASSEMBLEQWIDGET_H
