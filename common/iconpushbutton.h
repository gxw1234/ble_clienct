#ifndef ICONPUSHBUTTON_H
#define ICONPUSHBUTTON_H



#include <QPushButton>
#include <QIcon>
#include <QString>

class IconPushButton : public QPushButton {
    Q_OBJECT

public:
    explicit IconPushButton(const QString &iconPath, const QString &text, QWidget *parent = nullptr);

    void setIconPath(const QString &iconPath);
    void setTextLabel(const QString &text);
};

#endif // ICONPUSHBUTTON_H
