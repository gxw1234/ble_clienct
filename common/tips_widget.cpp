#include "tips_widget.h"

Tips_widget::Tips_widget(QString tipstext,QWidget *parent) : QWidget(parent, Qt::FramelessWindowHint | Qt::Tool)
{
    m_tipstext =tipstext;
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowModality(Qt::NonModal);

    QVBoxLayout *layout = new QVBoxLayout(this);
    label = new QLabel(m_tipstext, this);
    QFont font = label->font();
    font.setPointSize(12);

    label->setFont(font);
    layout->addWidget(label);

    setLayout(layout);

}
void Tips_widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    QColor backgroundColor(255, 255, 255, 204);
    painter.setBrush(backgroundColor);
    painter.setPen(Qt::NoPen);


    QRect rect = this->rect();
    QPainterPath path;
    path.addRoundedRect(rect, 20, 20);
    painter.drawPath(path);


    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
}
