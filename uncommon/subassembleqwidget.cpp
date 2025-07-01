#include "subassembleqwidget.h"
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QEvent>
#include <QMessageBox>
#include <QSizePolicy>
#include <QToolBar>
#include <QToolButton>
#include <QDir>
#include <QIcon>



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




    ui_init();
    addToolBar();
    tcpinit();
}

subassembleqwidget::~subassembleqwidget()
{


}

void subassembleqwidget::ui_init()
{

    test = new QPushButton;
    host_qstackedWidget = new QStackedWidget;
    Generate_test_files = new Generate_case_qwidget;
    test_case_widget  =new Test_case_qwidget;
    my_burn_qwidget = new burn_qwidget;
    my_disposition_qwidget = new Disposition;
    host_qstackedWidget->addWidget(test_case_widget);
    

    connect(test_case_widget, &Test_case_qwidget::testStateChanged, this, [this](bool isTestRunning) {
        if (isTestRunning) {
            testStatusButton->setText("服务端正在测试测试");
            testStatusButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: black; padding: 5px 10px; border-radius: 3px; }");
        } else {
            testStatusButton->setText("服务端未开始测试");
            testStatusButton->setStyleSheet("QPushButton { background-color: #808080; color: black; padding: 5px 10px; border-radius: 3px; }");
        }
    });


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
    tcpip_show = new QLineEdit;
    tcpip_show->setText(ipValue);

     QGridLayout *ui_ly;
     ui_ly =new QGridLayout();
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
    tcpaap->connectAndSetupListenerapp(ipValue);


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

               if (!stringAsBool)
               {
                   testStatusButton->setText("服务端未开始测试");

                       testStatusButton->setStyleSheet("QPushButton { background-color: #808080; color: black; padding: 5px 10px; border-radius: 3px; }");
               }
               else {
                   testStatusButton->setText("服务端正在测试测试");

                       testStatusButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: black; padding: 5px 10px; border-radius: 3px; }");
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
        networkStatusButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 5px 10px; border-radius: 3px; }");
        networkStatusButton->setText("客户端已连接");
        tcpaap->sendMessageapp("test_state",OUTPUTTESTSTATE);
    }
    else {
        networkStatusButton->setStyleSheet("QPushButton { background-color: #808080; color: white; padding: 5px 10px; border-radius: 3px; }");
        networkStatusButton->setText("客户端未连接");
    }
}

void subassembleqwidget::addToolBar()
{

    QToolBar *toolbar = new QToolBar(this);
    toolbar->setObjectName("mainToolBar");
    toolbar->setMovable(false);
    toolbar->setIconSize(QSize(16, 16)); // 设置更小的图标尺寸
    

    QAction *testAction = new QAction(QIcon(":/images/images/test_ui.png"), "", this);
    QAction *debugAction = new QAction(QIcon(":/images/images/debug_ui.png"), "", this);
    QAction *button1Action = new QAction(QIcon(":/images/images/brun_ui.png"), "", this);
    QAction *button2Action = new QAction(QIcon(":/images/images/configure_ui.png"), "", this);
    QAction *button3Action = new QAction(QIcon(":/images/images/Download_ui.png"), "", this);
    
    testAction->setToolTip("测试界面");
    debugAction->setToolTip("调试界面");
    button1Action->setToolTip("烧录界面");
    button2Action->setToolTip("配置界面");
    button3Action->setToolTip("下载数据");

    // 设置按钮样式
    QString normalStyle = "QToolButton { padding: 5px; margin: 2px; border: 1px solid #d0d0d0; background-color: #f0f0f0; }";
    QString selectedStyle = "QToolButton { padding: 5px; margin: 2px; border: 2px solid #0078d4; background-color: #e3f2fd; }";
    
    // 为每个按钮设置样式表
    testAction->setProperty("normalStyle", normalStyle);
    testAction->setProperty("selectedStyle", selectedStyle);
    debugAction->setProperty("normalStyle", normalStyle);
    debugAction->setProperty("selectedStyle", selectedStyle);
    button1Action->setProperty("normalStyle", normalStyle);
    button1Action->setProperty("selectedStyle", selectedStyle);
    button2Action->setProperty("normalStyle", normalStyle);
    button2Action->setProperty("selectedStyle", selectedStyle);
    button3Action->setProperty("normalStyle", normalStyle);
    button3Action->setProperty("selectedStyle", selectedStyle);

    toolbar->addAction(testAction);
    toolbar->addSeparator();
    toolbar->addAction(debugAction);
    toolbar->addSeparator();
    toolbar->addAction(button1Action);
    toolbar->addSeparator();
    toolbar->addAction(button2Action);
    toolbar->addSeparator();
    toolbar->addAction(button3Action);
    
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer);

    tcpip_show = new QLineEdit;
    tcpip_show->setText(ipValue);

    tcpip_show->setFixedWidth(120);
    toolbar->addWidget(tcpip_show);
    
    testStatusButton = new QPushButton("服务端未开始测试");
    networkStatusButton = new QPushButton("客户端未连网");
    testStatusButton->setStyleSheet("QPushButton { background-color: #808080; color: black; padding: 5px 10px; border-radius: 3px; }");
    networkStatusButton->setStyleSheet("QPushButton { background-color: #808080; color: white; padding: 5px 10px; border-radius: 3px; }");
    
    testStatusButton->setMinimumWidth(80);
    networkStatusButton->setMinimumWidth(80);
    
    toolbar->addWidget(testStatusButton);
    toolbar->addSeparator();
    toolbar->addWidget(networkStatusButton);
    
    toolbar->setStyleSheet("QToolBar {background-color: #f0f0f0; border: 1px solid #d0d0d0;}"
                         "QToolButton {padding: 5px; margin: 2px;}");
    
    QMainWindow::addToolBar(Qt::TopToolBarArea, toolbar);


    connect(testAction, &QAction::triggered, this, &subassembleqwidget::onTestActionTriggered);
    connect(debugAction, &QAction::triggered, this, &subassembleqwidget::onDebugActionTriggered);
    connect(button1Action, &QAction::triggered, this, &subassembleqwidget::onButton1Clicked);
    connect(button2Action, &QAction::triggered, this, &subassembleqwidget::onButton2Clicked);
    connect(button3Action, &QAction::triggered, this, &subassembleqwidget::onButton3Clicked);
    

    currentSelectedAction = testAction;
    updateButtonStyle(testAction, true);
}


void subassembleqwidget::updateButtonStyle(QAction *action, bool isSelected)
{
    if (!action) return;
    QToolBar *toolbar = findChild<QToolBar*>("mainToolBar");
    if (!toolbar) return;
    QList<QAction*> actions = toolbar->actions();
    for (QAction* act : actions) {
        if (act->property("normalStyle").isValid()) {
            QToolButton* toolButton = qobject_cast<QToolButton*>(toolbar->widgetForAction(act));
            if (toolButton) {
                toolButton->setStyleSheet(act->property("normalStyle").toString());
            }
        }
    }
    if (isSelected && action->property("selectedStyle").isValid()) {
        QToolButton* toolButton = qobject_cast<QToolButton*>(toolbar->widgetForAction(action));
        if (toolButton) {
            toolButton->setStyleSheet(action->property("selectedStyle").toString());
        }
    }
}

/**
 *测试界面
 *
 */
void subassembleqwidget::onTestActionTriggered() {

    QAction *testAction = qobject_cast<QAction*>(sender());
    if (testAction && testAction != currentSelectedAction) {
        updateButtonStyle(currentSelectedAction, false);
        currentSelectedAction = testAction;
        updateButtonStyle(currentSelectedAction, true);
    }

    host_qstackedWidget->setCurrentIndex(0);
    test_case_widget->Refreshfile();
    test_case_widget->isreceivetcp = true;
}

/**
 *调试界面
 *
 */

void subassembleqwidget::onDebugActionTriggered() {

    QAction *debugAction = qobject_cast<QAction*>(sender());
    if (debugAction && debugAction != currentSelectedAction) {
        updateButtonStyle(currentSelectedAction, false);
        currentSelectedAction = debugAction;
        updateButtonStyle(currentSelectedAction, true);
    }

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
}

/**
 *烧录界面
 *
 */
void subassembleqwidget::onButton1Clicked() {

    QAction *button1Action = qobject_cast<QAction*>(sender());
    if (button1Action && button1Action != currentSelectedAction) {
        updateButtonStyle(currentSelectedAction, false);
        currentSelectedAction = button1Action;
        updateButtonStyle(currentSelectedAction, true);
    }
    
    host_qstackedWidget->setCurrentIndex(2);
}

/**
 *版型配置
 *
 */
void subassembleqwidget::onButton2Clicked() {

    QAction *button2Action = qobject_cast<QAction*>(sender());
    if (button2Action && button2Action != currentSelectedAction) {
        updateButtonStyle(currentSelectedAction, false);
        currentSelectedAction = button2Action;
        updateButtonStyle(currentSelectedAction, true);
    }
    
    host_qstackedWidget->setCurrentIndex(3);
}

/**
 *下载测试结果
 *
 */
void subassembleqwidget::onButton3Clicked() {

    QAction *button3Action = qobject_cast<QAction*>(sender());
    if (button3Action && button3Action != currentSelectedAction) {
        updateButtonStyle(currentSelectedAction, false);
        currentSelectedAction = button3Action;
        updateButtonStyle(currentSelectedAction, true);
    }
    
    tcpaap->sendMessageapp("Downloadlog",OUTPUTACCORD);
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

