#include "run_all_case.h"
#include <QDebug>
run_all_case::run_all_case(const QString& str, int value, QList<TimelineBucket*> buckets, QObject *parent)
{
    m_str = str;
    m_value = value;
    m_buckets = buckets;
    key_signal();

}

void run_all_case::key_signal()
{
    connect(&m_agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(onDeviceDiscovered(QBluetoothDeviceInfo)));
    connect(&m_agent, SIGNAL(message(QString)), this, SLOT(onMessage(QString)));
    connect(&m_agent, SIGNAL(Scan_end(bool)), this, SLOT(onScan_end(bool)));
    connect(&m_controller, SIGNAL(message(QString)), this, SLOT(onMessage(QString)));
    connect(&m_controller, SIGNAL(connect_State(QString)), this, SLOT(onconnect_State(QString)));
    connect(&m_controller, SIGNAL(pair_end(bool)), this, SLOT(onpari_end(bool)));
    connect(&m_controller, SIGNAL(serviceDiscovered(QBluetoothUuid)), this, SLOT(onServiceDiscovered(QBluetoothUuid)));
    connect(&m_controller, SIGNAL(service_uuid_end(bool)), this, SLOT(onservice_uuid_end(bool)));
    connect(&m_controller, SIGNAL(connect_err_info(QString)), this, SLOT(onconnect_err_info(QString)));

    //服务
    connect(&m_service, SIGNAL(discoveryCharacteristic(QLowEnergyCharacteristic)), this, SLOT(onCharacteristicDiscovered(QLowEnergyCharacteristic)));
    connect(&m_service, SIGNAL(message(QString)), this, SLOT(onMessage(QString)));
    connect(&m_service, SIGNAL(onStateChanged_end()), this, SLOT(onservice_ch_end()));
    connect(&m_service, SIGNAL(onKeyresult(QString )), this, SLOT(handle_key_middle_Signal(QString )));
    connect(&m_service, SIGNAL(onaudio(QString )), this, SLOT(handle_onaudio_middle_Signal(QString )));
    connect(&m_bluetoothmanager, SIGNAL(message(QString)), this, SLOT(onMessage(QString)));
}

void run_all_case::SendMessage(QString info)
{

     qDebug() << info;

     emit  message( info);
}

void run_all_case::all_init()
{
    isallresult_list.clear();
    m_DeviceInfoList.clear();
    m_ServiceUuidList.clear();
    m_CharacteristicList.clear();
    r_key_result.clear();
    r_ble_result.clear();
    r_current_result.clear();

}

bool run_all_case::assertion_result(const QString expectation_text)
{

    if (!expectation_text.isEmpty()) {
        QList<bool> results;
        bool result =false;
        QString str =expectation_text;
        qDebug () <<"expectation" <<str ;
        QJsonObject json = parseCustomStringToJson(str);
        QStringList expectation_key, expectation_ble, expectation_current;
        for (QJsonObject::const_iterator iter = json.constBegin(); iter != json.constEnd(); ++iter) {
            if (iter.key() == "蓝牙" && iter.value().isArray()) {
                QJsonArray jsonArray = iter.value().toArray();
                for (const QJsonValue &value : jsonArray) {
                    expectation_ble.append(value.toString());
                }
            }
            else if (iter.key() == "按键" && iter.value().isArray()) {
                QJsonArray jsonArray = iter.value().toArray();
                for (const QJsonValue &value : jsonArray) {
                    expectation_key.append(value.toString());
                }
            }
            else if (iter.key() == "电流" && iter.value().isArray()) {
                QJsonArray jsonArray = iter.value().toArray();
                for (const QJsonValue &value : jsonArray) {
                    expectation_current.append(value.toString());
                }
            }
        }
        if (expectation_key.size() !=0)
          {
              if (expectation_key.size() == r_key_result.size()){
                  for (int i = 0; i < expectation_key.size(); i++)
                  {
                      qDebug() <<"PASS";
                      if (expectation_key[i] != r_key_result[i])
                      {
                          results.append(false);
                      }
                  }
              }
              else {
                  results.append(false);
              }
          }
        if (expectation_ble.size() !=0)
        {
            if (expectation_ble.size() == r_ble_result.size()){
                for (int i = 0; i < expectation_ble.size(); i++)
                {
                    if (expectation_ble[i] != r_ble_result[i])
                    {
                        results.append(false);
                    }
                    else {
                        qDebug() <<"-----PASS------";
                    }
                }
            }
            else {
                results.append(false);
            }
        }
        if (expectation_current.size() !=0)
        {
            if (expectation_current.size() == r_current_result.size()){
                for (int i = 0; i < expectation_current.size(); i++)
                {
                    bool ok1;
                    float expectation_float = expectation_current[i].toDouble(&ok1);
                    float reality_float = r_current_result[i];
                    if (expectation_float < reality_float)
                    {
                        results.append(false);
                    }
                    else {
                        qDebug()<< "-----pass-----";
                    }
                    qDebug()<< expectation_float  <<reality_float ;
                }
            }
            else {

                results.append(false);
            }

        }

        if (results.contains(false)){
            result =false;
            result_text = "结果异常\n";
            emit my_ui_debug_info_Signal(1,result_text,3);
        }
          else {
              result =true;
              result_text = "结果正常\n";
              emit my_ui_debug_info_Signal(1,result_text,2);
          }
        isallresult_list.append(result);
        result_text ="-------实测结果------\n";
        result_text.append("按键:[" );
        emit my_row_result_Signal(line_number, result);
        for (const QString &key : r_key_result) {
            result_text.append(key+",");
        }
        result_text.append("]\n" );
        result_text.append("蓝牙:[" );
        for (const QString &ble : r_ble_result) {
            result_text.append(ble+",");
        }
        result_text.append("]\n" );
        result_text.append("电流:[" );
        for (const float &current : r_current_result) {
            result_text.append(QString::number(current, 'f', 3) +",");
        }
        result_text.append("]\n" );
        emit my_ui_debug_info_Signal(1,result_text,1);
        return result;
       }
    else {
        result_text = "结果异常\n断言为空";
        emit my_ui_debug_info_Signal(1,result_text,3);
        return false;
    }
}

QJsonObject run_all_case::parseCustomStringToJson(const QString &str)
{
    QJsonObject result;
    QString jsonPart = str;
    jsonPart.replace("【", "{").replace("】", "}").replace("：", ":").replace("，", ",").replace("[", "").replace("]", "");
    jsonPart = jsonPart.mid(jsonPart.indexOf("{") + 1, jsonPart.lastIndexOf("}") - jsonPart.indexOf("{") - 1);
    QStringList pairs = jsonPart.split(",", Qt::SkipEmptyParts);
    QString currentKey;
    QJsonArray currentArray;
    foreach (const QString &pair, pairs) {
        if (pair.contains(":")) {
            if (!currentKey.isEmpty()) {
                result.insert(currentKey, currentArray);
                currentArray = QJsonArray();
            }
            QStringList keyValue = pair.split(":");
            if (keyValue.size() == 2) {
                currentKey = keyValue.at(0).trimmed();
                QString value = keyValue.at(1).trimmed();
                currentArray.append(value);
            }
        } else {

            currentArray.append(pair.trimmed());
        }
    }

    if (!currentKey.isEmpty()) {
        result.insert(currentKey, currentArray);
    }
    return result;
}

void run_all_case::go()
{
    all_init();
    my_case_thread = new MyThread(m_str,m_value,m_buckets);
//    connect(my_case_thread, SIGNAL(my_ble_scan_Signal()), this, SLOT(handle_ble_scan_middle_Signal()), Qt::QueuedConnection);
    connect(my_case_thread, SIGNAL(my_debug_info_Signal(int, QString)), this, SLOT(my_debug_info_middle_Signal(int, QString)), Qt::QueuedConnection);
//    connect(my_case_thread, SIGNAL(my_ble_connect_Signal()), this, SLOT(handle_ble_connect_middle_Signal()), Qt::QueuedConnection);
    connect(my_case_thread, SIGNAL(my_ble_disconnect_Signal()), this, SLOT(handle_ble_disconnect_middle_Signal()), Qt::QueuedConnection);
    connect(my_case_thread, SIGNAL(mySignal(int, QString)), this, SLOT(handle_title_middle_Signal(int, QString)), Qt::QueuedConnection);
    connect(my_case_thread, SIGNAL(my_line_end_Signal(QString)), this, SLOT(handle_ble_line_end_middle_Signal(QString)), Qt::QueuedConnection);
    connect(my_case_thread, SIGNAL(my_end_Signal()), this, SLOT(my_handle_all_case_end_middle_Signal()), Qt::QueuedConnection);
    connect(my_case_thread, SIGNAL(my_read_adc(float)), this, SLOT(my_adc_value_middle_Signal(float)), Qt::QueuedConnection);
    connect(my_case_thread, SIGNAL(message(QString)), this, SLOT(onMessage(QString)), Qt::QueuedConnection);


    connect(my_case_thread, &MyThread::my_ble_connect_Signal,
            this, &run_all_case::handle_ble_connect_middle_Signal,
            Qt::QueuedConnection);


    connect(my_case_thread, &MyThread::my_ble_scan_Signal,
            this, &run_all_case::handle_ble_scan_middle_Signal,
            Qt::QueuedConnection);

    my_case_thread->start();
}

void run_all_case::stop()
{


}
void run_all_case::my_handle_all_case_end_middle_Signal()
{

    qDebug() <<"12344";
    QThread::msleep(100);
    my_case_thread->wait();
//    input_event_key->wait();
    delete my_case_thread;
//    delete  input_event_key;
    qDebug() <<"1234w1134";
    bool containsFalse = isallresult_list.contains(false);
    emit my_end_Signal(!containsFalse);
}
void run_all_case::handle_ble_line_end_middle_Signal(QString assertion)
{

    SendMessage("end-------");
    assertion_result(assertion);
}

void run_all_case::handle_hid_key_middle_Signal(QString value)
{
    r_key_result.append(value);
}

void run_all_case::handle_key_middle_Signal(QString value)
{
    QString text ="";
    if(value == "语音按下")
    {
        text ="04 01";
    }
    else if (value == "语音抬起") {
        text ="04 00";
    }
    SendMessage("fc28"+value);
    m_service.WriteCharacteristic(m_CharacteristicList.at(1), QByteArray::fromHex(text.toLatin1()));
}

void run_all_case::handle_onaudio_middle_Signal(QString audio)
{

    qDebug() << "audio_data" <<audio;

}

// info
void run_all_case::handle_title_middle_Signal(int line, QString step)
{
    my_case_thread->scan_stop =false;
    my_case_thread->connect_stop =false;
    my_case_thread->scan_flag =false;
    my_case_thread->disconnect_stop =false;
    m_bluetoothmanager.remove_pari_name();
    result_text = "" ;
    all_init();
    line_number = line;
    emit my_row_Dignal(line,step);
    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    SendMessage(currentDateTime +"=========================="+step+"==========================");
}

void run_all_case::my_debug_info_middle_Signal(int type_tl, QString b)
{
    emit my_ui_debug_info_Signal(type_tl,b,1);
}

void run_all_case::my_adc_value_middle_Signal(float adc_value)
{
    r_current_result.append(adc_value);
}


void run_all_case::handle_ble_scan_middle_Signal()
{

    m_DeviceInfoList.clear();
    m_ServiceUuidList.clear();
    m_CharacteristicList.clear();
    m_DeviceInfoList.clear();
    targetMacAddress = m_str;
    m_agent.startScanDevice(5000,m_str);

}

void run_all_case::handle_ble_connect_middle_Signal()
{
    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    SendMessage( currentDateTime+"开始连接1");
    if (m_scan_flag)
    {
        int index = -1;
        for (int i = 0; i < m_DeviceInfoList.size(); i++)
        {
            if (m_DeviceInfoList[i].address().toString() == targetMacAddress)
            {
                blu_name =m_DeviceInfoList[i].name();
                index = i;
                break;
            }
        }
        if((index >= 0) && (m_DeviceInfoList.size() > index))
        {
            m_controller.ConnectDevice(m_DeviceInfoList.at(index));
        }
    }
    else {

        my_case_thread->connect_stop =true;
    }

}

void run_all_case::handle_ble_disconnect_middle_Signal()
{
    qDebug() <<"handle_ble_disconnect_middle_Signal";
//    input_event_key->stop();

    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    SendMessage(currentDateTime +"开始断开");
    m_controller.DisconnectDevice();
    qDebug() <<"handle_ble_disconnect_middle_Signal--";


}

void run_all_case::onDeviceDiscovered(const QBluetoothDeviceInfo &info)
{
    m_DeviceInfoList.append(info);

}

void run_all_case::onMessage(QString str)
{
    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    SendMessage(currentDateTime  + str);
}

//如果扫描不到就不连接
void run_all_case::onScan_end(bool end_bool)
{

    if (end_bool)
    {
        result_text = "已扫描到";
    }
    else {
        result_text = "未扫描到";
    }
    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    SendMessage(currentDateTime +result_text);
    r_ble_result.append(result_text);
    m_scan_flag =end_bool;
    my_case_thread->scan_stop =true;

}

void run_all_case::onconnect_State(QString end_bool)
{
    if (end_bool == "device connected")
    {
        result_text = "已连接";

    }
    else {
        my_case_thread->disconnect_stop =true;
        result_text = "已断开";

    }
    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    SendMessage(currentDateTime +result_text);

    r_ble_result.append(result_text);
}

void run_all_case::onconnect_err_info(QString err_info)
{

    if(err_info == "UnconnectedState")
    {

    }
}

void run_all_case::onpari_end(bool end_bool)
{
    if (end_bool)
    {
        QThread::msleep(1000);
//        input_event_key = new hid_key_input(blu_name);
//        connect(input_event_key, SIGNAL(my_key_Signal(QString )), this, SLOT(handle_hid_key_middle_Signal(QString )));
//        input_event_key->start();
        QThread::msleep(1000);
        my_case_thread->connect_stop =true;
        result_text = "已配对";
    }
    else {
        result_text = "未配对";
    }
    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
    SendMessage(currentDateTime + result_text);
    r_ble_result.append(result_text);
}


void run_all_case::onservice_uuid_end(bool)
{
    QUuid uuid(uuid_fc25);
    int index = m_ServiceUuidList.indexOf(uuid);
    if((index >= 0) && m_ServiceUuidList.size() > index)
    {
        QLowEnergyService *service = m_controller.CreateService(m_ServiceUuidList.at(index));
        m_service.ConnectService(service);
    }
}

void run_all_case::onservice_ch_end()
{

//    qDebug() <<"m_CharacteristicLissize:" <<m_CharacteristicList.size();
//    for(int i = 0; i < m_CharacteristicList.size(); i++) {
//        QLowEnergyCharacteristic ch = m_CharacteristicList.at(i);
//        quint16 handleValue = ch.handle();
//        QString handleStr = QString::number(handleValue,16);
//        qDebug() << "-----" <<i <<"----------"<<ch.uuid().toString() << "   handleStr:" <<handleValue;
//    }
//    m_service.OpenNotify(m_CharacteristicList.at(8),true);


//    qDebug() <<"写入------------------";
//    QString ss = "04 01";
//    m_service.WriteCharacteristic(m_CharacteristicList.at(1),ss.toLatin1());
//    my_case_thread->connect_stop =true;
}

void run_all_case::onServiceDiscovered(QBluetoothUuid uuid)
{

    m_ServiceUuidList.append(uuid);



}
void run_all_case::onCharacteristicDiscovered(QLowEnergyCharacteristic ch)
{
    m_CharacteristicList.append(ch);

}


