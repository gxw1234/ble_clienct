#include "test_case_qwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QThread>

#define START_TEXT "开始测试"
#define START_ING_TEXT "测试中....."

Test_case_qwidget::Test_case_qwidget(QWidget *parent) : QWidget(parent)
{
    QString currentPath = QDir::currentPath();
    testFilePath = currentPath + "/test_file/";
    suffix_text =".json";
    initView();
    key_signal();
    recordTestNp =0;
    connection_state= false;
    isreceivetcp =true;
    weChatMessageSender =new WeChatMessageSender;


}

Test_case_qwidget::~Test_case_qwidget()
{
    delete tcpaap;
}

/**
 * 接收服务端发来的信息
 * 1:测试状态
 * 2:接收测试文件
 * 3:测试次数
 * 4:MAC地址
 * 5:查询是否正在测试
 * 7:返回全部串口信息
 *
 * 9:查询串口设置
 */
void Test_case_qwidget::handleDataReceived(quint8 dataType,const QByteArray& buffer,bool islen_,bool ismd5_)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    if (isreceivetcp)
    {
        if (ismd5_)
        {
            switch (static_cast<TCP_client_data>(dataType)) {
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
            case Test_Display_test_item_2:
            {
                QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer);
                if (jsonDoc.isObject()) {
                    QJsonObject title_jsonObj = jsonDoc.object();
                    int line = title_jsonObj["line"].toInt();
                    QString case_name = title_jsonObj["case_name"].toString();
                    onHandleS_ignal(line,case_name);
                }
                break;
            }
            case 0x03:
            {
                QString data = QString::fromUtf8(buffer);
                bool stringAsBool =  STRING_TO_BOOL(data);
                onEnd_handleSignal(stringAsBool);
                break;
            }
            case 0x04:
            {
                QString data = QString::fromUtf8(buffer);
                QStringList list = data.split("&", QString::SkipEmptyParts);
                onCase_row_result_Signal( list.at(0).toInt() ,list.at(1).toLower() == "true" );
                break;
            }
            case 0x05:
            {
                QString data = QString::fromUtf8(buffer);
                stringAsBool = STRING_TO_BOOL(data);
                if(stringAsBool)
                {
                    start_test->setChecked(true);
                    start_test->setTextLabel(START_ING_TEXT);
                    start_test->setIconPath(":/images/images/start2.png");
                    tcpaap->sendMessageapp("OUTPUTACCORD",OUTPUT_TEST_ING);
                }
                 break;
            }
            case 0x06:
            {
                step_qlneEdit->setText("串口打开失败" );
                start_test->setChecked(false);
                start_test->setTextLabel(START_TEXT);
                start_test->setIconPath(":/images/images/start1.png");
                break;
            }
            case 0x07:
            {
                 break;
            }

            case 0x08:
            {
                 break;
            }
            case 0x09:
            {
                QString data = QString::fromUtf8(buffer);
                QStringList protlist = data.split("&", QString::SkipEmptyParts);
                test_ser_Box->clear();
                test_ser_Box->addItems(protlist);
                ble_ser_Box->clear();
                ble_ser_Box->addItems(protlist);
                 break;
            }
            case 0x0A:
            {
                 logtext = QString::fromUtf8(buffer);
                 break;
            }
            case 0x0B:
            {
                 sertext = QString::fromUtf8(buffer);
                 break;
            }
            case 0x0C:
            {
                 break;
            }
            case 0x0D:
            {
               
                QString data = QString::fromUtf8(buffer);
                bool stringAsBool =  STRING_TO_BOOL(data);
                saveToFile(stringAsBool);
                break;
            }
            case 0x0E:
            {
                ip = QString::fromUtf8(buffer);
                break;
            }
            case 0x0F:
            {
                QString temp = QString::fromUtf8(buffer);
                QStringList stringList = temp.split("&");
                ReportInfo info(stringList.at(0),
                                      stringList.at(1),
                                      stringList.at(2),
                                      stringList.at(3),
                                      stringList.at(4),
                                      stringList.at(5));
                save_row(ReportInfo(info));
                ReportInfolist.append(ReportInfo(stringList.at(0),
                                                 stringList.at(1),
                                                 stringList.at(2),
                                                 stringList.at(3),
                                                 "",
                                                 ""));
                break;
            }
            case Test_Individual_function_14:
            {
                if (!stringAsBool)
                {
                    QString data = QString::fromUtf8(buffer);
                    setcolumncolor(data);
                }
               break;
            }
            case 0x16:
            {
                stringAsBool =false;
                Generation_path = createOrGetDailyFolder(file_box->currentText());
                QString testfile = QString::fromUtf8(buffer);
                if (!testfile.isEmpty())
                {
                    rewrite_widget->clearAll();
                    rewrite_widget->fromString(testfile);
                }
                break;
            }
            case OUTPUTCASENAMEDATALIST_TO:
            {
                QString tempdata =QString::fromUtf8(buffer);
                file_box->setCurrentText(tempdata);
                Generation_path = createOrGetDailyFolder(file_box->currentText());
                show_debug_log->setText("");
                show_detailed_debug_log->setText("");
               break;
            }
            case Test_update_file_1d:
            {
               Generation_path = createOrGetDailyFolder(QString::fromUtf8(buffer));
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

}

void Test_case_qwidget::handleConnected_state(bool _connected_state)
{
    connection_state =_connected_state;
    if(!connection_state)
    {
        start_test->setChecked(false);
        start_test->setTextLabel(START_TEXT);
        start_test->setIconPath(":/images/images/start1.png");
    }
}

void Test_case_qwidget::initView()
{
    //设置层的QFrame
    set_up_qframe =new QFrame;
    start_test  = new IconPushButton(":/images/images/start2.png", START_TEXT);
    start_test->setCheckable(true);
    start_test->setStyleSheet(
        "QPushButton {\
            font-size: 16px;\
        }\
        QPushButton:checked {\
            background: #3cb371; /* 选中时的背景颜色 */\
            color: white;\
        }\
        QPushButton:pressed {\
            background: #808080; /* 按压时的背景颜色 */\
        }\
        QPushButton:!checked {\
            background: #f0f0f0; /* 未选中时的背景颜色 */\
            color: black;\
        }"
    );



    QGridLayout *set_up_qframe_Layout;
    mac_title =new QLabel;
    mac_title->setText("设置MAC地址：");
    mac_text =new QLineEdit;
    ip_text =new QLineEdit;
    file_text = new QLabel;
    file_text->setText("测试文件：");
    file_box = new QComboBox;
    test_ser_label= new QLabel;
    test_ser_label->setText("通讯串口:");
    test_ser_Box= new QComboBox;
    ble_ser_label= new QLabel;
    ble_ser_label->setText("日志串口:");
    ble_ser_Box= new QComboBox;

    pattern_label= new QLabel;
    pattern_label->setText("所属版型:");
    pattern_qlneEdit = new QLineEdit;
    pattern_qlneEdit->setStyleSheet("background: transparent;");
    pattern_qlneEdit->setReadOnly(true);
    abnormal_stop_label= new QLabel;
    abnormal_stop_label->setText("异常停止:");
    abnormal_stop_qCheckBox =new QCheckBox;

    Multiple_choice_label= new QLabel;
    Multiple_choice_label->setText("单选:");
    Multiple_choice_qCheckBox =new QCheckBox;
    Multiple_choice_qCheckBox->setChecked(true);



    QStringList items =  FileUtil::getAllFile(testFilePath);
    file_box->addItems(items);


    settestnp = new QLabel;
    settestnp->setText("设置测试次数");
    settestnpbox = new QSpinBox;
    settestnpbox->setRange(1,999999);
    settestnpbox->setValue(1);

    tests_all_numbe_label =new QLabel;
    tests_all_numbe_label->setText("测试次数");
    tests_pass_numbe_label = new QLabel;
    tests_pass_numbe_label->setText("合格次数");
    tests_pass_rate_label = new QLabel;
    tests_pass_rate_label->setText("合格效率");
    tests_all_numbe_lineEdit =  new QLineEdit;
    tests_all_numbe_lineEdit->setText("0");
    tests_pass_numbe_lineEdit = new QLineEdit;
    tests_pass_numbe_lineEdit->setText("0");
    tests_pass_rate_lineEdit =new QLineEdit;
    tests_pass_rate_lineEdit->setText("100%");
    QSpacerItem *spacer1 = new QSpacerItem(20, 1);  //

    set_up_qframe_Layout =new QGridLayout(set_up_qframe);
    set_up_qframe_Layout->addWidget(start_test,0,0,1,1);
    set_up_qframe_Layout->addWidget(file_text,0,3,1,1);
    set_up_qframe_Layout->addWidget(file_box,0,4,1,1);
    set_up_qframe_Layout->addWidget(pattern_label,0,5,1,1);
    set_up_qframe_Layout->addWidget(pattern_qlneEdit,0,6,1,1);
    set_up_qframe_Layout->addWidget(abnormal_stop_label,0,8,1,1);
    set_up_qframe_Layout->addWidget(abnormal_stop_qCheckBox,0,9,1,1);
    set_up_qframe_Layout->addWidget(Multiple_choice_label,0,1,1,1);
    set_up_qframe_Layout->addWidget(Multiple_choice_qCheckBox,0,2,1,1);
    set_up_qframe_Layout->addWidget(settestnp,0,10,1,1);
    set_up_qframe_Layout->addWidget(settestnpbox,0,11,1,1);
    set_up_qframe_Layout->addWidget(tests_all_numbe_label,0,14,1,1);
    set_up_qframe_Layout->addWidget(tests_all_numbe_lineEdit,0,15,1,1);
    set_up_qframe_Layout->addWidget(tests_pass_numbe_label,0,16,1,1);
    set_up_qframe_Layout->addWidget(tests_pass_numbe_lineEdit,0,17,1,1);
    set_up_qframe_Layout->addWidget(tests_pass_rate_label,0,18,1,1);
    set_up_qframe_Layout->addWidget(tests_pass_rate_lineEdit,0,19,1,1);


    //显示步骤
    step_qlneEdit =new QLineEdit;
    step_qlneEdit->setMinimumSize(0, 150);
    step_qlneEdit->setAlignment(Qt::AlignCenter);
    step_qlneEdit->setText("测试空闲中...........");
    step_qlneEdit->setFont(QFont("宋体", 20, QFont::Thin));
    step_qlneEdit->setAlignment(Qt::AlignCenter);
    step_qlneEdit->setStyleSheet("border: 3px solid rgb(0, 85, 255); background-color: rgb(0, 0, 0); color: rgb(0, 85, 255);");
    progressBar_test = new QProgressBar;
    progressBar_test->setAlignment(Qt::AlignCenter);
    progressBar_test->setFormat("%p%");
    progressBar_test->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid grey;"
        "    border-radius: 5px;"
        "    background-color: #FFFFFF;"
        "    text-align: center;"
        "    font-size: 18px;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #0082FC;"
//        "    width: 20px;"
//        "    margin: 0.5px;"
        "}"
    );



    //-------one ---rewrite_widget------

    rewrite_widget = new TimelineWidget;
    new TimelineUndoStack(rewrite_widget);

    connect(rewrite_widget,SIGNAL(selectItemsChanged( QVector<QVariant>)),this,SLOT(acceptSelectItemsChanged( QVector<QVariant>)));
    connect(rewrite_widget, SIGNAL(debugChanged_ch()), this, SLOT(m_debugChanged_ch()));


    Log_level = new  QLabel;
    Log_level->setText("等级:");
    Single_use_case = new  QLabel;
    Single_use_case->setText("用例:");
    Log_level_Box =  new QComboBox;
    QStringList items2;
    items2 << "结果等级" << "日志等级" ;
    Log_level_Box->addItems(items2);
    Single_use_case_Box = new QComboBox;

    show_detailed_debug_log = new QTextEdit();
    show_detailed_debug_log->setMaximumSize(QSize(300, 10000));

    show_debug_log = new QTextEdit();
    show_debug_log->setMaximumSize(QSize(300, 10000));

    debug_qstackedWidget = new QStackedWidget;
    debug_log_qwidget = new QWidget;
    detailed_debug_log_qwidget = new QWidget;
    debug_qstackedWidget->addWidget(debug_log_qwidget);
    debug_qstackedWidget->addWidget(detailed_debug_log_qwidget);
    QVBoxLayout *debug_log_qwidget_layout = new QVBoxLayout(debug_log_qwidget);
    debug_log_qwidget_layout->addWidget(show_debug_log);
    debug_log_qwidget->setLayout(debug_log_qwidget_layout);
    debug_log_qwidget_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *detailed_debug_log_qwidget_layout = new QVBoxLayout(detailed_debug_log_qwidget);
    detailed_debug_log_qwidget_layout->addWidget(show_detailed_debug_log);
    debug_log_qwidget->setLayout(detailed_debug_log_qwidget_layout);
    detailed_debug_log_qwidget_layout->setContentsMargins(0, 0, 0, 0);
    debug_log_qframe = new QFrame;
    QGridLayout *debug_log_qframe_ly;
    debug_log_qframe_ly =new QGridLayout(debug_log_qframe);
    debug_log_qframe_ly->addWidget(Log_level,0,0,1,1);
    debug_log_qframe_ly->addWidget(Log_level_Box,0,1,1,1);
    debug_log_qframe_ly->addWidget(Single_use_case,1,0,1,1);
    debug_log_qframe_ly->addWidget(Single_use_case_Box,1,1,1,1);
    debug_log_qframe_ly->addWidget(debug_qstackedWidget,2,0,1,2);
    debug_log_qframe_ly->setContentsMargins(0, 0, 0, 0);
    
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(set_up_qframe,0,0,1,2);
    layout->addWidget(step_qlneEdit,1,0,1,2);
    layout->addWidget(progressBar_test,2,0,1,2);
    layout->addWidget(rewrite_widget,3,0,1,1);
    layout->addWidget(debug_log_qframe,3,1,1,1);
    setLayout(layout);
    QString file_currentText  =file_box->currentText();
    import_file(file_currentText);
    }

void Test_case_qwidget::key_signal()
{
    connect(file_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &Test_case_qwidget::home_file_switching);
    connect(start_test, &QPushButton::clicked, this, &Test_case_qwidget::startclicked);
}

void Test_case_qwidget::import_file(QString test_file)
{
    rewrite_widget->clearAll();
    QString read_file_text =  testFilePath;
    QString file_currentText  =test_file;
    if (!file_currentText.isEmpty())
     {
        read_file_text.append(file_currentText);
        read_file_text.append(suffix_text);
        QStringList fulltext = FileUtil::readTextFileIfExistJSON(read_file_text);
        QString content =fulltext.at(2);
        QString Device_name = fulltext.at(0);
        pattern_qlneEdit->setText(Device_name);
         if (!content.isEmpty())
         {
             Savefiledata =content;
             rewrite_widget->fromString(content);
         }
    }

//    rewrite_widget->setTextLabelBorderColor(1,3,QColor(255,0,0));





}

void Test_case_qwidget::home_file_switching(int index)
{
    show_debug_log->clear();
    rewrite_widget->clearAll();
    QString read_file_text =  testFilePath;
    QString file_currentText  =file_box->currentText();
    if (!file_currentText.isEmpty())
     {
        read_file_text.append(file_currentText);
        read_file_text.append(suffix_text);
        QStringList fulltext = FileUtil::readTextFileIfExistJSON(read_file_text);
        QString content =fulltext.at(2);
        QString Device_name = fulltext.at(0);
        pattern_qlneEdit->setText(Device_name);
         if (!content.isEmpty())
         {
             Savefiledata =content;
             rewrite_widget->fromString(content);
         }
    }
}




void Test_case_qwidget::startclicked(bool start)
{
    test_name_list.clear();  //开始的时候把多选清除掉
    if (connection_state)
    {
        if(start)
        {
            if(Multiple_choice_qCheckBox->isChecked())
            {
                all_count =rewrite_widget->count();
                if (all_count !=0)
                {
                    start_network();
                }
                else {
                    start_test->setChecked(false);
                    start_test->setTextLabel(START_TEXT);
                    start_test->setIconPath(":/images/images/start1.png");
                }
            }
            else {
                QStringList items =  FileUtil::getAllFile(testFilePath);
                SelectionWindow *selectionWindow = new SelectionWindow(items);
                selectionWindow->setWindowModality(Qt::ApplicationModal);
                connect(selectionWindow, &SelectionWindow::selectionMade, this, &Test_case_qwidget::handleSelection); // 连接自定义信号
                selectionWindow->show();
            }
        }
        else {
            QString message1 =  "停止测试";
            tcpaap->sendMessageapp(message1,OUTPUTSTARTTEST);
        }
    }
    else {
        QMessageBox::information(this, "提示", "TCP连接失败");
        start_test->setChecked(false);
        start_test->setTextLabel(START_TEXT);
        start_test->setIconPath(":/images/images/start1.png");
    }
}


void Test_case_qwidget::onMessage(QString)
{

}


void Test_case_qwidget::acceptSelectItemsChanged(QVector<QVariant> p_selectInfo)
{
    _m_selectInfo = p_selectInfo;
}

void Test_case_qwidget::m_debugChanged_ch()
{
    QString result;
       for (const QVariant &var : _m_selectInfo) {
           if (var.type() == QVariant::String) {
               QString title = var.toString();
               result += title+"\n";
           } else if (var.type() == QVariant::StringList) {
               QStringList caseList = var.toStringList();
               int size = caseList.size();
               for (int i = 0; i < size; ++i) {
                   result += caseList[i];
                   if (i != size - 1) {
                       result += '\n';
                   } else {
                       result += "\nend\n";
                   }
               }
           }
       }
       rewrite_widget->clearAll();
       rewrite_widget->fromString(result);
       Savefiledata =result;
       start_test->setChecked(true);
       startclicked(true);
}

void Test_case_qwidget::handleSelection(QStringList selectedItems)
{
    if (selectedItems.isEmpty()) {
        QMessageBox::information(this, "选择结果", "没有选择任何项目");
        start_test->setChecked(false);
    } else {
        test_name_list = selectedItems;
        if (!test_name_list.isEmpty()) {
        for (int i = 1; i < test_name_list.size(); ++i) {
             file_box->setCurrentText(test_name_list.at(i));
             tcpaap->sendMessageapp(Savefiledata,OUTPUTCASENAMELIAT);
                             QThread::msleep(50);
            tcpaap->sendMessageapp(CONCAT_STRINGS_WITH_AMPERSAND(file_box->currentText(),pattern_qlneEdit->text()),OUTPUTCASENAMEDATALIST);

        }

            file_box->setCurrentText(test_name_list.at(0));
//            test_name_list.removeFirst();

            QThread::msleep(50);
            start_network();
        }
    }
}




void Test_case_qwidget::onEnd_handleSignal(bool result)
{

    int totalTests = tests_all_numbe_lineEdit ->text().toInt();
    int passedTests = tests_pass_numbe_lineEdit ->text().toInt();

    totalTests++;
    if (result)
    {
        passedTests++;
    }
    recordTestNp +=1;
    tests_all_numbe_lineEdit->setText(QString::number(totalTests));
    tests_pass_numbe_lineEdit->setText(QString::number(passedTests));
    double passRate = (double)passedTests / totalTests * 100;
    tests_pass_rate_lineEdit->setText(QString("%1%").arg(QString::number(passRate)));

    if(recordTestNp !=settestnpbox->value())
    {

    }
    else {
        step_qlneEdit->setText("测试已完成");
        rewrite_widget->setEnabled(true);
        start_test->setChecked(false);
        start_test->setTextLabel(START_TEXT);
        start_test->setIconPath(":/images/images/start1.png");
        recordTestNp =0;
    }
}

void Test_case_qwidget::onCase_row_result_Signal(int type_tl, bool result)
{
    rewrite_widget->setTextLabelBorderColor(Clear_color_row, Clear_color_column,QColor(0,0,255));
    if (result)
    {
        rewrite_widget->setEllColor(line_green_color,type_tl);
        rewrite_widget->setLineColor(line_green_color,type_tl);
    }
    else {

        rewrite_widget->setEllColor(line_red_color,type_tl);
        rewrite_widget->setLineColor(line_red_color,type_tl);

    }
}

void Test_case_qwidget::onCase_info_use_Signal(int type_tl, QString b, int result_colour)
{
    if(type_tl ==0)
    {
        add_Results_Log = show_debug_log->textCursor();
        QTextFrameFormat format;
        format.setBorder(1);
        format.setBorderBrush(QColor("black"));
        add_Results_Log.insertFrame(format);
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
    add_Results_Log.setCharFormat(format);
    add_Results_Log.insertText(b);
    show_debug_log->moveCursor(QTextCursor::End);
}


void Test_case_qwidget::onHandleS_ignal(int line, QString case_name)
{
    rewrite_widget->setEllColor(line_blue_color,line);
    rewrite_widget->setLineColor(line_blue_color,line);
    rewrite_widget->setCurrentItem(line);
    rewrite_widget->setVerticalScrollBarPosition(line*30);
    step_qlneEdit->setText("正在测试:" + case_name);
    int result = ((line + 1.0) / all_count) * 100;
    progressBar_test->setValue(result);
    Single_use_case_Box->addItem(case_name);
}


void Test_case_qwidget::setnetworkserviceOBJECT(Tcpapp *m_tcpaap,bool _connected_state)
{
    if (this->tcpaap == nullptr)
    {
        connection_state =_connected_state;
        this->tcpaap =m_tcpaap;
        connect(tcpaap,&Tcpapp::commandReceivedapp,this,&Test_case_qwidget::handleDataReceived);
        connect(tcpaap,&Tcpapp::m_connected_state,this,&Test_case_qwidget::handleConnected_state);
    }

}

void Test_case_qwidget::Refreshfile()
{
    file_box->clear();
    QStringList items =  FileUtil::getAllFile(testFilePath);
    file_box->addItems(items);

}

void Test_case_qwidget::saveToFile(bool isSuccessful)
{
    QString Result_name;
    if (isSuccessful) {
        Result_name = "pass";
    } else {
        Result_name ="fail";
    }
    QString pdfPortFileName = Result_name+ "_.xlsx";
    QString pdfPortFilePath = QString("%1/%2").arg(Generation_path).arg(pdfPortFileName);
    m_savexls.save_xls(pdfPortFilePath,isSuccessful,ReportInfolist);
    ReportInfolist.clear();


}

void Test_case_qwidget::setmac(QString mac ,QString ip)
{
    mac_text->setText(mac);
    ip_text->setText(ip);
}

void Test_case_qwidget::Generate_report(QString filepath, bool isSuccessful, QList<QStringList> report)
{



}

QString Test_case_qwidget::createOrGetDailyFolder(const QString &str = QString())
{
//    QString currentPath = QDir::currentPath();
//    QString dateString = QDateTime::currentDateTime().toString("yyyy年MM月dd日");
//    QRegularExpression regex(R"(机器名称:\s*\*+(\w+)\*+\s*ip:)");
//    QRegularExpressionMatch match = regex.match(ip_text->text());
//    QString dailyFolderPath = currentPath + "/results/" + match.captured(1) +"/" +dateString;
//    QDir dir(dailyFolderPath);
//    if (!dir.exists()) {
//        dir.mkpath(dailyFolderPath);
//    }
//    QString timeString = QDateTime::currentDateTime().toString("HH时mm分ss秒");
//    QString subFolderPath = dailyFolderPath + "/" + timeString +"_"+ file_box->currentText();

//    QDir subDir(subFolderPath);
//    if (!subDir.exists()) {
//        subDir.mkpath(subFolderPath);
//    }
//    return subFolderPath;




    QString currentPath = QDir::currentPath();
    QString dateString = QDateTime::currentDateTime().toString("yyyy年MM月dd日");
    QRegularExpression regex(R"(机器名称:\s*\*+(\w+)\*+\s*ip:)");
    QRegularExpressionMatch match = regex.match(ip_text->text());
    QString dailyFolderPath = currentPath + "/results/" + match.captured(1) + "/" + dateString;
    QDir dir(dailyFolderPath);
    if (!dir.exists()) {
        dir.mkpath(dailyFolderPath);
    }

    QString timeString = QDateTime::currentDateTime().toString("HH时mm分ss秒");
    // 如果传入的 str 为空，则使用 file_box->currentText()
    QString folderName = str.isEmpty() ? file_box->currentText() : str;
    QString subFolderPath = dailyFolderPath + "/" + timeString + "_" + folderName;

    QDir subDir(subFolderPath);
    if (!subDir.exists()) {
        subDir.mkpath(subFolderPath);
    }
    return subFolderPath;
}

void Test_case_qwidget::save_row(ReportInfo reportInfo)
{
     QString subFolderPath = Generation_path + "/" + reportInfo.title;
     QDir subDir(subFolderPath);
     if (!subDir.exists()) {
         subDir.mkpath(subFolderPath);
     }
     QString serialPortFileName =  "_serialport.txt";
     QString serialPortFilePath = QString("%1/%2").arg(subFolderPath).arg(serialPortFileName);
     QFile serialPortFile(serialPortFilePath);
     if (serialPortFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
         QTextStream out(&serialPortFile);
         out << sertext << endl;
         serialPortFile.close();
     }
     QString fileName =   "_Featurelog.txt";
     QString filePath = QString("%1/%2_log.txt").arg(subFolderPath).arg(fileName);
     QFile file(filePath);
     if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
         QTextStream out(&file);
         out << logtext << endl;
         file.close();
     }
     m_savexls.save_row_xls(subFolderPath +"/测试结果_.xlsx",  subFolderPath +"/_result_log.txt", reportInfo);
}

void Test_case_qwidget::setcolumncolor(QString data)
{
    QStringList testingtemp = data.split("&", QString::SkipEmptyParts);
    int row_temp = testingtemp[0].toInt();
    int column_temp = testingtemp[1].toInt();
    rewrite_widget->setTextLabelBorderColor(Clear_color_row, Clear_color_column,QColor(0,0,255));
    rewrite_widget->setTextLabelBorderColor(row_temp, column_temp,QColor(255,0,0));
    Clear_color_row=row_temp;
    Clear_color_column=column_temp;
}

void Test_case_qwidget::start_network()
{
    start_test->setChecked(true);
    start_test->setTextLabel(START_ING_TEXT);
    start_test->setIconPath(":/images/images/start2.png");
    QString message1 =  START_TEXT;
    tcpaap->sendMessageapp(Savefiledata,OUTPUTTESTDOCUMENT);
                    QThread::msleep(50);
    tcpaap->sendMessageapp(QString::number(settestnpbox->value()),OUTPUTTESTNP);
                    QThread::msleep(50);
    tcpaap->sendMessageapp(mac_text->text(),OUTPUTTESTMAC);
                    QThread::msleep(50);
    tcpaap->sendMessageapp(BOOL_TO_STRING(abnormal_stop_qCheckBox->isChecked()),OUTPUTFILASTOP);
    tcpaap->sendMessageapp(CONCAT_STRINGS_WITH_AMPERSAND(file_box->currentText(),pattern_qlneEdit->text()),OUTPUTTESNAME);
    tcpaap->sendMessageapp(message1,OUTPUTSTARTTEST);
    QThread::msleep(100);
    show_debug_log->setText("");
    show_detailed_debug_log->setText("");
    Generation_path = createOrGetDailyFolder();

}

