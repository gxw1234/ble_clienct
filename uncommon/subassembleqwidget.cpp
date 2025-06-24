#include "subassembleqwidget.h"
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QEvent>



subassembleqwidget::subassembleqwidget(const QString &title, const QString &ip, const QString &mac, QMainWindow *parent)
    : QMainWindow(parent)
{
    ipValue= ip;
    macValue = mac;
    _title ="机器名称:          "+title +"          ip:"+  ipValue +"  mac:"+  macValue ;
    settitle("测试界面");
    this->setWindowIcon(QIcon(":/images/images/Bluetooth.png"));
    QString currentPath = QDir::currentPath();
    testFilePath = currentPath + "/test_file/";
    MenuBar *menuBar = new MenuBar(this);
    setMenuBar(menuBar);
    connect(menuBar, &MenuBar::menuActionTriggered, this, &subassembleqwidget::onMenuActionTriggered);
    ui_init();
    tcpinit();
}

subassembleqwidget::~subassembleqwidget()
{


}

void subassembleqwidget::ui_init()
{
    iniInit();
    test = new QPushButton;
    host_qstackedWidget = new QStackedWidget;
    Generate_test_files = new Generate_case_qwidget;
    test_case_widget  =new Test_case_qwidget;
    my_burn_qwidget = new burn_qwidget;
    my_disposition_qwidget = new Disposition;
    host_qstackedWidget->addWidget(test_case_widget);
    host_qstackedWidget->addWidget(Generate_test_files);
    host_qstackedWidget->addWidget(my_burn_qwidget);
    host_qstackedWidget->addWidget(my_disposition_qwidget);
    test_case_widget->setmac(macValue,_title +"号机_");

    Generate_test_files->setdebugmac(macValue);
    show_title =new QLineEdit;
    close_ui =new QPushButton;
    connect(close_ui, SIGNAL(clicked()), this, SLOT(closeApplication()));

    close_ui->setText("关闭");
    show_title->setStyleSheet("background-color: transparent;");
    show_title->setReadOnly(true);
    show_title->setFocusPolicy(Qt::NoFocus);  //
    close_ui->setMaximumSize(QSize(50, 30));
    top_qframe =new QFrame;
    top_qframe->setStyleSheet("background-color: #D3D3D3; ");
    QGridLayout *ui_top_qframe;
    ui_top_qframe =new QGridLayout(top_qframe);
    ui_top_qframe->addWidget(show_title,0,0,1,1);
    QSpacerItem *spacer = new QSpacerItem(20, 1);  //
    ui_top_qframe->addItem(spacer, 0, 1);
    ui_top_qframe->addWidget(close_ui,0,2,1,1);
    ui_top_qframe->setColumnStretch(2, 1);


    show_tcp_state_qframe = new QFrame;
    tcpip = new QLabel;
    tcpip->setText("IP地址");
    tcpip_show = new QLineEdit;
    tcpip_show->setText(ipValue);
    tcpconnectstate = new QLabel;
    tcpconnectstate->setText("连接状态");
    tcpconnectstate_show  = new IconPushButton(":/images/images/unconnect.png", "连接状态");
    tcpteststate =  new QLabel;
    tcpteststate->setText("测试状态");
    tcpteststate_show =  new  QPushButton;
    QGridLayout *show_tcp_state_qframe_ly;

    show_tcp_state_qframe_ly =new QGridLayout(show_tcp_state_qframe);
    show_tcp_state_qframe_ly->addWidget(tcpip,0,0,1,1);
    show_tcp_state_qframe_ly->addWidget(tcpip_show,0,1,1,1);
    show_tcp_state_qframe_ly->addWidget(tcpconnectstate,0,2,1,1);
    show_tcp_state_qframe_ly->addWidget(tcpconnectstate_show,0,3,1,1);
    show_tcp_state_qframe_ly->addWidget(tcpteststate,0,4,1,1);
    show_tcp_state_qframe_ly->addWidget(tcpteststate_show,0,5,1,1);
     QGridLayout *ui_ly;
     ui_ly =new QGridLayout();
     ui_ly->addWidget(show_tcp_state_qframe,0,0,1,1);
     ui_ly->addWidget(host_qstackedWidget,1,0,1,1);
     ui_ly->setContentsMargins(0, 0, 0, 0);
     QWidget * maina =new QWidget;
     maina->setLayout(ui_ly);
     setCentralWidget(maina);
}

/**
 *连接TCP
 */


void subassembleqwidget::tcpinit()
{

    tcpaap = new Tcpapp;
    connect(tcpaap,&Tcpapp::commandReceivedapp,this,&subassembleqwidget::handleDataReceivedmain);
    connect(tcpaap,&Tcpapp::m_connected_state,this,&subassembleqwidget::get_connected_state);
    tcpaap->connectAndSetupListenerapp(tcpip_show->text());


}

QStringList subassembleqwidget::iniInit()
{
    QStringList temp;
    return temp ;
}

void subassembleqwidget::settitle(QString pagename)
{
    QString temp = _title+ "   当前页面：***************" + pagename+ "***************";
    this->setWindowTitle(temp);
}

void subassembleqwidget::closeApplication(){
    this->close();
}

void subassembleqwidget::handleDataReceivedmain(quint8 dataType, const QByteArray &buffer, bool islen_, bool ismd5_)
{
    if (ismd5_)
       {
           switch (dataType) {
           case 0x01:
           {
               break;
           }
           case 0x02:
           {
               break;
           }
           case 0x03:
           {
               break;
           }
           case 0x04:
           {
               break;
           }
           case 0x05:
           {
               QString data = QString::fromUtf8(buffer);
               bool stringAsBool =STRING_TO_BOOL(data);
               tcpteststate_show->setChecked(stringAsBool);
               if (!stringAsBool)
               {
                   tcpteststate_show->setText("未测试");
                   tcpteststate_show->setStyleSheet("QPushButton { background-color: lightblue; }");
               }
               else {
                   tcpteststate_show->setText("正在测试");
                   tcpteststate_show->setStyleSheet("QPushButton { background-color: green; }");
               }
               break;
           }
           default:
               break;
           }
       }
       else {
           qDebug()<<"MD5---Validation error";
       }
}



void subassembleqwidget::get_connected_state(bool state)
{
    if(state)
    {
        Generate_test_files->setnetworkserviceOBJECT(tcpaap,state);
        test_case_widget->setnetworkserviceOBJECT(tcpaap,state);
        my_burn_qwidget->setnetworkserviceOBJECT(tcpaap,state);
        my_disposition_qwidget->setnetworkserviceOBJECT(tcpaap,state);
        tcpconnectstate_show->setStyleSheet("QPushButton { background-color: green; }");
        tcpconnectstate_show->setText("已连接");
        tcpaap->sendMessageapp("test_state",OUTPUTTESTSTATE);
    }
    else {
        tcpconnectstate_show->setStyleSheet("QPushButton { background-color: red; }");
        tcpconnectstate_show->setTextLabel("未连接");
    }
}


void subassembleqwidget::onMenuActionTriggered(QAction *action) {

     settitle(action->text());
    if (action->text() == tr("调试界面")) {
        if(test_case_widget->start_test->isChecked())
        {
            QMessageBox::information(this, "提示", "测试中不能切换");
        }else {
            Generate_test_files->test_text->setText("");
            host_qstackedWidget->setCurrentIndex(1);
            test_case_widget->isreceivetcp = false;
            Generate_test_files->indexinit();
            tcpaap->sendMessageapp("Devicename",OUTPUTINQUIRECFG);
        }

    } else if (action->text() == tr("测试界面")) {
        host_qstackedWidget->setCurrentIndex(0);
        test_case_widget->Refreshfile();
        test_case_widget->isreceivetcp = true;

    } else if (action->text() == tr("退出")) {
        qApp->closeAllWindows();
        qApp->quit();
    }
    else if (action->text() == tr("TCP回连")) {
    }
    else if (action->text() == tr("烧录界面")) {
         host_qstackedWidget->setCurrentIndex(2);
    }
    else if (action->text() == tr("版型配置")) {
         host_qstackedWidget->setCurrentIndex(3);
    }

    else if (action->text() == tr("下载测试结果")) {
         tcpaap->sendMessageapp("Downloadlog",OUTPUTACCORD);
    }
}
