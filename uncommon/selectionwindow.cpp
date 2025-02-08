#include "selectionwindow.h"
#include <QCloseEvent>
#include <QDebug>

SelectionWindow::SelectionWindow(QStringList items,QWidget *parent) : QWidget(parent) {


    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    QVBoxLayout *layout = new QVBoxLayout(this);
    this->resize(800, 600);

    listView = new QListView();
    model = new QStandardItemModel(this);
    listView->setModel(model);
    listView->setSelectionMode(QAbstractItemView::MultiSelection); // 设置为多重选择
    for (const QString &itemText : items) {
        QStandardItem *item = new QStandardItem(itemText);
        model->appendRow(item);
    }

    layout->addWidget(listView);


    QPushButton *button = new QPushButton("确认选择测试文件并关闭");
    layout->addWidget(button);


    connect(button, &QPushButton::clicked, this, &SelectionWindow::onButtonClicked);
    qDebug() << items;
}

void SelectionWindow::onButtonClicked() {
    QModelIndexList selectedIndexes = listView->selectionModel()->selectedIndexes();
//    QString selectedItems;

//
//    for (const QModelIndex &index : selectedIndexes) {
//        selectedItems += index.data().toString() + "\n"; // 拼接选中的项目文本
//    }


    QStringList selectedItems;

        for (const QModelIndex &index : selectedIndexes) {
            selectedItems << index.data().toString(); // 将选中的项目添加到 QStringList
        }

    emit selectionMade(selectedItems);
    close();


}
void SelectionWindow::closeEvent(QCloseEvent *event) {

    event->accept();
}
