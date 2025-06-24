#include "burn_qwidget.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QCoreApplication>
#include <QApplication>
#include <QScrollBar>

// ProcessThread implementation
ProcessThread::ProcessThread(const QString& program, const QStringList& args, QObject* parent)
    : QThread(parent), m_program(program), m_args(args)
{
}
void ProcessThread::run()
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    connect(&process, &QProcess::readyRead, this, [this, &process]() {
        QByteArray output = process.readAll();
        if (!output.isEmpty()) {
            emit outputReceived(QString::fromLocal8Bit(output));
        }
    }, Qt::DirectConnection);
    process.start(m_program, m_args);
    if (!process.waitForStarted()) {
        emit errorOccurred("启动失败");
        return;
    }
    process.waitForFinished(-1);
}

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
    showlog->clear();
    
    QString program = QCoreApplication::applicationDirPath() + "/tool/temp.exe";
    QStringList arguments;
    arguments << "10";
    ProcessThread* thread = new ProcessThread(program, arguments, this);
    

    connect(thread, &ProcessThread::outputReceived, this, [this](const QString& text) {
        showlog->moveCursor(QTextCursor::End);
        showlog->insertPlainText(text);
        showlog->moveCursor(QTextCursor::End);
        showlog->verticalScrollBar()->setValue(showlog->verticalScrollBar()->maximum());
        QApplication::processEvents();  // 强制处理事件
    }, Qt::QueuedConnection);
    

    connect(thread, &ProcessThread::errorOccurred, this, [this](const QString& error) {
        showlog->append("错误：" + error);
    }, Qt::QueuedConnection);
    

    connect(thread, &ProcessThread::finished, thread, &ProcessThread::deleteLater);
    
    showlog->append("蓝牙设备扫描中，扫描10秒，结果最后一起输出。。。。。。。。");
    thread->start();
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
