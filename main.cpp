#include "mainwindow.h"

#include <QApplication>
#include <QApplication>
#include <QTextCodec>
#include <QStyleFactory>

#include <QtGlobal>

int main(int argc, char *argv[])
{

//    qputenv("QT_SCALE_FACTOR", "1.2");
//    qputenv("QT_IM_MODULE", QByteArray("fcitx"));



    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    MainWindow win;
    QFont font;
    font.setPointSize(20);
    QString text_title = "遥控_1.2.7";


//    win.top_qframe->setMaximumSize(QSize(15000, 70));
//    QApplication::setStyle(QStyleFactory::create("Fusion"));
//    win.show_title->setFont(font);
//    win.show_title->setText(text_title);



    win.showMaximized();
    a.setStyle(QStyleFactory::create("windowsvista"));
    return a.exec();
}
