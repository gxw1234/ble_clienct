#include "IconPushButton.h"

IconPushButton::IconPushButton(const QString &iconPath, const QString &text, QWidget *parent)
    : QPushButton(parent)
{
    setIconPath(iconPath);
    setTextLabel(text);
}

void IconPushButton::setIconPath(const QString &iconPath) {
    QIcon buttonIcon(iconPath);
    setIcon(buttonIcon);
}

void IconPushButton::setTextLabel(const QString &text) {
    setText(text);
}
