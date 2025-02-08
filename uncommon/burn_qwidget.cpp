#include "burn_qwidget.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
burn_qwidget::burn_qwidget(QWidget *parent) : QWidget(parent)
{
    initView();
}

void burn_qwidget::initView()
{

    burn_qlabel =new QLabel;
    burn_qlabel->setText("烧录：");
    burn_lindit = new QLineEdit;

    burn_button = new QPushButton;
    burn_button->setText("选择路径");
    start_burn_button =new QPushButton;
    start_burn_button->setText("开始烧录");
    info_mac_button =new QPushButton;
    info_mac_button->setText("查询MAC");
    showlog = new QTextEdit;
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(burn_qlabel,0,0,1,1);
    layout->addWidget(burn_lindit,0,1,1,1);
    layout->addWidget(burn_button,0,2,1,1);
    layout->addWidget(start_burn_button,0,3,1,1);
    layout->addWidget(info_mac_button,0,4,1,1);
    layout->addWidget(showlog,1,0,1,5);
    connect(burn_button, SIGNAL(clicked()), this, SLOT(selection_path()));
    connect(start_burn_button, SIGNAL(clicked()), this, SLOT(onstart_burn()));
    connect(info_mac_button, SIGNAL(clicked()), this, SLOT(oninfo_mac_button()));
    setLayout(layout);
}

void burn_qwidget::setnetworkserviceOBJECT(Tcpapp *m_tcpaap, bool status)
{
    connection_state = status;
    if (this->tcpaap == nullptr)
    {
        this->tcpaap = m_tcpaap;
        connect(tcpaap,&Tcpapp::commandReceivedapp,this,&burn_qwidget::handleDataReceived);
        connect(tcpaap,&Tcpapp::m_connected_state,this,&burn_qwidget::handleConnected_state);
    }
}

void burn_qwidget::selection_path()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "所有文件 (*.*)");
    burn_lindit->setText(filePath);

}

void burn_qwidget::onstart_burn()
{

    if (connection_state)
    {

        showlog->clear();
        if (burn_lindit->text().isEmpty())

        {
            showlog->append("文件为空");


        }
        else {

            QFile file(burn_lindit->text());
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug() << "无法打开文件：" << burn_lindit->text();
            }
            QByteArray binData = file.readAll();
            qDebug() <<"===========================binData.size=================="<<binData.size();
            file.close();
            tcpaap->sendMessageappQByteArray(binData,14);
        }


    }
    else {
        QMessageBox::information(this, "提示", "TCP连接失败");


    }




}

void burn_qwidget::oninfo_mac_button()
{
    if (connection_state)
    {
    showlog->clear();
    showlog->append("***************正在查询mac***************");
    tcpaap->sendMessageapp("11",OUTPUTINFOMAC);

    }
    else {
        QMessageBox::information(this, "提示", "TCP连接失败");

    }
}

void burn_qwidget::handleDataReceived(quint8 dataType, const QByteArray &buffer, bool islen_, bool ismd5_)
{

    if (ismd5_)
    {
        switch (dataType) {
        case 0x15:
        {
            showlog->append(QString::fromUtf8(buffer));
             break;
        }
        case 0x18:
        {
            showlog->append(QString::fromUtf8(buffer));
             break;
        }
        case 0x19:
        {
            QString allText = showlog->toPlainText();
            QString temp_mark = "run successfully";
            QString temp_text = "";
            if (allText.contains(temp_mark))
            {
                temp_text =  "==================end========= Tburn   pass";
            }
            else
            {
                temp_text =  "==================end========= Tburn   fail";
            }
            showlog->append(temp_text);
            showlog->append("***************正在查询mac***************");
            break;
        }
        default:
            break;
        }
    }
}

void burn_qwidget::handleConnected_state(bool connected_state)
{

     connection_state = connected_state;

}
