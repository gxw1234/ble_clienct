#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "uncommon/subassembleqwidget.h"
#include <QMdiArea>
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMdiArea *mdiArea;
    void createSubWindow(const QString &title,const QString &ip,const QString &mac);
    QSettings settings;
    QComboBox *topsideboBox;
    QComboBox *maximizeboBox;
    QPushButton *tiledcomboBox;
    QLabel *topsidebolabel;
    QLabel *maximizebolabel;
    QLabel *tiledcombolabel;
    QComboBox *showwindowBox;
    QPushButton *showwindow;





private slots:
    void ontopsideboBox(int index);
    void onmaximizeboBox(int index);
    void onshowwindow();

};
#endif // MAINWINDOW_H
