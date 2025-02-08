#include "menubar.h"
#include <QApplication>

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
    menuBarHoverWatcher = new MenuBarHoverWatcher(this);
    createActions();
    createMenus();
}

MenuBar::~MenuBar() {
    delete menuBarHoverWatcher;
}

void MenuBar::createActions() {

    debug_ui = new QAction(tr("调试界面"), this);
    connect(debug_ui, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(debug_ui);
    });



    test_ui = new QAction(tr("测试界面"), this);
    connect(test_ui, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(test_ui);
    });


    burn_ui = new QAction(tr("烧录界面"), this);
    connect(burn_ui, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(burn_ui);
    });

    disposition_ui = new QAction(tr("版型配置"), this);
    connect(disposition_ui, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(disposition_ui);
    });



    download_log = new QAction(tr("下载测试结果"), this);
    connect(download_log, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(download_log);
    });



    help_a = new QAction(tr("帮助"), this);
    connect(help_a, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(help_a);
    });


    tcp_lashback = new QAction(tr("TCP回连"), this);
    connect(tcp_lashback, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(tcp_lashback);
    });


    help_a = new QAction(tr("帮助"), this);
    connect(help_a, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(help_a);
    });


    exit_a = new QAction(tr("退出"), this);
    connect(exit_a, &QAction::triggered, this, [this]() {
        emit menuActionTriggered(exit_a);
    });





}


void MenuBar::createMenus() {

    // 创建文件菜单
    fileMenu = addMenu(tr("测试界面切换"));
    fileMenu->addAction(debug_ui);
    fileMenu->addAction(test_ui);

    fileMenu->installEventFilter(menuBarHoverWatcher);

    help_m = addMenu(tr("辅助界面切换"));
    help_m->addAction(burn_ui);
    help_m->addAction(disposition_ui);
    help_m->addAction(download_log);
    help_m->installEventFilter(menuBarHoverWatcher);

    download_m = addMenu(tr("下载"));
    download_m->addAction(download_log);
    download_m->installEventFilter(menuBarHoverWatcher);

    exit_m = addMenu(tr("退出"));
    exit_m->addAction(exit_a);
    exit_m->installEventFilter(menuBarHoverWatcher);

}

MenuBarHoverWatcher::MenuBarHoverWatcher(QObject *parent) : QObject(parent) {

}

bool MenuBarHoverWatcher::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::HoverEnter) {
        if (QMenu *menu = qobject_cast<QMenu *>(obj)) {
            menu->exec();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}


