﻿#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QUndoCommand>
#include "caselinewidget.h"

class TimelineBucketAddCommand : public QUndoCommand
{
public:
    TimelineBucketAddCommand(TimelineWidget* widget, int index, QUndoCommand* parent = nullptr);
    TimelineBucketAddCommand(TimelineWidget* widget, int index, QString time, QUndoCommand* parent = nullptr);
    TimelineBucketAddCommand(TimelineWidget* widget, int index, QString time, QString text, QUndoCommand* parent = nullptr);
    TimelineBucketAddCommand(TimelineWidget* widget, int index, QString time, QStringList texts, QUndoCommand* parent = nullptr);
    TimelineBucketAddCommand(TimelineWidget* widget, QList<int> indexes, QUndoCommand* parent = nullptr);
    TimelineBucketAddCommand(TimelineWidget* widget, QList<int> indexes, QStringList times, QUndoCommand* parent = nullptr);
    TimelineBucketAddCommand(TimelineWidget* widget, QList<int> indexes, QStringList times, QList<QStringList> textss, QUndoCommand* parent = nullptr);
    TimelineBucketAddCommand(TimelineWidget* widget, QList<int> indexes, QList<QPair<QString, QStringList>> line_texts, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    static QStringList numStringList(int number);
    static QList<QPair<QString, QStringList>> string2lineTexts(QStringList list);
    static QList<QPair<QString, QStringList>> string2lineTexts(QStringList list, QList<QStringList> textss);

private:
    TimelineWidget* widget;
    QList<int> indexes; // 这是插入位置（改动之前的索引，上面的插入会引起下面索引的变动）。请确保先从小到大排好序
    QList<QPair<QString, QStringList>> line_texts;
};


class TimelineBucketTextAddCommand : public QUndoCommand
{
public:
    TimelineBucketTextAddCommand(TimelineWidget* widget, int bucket_index, int index, QUndoCommand *parent = nullptr);
    TimelineBucketTextAddCommand(TimelineWidget* widget, int bucket_index, QList<int> indexes, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    TimelineWidget* widget;
    int bucket_index;
    QList<int> indexes; // 请确保先从小到大排好序
};

class TimelineBucketTextsAddCommand : public QUndoCommand
{
public:
    TimelineBucketTextsAddCommand(TimelineWidget* widget, int bucket_index, int text_index, QUndoCommand *parent = nullptr);
    TimelineBucketTextsAddCommand(TimelineWidget* widget, QList<int> bucket_indexes, QList<int>text_indexes, QUndoCommand* parent = nullptr);
    TimelineBucketTextsAddCommand(TimelineWidget* widget, QList<int> bucket_indexes, QList<QList<int>>texts_indexes, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    static QList<QList<int>> intRow2Col(QList<int> row);

private:
    TimelineWidget* widget;
    QList<int> bucket_indexes; // 请确保从小到大排好序
    QList<QList<int>> texts_indexes; // 请确保从小到大排好序
};


class TimelineBucketDeleteCommand : public QUndoCommand
{
public:
    TimelineBucketDeleteCommand(TimelineWidget* widget, int index, QUndoCommand* parent = nullptr);
    TimelineBucketDeleteCommand(TimelineWidget* widget, QList<int> indexes, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    TimelineWidget* widget;
    QList<int> indexes; // 请确保先从小到大排好序
    QList<QPair<QString, QStringList>> line_texts;
};


class TimelineBucketTextDeleteCommand : public QUndoCommand
{
public:
    TimelineBucketTextDeleteCommand(TimelineWidget* widget, int bucket_index, int index, QUndoCommand* parent = nullptr);
    TimelineBucketTextDeleteCommand(TimelineWidget* widget, int bucket_index, QList<int> indexes, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    TimelineWidget* widget;
    int bucket_index;
    QList<int> indexes; // 请确保先从小到大排好序
    QStringList texts;
};


class TimelineBucketMoveCommand : public QUndoCommand
{
public:
    TimelineBucketMoveCommand(TimelineWidget* widget, int old_index, int new_index, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    TimelineWidget* widget;
    int old_index;
    int new_index;
};


class TimelineBucketTextMoveCommand : public QUndoCommand
{
public:
    TimelineBucketTextMoveCommand(TimelineWidget* widget, int bucket_index, int old_index, int new_index, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    TimelineWidget* widget;
    int bucket_index;
    int old_index;
    int new_index;
};


class TimelineBucketTextBucketMoveCommand : public QUndoCommand
{
public:
    TimelineBucketTextBucketMoveCommand(TimelineWidget* widget, int old_bucket_index, int new_bucket_index, int old_index, int new_index, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    TimelineWidget* widget;
    int old_bucket_index;
    int new_bucket_index;
    int old_index;
    int new_index;
};


class TimelineBucketTimeModifyCommand : public QUndoCommand
{
public:
    TimelineBucketTimeModifyCommand(TimelineWidget* widget, int bucket_index, QString old_text, QString new_text, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    TimelineWidget* widget;
    int bucket_index;
    QString old_text;
    QString new_text;
};


class TimelineBucketTextModifyCommand : public QUndoCommand
{
public:
    TimelineBucketTextModifyCommand(TimelineWidget* widget, int bucket_index, int label_index, QString old_text, QString new_text, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    TimelineWidget* widget;
    int bucket_index;
    int label_index;
    QString old_text;
    QString new_text;
};

#endif // UNDOCOMMANDS_H
