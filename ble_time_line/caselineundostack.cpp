﻿#pragma execution_character_set("utf-8")
#include "caselineundostack.h"

TimelineUndoStack::TimelineUndoStack(TimelineWidget *widget) : QUndoStack(widget), widget(widget)
{
    timeline_undos = this;
    widget->setTimelineUndoVirtual(this);
    //    auto undo_action = createUndoAction(widget, tr("&Undo"));
    //    undo_action->setShortcut(QKeySequence::Undo);
    //    auto redo_action = createRedoAction(widget, tr("&Redo"));
    //    redo_action->setShortcut(QKeySequence::Redo);
}

void TimelineUndoStack::addCommand(int index)
{
    push(new TimelineBucketAddCommand(widget, index));
}

void TimelineUndoStack::addCommand(QList<int> indexes)
{
    push(new TimelineBucketAddCommand(widget, indexes));
}

void TimelineUndoStack::addCommand(QList<int> indexes, QStringList times, QList<QStringList> texts)
{
    push(new TimelineBucketAddCommand(widget, indexes, times, texts));
}

void TimelineUndoStack::addCommand(TimelineBucket *bucket, int index)
{
    push(new TimelineBucketTextAddCommand(widget, widget->indexOf(bucket), index));
}

void TimelineUndoStack::addCommand(TimelineBucket *bucket, QList<int> indexes)
{
    push(new TimelineBucketTextAddCommand(widget, widget->indexOf(bucket), indexes));
}

void TimelineUndoStack::addCommand(QList<int> bucket_indexes, QList<int> text_indexes)
{
    push(new TimelineBucketTextsAddCommand(widget, bucket_indexes, text_indexes));
}

void TimelineUndoStack::addCommand(QList<int> bucket_indexes, QList<QList<int> > texts_indexes)
{
    push(new TimelineBucketTextsAddCommand(widget, bucket_indexes, texts_indexes));
}

void TimelineUndoStack::deleteCommand(int index)
{
    push(new TimelineBucketDeleteCommand(widget, index));
}

void TimelineUndoStack::deleteCommand(QList<int> indexes)
{
    push(new TimelineBucketDeleteCommand(widget, indexes));
}

void TimelineUndoStack::deleteCommand(TimelineBucket *bucket, int index)
{
    push(new TimelineBucketTextDeleteCommand(widget, widget->indexOf(bucket), index));
}

void TimelineUndoStack::deleteCommand(TimelineBucket *bucket, QList<int> indexes)
{
    push(new TimelineBucketTextDeleteCommand(widget, widget->indexOf(bucket), indexes));
}

void TimelineUndoStack::moveCommand(int old_index, int new_index)
{
    push(new TimelineBucketMoveCommand(widget, old_index, new_index));
}

void TimelineUndoStack::moveCommand(TimelineBucket *bucket, int old_index, int new_index)
{
    push(new TimelineBucketTextMoveCommand(widget, widget->indexOf(bucket), old_index, new_index));
}

void TimelineUndoStack::moveCommand(TimelineBucket *old_bucket, TimelineBucket *new_bucket, int old_index, int new_index)
{
    push(new TimelineBucketTextBucketMoveCommand(widget, widget->indexOf(old_bucket), widget->indexOf(new_bucket), old_index, new_index));
}

void TimelineUndoStack::modifyCommand(TimelineBucket *bucket, QString old_text, QString new_text)
{
    push(new TimelineBucketTimeModifyCommand(widget, widget->indexOf(bucket), old_text, new_text));
}

void TimelineUndoStack::modifyCommand(TimelineBucket *bucket, TimelineTextLabel *label, QString old_text, QString new_text)
{
    push(new TimelineBucketTextModifyCommand(widget, widget->indexOf(bucket), bucket->indexOf(label), old_text, new_text));
}

void TimelineUndoStack::undoCommand()
{
    QUndoStack::undo();
}

void TimelineUndoStack::redoCommand()
{
    QUndoStack::redo();
}
