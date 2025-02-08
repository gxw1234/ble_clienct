#ifndef GENERATE_CASE_QWIDGET_H
#define GENERATE_CASE_QWIDGET_H
#include <QWidget>
#include <QDir>
#include <QFrame>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <caselinewidget.h>
#include <QDir>
#include <QMessageBox>
#include "common/fileutil.h"
#include "ble_time_line/timelineundostack.h"
#include "uncommon/mydragwidget.h"
#include <QTextBrowser>
#include "tcpserver/tcpapp.h"
#include "common/tips_widget.h"


struct equipmentcfg {
    QString category;
    QStringList keyBluetooth;

    equipmentcfg() = default;
    equipmentcfg(const QString& category, const QStringList& keyBluetooth)
        : category(category), keyBluetooth(keyBluetooth) {}
};






class Generate_case_qwidget: public QWidget
{
     Q_OBJECT
public:
    explicit Generate_case_qwidget(QWidget *parent = nullptr);
    void initView();
    void onCase_info_use_Signal(int type_tl, QString b,int result_colour);
    void setnetworkserviceOBJECT(Tcpapp *tcpaap ,bool status);
    QTextEdit *test_text=nullptr;
    bool connection_state;
    void setdebugmac(QString debugmac);
    void indexinit();
private:
    QStringList get_all_file();
    QLabel *file_qlabel=nullptr;
    QGroupBox *test_file_qroupbox=nullptr;
    QComboBox *file_box_new=nullptr;
    QPushButton *delete_file_button=nullptr;
    QLineEdit *added_file_lindit=nullptr;
    QPushButton *added_file_button=nullptr;
    QPushButton *save_file_button=nullptr;
    QString testFilePath ;
    TimelineWidget *rewrite_file_widget=nullptr;
    MyDragWidget *widget_case=nullptr;
    QTextEdit *assertion_text=nullptr;
    QString debug_test=nullptr;
    QFrame *assertion_QFrame=nullptr;
//    NetworkService *networkService=NULL;

    QLabel *pattern_label1=nullptr;
    QComboBox *pattern_new=nullptr;


    QLabel *pattern_label=nullptr;
    QLineEdit *pattern_qlneEdit=nullptr;


    Tcpapp *tcpaap = nullptr;
    QTextCursor add_Results_Log;
    QString suffix_text;
    QString macValue;
    Tips_widget *tipsWidget =nullptr ;
    QList<equipmentcfg> stringToBluetoothDataList(const QString& string);


    QLabel *save_file_button_qlabel=nullptr;
    QString Device_name;
    QVector<QVariant> _m_selectInfo;




private slots:
    void added_file_func();
    void save_file_func();
    void deletefile_func();
    void file_switching(int);
    void c_Click_event_Signal(int , QString,QStringList );
    void m_debugChanged_ch();
    void handleDataReceived(quint8 dataType, const QByteArray& buffer,bool islen_, bool ismd5_);
    void handleConnected_state(bool connected_state);
    void handTipsevent(const QString &text);
    void handTipsleavevent();
    void  handleselect_Device(const QString &text);
    void acceptSelectItemsChanged( QVector<QVariant>);
};




#endif // GENERATE_CASE_QWIDGET_H
