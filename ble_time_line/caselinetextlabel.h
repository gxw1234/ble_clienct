#ifndef TIMELINETEXTLABEL_H
#define TIMELINETEXTLABEL_H

#include <QObject>
#include <QApplication>
#include <QLabel>
#include <QMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QAction>
#include <QClipboard>
#include <QMouseEvent>
#include <QDebug>
#include <QMimeData>
#include <QDrag>
#include <cmath>
#include <QStandardPaths>
#include "caselineglobal.h"

#define TIMELINE_TEXT_MIME_KEY "TIMELINE_TEXT_WIDGET"

class TimelineBucket;
//文本框
class TimelineTextLabel : public QLabel
{
    Q_OBJECT
public:
    TimelineTextLabel(QWidget* parent = nullptr);
    TimelineTextLabel(const TimelineTextLabel*& another, QWidget* parent = nullptr);

    void adjustSize(bool notify = true, QString text = "");

    QPoint getGlobalPos() const;
    void draggedToOut();

    bool getInoutState();
    void setInoutState(bool);


protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    virtual void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
signals:
    void signalClicked();
    void signalDoubleClicked();
    void signalInsertLeft();
    void signalInsertRight();
    void signalDelete();
    void signalCopyText();
    void signalDraggedToOut();
    void signalSizeChanged(QSize size);
    void mouseEntered(const QString& text);
    void mouseLeft(const QString& text);

public slots:
    void slotMenuShowed(const QPoint &);

private:
    QPoint press_pos;
    bool  m_inoutState = false;
};

#endif // TIMELINETEXTLABEL_H
