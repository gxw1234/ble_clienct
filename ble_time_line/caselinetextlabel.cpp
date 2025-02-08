#pragma execution_character_set("utf-8")
#include "caselinetextlabel.h"

TimelineTextLabel::TimelineTextLabel(QWidget *parent) : QLabel(parent)
{
    setObjectName("TimelineTextLabel");
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested (const QPoint&)),this,SLOT(slotMenuShowed(const QPoint&)));
    setWordWrap(true);
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
//
void TimelineTextLabel::paintEvent(QPaintEvent *event)
{
    if(m_inoutState == true){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(Qt::white);
        painter.setPen(Qt::blue);
        painter.drawRoundedRect(0, 0, 100, 40, 10, 10);

        QTextOption textOption;
        textOption.setAlignment(Qt::AlignCenter);
        painter.drawText(this->rect(),this->text(),textOption);
    }else{
        QPainter painter(this);
        painter.setBrush(QColor("blue"));
        painter.setRenderHint(QPainter::Antialiasing);
        QTextOption textOption;
        textOption.setAlignment(Qt::AlignCenter);
        painter.drawText(this->rect(),this->text(),textOption);
    }
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
