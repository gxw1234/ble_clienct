#ifndef RUN_ALL_CASE_H
#define RUN_ALL_CASE_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "timelinebucket.h"
#include <QObject>
#include "QtBluetooth/agent.h"
#include "QtBluetooth/controller.h"
#include "QtBluetooth/service.h"
#include "Thread_service/hid_key_input.h"
#include "Thread_service/mythread.h"
#include "QtBluetooth/bluetoothmanager.h"
#include "logwindow.h"

class run_all_case : public QObject
{
     Q_OBJECT
public:
    run_all_case(const QString& str, int value, QList<TimelineBucket*> buckets,QObject *parent = nullptr);
//    void key_signal();
    void go();
    void stop();

private:
    QString m_str;
    int m_value;
    QList<TimelineBucket*> m_buckets;
    QList<QBluetoothDeviceInfo> m_DeviceInfoList;
    QList<QBluetoothUuid> m_ServiceUuidList;
    QList<QLowEnergyCharacteristic> m_CharacteristicList;
    Agent m_agent;
    Controller m_controller;
    Service m_service;
    MyThread * my_case_thread;
    QString targetMacAddress;
    QString connect_text = "---->\n";
    bool m_scan_flag;
    void key_signal();
    void SendMessage(QString);
    QString result_text;
    QString uuid_fc25 ="{0000fc25-0000-1000-8000-00805f9b34fb}";
    void all_init();
    bool assertion_result(const QString str);
    QJsonObject parseCustomStringToJson(const QString &str);
    QList<QString> key_list;
    hid_key_input *input_event_key;
    bluetoothmanager m_bluetoothmanager;
    QString blu_name;
    QList<QString> r_ble_result;
    QList<QString> r_key_result;
    QList<float> r_current_result;
    int line_number = 0;
    bool isallresult ;
    QList<bool> isallresult_list;


public slots:
    void handle_ble_scan_middle_Signal();  //开始扫描
    void handle_ble_connect_middle_Signal(); //开始连接
    void handle_ble_disconnect_middle_Signal();  //断开连接
    void handle_title_middle_Signal(int line, QString title); //单一用例开始之前的信号
    void my_debug_info_middle_Signal(int type_tl, QString b); //单一用例开始之前的信号
    void my_adc_value_middle_Signal(float adc_value);
    void my_handle_all_case_end_middle_Signal(); // 全部结束
    void handle_ble_line_end_middle_Signal(QString); // 单一用例结束
    void handle_key_middle_Signal(QString);
    void handle_hid_key_middle_Signal(QString);
    void handle_onaudio_middle_Signal(QString);
    void onDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void onMessage(QString);
    void onScan_end(bool);
    void onconnect_State(QString);
    void onconnect_err_info(QString);
    void onpari_end(bool);
    void onservice_uuid_end(bool);
    void onservice_ch_end();
    void onServiceDiscovered(QBluetoothUuid);
    void onCharacteristicDiscovered(QLowEnergyCharacteristic);

signals:
//    void mySignal(int intValue, const QString &stringValue);
    void my_ui_debug_info_Signal(int intValue, const QString &stringValue,int result_colour);
    void my_row_Dignal (int line,QString step);
    void my_start_Signal();
    void my_end_Signal(bool);
    void my_row_result_Signal (int line,bool result);
    void message (QString mes);
};

#endif // RUN_ALL_CASE_H
