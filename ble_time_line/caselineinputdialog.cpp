#include "caselineinputdialog.h"

#include <QDebug>

void InputDialog::setinput(const QVector<InputDialog::ControlData> &controls)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    for (const auto &control : controls) {
        QHBoxLayout *hLayout = new QHBoxLayout();

        QLabel *label = new QLabel(control.label, this);
        hLayout->addWidget(label);

        QWidget *inputWidget = nullptr;

        switch (control.type) {
            case LineEdit: {
                QLineEdit *lineEdit = new QLineEdit(this);
                lineEdit->setPlaceholderText(control.label);
                inputWidget = lineEdit;
                lineEdits.append(lineEdit);
                break;
            }
            case SpinBox: {
                QSpinBox *spinBox = new QSpinBox(this);
                inputWidget = spinBox;
                spinBoxes.append(spinBox);
                break;
            }
            case Button: {
                QPushButton *button = new QPushButton("Action", this);
                inputWidget = button;
                connect(button, &QPushButton::clicked, this, [&]() {
                    qDebug() << control.label << " button clicked!";
                });
                break;
            }
            case CheckBox: {
                QCheckBox *checkBox = new QCheckBox( this); // 使用标签作为文本
                inputWidget = checkBox;
                checkBoxes.append(checkBox); // 存储 QCheckBox 指针
                break;
            }
        }

        if (inputWidget) {
            hLayout->addWidget(inputWidget);
        }

        mainLayout->addLayout(hLayout);
    }

    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &InputDialog::onOkClicked);
    mainLayout->addWidget(okButton);

}

InputDialog::InputDialog(QString fun_title, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(fun_title);

}

QVector<InputDialog::ControlData> InputDialog::getControls(const QString &config)
{

    static std::map<QString, QVector<InputDialog::ControlData>> configMap = {
        {"tmep", {
             {"次数", InputDialog::LineEdit},
             {"延时时间", InputDialog::SpinBox},
             {"同步接口", InputDialog::CheckBox},
             {"参数", InputDialog::LineEdit}
         }},

        {"扫描", {
             {"扫描时间", InputDialog::CheckBox}
         }},
        {"延时", {
             {"延时时间", InputDialog::SpinBox}
         }},
        {"连接", {
             {"连接时间", InputDialog::SpinBox},
             {"同步接口", InputDialog::CheckBox}
         }}
    };
    auto it = configMap.find(config);
    if (it != configMap.end()) {
        return it->second;
    } else {
        return {};
    }

}

void InputDialog::onOkClicked() {
    QMap<QString, QVariant> result;

    // 获取 QLineEdit 的值，并存储在 result 中
    for (auto lineEdit : lineEdits) {
        QString key = lineEdit->placeholderText(); // 使用 placeholder 作为键
        if (!lineEdit->text().isEmpty()) { // 仅在有内容时添加
            result[key] = lineEdit->text();
            qDebug() << "QLineEdit:" << key << "=" << lineEdit->text(); // 调试输出
        }
    }

    // 获取 QSpinBox 的值，并存储在 result 中
    for (auto spinBox : spinBoxes) {
        // 使用对应的 QLabel 文本作为键
        QString key = QString("Input 2"); // 确保使用正确的标签
        result[key] = spinBox->value(); // 获取值
        qDebug() << "QSpinBox:" << key << "=" << spinBox->value(); // 调试输出
    }

    // 获取 QCheckBox 的状态，并存储在 result 中
    for (auto checkBox : checkBoxes) {
        QString key = checkBox->text(); // 使用标签作为键
        result[key] = checkBox->isChecked(); // 获取状态
        qDebug() << "QCheckBox:" << key << "=" << checkBox->isChecked(); // 调试输出
    }

    // 确保至少有一个有效的输入
    if (result.isEmpty()) {
        qDebug() << "No valid input provided.";
        return; // 如果没有有效的输入，则不发送信号
    }





    emit dataSubmitted(result); // 发出信号
    accept(); // 关闭对话框
}


