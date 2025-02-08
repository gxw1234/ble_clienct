#ifndef TIPS_WIDGET_H
#define TIPS_WIDGET_H


#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>


class Tips_widget: public QWidget
{
public:
    Tips_widget( QString tipstext,QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *label;
    QString m_tipstext;
};

#endif // TIPS_WIDGET_H
