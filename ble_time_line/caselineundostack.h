﻿#ifndef TIMELINEUNDOSTACK_H
#define TIMELINEUNDOSTACK_H

#include <QObject>
#include <QUndoStack>
#include <QAction>
#include "caselinewidget.h"
#include "caselineundocommands.h"
//撤销栈
class TimelineUndoStack : public QUndoStack, public TimelineUndoVirtual
{
public:
    TimelineUndoStack(TimelineWidget* widget);

    virtual void addCommand(int index) override;
    virtual void addCommand(QList<int> indexes) override;
    virtual void addCommand(QList<int> indexes, QStringList times, QList<QStringList> texts) override;
    virtual void addCommand(TimelineBucket* bucket, int index) override;
    virtual void addCommand(TimelineBucket* bucket, QList<int> indexes) override;
    virtual void addCommand(QList<int> bucket_indexes, QList<int> text_indexes) override;
    virtual void addCommand(QList<int> bucket_indexes, QList<QList<int>> texts_indexes) override;
    virtual void deleteCommand(int index) override;
    virtual void deleteCommand(QList<int> indexes) override;
    virtual void deleteCommand(TimelineBucket* bucket, int index) override;
    virtual void deleteCommand(TimelineBucket* bucket, QList<int> indexes) override;
    virtual void moveCommand(int old_index, int new_index) override;
    virtual void moveCommand(TimelineBucket* bucket, int old_index, int new_index) override;
    virtual void moveCommand(TimelineBucket* old_bucket, TimelineBucket* new_bucket, int old_index, int new_index) override;
    virtual void modifyCommand(TimelineBucket* bucket, QString old_text, QString new_text) override;
    virtual void modifyCommand(TimelineBucket* bucket, TimelineTextLabel* label, QString old_text, QString new_text) override;

    virtual void undoCommand() override;
    virtual void redoCommand() override;

private:
    TimelineWidget* widget;
};

#endif // TIMELINEUNDOSTACK_H
