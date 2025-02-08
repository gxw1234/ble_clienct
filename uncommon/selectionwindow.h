#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H


#include <QWidget>
#include <QListView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

class SelectionWindow : public QWidget {
    Q_OBJECT

public:
    explicit SelectionWindow(QStringList items,QWidget *parent = nullptr);
    QStringList _items;

signals:
    void selectionMade(QStringList selectedItems); // 定义信号，用于返回选中的项目

private slots:
    void onButtonClicked();

private:
    QListView *listView;
    QStandardItemModel *model;

protected:
    void closeEvent(QCloseEvent *event) override; // 声明 closeEvent 方法
};

#endif // SELECTIONWINDOW_H
