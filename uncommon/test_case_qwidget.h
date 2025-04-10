#ifndef TEST_CASE_QWIDGET_H
#define TEST_CASE_QWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QPushButton>
#include <QTextEdit>
#include <QFrame>
#include <QProgressBar>
#include <QStackedWidget>
#include <QTextCursor>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QFrame>
#include <QLineEdit>
#include<QComboBox>
#include <QToolBar>
#include <QAction>
#include <QToolBox>
#include <QStatusBar>
#include <QSpinBox>
#include "common/fileutil.h"
#include <caselinewidget.h>
#include "timelineundostack.h"
#include "common/iconpushbutton.h"
#include "tcpserver/tcpapp.h"
#include <QPainter>
#include <QPrinter>
#include <QCheckBox>
#include "common/savexls.h"
#include "common/wechatnotifier.h"
#include "uncommon/selectionwindow.h"

class Test_case_qwidget: public QWidget
{
    Q_OBJECT
public:
    explicit Test_case_qwidget(QWidget *parent = nullptr);
    ~Test_case_qwidget();
    void initView();
    void key_signal();
    void import_file(QString);
    void onMessage(QString);
    void onEnd_handleSignal(bool);
    void onCase_row_result_Signal(int type_tl, bool result);
    void onCase_info_use_Signal(int type_tl, QString b,int result_colour);
    void onHandleS_ignal(int line, QString b);
    QComboBox *file_box= nullptr;
    bool connection_state;
    Tcpapp *tcpaap = nullptr;
    void setnetworkserviceOBJECT(Tcpapp *tcpaap ,bool _connected_state);
    void Refreshfile();
    void saveToFile(bool isSuccessful);
    QString logtext ;
    QString sertext ;
    QList<QStringList> reportdata;
    bool result ;
    bool isreceivetcp;
    void setmac(QString mac,QString ip);
    IconPushButton *start_test;

private:
    //----设置层的QFrame-----
    QFrame *set_up_qframe = nullptr;


    QLabel *mac_title= nullptr;
    QLineEdit *mac_text= nullptr;
    QLineEdit *ip_text= nullptr;
    QLabel *file_text= nullptr;
    //---------------
    QLabel *tests_all_numbe_label= nullptr;
    QLabel *tests_pass_numbe_label= nullptr;
    QLabel *tests_pass_rate_label= nullptr;
    QLineEdit *tests_all_numbe_lineEdit= nullptr;
    QLineEdit *tests_pass_numbe_lineEdit= nullptr;
    QLineEdit *tests_pass_rate_lineEdit= nullptr;
    QLabel *settestnp= nullptr;
    QSpinBox *settestnpbox= nullptr;

    //----新增---------
    QLabel *pattern_label= nullptr;
    QLineEdit * pattern_qlneEdit= nullptr;
    QLabel *abnormal_stop_label= nullptr;
    QCheckBox * abnormal_stop_qCheckBox= nullptr;

    QLabel *Multiple_choice_label= nullptr;
    QCheckBox * Multiple_choice_qCheckBox= nullptr;



    //----显示步骤-----
    QLineEdit * step_qlneEdit= nullptr;
    // 进度条
    QProgressBar *progressBar_test= nullptr;

    TimelineWidget *rewrite_widget;
    QFrame *debug_log_qframe= nullptr;
    QLabel *Log_level= nullptr;
    QLabel *Single_use_case= nullptr;
    QComboBox *Log_level_Box= nullptr;
    QComboBox *Single_use_case_Box= nullptr;
    QStackedWidget *debug_qstackedWidget= nullptr;
    QWidget *debug_log_qwidget= nullptr;
    QWidget *detailed_debug_log_qwidget= nullptr;
    QStatusBar *statusbar= nullptr;
    QTextEdit *show_debug_log= nullptr;
    QTextEdit *show_detailed_debug_log= nullptr;
    int all_count;
    QTextCursor add_Results_Log;
    QString testFilePath ;
    QColor line_green_color = QColor(0, 255, 0);
    QColor line_red_color = QColor(255, 0, 0);
    QColor line_blue_color = QColor(0, 0, 255);
    int recordTestNp;
    QString Savefiledata;

    QLabel *test_ser_label = nullptr;
    QComboBox *test_ser_Box= nullptr;

    QLabel *ble_ser_label;
    QComboBox *ble_ser_Box= nullptr;
    QString ip;
    QString suffix_text;
    savexls m_savexls;
    void Generate_report(QString filepath,bool isSuccessful,QList<QStringList> report);
    QList<ReportInfo> ReportInfolist;

    QString Generation_path;

    QString createOrGetDailyFolder(const QString &str);
    void save_row(ReportInfo reportInfo);
    void setcolumncolor(QString data);
    void start_network();
    int Clear_color_row=0;
    int Clear_color_column=0;
    QVector<QVariant> _m_selectInfo;

    WeChatMessageSender *weChatMessageSender;
//    SelectionWindow *selectionWindow;

    QStringList test_name_list;
    bool stringAsBool =false;

private slots:
    void home_file_switching(int);
    void startclicked(bool start);
    void handleDataReceived(quint8 dataType, const QByteArray& buffer,bool islen_, bool ismd5_);
    void handleConnected_state(bool connected_state);
    void acceptSelectItemsChanged( QVector<QVariant>);
    void m_debugChanged_ch();
    void handleSelection(QStringList selectedItems);
};

#endif // TEST_CASE_QWIDGET_H
