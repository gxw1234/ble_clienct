#ifndef MENUBAR_H
#define MENUBAR_H
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QObject>
#include <QEvent>



class MenuBarHoverWatcher;

class MenuBar : public QMenuBar {
    Q_OBJECT

public:
    explicit MenuBar(QWidget *parent = nullptr);
    virtual ~MenuBar();

signals:
    void menuActionTriggered(QAction* action);

private:
    void createActions();
    void createMenus();

    QAction *debug_ui;
    QAction *test_ui;
    QAction *burn_ui;
    QAction *disposition_ui;
    QMenu *fileMenu;
    MenuBarHoverWatcher *menuBarHoverWatcher;
    QAction *help_a;
    QAction *tcp_lashback;
    QMenu *help_m;
    QAction *exit_a;
    QMenu *exit_m;
    QAction *download_log;
    QMenu *download_m;
};

class MenuBarHoverWatcher : public QObject {
    Q_OBJECT

public:
    explicit MenuBarHoverWatcher(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // MENUBAR_H
