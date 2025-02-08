﻿#pragma execution_character_set("utf-8")
#include "labeleditor.h"

LabelEditor::LabelEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    setObjectName("TimelineEdit");
    // setMaximumBlockCount(1); // 虽然很想加，但是会导致不能撤销……
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void LabelEditor::setOriginText(QString text)
{
    origin_text = text;
}

QString LabelEditor::getOriginText()
{
    return origin_text;
}

/**
 * 切换其它操作时，自动结束编辑
 */
void LabelEditor::finishIfEditing()
{
    if (!this->isHidden())
        emit signalEditFinished(toPlainText());
}

void LabelEditor::keyPressEvent(QKeyEvent *event)
{
    auto key = event->key();
    auto modifiers = event->modifiers();

    if (key == Qt::Key_Escape)
    {
        emit signalEditCanceled(origin_text);
        this->hide();
        return ;
    }
    else if (key == Qt::Key_Return || key == Qt::Key_Enter || key == Qt::Key_Tab)
    {
        emit signalEditFinished(toPlainText());
        hide();
        return ;
    }

    return QPlainTextEdit::keyPressEvent(event);
}
