#ifndef CASELINEINPUTDIALOG_H
#define CASELINEINPUTDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMap>
#include <QVariant>
#include <QDebug>


class InputDialog : public QDialog {
    Q_OBJECT

public:
    enum ControlType {
        LineEdit,
        SpinBox,
        Button,
        CheckBox
    };

    struct ControlData {
        QString label;
        ControlType type;
    };

    void setinput(const QVector<ControlData> &controls);

    explicit InputDialog(QString fun_title, QWidget *parent = nullptr);
    QVector<InputDialog::ControlData> getControls(const QString& config);
signals:
    void dataSubmitted(const QMap<QString, QVariant> &data);

private slots:
    void onOkClicked();
private:
    QVector<QLineEdit*> lineEdits; // 存储 QLineEdit 的指针
    QVector<QSpinBox*> spinBoxes;   // 存储 QSpinBox 的指针
    QVector<QCheckBox*> checkBoxes; // 存储 QCheckBox 的指针
};
#endif // CASELINEINPUTDIALOG_H
