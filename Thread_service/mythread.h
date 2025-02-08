#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
#include <QThread>
#include "timelinebucket.h"
#include "usb/usbxxx_arrange.h"
#include <QMap>
#include "common/datetimeutil.h"
#include <QEventLoop>
class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread(const QString& str, int value, QList<TimelineBucket*> buckets, QObject* parent = nullptr);
    bool scan_stop = false;
    bool connect_stop = false;
    bool scan_flag = false;
    bool disconnect_stop = false;
    void stop();
signals:
    void mySignal(int intValue, const QString &stringValue);
    void my_debug_info_Signal(int intValue, const QString &stringValue);
    void my_start_Signal();
    void my_end_Signal();
    void my_line_end_Signal(QString);
    void my_ble_scan_Signal();
    void my_ble_connect_Signal();
    void my_ble_disconnect_Signal();
    void my_read_adc(float adc_value);
    void message(QString msg);

public slots:
    void h_determine_key_down(QString param);
    void h_determine_key_upward(QString param);
    void h_function1(QString param);
    void h_tv_key_down(QString param);
    void h_tv_key_upward(QString param);
    void h_msleep(QString param);
    void h_scan_ble(QString param);
    void h_connect_ble(QString param);
    void h_disconnect_ble(QString param);
    void h_pair_ble(QString param);
    void h_read_voltage(QString param);
    void h_voice_voltage(QString param);
    void h_1_key_down(QString param);
    void h_1_key_upward(QString param);
    void h_2_key_down(QString param);
    void h_2_key_upward(QString param);
    void h_voice_key_down(QString param);
    void h_voice_key_upward(QString param);



protected:
    void run() override;


private:
    QString m_str;
    int m_value;
    QList<TimelineBucket*> m_buckets;
    QMap<QString, void (MyThread::*)(QString)> functionsMap;
    bool usb_init();
    void key_signal();
    void all_init();
    usbxxx_arrange usb_handle;
    bool m_scan_flag;
    QString targetMacAddress;
    QString connect_text = "---->\n";
    QString assertion_text;
    void SendMessage(QString info);
    bool isruning;

};

#endif // MYTHREAD_H
