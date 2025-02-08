#include "disposition.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
Disposition::Disposition(QWidget *parent) : QWidget(parent)
{

    initView();
    FunctionModuleList.append(FunctionModule("延时","",""));
    FunctionModuleList.append(FunctionModule("扫描","",""));
    FunctionModuleList.append(FunctionModule("连接","",""));
    FunctionModuleList.append(FunctionModule("断开","",""));
    FunctionModuleList.append(FunctionModule("配对","",""));
    FunctionModuleList.append(FunctionModule("取消配对","",""));
    FunctionModuleList.append(FunctionModule("上电","",""));
    FunctionModuleList.append(FunctionModule("设置电压","",""));
    FunctionModuleList.append(FunctionModule("抖动上电","",""));
    FunctionModuleList.append(FunctionModule("读取LED","",""));
    FunctionModuleList.append(FunctionModule("随机按键","",""));
    FunctionModuleList.append(FunctionModule("接收结果","",""));
    FunctionModuleList.append(FunctionModule("不接收结果","",""));
    FunctionModuleList.append(FunctionModule("蓝牙连接前置","",""));
    FunctionModuleList.append(FunctionModule("蓝牙连接后置","",""));
    FunctionModuleList.append(FunctionModule("读取功耗","",""));

    ReadVersionList.append(ReadVersion("读取SN","",""));

}

void Disposition::initView()
{
    burn_qlabel =new QLabel;
    burn_qlabel->setText("配置名称：");
    burn_lindit = new QLineEdit;


    start_study_button =new QPushButton;
    start_study_button->setText("开始配置");

    generate_json_button =new QPushButton;
    generate_json_button->setText("生成配置");

    QSpinBox_cdm =new QSpinBox;


    Generate_cmd =new QPushButton;
    Generate_cmd->setText("生成协议");



    showlog = new QTextEdit;
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(burn_qlabel,0,0,1,1);
    layout->addWidget(burn_lindit,0,1,1,1);
    layout->addWidget(start_study_button,0,3,1,1);
    layout->addWidget(generate_json_button,0,4,1,1);
    layout->addWidget(showlog,1,0,1,4);
    layout->addWidget(QSpinBox_cdm,0,5,1,1);
    layout->addWidget(Generate_cmd,0,6,1,1);

    connect(start_study_button, SIGNAL(clicked()), this, SLOT(onstart_burn()));
    connect(generate_json_button, SIGNAL(clicked()), this, SLOT(onstart_savejson()));
    connect(Generate_cmd, SIGNAL(clicked()), this, SLOT(Generate_cmd_start()));
    setLayout(layout);


}

void Disposition::setnetworkserviceOBJECT(Tcpapp *m_tcpaap, bool status)
{

    connection_state = status;
    if (this->tcpaap == nullptr)
    {
        this->tcpaap = m_tcpaap;
        connect(tcpaap,&Tcpapp::commandReceivedapp,this,&Disposition::handleDataReceived);
        connect(tcpaap,&Tcpapp::m_connected_state,this,&Disposition::handleConnected_state);
    }
}

QJsonArray  Disposition::createSingleKeyPressJson(const QList<SingleKeyPress>& keyPressList)
{
    QJsonArray array;
    for (const SingleKeyPress& keyPress : keyPressList) {
        QJsonObject obj;
        obj["feature_name"] = keyPress.feature_name;
        obj["key_cmd"] = keyPress.key_cmd;
        obj["key_ir"] = keyPress.key_ir;
        obj["key_ble"] = keyPress.key_ble;
        obj["handler"] = keyPress.handler;
        array.append(obj);
    }
    return array;
}

QJsonArray  Disposition::createSingleKeyUpJson(const QList<SingleKeyUp>& keyUpList)
{
    QJsonArray array;
    for (const SingleKeyUp& keyUp : keyUpList) {
        QJsonObject obj;
        obj["feature_name"] = keyUp.feature_name;
        obj["key_cmd"] = keyUp.key_cmd;
        array.append(obj);
    }
    return array;
}

QJsonArray  Disposition::createSingleFunctionModuleJson(const QList<FunctionModule>& FunctionModuleList)
{
    QJsonArray array;
    for (const FunctionModule& Module : FunctionModuleList) {
        QJsonObject obj;
        obj["feature_name"] = Module.feature_name;
        obj["description"] = Module.description;
        obj["_assert"] = Module._assert;
        array.append(obj);
    }
    return array;
}

QJsonArray Disposition::createSingleReadVersionJson(const QList<ReadVersion> &ReadVersionList)
{
    QJsonArray array;
    for (const ReadVersion& Version : ReadVersionList) {
        QJsonObject obj;
        obj["feature_name"] = Version.feature_name;
        obj["description"] = Version.description;
        obj["_assert"] = Version._assert;
        array.append(obj);
    }
    return array;

}



QJsonArray Disposition::createSingleKeyUpJson(const QList<TriggerKey> &TriggerKeyList)
{

    QJsonArray array;
    for (const TriggerKey& keyUp : TriggerKeyList) {
        QJsonObject obj;
        obj["feature_name"] = keyUp.feature_name;
        obj["first_key_cmd"] = keyUp.first_key_cmd;
        obj["delay"] = keyUp.delay;
        obj["after_key_cmd"] = keyUp.after_key_cmd;
        array.append(obj);
    }
    return array;

}

void Disposition::onstart_burn()
{
    showlog->clear();
    if(connection_state)

    {
        tcpaap->sendMessageapp("info",15);
    }

    else {


    }

    showlog->append("生成配置中。。。。。。");
    singleKeyPressList.clear();
    singleKeyUpList.clear();
    TriggerKeyList.clear();


}

void Disposition::handleDataReceived(quint8 dataType, const QByteArray &buffer, bool islen_, bool ismd5_)
{
    if (ismd5_)
    {
        switch (dataType) {
        case 0x13:
        {
            QString data = QString::fromUtf8(buffer);
            QStringList protlist = data.split("&", QString::SkipEmptyParts);
            showlog->append("按下：" +protlist.at(0) +"    抬起："  + protlist.at(1)  +"     按键值：" + protlist.at(2));
            singleKeyPressList.append(SingleKeyPress(protlist.at(2) +"按键按下",protlist.at(0),"","",""));
            singleKeyUpList.append(SingleKeyUp(protlist.at(2) +"按键抬起",protlist.at(1)));
            TriggerKeyList.append(TriggerKey(protlist.at(2) +"按键触发",protlist.at(0),1000,protlist.at(1) ));
            break;
        }
        default:
            break;

        }
    }

}

void Disposition::handleConnected_state(bool connected_state)
{
    connection_state = connected_state;
}

void Disposition::onstart_savejson()
{
    if (burn_lindit->text() =="")
    {
        QMessageBox::information(this, "提示", "文件名称不能为空");
    }
    else {
    QString filePath = QFileDialog::getExistingDirectory(this, "选择文件存放路径", QDir::homePath());
    QJsonObject rootObject;
    rootObject["single_key_press"] = createSingleKeyPressJson(singleKeyPressList);
    rootObject["single_key_up"] = createSingleKeyUpJson(singleKeyUpList);
    rootObject["trigger_key"] = createSingleKeyUpJson(TriggerKeyList);
    rootObject["Function_module"] = createSingleFunctionModuleJson(FunctionModuleList);
    rootObject["Read_version"] = createSingleReadVersionJson(ReadVersionList);
    QJsonDocument jsonDoc(rootObject);

    QString jsfilePath = filePath + "/"+burn_lindit->text() +".json";
    QFile file(jsfilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }
    file.write(jsonDoc.toJson());
    file.close();
    }
}

void Disposition::Generate_cmd_start()
{
    QString key_down  = get_cmd.key_down(QSpinBox_cdm->value());
    QString key_upward  = get_cmd.key_upward(QSpinBox_cdm->value());
    showlog->append("按下：" +key_down +"    抬起："  + key_upward  +"     按键值：" + QString::number(QSpinBox_cdm->value()));
}
