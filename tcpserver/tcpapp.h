#ifndef TCPAPP_H
#define TCPAPP_H
#include <QObject>
#include "tcpserver/networkservice.h"

#define OUTPUT 0
#define OUTPUTSTARTTEST 1  //开始测试
#define OUTPUTTESTDOCUMENT 2  //发送测试文件
#define OUTPUTTESTNP 3  //发送测试次数
#define OUTPUTTESTMAC 4  //设置MAC地址
#define OUTPUTTESTSTATE 5  //发送获取状态
#define OUTPUTTESNAME 8  //发送测试文件名称 和 所版型

#define OUTPUTINQUIRECFG 11 // 查询配置文件
#define OUTPUTARGUMENT 12 // 查询配置文件
#define OUTPUTFILASTOP 13  // 是否异常停止
#define OUTPUTINFOMAC 16  //查询MAC
#define OUTPUTACCORD 17  //  当发现在测试中，需要同步数据
#define OUTPUTCASENAMELIAT 26 //测试文件list
#define OUTPUTCASENAMEDATALIST 27 //测试文件名称list
#define OUTPUTCASENAMEDATALIST_TO 28 //接收测试文件的名称


enum TCP_client_data {
    Test_Display_list_1 = 0x01, //显示列表
    Test_Display_test_item_2 = 0x02, //显示测试项
    Test_number_3 = 0x03, //测试文件
    Test_mac_3 = 0x04, //mac
    Starttest_4 = 0x01, //开始测试
    Test_file_5 = 0x02, //测试文件
    Test_numbe_6 = 0x03, //测试文件
    Test_Individual_function_14 = 0x14, //每一条用例的每一个功能

};


//字符拼接
#define CONCAT_STRINGS_WITH_AMPERSAND(str1, str2) ((str1) + '&' + (str2))
//返回文本
#define BOOL_TO_STRING(b) ((b) ? "true" : "false")
//判断传的结果
#define STRING_TO_BOOL(str) ((str).compare("true", Qt::CaseInsensitive) == 0 || (str) == "1")
class Tcpapp : public QObject
{
    Q_OBJECT
public:
    explicit Tcpapp(QObject *parent = nullptr);
    ~Tcpapp();
    bool connectAndSetupListenerapp(const QString &host, int port =12345) ;
    bool getconnectstateapp();
    void sendMessageapp(const QString &message, char messageType);
    void sendMessageappQByteArray(const QByteArray &message, char messageType);
    void startWorking(const QString& ip);
private:
    NetworkService *networkService;
    bool getstate;

signals:
    void connectedapp();
    void errorOccurredapp(QString errorString);
    void commandReceivedapp(quint8 dataType, const QByteArray& buffer,bool islen_,bool ismd5_);
    void m_connected_state(bool state);



private slots:
    void onConnectedapp();
    void onErrorOccurredapp(QString errorString);
    void onhandleDataReceivedapp(quint8 dataType, const QByteArray& buffer,bool islen_, bool ismd5_);
    void onconnected_state(bool state);


};

#endif // TCPAPP_H
