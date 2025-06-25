#pragma execution_character_set("utf-8")
#include "caselinebucket.h"
#include <QPainterPath>
#include "../common/icon_config.h"
TimelineBucket::TimelineBucket(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
    selecting = false;
    current_index = -1;
    line_color = QColor(0, 0, 255, 126);
    ell_color = QColor(0, 0, 255, 126);
    // 保存初始颜色，用于RadioButton状态切换恢复
    original_line_color = line_color;
    original_ell_color = ell_color;
    initView();
    m_inoutState = false;
}

void TimelineBucket::setTextLabelBorderColor(int index, QColor p_color)
{
    QString style = QString("#TimelineTextLabel { background:white; border: 1px solid rgb(%1,%2,%3); border-radius: 5px; padding: 10px; }").arg(p_color.red()).arg(p_color.green()).arg(p_color.blue());
    if(index < text_widgets.size()){
         text_widgets.at(index)->setStyleSheet(style);
    }
}

void TimelineBucket::setTextLabelBorderAndBackgroundColor(int index, QColor borderColor, QColor backgroundColor)
{
    QString style = QString("#TimelineTextLabel { background:rgb(%1,%2,%3); border: 1px solid rgb(%4,%5,%6); border-radius: 5px; padding: 10px; }")
        .arg(backgroundColor.red()).arg(backgroundColor.green()).arg(backgroundColor.blue())
        .arg(borderColor.red()).arg(borderColor.green()).arg(borderColor.blue());
    if(index < text_widgets.size()){
         text_widgets.at(index)->setStyleSheet(style);
    }
}

void TimelineBucket::setTimelineUndoVirtual(TimelineUndoVirtual *strcs)
{
       m_xx_undos = strcs;
}

void TimelineBucket::initView()
{
    leading_dot = new TimelineLeadingDot(this);
    time_widget = new TimelineTimeLabel(this);

    leading_dot->setRadius(5);

    adjustWidgetsPositions();

    // 连接圆点选中状态变化信号
    connect(leading_dot, &QRadioButton::toggled, this, [=](bool checked) {
        updateRowAppearance(checked);
    });

    connect(time_widget, &TimelineTimeLabel::signalClicked, this, [=] {
        emit signalTimeWidgetClicked(time_widget);
    });
    connect(time_widget, &TimelineTimeLabel::signalDoubleClicked, this, [=] {
        emit signalTimeWidgetDoubleClicked(time_widget);
    });
    connect(time_widget, &TimelineTimeLabel::signalSizeChanged, this, [=](QSize) { // 一般由 setTime 触发
        adjustWidgetsPositionsWithAnimation();
    });
}

void TimelineBucket::setVerticalIndex(int index)
{
    vertical_index = index;
}

void TimelineBucket::setTime(QString time)
{
    time_widget->setText(time);
    time_widget->setScaledContents(true);
    time_widget->adjustSize();
}

void TimelineBucket::setText(int index, QString text)
{
    if (index < 0 || index > text_widgets.size()) // 错误
        return ;
    if (index == text_widgets.size()) // 加一个
    {
        addTextWidget(text);
        return ;
    }

    // 设置内容
    text_widgets.at(index)->setText(text);
    text_widgets.at(index)->adjustSize();
}

void TimelineBucket::setText(QString text)
{
    clearText();
    addTextWidget(text);

    adjustWidgetsSize();
    adjustWidgetsPositions();
}

void TimelineBucket::setText(QStringList texts)
{
    clearText();
    foreach (QString text, texts)
    {
        addTextWidget(text);
    }

    adjustWidgetsSize();
    adjustWidgetsPositions();
}

TimelineTextLabel* TimelineBucket::insertText(int index, QString text)
{
    auto widget = insertTextWidget(text, index);
    adjustWidgetsPositionsWithAnimation();
    return widget;
}

QString TimelineBucket::getText(int index)
{
    if (index < 0 || index >= text_widgets.size())
        return "";
    return text_widgets.at(index)->text();
}

QString TimelineBucket::getTime()
{
    return time_widget->text();
}

QStringList TimelineBucket::getTexts()
{
    QStringList sl;
    foreach (auto label, text_widgets)
        sl << label->text();
    return sl;
}

int TimelineBucket::count()
{
    return text_widgets.size();
}

void TimelineBucket::edit(int index)
{
    if (index == 0)
        emit signalTimeWidgetDoubleClicked(time_widget);
    else if (index > 0 && index <= text_widgets.size())
        emit signalTextWidgetDoubleClicked(text_widgets.at(index-1));
}

TimelineTimeLabel *TimelineBucket::timeLabel() const
{
    return time_widget;
}

TimelineTextLabel *TimelineBucket::at(int index) const
{
    if (index < 0 || index >= text_widgets.size())
        return nullptr;
    return text_widgets.at(index);
}

int TimelineBucket::indexOf(TimelineTextLabel *label)
{
    return text_widgets.indexOf(label);
}

TimelineTextLabel *TimelineBucket::createTextLabel(const TimelineTextLabel *another, int index, QPoint pos)
{
    auto widget = new TimelineTextLabel(another, this);
    this->connectWidgetEvent(widget);
    widget->move(pos.x(), pos.y());
    widget->show();
    text_widgets.insert(index, widget);
    return widget;
}

TimelineTextLabel* TimelineBucket::addTextWidget(QString text)
{
    return insertTextWidget(text, -1);
}

TimelineTextLabel* TimelineBucket::insertTextWidget(QString text, int index)
{
    TimelineTextLabel* label = new TimelineTextLabel(this);
    label->setText(text);
    label->adjustSize(false);
    
    // 为文本标签设置图标
    QIcon icon = IconConfig::getInstance().getIcon(text);
    label->setIcon(icon);
    label->setIconSize(QSize(16, 16));

    if (index > -1)
    {
        if (index > 0)
            label->move(text_widgets.at(index-1)->geometry().topRight());
        else if (index < text_widgets.size())
            label->move(text_widgets.at(index)->geometry().topLeft());
        text_widgets.insert(index, label);
    }
    else // index <= -1
    {
        text_widgets.append(label);
        if (text_widgets.size()>1)
        {
            label->move(text_widgets.at(text_widgets.size()-2)->geometry().topRight());
        }
        else
            label->move(time_widget->geometry().topRight());
    }
    label->show();

    //链接信号槽事件
    connectWidgetEvent(label);
    return label;
}

void TimelineBucket::removeAt(int index)
{
    text_widgets.takeAt(index)->deleteLater();
}

void TimelineBucket::connectWidgetEvent(TimelineTextLabel *label)
{
    connect(label, &TimelineTextLabel::signalClicked, this, [=] {
        emit signalTextWidgetClicked(label);
    });
    connect(label, &TimelineTextLabel::signalDoubleClicked, this, [=] {
        emit signalTextWidgetDoubleClicked(label);
    });
    connect(label, &TimelineTextLabel::signalInsertLeft, this, [=]{
        actionInsertLeft(label);
    });
    connect(label, &TimelineTextLabel::signalInsertRight, this, [=]{
        actionInsertRight(label);
    });
    connect(label, &TimelineTextLabel::signalDelete, this, [=]{
        actionDelete(label);
    });
    connect(label, &TimelineTextLabel::signalDraggedToOut, this, [=]{
        int index = text_widgets.indexOf(label);
        text_widgets.takeAt(index)->deleteLater();
        adjustBucketSize();
        adjustWidgetsPositionsWithAnimation();
    });
    connect(label, &TimelineTextLabel::signalSizeChanged, this, [=](QSize) {
        // 一般由 setText(index, text) 触发，调整内容时文本框大小改变
        adjustBucketSize();
        adjustWidgetsPositionsWithAnimation();
    });
}

void TimelineBucket::actionInsertLeft(TimelineTextLabel *label)
{
    int index = text_widgets.indexOf(label);
    if (index == -1)
        return ;

    m_xx_undos->addCommand(this, index);
    emit signalBucketContentsChanged();
    qDebug()<<"actionInsertLeft"<<index;    
}

void TimelineBucket::actionInsertRight(TimelineTextLabel *label)
{
    int index = text_widgets.indexOf(label);
    if (index == -1)
        return ;

    m_xx_undos->addCommand(this, index+1);
    emit signalBucketContentsChanged();

    qDebug()<<"actionInsertRight"<<index;    
}

void TimelineBucket::actionDelete(TimelineTextLabel *label)
{
    int index = text_widgets.indexOf(label);
    if (index == -1)
        return ;

    m_xx_undos->deleteCommand(this, index);
    emit signalBucketContentsChanged();
}

void TimelineBucket::actionMoveTextLabel(int from, int to)
{
    auto widget = text_widgets.takeAt(from);
    text_widgets.insert(to, widget);

    adjustWidgetsPositionsWithAnimation(qMin(from, to));
}

void TimelineBucket::clearText()
{
    foreach (TimelineTextLabel* label, text_widgets) {
        label->deleteLater();
    }
    text_widgets.clear();
}

QString TimelineBucket::toString(QString time_format, QString para_split)
{
    QString result = QString(time_format).arg(time_widget->text());
    foreach (auto widget, text_widgets)
    {
        result += para_split + widget->text();
    }
    return result;
}

void TimelineBucket::setTimeLabelWidth(int w)
{
    time_widget->setFixedWidth(w);
}

/**
 * 修改控件尺寸（不包含位置）
 */
void TimelineBucket::adjustWidgetsSize()
{
    time_widget->adjustSize(false);
    for (int i = 0; i < text_widgets.size(); i++)
        text_widgets.at(i)->adjustSize(false);
}

/**
 * 根据控件的大小，修改整个外框的大小
 */
void TimelineBucket::adjustBucketSize()
{
    QSize size = getSuitableSize();
    setMinimumSize(size);
    //    resize(size);
    setFixedHeight(size.height());
    emit signalSizeHintChanged(size);
}

/**
 * 根据控件大小，获取对应合适的宽度和高度
 */
QSize TimelineBucket::getSuitableSize()
{
    int sw = padding_left + leading_dot_radius*2 + time_widget->width() + dot_time_spacing;
    int sh = time_widget->height();
    for (int i = 0; i < text_widgets.size(); ++i)
    {
        if (sh < text_widgets.at(i)->height())
            sh = text_widgets.at(i)->height();
        sw += text_widgets.at(i)->width();
    }
    sw += horizone_spacing * (text_widgets.size()+1);
    sh += vertical_spacing;
    return QSize(sw, sh);
}

/**
 * 移动所有控件的位置（不改变大小）
 */
void TimelineBucket::adjustWidgetsPositions(int start)
{
    QSize old_size = size();
    QSize size = getSuitableSize();
    if (size != old_size)
    {
        setMinimumSize(size);
        setFixedHeight(size.height());
        emit signalSizeHintChanged(size);
    }
    int mid_y = height() / 2;
    leading_dot->move(padding_left, mid_y-leading_dot_radius);
    time_widget->move(leading_dot->geometry().right() + dot_time_spacing, mid_y - time_widget->height()/2);

    int left = (start-1)>=0 ? text_widgets.at(start-1)->geometry().right() : time_widget->geometry().right();
    int end = text_widgets.size();
    for (int i = start; i < end; i++)
    {
        TimelineTextLabel* label = text_widgets.at(i);
        left += horizone_spacing;
        label->move(left, mid_y - label->height() / 2);
        left += label->width();
    }
}

/**
 * 调整所有控件的位置，包含动画
 */
void TimelineBucket::adjustWidgetsPositionsWithAnimation(int start, int end)
{
    QSize old_size = size();
    QSize size = getSuitableSize();
    if (size != old_size)
    {
        setMinimumSize(size);
        setFixedHeight(size.height());
        emit signalSizeHintChanged(size);
    }
    int mid_y = height() / 2;
    leading_dot->move(padding_left, mid_y-leading_dot_radius);
    time_widget->move(leading_dot->geometry().right() + dot_time_spacing, mid_y - time_widget->height()/2);

    int left = (start-1)>=0 ? text_widgets.at(start-1)->geometry().right() : time_widget->geometry().right();
    if (end == -1)
        end = text_widgets.size();
    bool firsted = false;
    for (int i = start; i < end; i++)
    {
        TimelineTextLabel* label = text_widgets.at(i);
        left += horizone_spacing;

        QPropertyAnimation* ani = new QPropertyAnimation(label, "pos");
        ani->setStartValue(label->pos());
        ani->setEndValue(QPoint(left, mid_y - label->height()/2));
        ani->setDuration(300);
        ani->setEasingCurve(QEasingCurve::OutQuart);
        connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
        ani->start();
        if (!firsted)
        {
            connect(ani, SIGNAL(valueChanged(const QVariant &)), this, SLOT(update()));
            firsted = true;
        }

        left += label->width();
    }
}

bool TimelineBucket::isSelected()
{
    return selecting;
}

void TimelineBucket::setSelected(bool select)
{
    this->selecting = select;
    repaint();
    QPropertyAnimation* ani = new QPropertyAnimation(this, "water_prop");
    ani->setStartValue(water_prop);
    ani->setEndValue( select ? 100 : 0 );
    ani->setEasingCurve(QEasingCurve::OutQuad);
    ani->setDuration(300);
    connect(ani, SIGNAL(finished()), ani, SLOT(deleteLater()));
    ani->start();
}

void TimelineBucket::setPressPos(QPoint pos)
{
    water_source = pos;
}

bool TimelineBucket::getInoutState()
{
    qDebug()<<"m_inoutState==="<<m_inoutState;
    return m_inoutState;
}

void TimelineBucket::setInoutState(bool state)
{
    m_inoutState = state;
}

void TimelineBucket::setLineColor(QColor color)
{
    line_color = color;
    update();
}
void TimelineBucket::setEllColor(QColor color)
{
    ell_color = color;
    leading_dot->setColor(color);
    update();
}

void TimelineBucket::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    adjustWidgetsSize();
    adjustWidgetsPositions();
}

void TimelineBucket::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(line_color));
    int y = leading_dot->geometry().center().y();

    // 画选中情况
    if (water_prop == 0)
    {

    }
    else if (water_prop == 100)
    {
        painter.fillRect(QRect(0,0,width(),height()), select_color);
    }
    else // 1 ~ 99
    {
        if (!selecting || water_source == QPoint(-1, -1)) // 不知位置，直接渐变
        {
            QColor c = select_color;
            c.setAlpha(select_color.alpha() * water_prop / 100);
            painter.fillRect(QRect(0,0,width(),height()), c);
        }
        else // 画水波纹动画
        {
            int w_max = qMax(water_source.x(), width() - water_source.y());
            int h_max = qMax(water_source.y(), height() - water_source.y());
            int r_max = qMax(w_max, h_max);
            int radius = r_max * water_prop / 100;
            QPainterPath path;
            path.addEllipse(water_source.x() - radius, water_source.y() - radius, radius*2, radius*2);
            painter.fillPath(path, select_color);
        }
    }

    // 画时间轴的线
    int left = padding_left + leading_dot_radius*2;
    int right = time_widget->geometry().left();
    painter.drawLine(QPoint(left, y), QPoint(right, y));

    // 每个控件之前画线条
    for (int i = 0; i < text_widgets.size(); ++i)
    {
        if (i)
            left = text_widgets.at(i-1)->geometry().right();
        else
            left = time_widget->geometry().right();
        right = text_widgets.at(i)->geometry().left();
        painter.drawLine(QPoint(left, y), QPoint(right, y));
    }

    // 画和下一个连接的线条
    if (vertical_index)
    {
        painter.drawLine(QPoint(leading_dot->geometry().center().x(), 0), QPoint(leading_dot->geometry().center().x(), height()));
    }
    else // 第一行
    {
        painter.drawLine(leading_dot->geometry().center(), QPoint(leading_dot->geometry().center().x(), height()));
    }
}

void TimelineBucket::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
}

void TimelineBucket::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
}

void TimelineBucket::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        water_source = press_pos = event->pos();
        if (water_prop != 100) // 如果已经选中了，就不重新刷新了
            water_prop = 0;
        emit signalBucketWidgetPressed();
        return event->accept();
    }
    else if (event->button() == Qt::RightButton)
    {
        if (!isSelected())
            emit signalBucketWidgetPressed();
    }

    QWidget::mousePressEvent(event);
}

void TimelineBucket::mouseReleaseEvent(QMouseEvent *event)
{
    if ((press_pos-event->pos()).manhattanLength() < QApplication::startDragDistance())
    {
        emit signalBucketWidgetClicked();
        return event->accept();
    }

    QWidget::mouseReleaseEvent(event);
}

void TimelineBucket::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
}

void TimelineBucket::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) // 左键拖拽
    {
        if ((event->pos() - press_pos).manhattanLength() >= QApplication::startDragDistance())
        {
            QMimeData* mime = new QMimeData();
            mime->setData(TIMELINE_BUCKET_MIME_KEY, QString::number(reinterpret_cast<qint64>(this)).toUtf8());
            mime->setText(toString());
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mime);
            drag->setHotSpot(event->pos()); // 好像没什么用
            QPixmap pixmap(getSuitableSize());

            {
                water_prop = 0; // 画未选中的
                repaint();
                pixmap.fill(Qt::transparent);
                render(&pixmap);

                // 保存临时文件
                QString path = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
                QString time = time_widget->text();
                time.replace("\\", "").replace("/", "").replace(":", "").replace("*", "").replace("?", "").replace("\"", "")
                        .replace("<", "").replace(">", "").replace("|", "");
                if (time.isEmpty())
                    time = "未定";
                path += "/"+time+".png";
                pixmap.save(path);
                mime->setUrls(QList<QUrl>{QUrl("file:///" + path)});
            }
            {
                water_prop = 100; // 画选中的
                repaint();
                pixmap.fill(Qt::transparent);
                render(&pixmap);
                drag->setPixmap(pixmap);
            }
            drag->exec(Qt::MoveAction);
        }
        return event->accept();
    }

    QWidget::mouseMoveEvent(event);
}

/**
 * 拖拽的内容进入事件
 */
void TimelineBucket::dragEnterEvent(QDragEnterEvent *event)
{
    if (canDropMimeData(event))
        event->accept();
    QWidget::dragEnterEvent(event);
}

void TimelineBucket::dragMoveEvent(QDragMoveEvent *event)
{
    if (canDropMimeData(event))
        event->accept();

    QWidget::dragMoveEvent(event);
}

void TimelineBucket::dragLeaveEvent(QDragLeaveEvent *event)
{
    QWidget::dragLeaveEvent(event);
}

/**
 * 拖拽时鼠标松开事件
 */
void TimelineBucket::dropEvent(QDropEvent *event)
{
    qDebug()<<"拖拽时鼠标松开事件";
    const QMimeData* mime = event->mimeData();
    if (event->source() == this) // 内部拖拽
    {
        // 经常触发的自己拖拽给自己，无视
        qDebug()<<"经常触发的自己拖拽给自己，无视";
    }
    else // 外部拖拽，交换顺序/移动数据
    {
        qDebug()<<"外部拖拽，交换顺序/移动数据";
        if (mime->hasFormat(TIMELINE_BUCKET_MIME_KEY)) // 上下交换行
        {
            qDebug()<<"TimelineBucket";
            TimelineBucket* bucket = reinterpret_cast<TimelineBucket*>(mime->data(TIMELINE_BUCKET_MIME_KEY).toLongLong());
            emit signalDroppedAndMoved(bucket);
        }
        else if (mime->hasFormat(TIMELINE_TEXT_MIME_KEY)) // 左右或者和其他bucket交换文字
        {
            qDebug()<<"TimelineTextLabel1";
            TimelineTextLabel* label = reinterpret_cast<TimelineTextLabel*>(mime->data(TIMELINE_TEXT_MIME_KEY).toLongLong());
            qDebug()<<"TimelineTextLabel2";
            // 获取拖拽到目标的索引
            int to_index = text_widgets.size(); // 默认是到最后面
            QPoint pos = event->pos();
            for (int i = 0; i < text_widgets.size(); i++)
            {
                if (text_widgets.at(i)->geometry().right() >= pos.x()) // 移到这个 label 的后面
                {
                    to_index = i;
                    break;
                }
            }
            // qDebug()<<"TimelineTextLabel3";
            if(label->getInoutState() == false){//内部文本
                // 获取被拖拽的目标
                int from_index = text_widgets.indexOf(label);
                // qDebug()<<"TimelineTextLabel4";
                if (from_index == -1) // 外面拖进来的
                {
                    // qDebug()<<"TimelineTextLabel6";
                    auto prev_bucket = static_cast<TimelineBucket*>(label->parentWidget());
                    // qDebug()<<"TimelineTextLabel7";

                    if(prev_bucket!=nullptr){
                        bool state = prev_bucket->getInoutState();
                        if(state == false){//自己人
                            qDebug()<<"自己人--";
                            int prev_index = prev_bucket->indexOf(label);
                            qDebug()<<"prev_index=="<<prev_index;
                            
                            // 在调用moveCommand前，确保获取原始标签的图标信息
                            QIcon icon = label->getIcon();
                            QSize iconSize = label->getIconSize();
                            
                            // 执行移动命令
                            m_xx_undos->moveCommand(prev_bucket, this, prev_index, to_index);
                            
                            // 确保移动后的标签拥有正确的图标
                            if (!text_widgets.isEmpty() && to_index < text_widgets.size()) {
                                TimelineTextLabel* movedLabel = text_widgets.at(to_index);
                                movedLabel->setIcon(icon);
                                movedLabel->setIconSize(iconSize);
                            }
                        }else{
                            qDebug()<<"外部来的--"<<label->text();
                            auto widget = new TimelineTextLabel( this);
                            connectWidgetEvent(widget);
                            widget->setText(label->text());
                            widget->move(label->x(), label->getGlobalPos().y() - this->pos().y());
                            
                           
                            QIcon icon = IconConfig::getInstance().getIcon(label->text());
                            widget->setIcon(icon);
                            widget->setIconSize(QSize(16, 16));
                            widget->show();
                            text_widgets.insert(to_index, widget);
                            adjustBucketSize(); // 从其他bucket那里移动过来，需要手动更换位置
                            adjustWidgetsPositionsWithAnimation(); // TODEL
                        }
                    }else{
                        qDebug()<<"外部来的--";
                    }
                }
                else // 自己的，删掉旧的
                {
                    // moveTextLabel(from_index, to_index);
                    m_xx_undos->moveCommand(this, from_index, to_index);
                }
            }else{//外部拖拽进来的
                qDebug()<<"外部来的--"<<label->text();
                auto widget = new TimelineTextLabel( this);
                connectWidgetEvent(widget);
                widget->setText(label->text());
                widget->move(label->x(), label->getGlobalPos().y() - this->pos().y());
                
                // 为新创建的文本标签设置图标
                QIcon icon = IconConfig::getInstance().getIcon(label->text());
                widget->setIcon(icon);
                widget->setIconSize(QSize(16, 16));
                
                widget->show();
                text_widgets.insert(to_index, widget);
                adjustBucketSize(); // 从其他bucket那里移动过来，需要手动更换位置
                adjustWidgetsPositionsWithAnimation(); // TODEL
            }
            emit signalBucketContentsChanged();
            repaint();
        }
    }

    QWidget::dropEvent(event);
}

bool TimelineBucket::canDropMimeData(QDropEvent *event)
{
    const QMimeData* mime = event->mimeData();
    if (mime->hasFormat(TIMELINE_BUCKET_MIME_KEY)) // 整行拖拽
    {

        TimelineBucket* bucket = reinterpret_cast<TimelineBucket*>(mime->data(TIMELINE_BUCKET_MIME_KEY).toInt());
        if (bucket)
        {
            return true;
        }
    }
    else if (mime->hasFormat(TIMELINE_TEXT_MIME_KEY)) // 单个TextWidget拖拽
    {
        // qDebug() <<"整行";
        return true;
    }
    return false;
}

int TimelineBucket::getWaterProp()
{
    return water_prop;
}

void TimelineBucket::setWaterProp(int p)
{
    water_prop = p;
    update();
}

// 更新整行外观，根据圆点选中状态
void TimelineBucket::updateRowAppearance(bool checked)
{
    

}
