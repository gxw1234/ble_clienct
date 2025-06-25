#pragma execution_character_set("utf-8")
#include "caselineleadingdot.h"
#include <QPainterPath>

TimelineLeadingDot::TimelineLeadingDot(QWidget *parent) : QRadioButton(parent), bg_color(Qt::blue)
{
    this->setColor(Qt::blue);
    this->setChecked(true); // 默认选中状态
    this->setAutoExclusive(false); // 不自动互斥，让它可以独立控制
    
    // 移除文本和对焦边框
    this->setText("");
    this->setFocusPolicy(Qt::NoFocus);
}

/**
 * 设置背景颜色
 */
void TimelineLeadingDot::setColor(QColor c)
{
    this->bg_color = c;
    update();
}

/**
 * 设置半径，即width和height都是r*2
 */
void TimelineLeadingDot::setRadius(int r)
{
    setFixedSize(r*2, r*2);
}

void TimelineLeadingDot::paintEvent(QPaintEvent *event)
{
    QRadioButton::paintEvent(event);

    // 自定义绘制，覆盖默认RadioButton外观
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    
    // 清除默认外观
    painter.eraseRect(rect());
    
    // 绘制圆形
    QPainterPath path;
    path.addEllipse(0, 0, width(), height());
    
    if (isChecked()) {
        // 选中状态填充颜色
        painter.fillPath(path, bg_color);
    } else {
        // 未选中状态只绘制边框
        painter.setPen(QPen(bg_color, 1));
        painter.drawPath(path);
    }
}

// 设置选中状态
void TimelineLeadingDot::setChecked(bool checked)
{
    QRadioButton::setChecked(checked);
    update();
}

// 获取选中状态
bool TimelineLeadingDot::isChecked() const
{
    return QRadioButton::isChecked();
}
