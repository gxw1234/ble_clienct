#ifndef LABELEDITOR_H
#define LABELEDITOR_H

#include <QObject>
#include <QPlainTextEdit>
#include <QLabel>

class LabelEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    LabelEditor(QWidget* parent = nullptr);

    void setOriginText(QString text);//设置文本
    QString getOriginText();//获取文本
    void finishIfEditing();

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void signalEditCanceled(QString origin);
    void signalEditFinished(QString text);

private:
    QString origin_text;
};

#endif // LABELEDITOR_H
