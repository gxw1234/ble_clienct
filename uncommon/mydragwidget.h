#ifndef MYDRAGWIDGET_H
#define MYDRAGWIDGET_H
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QGraphicsOpacityEffect>
//#include "common/tips_widget.h"
#include <QScrollBar>
#include <QScrollArea>
#include <QComboBox>
#include <QToolButton>
#include <QSpacerItem>

#include <QTabWidget>
#include "common/icon_config.h"
class QDragEnterEvent;
class QDropEvent;





class MyDragWidget : public QWidget
{
    Q_OBJECT

public:
    MyDragWidget(QWidget *parent = nullptr);
    ~MyDragWidget() override;

    void setitems(QStringList);
    void setkeyname_parameters(QStringList ,bool);
    void setkeyname(QStringList ,bool);
    void setkeyname_press(QStringList ,bool);
    void setkeyname_trigger(QStringList ,bool);
    void setkeyname_combination(QStringList ,bool);
    void setkeyname_feature(QStringList ,bool);
    void setkeyname_read_v(QStringList ,bool);

    void Refresh_QWidget();
    void host_qstackedWidgetinit();

    void Refresh_box();
    QComboBox* PlatecutBox = nullptr;
private:

    void setQWidgetlayout(QWidget *wid,QStringList ,bool);
    int labelWidth = 100;
    int labelHeight = 40;
    int columnSpacing = 130;
    int lineSpacing = 50;
    QStackedWidget *host_qstackedWidget;
    QTextEdit *show_debug_info= nullptr;
    QScrollArea *scrollArea = nullptr;

    QStringList FeaturekeytextList;
    QWidget *QWidget_key;
    QWidget *QWidget_trigger;
    QComboBox* typboBox= nullptr;


    QWidget* QWidget_combination;
    QWidget* QWidget_Key_press;
    QWidget *QWidget_read;
    QWidget *QWidget_feature;
    QWidget *QWidget_temp;

    QStringList FeaturetextList;



    //--------------
    QTabWidget *tabWidget = new QTabWidget();



     QWidget* QWidget_Set_parameters_tab;
    QWidget* QWidget_combination_tab;
    QWidget *QWidget_trigger_tab;
    QWidget *QWidget_key_tab;
    QWidget* QWidget_Key_press_tab;
    QWidget *QWidget_read_tab;
    QWidget *QWidget_feature_tab;


    QWidget* QWidget_Set_parameters_tab_scrollArea;
    QWidget* QWidget_combination_tab_scrollArea;
    QWidget *QWidget_trigger_tab_scrollArea;
    QWidget *QWidget_key_tab_scrollArea;
    QWidget* QWidget_Key_press_tab_scrollArea;
    QWidget *QWidget_read_tab_scrollArea;
    QWidget *QWidget_feature_tab_scrollArea;


    QScrollArea* QWidget_Set_parameters_scrollArea;

    QScrollArea* QWidget_combination_scrollArea;
    QScrollArea *QWidget_trigger_scrollArea;
    QScrollArea *QWidget_key_scrollArea;
    QScrollArea* QWidget_Key_press_scrollArea;
    QScrollArea *QWidget_read_scrollArea;
    QScrollArea *QWidget_feature_scrollArea;



    void  reconfiguration();



private slots:
    void fun_switching(int);
    void ondevice_name(int);
    void onLabelMouseEntered(const QString& text);
    void onLabelMouseLeft(const QString& text);

signals:

    void Tipsevent(const QString &text);
    void Tipsleavevent();
    void myselect_Device(const QString &text);
};

#endif // MYDRAGWIDGET_H
