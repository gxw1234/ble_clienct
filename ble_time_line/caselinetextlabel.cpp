#pragma execution_character_set("utf-8")
#include "caselinetextlabel.h"

TimelineTextLabel::TimelineTextLabel(QWidget *parent) : QLabel(parent)
{
    setObjectName("TimelineTextLabel");
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested (const QPoint&)),this,SLOT(slotMenuShowed(const QPoint&)));
    setWordWrap(true);
    
    // 初始化图标相关成员变量
    m_iconSize = QSize(16, 16);
    m_iconPosition = Qt::AlignLeft | Qt::AlignVCenter;
}

TimelineTextLabel::TimelineTextLabel(const TimelineTextLabel *&another, QWidget *parent) : TimelineTextLabel(parent)
{
    setText(another->text());
    resize(another->size());
}

void TimelineTextLabel::adjustSize(bool notify, QString text)
{
    QSize old_size = size();
    {
        QFontMetrics fm(this->font());

        int line_height = fm.lineSpacing();
        int total_width = fm.horizontalAdvance(text);

        if (total_width <= 20)
        {
            setMinimumWidth(0);
        }
        else
        {
            int line_count =static_cast<int>(sqrt(qMax(total_width / line_height / 5, 1)));
            int text_width = (total_width + line_count - 1) / line_count;
            setMinimumWidth(text_width + 20); // padding=10
        }
        QLabel::adjustSize();
    }

    if (notify && old_size != size())
        emit signalSizeChanged(size());
}

QPoint TimelineTextLabel::getGlobalPos() const
{
    return pos() + parentWidget()->pos();
}

void TimelineTextLabel::draggedToOut()
{
    emit signalDraggedToOut();
}

bool TimelineTextLabel::getInoutState()
{
//    qDebug()<<"getInoutState==="<<m_inoutState;
    return m_inoutState;
}

void TimelineTextLabel::setInoutState(bool state)
{
    m_inoutState = state;
//    qDebug()<<"setInoutState==="<<m_inoutState;
}

void TimelineTextLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        press_pos = event->pos();
    }
    QLabel::mousePressEvent(event);
}

void TimelineTextLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if ((press_pos-event->pos()).manhattanLength() < QApplication::startDragDistance())
        {
            emit signalClicked();
        }
        return event->accept();
    }
    QLabel::mouseReleaseEvent(event);
}

void TimelineTextLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit signalDoubleClicked();
        return event->accept();
    }

    QLabel::mouseDoubleClickEvent(event);
}

void TimelineTextLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if ((event->pos() - press_pos).manhattanLength() >= QApplication::startDragDistance())
        {
            QMimeData* mime = new QMimeData();
            mime->setData(TIMELINE_TEXT_MIME_KEY, QString::number(reinterpret_cast<qint64>(this)).toUtf8());
            mime->setText(this->text());
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mime);
            drag->setHotSpot(event->pos());
            QPixmap pixmap;
            if(m_inoutState == false){
                pixmap = QPixmap(size());
                pixmap.fill(Qt::transparent);
            }else{
                pixmap = QPixmap(100,40);
                pixmap.fill(QColor("red"));
            }
            render(&pixmap);
            {
                // 保存临时文件
                QString path = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
                QString text = this->text();
                text.replace("\\", "").replace("/", "").replace(":", "").replace("*", "").replace("?", "").replace("\"", "")
                        .replace("<", "").replace(">", "").replace("|", "");
                if (text.isEmpty())
                    text = "未定";
                else if (text.length() > 8)
                    text = text.left(8);
                path += "/"+text+".png";
                pixmap.save(path);
                mime->setUrls(QList<QUrl>{QUrl("file:///" + path)});
            }
            drag->setPixmap(pixmap);
            drag->exec(Qt::MoveAction);
        }
        return event->accept();
    }
    QLabel::mouseMoveEvent(event);
}

// 新增图标相关方法实现
void TimelineTextLabel::setIcon(const QIcon& icon)
{
    m_icon = icon;
    update(); // 重绘控件
}

void TimelineTextLabel::setIcon(const QString& iconPath)
{
    m_icon = QIcon(iconPath);
    update(); // 重绘控件
}

void TimelineTextLabel::setIconSize(const QSize& size)
{
    m_iconSize = size;
    update(); // 重绘控件
}

QIcon TimelineTextLabel::getIcon() const
{
    return m_icon;
}

QSize TimelineTextLabel::getIconSize() const
{
    return m_iconSize;
}

void TimelineTextLabel::setIconPosition(Qt::Alignment position)
{
    m_iconPosition = position;
    update(); // 重绘控件
}

Qt::Alignment TimelineTextLabel::getIconPosition() const
{
    return m_iconPosition;
}

void TimelineTextLabel::drawIconAndText(QPainter& painter, const QRect& rect)
{
    if (m_icon.isNull()) {
        // 没有图标，只绘制文本
        QTextOption textOption;
        textOption.setAlignment(Qt::AlignCenter);
        painter.drawText(rect, this->text(), textOption);
        return;
    }

    QPixmap iconPixmap = m_icon.pixmap(m_iconSize);
    if (iconPixmap.isNull()) {
        // 图标加载失败，只绘制文本
        QTextOption textOption;
        textOption.setAlignment(Qt::AlignCenter);
        painter.drawText(rect, this->text(), textOption);
        return;
    }

    // 计算图标和文本的位置
    QRect iconRect;
    QRect textRect;
    
    int iconTextSpacing = 4; // 图标和文本之间的间距
    
    if (m_iconPosition & Qt::AlignLeft) {
        // 图标在左侧
        iconRect = QRect(rect.left() + 2, rect.center().y() - m_iconSize.height()/2, 
                        m_iconSize.width(), m_iconSize.height());
        textRect = QRect(iconRect.right() + iconTextSpacing, rect.top(), 
                        rect.width() - iconRect.width() - iconTextSpacing - 4, rect.height());
    } else if (m_iconPosition & Qt::AlignRight) {
        // 图标在右侧
        iconRect = QRect(rect.right() - m_iconSize.width() - 2, rect.center().y() - m_iconSize.height()/2, 
                        m_iconSize.width(), m_iconSize.height());
        textRect = QRect(rect.left() + 2, rect.top(), 
                        rect.width() - iconRect.width() - iconTextSpacing - 4, rect.height());
    } else if (m_iconPosition & Qt::AlignTop) {
        // 图标在上方
        iconRect = QRect(rect.center().x() - m_iconSize.width()/2, rect.top() + 2, 
                        m_iconSize.width(), m_iconSize.height());
        textRect = QRect(rect.left(), iconRect.bottom() + iconTextSpacing, 
                        rect.width(), rect.height() - iconRect.height() - iconTextSpacing - 4);
    } else {
        // 图标在下方
        iconRect = QRect(rect.center().x() - m_iconSize.width()/2, rect.bottom() - m_iconSize.height() - 2, 
                        m_iconSize.width(), m_iconSize.height());
        textRect = QRect(rect.left(), rect.top() + 2, 
                        rect.width(), rect.height() - iconRect.height() - iconTextSpacing - 4);
    }

    // 绘制图标
    painter.drawPixmap(iconRect, iconPixmap);
    
    // 绘制文本
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignCenter);
    painter.drawText(textRect, this->text(), textOption);
}

//单个输入框菜单
void TimelineTextLabel::slotMenuShowed(const QPoint &)
{
    QMenu* menu = new QMenu("菜单", this);
    QAction* insert_left_action = new QAction("左边插入步骤", this);
    QAction* insert_right_action = new QAction("右边插入步骤", this);
    QAction* delete_action = new QAction("删除步骤", this);
    QAction* copy_text_action = new QAction("复制节点文字", this);
    QAction* paste_text_action = new QAction("粘贴文字", this);
    menu->addAction(insert_left_action);
    menu->addAction(insert_right_action);
    menu->addAction(delete_action);
    menu->addSeparator();
    menu->addAction(copy_text_action);
    menu->addAction(paste_text_action);

    QClipboard* clip = QApplication::clipboard();
    if (!clip->mimeData()->hasText() || clip->mimeData()->text().contains("\n"))
        paste_text_action->setEnabled(false);

    connect(insert_left_action, &QAction::triggered, this, [=] {
        emit signalInsertLeft();
    });
    connect(insert_right_action, &QAction::triggered, this, [=] {
        emit signalInsertRight();
    });
    connect(delete_action, &QAction::triggered, this, [=] {
        emit signalDelete();
    });
    connect(copy_text_action, &QAction::triggered, this, [=] {
        QClipboard* clip = QApplication::clipboard();
        clip->setText(text());
    });
    connect(paste_text_action, &QAction::triggered, this, [=] {
        QClipboard* clip = QApplication::clipboard();
        QString text = clip->mimeData()->text();
        timeline_undos->modifyCommand((TimelineBucket*)(parentWidget()), this, this->text(), text);
    });

    menu->exec(QCursor::pos());
}

void TimelineTextLabel::enterEvent(QEvent* event) {

    emit mouseEntered(this->text());
    QLabel::enterEvent(event);
}
void TimelineTextLabel::leaveEvent(QEvent* event) {

    emit mouseLeft(this->text());
    QLabel::leaveEvent(event);
}

//
void TimelineTextLabel::paintEvent(QPaintEvent *event)
{

    // qDebug()<<"paintEvent----------";
    if(m_inoutState == true){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(Qt::white);
        painter.setPen(Qt::blue);
        painter.drawRoundedRect(0, 0, 100, 40, 10, 10);

        // 使用新的绘制方法，支持图标
        drawIconAndText(painter, this->rect());
    }else{
        QPainter painter(this);
        painter.setBrush(QColor("blue"));
        painter.setRenderHint(QPainter::Antialiasing);
        
        // 使用新的绘制方法，支持图标
        drawIconAndText(painter, this->rect());
    }
}
