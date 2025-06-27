#include "generate_case_qwidget.h"
#include <QGridLayout>
#include <QScrollArea>
#include <QThread>
#include "common/mapfle.h"

Generate_case_qwidget::Generate_case_qwidget(QWidget *parent) : QWidget(parent)
{

    QString currentPath = QDir::currentPath();
    testFilePath = currentPath + "/test_file/";
    suffix_text =".json";
    connection_state =false;
    initView();
}
void Generate_case_qwidget::initView()
{
    test_file_qroupbox = new QGroupBox();
    test_file_qroupbox->setMaximumSize(100000,200);
    file_qlabel = new QLabel;
    file_qlabel->setText("测试文件选择：");
    file_box_new = new QComboBox;


    save_file_button_qlabel =new QLabel;
    save_file_button_qlabel->setText("新增测试文件：");
    file_box_new->addItems(get_all_file());
    added_file_lindit =new QLineEdit;
    added_file_button = new  QPushButton;
    added_file_button->setText("新增测试文件名");

    added_refresh = new  QPushButton;
    added_refresh->setText("刷新");

    save_file_button = new  QPushButton;
    save_file_button->setText("保存文件");
    delete_file_button = new  QPushButton;
    delete_file_button->setText("删除文件");
    pattern_label = new QLabel;
    pattern_label->setText("所属版型:");

    pattern_label1 = new QLabel;
    pattern_label1->setText("所属版型:");
    pattern_qlneEdit = new QLineEdit;
    pattern_qlneEdit->setStyleSheet("background: transparent;");
    pattern_qlneEdit->setMaximumSize(200, 30);
    pattern_qlneEdit->setReadOnly(true);


    rewrite_file_widget =new TimelineWidget;

    (new TimelineUndoStack(rewrite_file_widget));
    rewrite_file_widget->setpop_up(true);
    connect(rewrite_file_widget, SIGNAL(targetItemsChanged_ch(int, QString,QStringList)), this, SLOT(c_Click_event_Signal(int, QString,QStringList)));
    connect(rewrite_file_widget,SIGNAL(selectItemsChanged( QVector<QVariant>)),this,SLOT(acceptSelectItemsChanged( QVector<QVariant>)));

    connect(rewrite_file_widget, SIGNAL(debugChanged_ch()), this, SLOT(m_debugChanged_ch()));
    assertion_text = new QTextEdit;
//    assertion_text->setMaximumSize(400, 200);

    assertion_QFrame = new QFrame;
    test_text = new QTextEdit;
    assertion_QFrame->setMaximumSize(400, 200);
    pattern_new = new QComboBox;

    QGridLayout *assertion_QFrame_layout = new QGridLayout(assertion_QFrame);
    assertion_QFrame_layout->addWidget(assertion_text,0,0,1,1);
    assertion_QFrame_layout->addWidget(test_text,1,0,1,1);
    QSpacerItem* separator = new QSpacerItem(1, 2, QSizePolicy::Fixed, QSizePolicy::Minimum);

    rewrite_file_widget->adjustBucketsPositionsWithAnimation();
    QGridLayout *qroupbox_layout = new QGridLayout(test_file_qroupbox);
    qroupbox_layout->addWidget(file_qlabel,0,0,1,1);
    qroupbox_layout->addWidget(file_box_new,0,1,1,1);

    qroupbox_layout->addWidget(pattern_label,0,2,1,1);
    qroupbox_layout->addWidget(pattern_qlneEdit,0,3,1,1);
    qroupbox_layout->addWidget(save_file_button,0,4,1,1);
    qroupbox_layout->addWidget(delete_file_button,0,5,1,1);



    qroupbox_layout->addWidget(save_file_button_qlabel,1,0,1,1);
    qroupbox_layout->addWidget(added_file_lindit,1,1,1,1);
    qroupbox_layout->addWidget(pattern_label1,1,2,1,1);
    qroupbox_layout->addWidget(pattern_new,1,3,1,1);
    qroupbox_layout->addWidget(added_file_button,1,4,1,1);
    qroupbox_layout->addWidget(added_refresh,1,5,1,1);



    widget_case = new MyDragWidget;
    connect( widget_case, &MyDragWidget::Tipsevent, this, &Generate_case_qwidget::handTipsevent);
    connect( widget_case, &MyDragWidget::Tipsleavevent, this, &Generate_case_qwidget::handTipsleavevent);
    connect( widget_case, &MyDragWidget::myselect_Device, this, &Generate_case_qwidget::handleselect_Device);
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(test_file_qroupbox,0,0,1,10);
    layout->addWidget(assertion_QFrame,0,10,1,2);
    layout->addWidget(rewrite_file_widget,1,0,1,10);
    layout->addWidget(widget_case,1,10,1,2);
    setLayout(layout);
    connect(save_file_button, SIGNAL(clicked()), this, SLOT(save_file_func()));
    connect(added_file_button, SIGNAL(clicked()), this, SLOT(added_file_func()));

    connect(added_refresh, SIGNAL(clicked()), this, SLOT(added_refresh_func()));

    connect(delete_file_button, SIGNAL(clicked()), this, SLOT(deletefile_func()));
    connect(file_box_new, SIGNAL(currentIndexChanged(int)), this, SLOT(file_switching(int)));



}

void Generate_case_qwidget::onCase_info_use_Signal(int type_tl, QString b, int result_colour)
{
    if(type_tl ==0)
    {
//        test_text->clear();
    }
    QTextCharFormat format;
    if (result_colour ==1)
    {
        format.setForeground(QColor(Qt::blue)); // 设置字体颜色为蓝色
    }
    else if (result_colour ==2) {
        format.setForeground(QColor(Qt::green)); // 设置字体颜色为绿色
    }
    else if (result_colour ==3) {
        format.setForeground(QColor(Qt::red)); // 设置字体颜色为红色
    }


    if (result_colour==1)
    {

        if (b !="---end---")

        {
            test_text->setPlainText(b);
        }

    }
    test_text->moveCursor(QTextCursor::End);

}

void Generate_case_qwidget::setnetworkserviceOBJECT(Tcpapp *m_tcpaap,bool status)
{
    connection_state = status;
    if (this->tcpaap == nullptr)
    {
        this->tcpaap = m_tcpaap;
        connect(tcpaap,&Tcpapp::commandReceivedapp,this,&Generate_case_qwidget::handleDataReceived);
        connect(tcpaap,&Tcpapp::m_connected_state,this,&Generate_case_qwidget::handleConnected_state);
    }
}

void Generate_case_qwidget::setdebugmac(QString debugmac)
{
    macValue =debugmac;
}

void Generate_case_qwidget::indexinit()
{

//    file_box_new->setCurrentIndex(0);
    file_switching(0);



    widget_case->host_qstackedWidgetinit();

}


QStringList Generate_case_qwidget::get_all_file()
{
    return   FileUtil::getAllFile(testFilePath);
}

QList<equipmentcfg> Generate_case_qwidget::stringToBluetoothDataList(const QString &string)
{

    QStringList dataList = string.split(";", QString::SkipEmptyParts);
    dataList.removeAll("");

    QMap<QString, QStringList> bluetoothDataMap;
    for (const QString& data : dataList) {
        QStringList parts = data.split(":");
        if (parts.size() == 2) {
            QString category = parts[0];
            QStringList keyBluetooth = parts[1].split(",");
            if (bluetoothDataMap.contains(category)) {
                bluetoothDataMap[category].append(keyBluetooth);
            } else {
                bluetoothDataMap.insert(category, keyBluetooth);
            }
        }
    }
    QList<equipmentcfg> bluetoothDataList;
    for (auto it = bluetoothDataMap.begin(); it != bluetoothDataMap.end(); ++it) {
        bluetoothDataList.append(equipmentcfg(it.key(), it.value()));
    }
    return bluetoothDataList;
}

void Generate_case_qwidget::added_file_func()
{
    QString text = added_file_lindit->text();
    if (text.isEmpty())
    {
         QMessageBox::information(this, "提示", "保存失败文件名为空");
    }
    else {
        QString file_text = testFilePath;
        file_text.append(text);
        file_text.append(suffix_text);
        FileUtil::writeTextFileJSON(file_text, "开始第一个case\n",pattern_new->currentText());
        file_box_new->clear();
        QStringList currentItems = get_all_file();
        file_box_new->addItems(currentItems);
        for (int i = 0; i < file_box_new->count(); i++) {
            if (!currentItems.contains(text)) {
                file_box_new->setCurrentIndex(i);
                break;
            }
        }
    }
}

void Generate_case_qwidget::added_refresh_func()
{
    file_box_new->clear();

    file_box_new->addItems(get_all_file());
}


void Generate_case_qwidget::save_file_func()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "文件已存在", "文件已存在，是否覆盖？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
    }
    else {

        QString file_text = testFilePath;


        file_text.append( file_box_new->currentText());
        file_text.append(suffix_text);


        FileUtil::writeTextFileJSON(file_text, rewrite_file_widget->toString() ,pattern_qlneEdit->text());
    }
}


void Generate_case_qwidget::deletefile_func()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "确定删除", "确定删除？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
    }
    else {
        QString file_text = testFilePath;
        file_text.append(file_box_new->currentText());
        file_text.append(suffix_text);
        QFile file(file_text);
        if (file.exists()) {
            if (file.remove()) {
                qDebug() << "File removed successfully";
            } else {
                qDebug() << "Failed to remove file";
            }
        } else {
            qDebug() << "File does not exist";
        }
        file_box_new->clear();
        QStringList currentItems = get_all_file();
        file_box_new->addItems(currentItems);
    }
}

void Generate_case_qwidget::file_switching(int)
{

    rewrite_file_widget->clearAll();

    QString read_file_text =  testFilePath;

    QString file_currentText  =file_box_new->currentText();

    if (!file_currentText.isEmpty())
     {

        read_file_text.append(file_currentText);
        read_file_text.append(suffix_text);
        QStringList fulltext = FileUtil::readTextFileIfExistJSON(read_file_text);
        QString content = fulltext.at(2);
        Device_name = fulltext.at(0);
        pattern_qlneEdit->setText(Device_name);
         if (!content.isEmpty())
         {
             rewrite_file_widget->fromString(content);
         }
    }
    else {
        rewrite_file_widget->clearAll();
    }
}

void Generate_case_qwidget::c_Click_event_Signal(int, QString title, QStringList texts)
{
        debug_test = title;
        debug_test.append("\n");
        debug_test.append(texts.join("\n"));
        QMap<QString, QStringList> dataMap;
        dataMap.insert("蓝牙", QStringList());
        dataMap.insert("按键", QStringList());
        dataMap.insert("电流", QStringList());
        dataMap.insert("read", QStringList());
        dataMap.insert("读取名称", QStringList());
        dataMap.insert("读取LED", QStringList());
        dataMap.insert("语音", QStringList());
        foreach (const QString& text, texts)
        {

            if (text.contains("断言"))
            {
                continue;
            }
            if (text == "扫描")
            {
                dataMap["蓝牙"].append("已扫描到");
            }
            else if (text == "连接")
            {
                dataMap["蓝牙"].append("已连接");
            }
            else if (text == "配对")
            {
                dataMap["蓝牙"].append("已配对");
            }
            else if (text == "断开")
            {
                dataMap["蓝牙"].append("已断开");
            }
            else if (text == "取消配对")
            {
                dataMap["蓝牙"].append("已断开");
            }
            else if (text == "读取功耗")
            {
                dataMap["电流"].append("0.000");
            }
            else if (text.contains("按键按下"))
            {
                dataMap["按键"].append(text);
            }
            else if (text.contains("按键触发"))
            {
                QString originalString =text;
                QString target = "触发";
                QString replacement = "按下";

                QString modifiedString = originalString.replace(target, replacement);
                dataMap["按键"].append(modifiedString);
            }
            else if (text.contains("read"))
            {

                dataMap["read"].append("xx");
            }


            else if (text == "读取广播名称")
            {
                dataMap["读取广播名称"].append("xx");
            }
            else if (text.contains("读取LED"))
            {
                dataMap["读取LED"].append("1/1");
            }




        }

        QMap<QString, QStringList> nonEmptyDataMap;
        foreach(const QString& key, dataMap.keys())
        {
            if (!dataMap[key].isEmpty())
            {
                nonEmptyDataMap[key] = dataMap[key];
            }
        }

        QString result = "断言:{";
        foreach(const QString& key, nonEmptyDataMap.keys())
        {
            result += key + ":[";
            result += nonEmptyDataMap[key].join(",");
            result += "],";
        }
        result.chop(1);
        result += "}";
        assertion_text->setText(result);




}

void Generate_case_qwidget::m_debugChanged_ch()
{

    QString debug_case;
    for (const QVariant &var : _m_selectInfo) {
        if (var.type() == QVariant::String) {
            QString title = var.toString();

            debug_case += title+"\n";
        } else if (var.type() == QVariant::StringList) {
            QStringList caseList = var.toStringList();
            int size = caseList.size();
            for (int i = 0; i < size; ++i) {
                debug_case += caseList[i];
                if (i != size - 1) {
                    debug_case += '\n';
                } else {
                    debug_case += "\nend\n";
                }
            }
        }
    }

    if (connection_state)
    {

        tcpaap->sendMessageapp("Query the test status",5);

        if(test_isChecked)
        {
            tcpaap->sendMessageapp("停止测试",1);
            QMessageBox::information(this, "提示", "服务端正在测试，已停止服务端测试，请稍后重试");
        }
        else {

            tcpaap->sendMessageapp( "1",OUTPUT_TEST_MODE);
            QString message1 =  "开始测试";
            tcpaap->sendMessageapp(debug_case,2);
            QThread::msleep(50);
            tcpaap->sendMessageapp("1",3);
            QThread::msleep(50);
            tcpaap->sendMessageapp(macValue,4);
            QThread::msleep(50);
            tcpaap->sendMessageapp(file_box_new->currentText() + "&"+Device_name,8);
            QThread::msleep(100);
            tcpaap->sendMessageapp(message1,1);
            QThread::msleep(100);
        }
    }
    else {
        QMessageBox::information(this, "提示", "TCP连接失败");
    }
}

void Generate_case_qwidget::handleDataReceived(quint8 dataType, const QByteArray &buffer, bool islen_, bool ismd5_)
{

    if (ismd5_)
    {
        switch (dataType) {
        case Test_Display_list_1:
        {
            QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer);
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                int type = jsonObj["type"].toInt();
                QString data = jsonObj["data"].toString();
                int colour = jsonObj["colour"].toInt();
                onCase_info_use_Signal(type, data, colour);
            }
            break;
        }

        case 0x5:
        {
            QString tempstr = QString::fromUtf8(buffer);
            test_isChecked = (tempstr.toLower() == "true");
            break;
        }
        case 0x10:
        {
            QString temp = QString::fromUtf8(buffer);
            QStringList stringList = temp.split("&");
            pattern_new->clear();
            pattern_new->addItems(stringList);
            widget_case->setitems( stringList);
//            pattern_qlneEdit->setText(stringList.at(0));
            break;
        }
        case 0x11:
        {
            QString temp = QString::fromUtf8(buffer);
            QList<equipmentcfg> newBluetoothDataList = stringToBluetoothDataList(temp);
            for (const equipmentcfg& bluetoothData : newBluetoothDataList) {



                if (bluetoothData.category =="single_key_press")
                {
                    widget_case->setkeyname( bluetoothData.keyBluetooth ,true);
                }
                else if (bluetoothData.category =="single_key_up") {

                    widget_case->setkeyname_press( bluetoothData.keyBluetooth ,true);
                }
                else if (bluetoothData.category =="combination_key") {
                     widget_case->setkeyname_combination( bluetoothData.keyBluetooth ,true);
                }
                else if (bluetoothData.category =="trigger_key") {
                     widget_case->setkeyname_trigger( bluetoothData.keyBluetooth ,true);
                }
                else if (bluetoothData.category =="Function_module") {
                    widget_case->setkeyname_feature( bluetoothData.keyBluetooth ,false);

                }
                else if (bluetoothData.category =="Read_version") {
                    widget_case->setkeyname_read_v( bluetoothData.keyBluetooth ,true);
                }
                else if (bluetoothData.category =="Set_parameters") {
                    widget_case->setkeyname_parameters( bluetoothData.keyBluetooth ,true);
                }
            }
            widget_case->Refresh_QWidget();
        }
        default:
            break;
        }
    }
    else {
        qDebug()<<"MD5---Validation error";
    }
}

void Generate_case_qwidget::handleConnected_state(bool connected_state)
{
    connection_state = connected_state;

}

void Generate_case_qwidget::handTipsevent(const QString &text)
{

//    QString map_key_name ="";
//    if (mapping_tips.contains(text)) {
//        map_key_name =mapping_tips[text];
//    }
//    if (!tipsWidget) {
//        tipsWidget = new Tips_widget(map_key_name ,this);
//        tipsWidget->resize(200, 100);
//        QPoint parentCenter = this->geometry().center();
//        int widgetX = parentCenter.x() - (tipsWidget->width() / 2);
//        int widgetY = parentCenter.y() - (tipsWidget->height() / 2);
//        QPoint globalPos = this->mapToGlobal(QPoint(widgetX-200, widgetY));
//        tipsWidget->move(globalPos);
//        tipsWidget->show();
//    }
}

void Generate_case_qwidget::handTipsleavevent()
{
    if (tipsWidget) {
        tipsWidget->close();
        delete tipsWidget;
        tipsWidget = nullptr;
    }
}

void Generate_case_qwidget::handleselect_Device(const QString &text)
{

    if (connection_state)
    {
        tcpaap->sendMessageapp(text,12);
    }
    else {
        QMessageBox::information(this, "提示", "TCP连接失败");
    }

}

void Generate_case_qwidget::acceptSelectItemsChanged(QVector<QVariant> p_selectInfo)
{
    _m_selectInfo = p_selectInfo;

}




