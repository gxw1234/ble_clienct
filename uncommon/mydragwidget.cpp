#pragma execution_character_set("utf-8")
#include "mydragwidget.h"
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDebug>
#include <QLabel>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include "caselinebucket.h"
#include "labeleditor.h"
#include <QVBoxLayout>
#include <QWidget>


#define STYTEST "background-color: gray;"

MyDragWidget::MyDragWidget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(330, 100);
    setAcceptDrops(true);
    host_qstackedWidget = new QStackedWidget() ;
    typboBox = new QComboBox();
    PlatecutBox = new QComboBox();
    show_debug_info= new QTextEdit;
    show_debug_info->setMaximumSize(300,60);
    QStringList items2;
    items2 << "功能模块" <<"读取版本"  << "单按键按下" << "单按键抬起"<< "按键触发"<<"组合按键"<<"设置";
    QList<QIcon> icons;

    icons.append(QIcon(":/images/images/Feature.png"));
    icons.append(QIcon(":/images/images/edition.png"));
    icons.append(QIcon(":/images/images/key_unde.png"));
    icons.append(QIcon(":/images/images/key_up.png"));
    icons.append(QIcon(":/images/images/key_up_unde.png"));
    icons.append(QIcon(":/images/images/key_m.png"));
    for (int i = 0; i < items2.size(); ++i) {
        typboBox->addItem(icons[i], items2[i]);
    }

    connect(typboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &MyDragWidget::fun_switching);
    connect(PlatecutBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &MyDragWidget::ondevice_name);


    QWidget_feature  =new QWidget;
    QWidget_key  =new QWidget;
    QWidget_read  =new QWidget;
    QWidget_Key_press  =new QWidget;
    QWidget_trigger  =new QWidget;
    QWidget_combination  =new QWidget();

    QWidget_temp  =new QWidget;

    host_qstackedWidget->addWidget(QWidget_temp);
    host_qstackedWidget->addWidget(QWidget_feature);
    host_qstackedWidget->addWidget(QWidget_read);
    host_qstackedWidget->addWidget(QWidget_key);
    host_qstackedWidget->addWidget(QWidget_Key_press);
    host_qstackedWidget->addWidget(QWidget_trigger);
    host_qstackedWidget->addWidget(QWidget_combination);



    int labelWidth = 100;
    int labelHeight = 40;
    int columnSpacing = 130;
    int lineSpacing = 50;



    setQWidgetlayout(QWidget_feature,FeaturetextList,true);
    QStringList FeaturereadtextList;
    QWidget_temp  =new QWidget;

    QGridLayout *layout1 = new QGridLayout(QWidget_temp);
    layout1->addWidget(host_qstackedWidget,0,0,1,1);
    layout1->setContentsMargins(0, 0, 0, 0);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(QWidget_temp);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->verticalScrollBar()->setValue(100);
//    QGridLayout *layout = new QGridLayout(this);
//    layout->addWidget(typboBox,1,0,1,1);
//    layout->addWidget(PlatecutBox,1,1,1,1);
//    layout->addWidget(scrollArea,2,0,1,2);


//    setLayout(layout);

    reconfiguration();







}

MyDragWidget::~MyDragWidget()
{

}

void MyDragWidget::setitems(QStringList _addItems)
{


    PlatecutBox->clear();

    PlatecutBox->addItems(_addItems);
//    QList<QIcon> icons;
//    icons.append(QIcon(":/images/images/Feature.png"));
//    icons.append(QIcon(":/images/images/key.png"));
//    icons.append(QIcon(":/images/images/edition.png"));
//    icons.append(QIcon(":/images/images/edition.png"));
//    icons.append(QIcon(":/images/images/edition.png"));
//    for (int i = 0; i < _addItems.size(); ++i) {
//        PlatecutBox->addItem(icons[0], _addItems[i]);
//    }

}

void MyDragWidget::setkeyname_parameters(QStringList keynamelist, bool f_clear)
{
    setQWidgetlayout(QWidget_Set_parameters_tab_scrollArea,keynamelist ,f_clear);

}

void MyDragWidget::setkeyname(QStringList keynamelist, bool f_clear)
{

     setQWidgetlayout(QWidget_Key_press_tab_scrollArea,keynamelist ,f_clear);
}

void MyDragWidget::setkeyname_press(QStringList keynamelist, bool f_clear)
{
     setQWidgetlayout(QWidget_key_tab_scrollArea,keynamelist ,f_clear);
}

void MyDragWidget::setkeyname_trigger(QStringList keynamelist, bool f_clear)
{
    FeaturetextList =keynamelist;
    setQWidgetlayout(QWidget_trigger_tab_scrollArea,keynamelist ,f_clear);

}

void MyDragWidget::setkeyname_combination(QStringList keynamelist, bool f_clear)
{
    setQWidgetlayout(QWidget_combination_tab_scrollArea,keynamelist ,f_clear);
}

void MyDragWidget::setkeyname_feature(QStringList keynamelist, bool f_clear)
{
    setQWidgetlayout(QWidget_feature_tab_scrollArea,keynamelist,true);
}

void MyDragWidget::setkeyname_read_v(QStringList keynamelist, bool f_clear)
{
    setQWidgetlayout(QWidget_read_tab_scrollArea,keynamelist ,f_clear);
}

void MyDragWidget::Refresh_QWidget()
{
    host_qstackedWidget->setCurrentIndex(1);
     int labelWidth = 100;
     int labelHeight = 40;
     int columnSpacing = 130;
     int lineSpacing = 50;
     int requiredHeight = 20 + (FeaturetextList.size() / 2) * (labelHeight + lineSpacing) + labelHeight;
     QWidget_temp->setMinimumSize(299, requiredHeight);



}

void MyDragWidget::host_qstackedWidgetinit()
{
    host_qstackedWidget->setCurrentIndex(0);

}

void MyDragWidget::Refresh_box()
{
    host_qstackedWidget->setCurrentIndex(0);
    typboBox->setCurrentIndex(0);
    emit myselect_Device(PlatecutBox->currentText());

}

//void MyDragWidget::setQWidgetlayout( QWidget *widnew, QStringList funlist , bool f_clear)
//{

//    if (f_clear) {
//        // 遍历并删除所有子部件
//        QList<QWidget*> children = widnew->findChildren<QWidget*>();
//        for (QWidget* child : children) {
//            child->deleteLater();
//        }
//    }

//    for (int i = 0; i < funlist.size(); i++) {
//        TimelineTextLabel* label = new TimelineTextLabel(widnew);
//        label->setInoutState(widnew);
//        label->setText(funlist.at(i));
//        label->adjustSize();
//        label->move(20 + (i % 2) * columnSpacing, 20 + (i / 2) * (labelHeight + lineSpacing));
//        label->resize(labelWidth, labelHeight);
//        connect(label, &TimelineTextLabel::mouseEntered, this, &MyDragWidget::onLabelMouseEntered);
//        connect(label, &TimelineTextLabel::mouseLeft, this, &MyDragWidget::onLabelMouseLeft);
//        if (i > 0) {

//            QFrame* line = new QFrame(widnew);
//            line->setFrameShape(QFrame::HLine);
//            line->setFrameShadow(QFrame::Sunken);
//            line->setLineWidth(2);
//            line->setGeometry(20 + (i % 2) * columnSpacing, 20 + (i / 2) * (labelHeight + lineSpacing) - lineSpacing/2, columnSpacing, 2); // 设置模线的位置和尺寸
//        }
//    }
//}


void MyDragWidget::setQWidgetlayout( QWidget *widnew, QStringList funlist , bool f_clear)
{


    if (!widnew) {
        return;
    }


    if (f_clear) {

        QLayout *layout = widnew->layout();
        if (layout) {
            QLayoutItem *item;
            while ((item = layout->takeAt(0))) {
                delete item->widget();
                delete item;
            }
            delete layout;
        }

        layout = new QGridLayout(widnew);
        widnew->setLayout(layout);
    }
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(widnew->layout());
    gridLayout->setContentsMargins(0, 0, 0, 0);
    int labelWidth = 100;
    int labelHeight = 40;
    int columnSpacing = 10;
    int lineSpacing = 20;
    gridLayout->setHorizontalSpacing(columnSpacing);
    gridLayout->setVerticalSpacing(lineSpacing);
    int row = 0;
    int column = 0;
    for (const QString &text : funlist) {
        TimelineTextLabel* label = new TimelineTextLabel(widnew);
        label->setInoutState(widnew);
        label->setText(text);
        label->adjustSize();
        label->setFixedSize(labelWidth, labelHeight);
        gridLayout->addWidget(label, row, column);
        column++;
        if (column >= 2) {
            column = 0;
            row++;
        }
    }

    widnew->layout()->update();
}




void MyDragWidget::reconfiguration()
{


    tabWidget = new QTabWidget;

    QWidget_Set_parameters_tab =new QWidget;
    QWidget_combination_tab =new QWidget;
    QWidget_trigger_tab =new QWidget;
    QWidget_key_tab =new QWidget;
    QWidget_Key_press_tab =new QWidget;
    QWidget_read_tab =new QWidget;
    QWidget_feature_tab =new QWidget;


    QWidget_Set_parameters_tab_scrollArea =new QWidget;
    QWidget_combination_tab_scrollArea =new QWidget;
    QWidget_trigger_tab_scrollArea =new QWidget;
    QWidget_key_tab_scrollArea =new QWidget;
    QWidget_Key_press_tab_scrollArea =new QWidget;
    QWidget_read_tab_scrollArea =new QWidget;
    QWidget_feature_tab_scrollArea =new QWidget;


        QWidget_Set_parameters_scrollArea =new QScrollArea;
    QWidget_combination_scrollArea =new QScrollArea;
    QWidget_trigger_scrollArea =new QScrollArea;
    QWidget_key_scrollArea =new QScrollArea;
    QWidget_Key_press_scrollArea =new QScrollArea;
    QWidget_read_scrollArea =new QScrollArea;
    QWidget_feature_scrollArea =new QScrollArea;


    QWidget_feature_scrollArea->setWidgetResizable(true);
    QWidget_read_scrollArea->setWidgetResizable(true);
    QWidget_Key_press_scrollArea->setWidgetResizable(true);
    QWidget_key_scrollArea->setWidgetResizable(true);
    QWidget_trigger_scrollArea->setWidgetResizable(true);
    QWidget_combination_scrollArea->setWidgetResizable(true);
    QWidget_Set_parameters_scrollArea->setWidgetResizable(true);





    tabWidget->addTab(QWidget_feature_tab, QIcon(":/images/images/Feature.png"),"");
    tabWidget->addTab(QWidget_Key_press_tab, QIcon(":/images/images/key_unde.png"), "");
    tabWidget->addTab(QWidget_key_tab, QIcon(":/images/images/key_up.png"), "");
    tabWidget->addTab(QWidget_trigger_tab, QIcon(":/images/images/key_up_unde.png"), "");
    tabWidget->addTab(QWidget_combination_tab, QIcon(":/images/images/key.png"), "");
    tabWidget->addTab(QWidget_read_tab, QIcon(":/images/images/read.png"), "");
    tabWidget->addTab(QWidget_Set_parameters_tab, QIcon(":/images/images/key_m.png"), "");


    //--------
    QVBoxLayout *tab1Layout = new QVBoxLayout(QWidget_feature_tab);
    QWidget_feature_scrollArea->setWidget(QWidget_feature_tab_scrollArea);
    tab1Layout->addWidget(QWidget_feature_scrollArea);

    //--------
    QVBoxLayout *tab2Layout = new QVBoxLayout(QWidget_read_tab);
    QWidget_read_scrollArea->setWidget(QWidget_read_tab_scrollArea);
    tab2Layout->addWidget(QWidget_read_scrollArea);

    //--------
    QVBoxLayout *tab3Layout = new QVBoxLayout(QWidget_Key_press_tab);
    QWidget_Key_press_scrollArea->setWidget(QWidget_Key_press_tab_scrollArea);
    tab3Layout->addWidget(QWidget_Key_press_scrollArea);

    //--------
    QVBoxLayout *tab4Layout = new QVBoxLayout(QWidget_key_tab);
    QWidget_key_scrollArea->setWidget(QWidget_key_tab_scrollArea);
    tab4Layout->addWidget(QWidget_key_scrollArea);

    //--------
    QVBoxLayout *tab5Layout = new QVBoxLayout(QWidget_trigger_tab);
    QWidget_trigger_scrollArea->setWidget(QWidget_trigger_tab_scrollArea);
    tab5Layout->addWidget(QWidget_trigger_scrollArea);

    //--------
    QVBoxLayout *tab6Layout = new QVBoxLayout(QWidget_combination_tab);
    QWidget_combination_scrollArea->setWidget(QWidget_combination_tab_scrollArea);
    tab6Layout->addWidget(QWidget_combination_scrollArea);

    //--------
    QVBoxLayout *tab7Layout = new QVBoxLayout(QWidget_Set_parameters_tab);
    QWidget_Set_parameters_scrollArea->setWidget(QWidget_Set_parameters_tab_scrollArea);
    tab7Layout->addWidget(QWidget_Set_parameters_scrollArea);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(PlatecutBox);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

void MyDragWidget::fun_switching(int np)
{

    host_qstackedWidget->setCurrentIndex(np +1 );
    scrollArea->verticalScrollBar()->setValue(0);
}

void MyDragWidget::ondevice_name(int)
{

    host_qstackedWidget->setCurrentIndex(0);
    typboBox->setCurrentIndex(0);
    emit myselect_Device(PlatecutBox->currentText());
}

void MyDragWidget::onLabelMouseEntered(const QString &text)
{

    if ( typboBox->currentText()  == "功能模块"){
         emit Tipsevent(text);
    }
}

void MyDragWidget::onLabelMouseLeft(const QString &text)
{
    emit Tipsleavevent();
}


