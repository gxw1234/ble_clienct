#include "mythread.h"
#include <QDebug>
#include <QDateTime>
#include <QTimer>
MyThread::MyThread(const QString &str, int value, QList<TimelineBucket *> buckets, QObject *parent)
    : QThread(parent), m_str(str), m_value(value), m_buckets(buckets) {
    functionsMap["按键配对"] = &MyThread::h_function1;
    functionsMap["TV按键按下"] = &MyThread::h_tv_key_down;
    functionsMap["TV按键抬起"] = &MyThread::h_tv_key_upward;
    functionsMap["确定按键按下"] = &MyThread::h_determine_key_down;
    functionsMap["确定按键抬起"] = &MyThread::h_determine_key_upward;
    functionsMap["延时"] = &MyThread::h_msleep;
    functionsMap["扫描"] = &MyThread::h_scan_ble;
    functionsMap["连接"] = &MyThread::h_connect_ble;
    functionsMap["断开"] = &MyThread::h_disconnect_ble;
    functionsMap["配对"] = &MyThread::h_pair_ble;
    functionsMap["读取功耗"] = &MyThread::h_read_voltage;
    functionsMap["语音按键按下"] = &MyThread::h_voice_key_down;
    functionsMap["语音按键抬起"] = &MyThread::h_voice_key_upward;
    functionsMap["按键1开"] = &MyThread::h_1_key_down;
    functionsMap["按键1关"] = &MyThread::h_1_key_upward;
    functionsMap["按键2开"] = &MyThread::h_2_key_down;
    functionsMap["按键2关"] = &MyThread::h_2_key_upward;
    isruning= false;
}

void MyThread::stop()
{
    isruning =true;


}

void MyThread::h_determine_key_down(QString param)
{
    usb_handle._Key_down(0x4,0x1000);
}

void MyThread::h_determine_key_upward(QString param)
{
    usb_handle._Key_lift(0x4,0x1000);
}

//--------------按键配对--------
void MyThread::h_function1(QString param)
{
    usb_handle._Key_down(0x4,0x1000);
    usb_handle._Key_down(0x4,0x4000);
    QThread::msleep(5000);
    usb_handle._Key_lift(0x4,0x1000);
    usb_handle._Key_lift(0x4,0x4000);
}

void MyThread::h_tv_key_down(QString param)
{
    usb_handle._Key_down(0x10,0x4000);
}

void MyThread::h_tv_key_upward(QString param)
{
    usb_handle._Key_lift(0x10,0x4000);
}

//延时
void MyThread::h_msleep(QString sleep_time)
{
    QRegExp regex("\\d+");
    int delay = 1000;
    if (regex.indexIn(sleep_time) != -1) {
        delay = regex.cap(0).toInt();
    }
    QString delayString = QString::number(delay);
    SendMessage("msleep: "+delayString);
    QThread::msleep(delay);

}

//扫描
void MyThread::h_scan_ble(QString param)
{
    emit my_ble_scan_Signal();
    SendMessage("多线程开始扫描");
    QElapsedTimer timer;
    timer.start();
    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    SendMessage(currentDateTime +"扫描时间1----------------s");
    qint64 t1 = QDateTime::currentMSecsSinceEpoch();
    while (1) {
        QThread::msleep(200);
        qint64 t2 = QDateTime::currentMSecsSinceEpoch();
        if (t2 - t1 >=4000) {
            break;
        }
        if(scan_stop)
        {
            break;
        }
    }


    QDateTime currentTime1 = QDateTime::currentDateTime();
    QString formattedTime1 = currentTime1.toString("yyyy-MM-dd HH:mm:ss:zzz");
    SendMessage( formattedTime1 +"扫描时间2----------------e");
    scan_stop =false;
}
void MyThread::h_connect_ble(QString param)
{
    emit my_ble_connect_Signal();
    SendMessage("多线程开始连接");
    QElapsedTimer timer;
    timer.start();
    while (!connect_stop) {
        QThread::msleep(200);
        if (timer.elapsed() >= 7000) {
            break;
        }
    }
    SendMessage("多线程结束连接");
    connect_stop =false;
}

void MyThread::h_disconnect_ble(QString param)
{
    emit my_ble_disconnect_Signal();
    QElapsedTimer timer;
    timer.start();
    while (!disconnect_stop) {
        QThread::msleep(100);
        if (timer.elapsed() >= 5000) {
            break;
        }
    }
    disconnect_stop =false;

}
void MyThread::h_pair_ble(QString param)
{

}

void MyThread::h_read_voltage(QString param)
{

    float adc_value;
    adc_value =usb_handle._read_adc_usbxxx();
    emit my_read_adc(adc_value);

}

void MyThread::h_voice_voltage(QString param)
{

}

void MyThread::h_1_key_down(QString param)
{

}

void MyThread::h_1_key_upward(QString param)
{

}

void MyThread::h_2_key_down(QString param)
{

}

void MyThread::h_2_key_upward(QString param)
{

}

void MyThread::h_voice_key_down(QString param)
{


    usb_handle._Key_down(0x8,0x80);

}

void MyThread::h_voice_key_upward(QString param)
{
    usb_handle._Key_lift(0x8,0x80);
}


void MyThread::run()
{
    emit my_start_Signal( );

    if (usb_init())

    {
        for (int i = 0; i < m_buckets.size(); i++) {
            TimelineBucket* bucket = m_buckets.at(i);
            QString title;
            title =bucket->getTime();
            emit mySignal(i,title );
            QStringList text_;
            text_  = bucket->getTexts();
            emit my_debug_info_Signal(0,title+ "--->\n");
            assertion_text ="";
            for(const QString& text : text_) {
                QString temp;
                temp = text;
                temp.remove(' ');
                QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
                SendMessage("------->case: "+currentDateTime+temp);
                if (temp.contains("延时"))
                {
                    h_msleep(temp);
//                    auto delayFunctionPtr = functionsMap["延时"];
//                    using FunctionType = void (MyThread::*)(QString);
//                    FunctionType typedFunctionPtr = reinterpret_cast<FunctionType>(delayFunctionPtr);
//                    (this->*typedFunctionPtr)(temp);
                }
                else if (temp.contains("断言")) {
                    assertion_text =temp;
                }
                else if (temp.contains("扫描")) {
                    h_scan_ble(temp);
                }
                else if (temp.contains("连接")) {
                    h_connect_ble(temp);
                }
                else
                {

                    auto functionPtr = functionsMap[temp];
                    if (functionPtr)
                    {
                        using FunctionType = void (MyThread::*)(QString);
                        FunctionType typedFunctionPtr = reinterpret_cast<FunctionType>(functionPtr);
                        (this->*typedFunctionPtr)(temp);
                    }
                    else
                    {
                        qDebug() << "Function does not exist."<<temp;
                    }
                }



                if(isruning)
                {
                    break;
                }
            }
            QThread::msleep(100);
            emit my_line_end_Signal(assertion_text);
            assertion_text ="";
            if(isruning)
            {
                break;
            }
        }
    }
    else {
        emit my_debug_info_Signal(1, "设备未打开" );
    }
    QThread::msleep(100);
    usb_handle._close_usbxxx();
    SendMessage("测试完成");
    emit my_end_Signal( );
}

bool MyThread::usb_init()
{
    bool ret;
    ret = usb_handle._open_usbxxx();
    return ret;
}

void MyThread::SendMessage(QString info)
{

    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    emit message(currentDateTime +info);

}




