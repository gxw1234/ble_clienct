#ifndef TIMELINELEADINGDOT_H
#define TIMELINELEADINGDOT_H

#include <QObject>
#include <QRadioButton>
#include <QPainter>
#include <QDebug>
#include "caselineglobal.h"

//这里画圆点
class TimelineLeadingDot : public QRadioButton
{
    Q_OBJECT
public:
    TimelineLeadingDot(QWidget *parent = nullptr);

    void setColor(QColor c);
    void setRadius(int r);
    void setChecked(bool checked);
    bool isChecked() const;

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

public slots:

private:
    QColor bg_color;
};

#endif // TIMELINELEADINGDOT_H
