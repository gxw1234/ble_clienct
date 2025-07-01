#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QEvent>
#include <QMdiSubWindow>
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),settings("./record/config.ini", QSettings::IniFormat)
{
    this->setWindowTitle("1.3.1");
    this->setWindowIcon(QIcon(":/images/images/Bluetooth.png"));
    mdiArea = new QMdiArea(this);
    topsideboBox = new QComboBox;
    maximizeboBox= new QComboBox;
    tiledcomboBox= new QPushButton;
    showwindowBox= new QComboBox;
    showwindow= new QPushButton;
    topsidebolabel=  new QLabel;
    topsidebolabel->setText("窗口最上面");
    maximizebolabel=  new QLabel;
    maximizebolabel->setText("窗口最大化");
    tiledcombolabel=  new QLabel;
    tiledcombolabel->setText("平铺");
    connect(topsideboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::ontopsideboBox);
    connect(maximizeboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onmaximizeboBox);
    connect(showwindow, &QPushButton::clicked, this, &MainWindow::onshowwindow);
    QFrame * temp = new QFrame;
    QGridLayout *temp_ly;
    temp_ly =new QGridLayout(temp);
    temp_ly->addWidget(topsidebolabel,0,0,1,1);
    temp_ly->addWidget(topsideboBox,0,1,1,1);
    temp_ly->addWidget(maximizebolabel,0,2,1,1);
    temp_ly->addWidget(maximizeboBox,0,3,1,1);
    temp_ly->addWidget(tiledcombolabel,0,4,1,1);
    temp_ly->addWidget(tiledcomboBox,0,5,1,1);
    temp_ly->addWidget(showwindowBox,0,6,1,1);
    temp_ly->addWidget(showwindow,0,7,1,1);
    settings.beginGroup("Settings");
    QStringList valueList;
    QStringList keys = settings.allKeys();

    for (const QString& key : keys) {
        QString value = settings.value(key).toString();
        valueList.append(key+ "ip: "+value);
        QStringList parts = value.split('&');
        createSubWindow(key,parts.at(0),parts.at(1));
    }
    settings.endGroup();
    

    int windowCount = keys.size();
    if (windowCount == 1) {
        QList<QMdiSubWindow*> subWindows = mdiArea->subWindowList();
        if (!subWindows.isEmpty()) {
            subWindows.first()->showMaximized();
        }
    } else if (windowCount > 1) {
        mdiArea->tileSubWindows();
    }
    
    QGridLayout *ui_ly;
    ui_ly =new QGridLayout();
    ui_ly->addWidget(temp,0,0,1,1);
    ui_ly->addWidget(mdiArea,1,0,1,1);
    ui_ly->setContentsMargins(0, 0, 0, 0);
    QWidget * maina =new QWidget;
    maina->setLayout(ui_ly);
         if (centralWidget()) {
         centralWidget()->setParent(nullptr);
     }
    setCentralWidget(maina);

}

void MainWindow::createSubWindow(const QString &title,const QString &ip,const QString &mac)
{
    subassembleqwidget *subWidget = new subassembleqwidget(title,ip,mac);
    QMdiSubWindow *subWindow = mdiArea->addSubWindow(subWidget);
    subWidget->setAttribute(Qt::WA_DeleteOnClose);
    subWidget->show();
    topsideboBox->addItem(title, QVariant::fromValue(static_cast<void*>(subWindow)));
    maximizeboBox->addItem(title, QVariant::fromValue(static_cast<void*>(subWindow)));
    showwindowBox->addItem(title, QVariant::fromValue(static_cast<void*>(subWindow)));
}

void MainWindow::ontopsideboBox(int index)
{
    QVariant data = topsideboBox->itemData(index);
    QMdiSubWindow *subWindow = static_cast<QMdiSubWindow*>(data.value<void*>());
    if (subWindow) {
        mdiArea->setActiveSubWindow(subWindow);
        subWindow->raise();
        subWindow->activateWindow();
    }
}

void MainWindow::onshowwindow()
{
    int index = showwindowBox->currentIndex();
    if (index != -1) {
        QVariant data = showwindowBox->itemData(index);
        QMdiSubWindow *subWindow = static_cast<QMdiSubWindow*>(data.value<void*>());
        if (subWindow && subWindow->isHidden()) {
            subWindow->show();
        }
    }
}



void MainWindow::onmaximizeboBox(int index)
{
    int currentIndex = showwindowBox->currentIndex();
    if (currentIndex != -1) {
        QVariant data = showwindowBox->itemData(currentIndex);
        QMdiSubWindow *subWindow = static_cast<QMdiSubWindow*>(data.value<void*>());
        if (subWindow) {
            if (subWindow->isHidden()) {
                subWindow->show();
            }
            subWindow->raise();
            subWindow->activateWindow();
        }
    }
}


MainWindow::~MainWindow()
{

}

