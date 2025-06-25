#ifndef ICON_CONFIG_H
#define ICON_CONFIG_H

#include <QString>
#include <QMap>
#include <QIcon>

#define ICON_PATH_PREFIX ":/images/images/"
#define ICON_PATH(iconName) ICON_PATH_PREFIX iconName

class IconConfig
{
public:
    static IconConfig& getInstance();
    QString getIconPath(const QString& functionName) const;
    QIcon getIcon(const QString& functionName) const;
    void addIconMapping(const QString& functionName, const QString& iconPath);
    void removeIconMapping(const QString& functionName);
    void clearMappings();
    QMap<QString, QString> getAllMappings() const;

private:
    IconConfig();
    ~IconConfig() = default;
    IconConfig(const IconConfig&) = delete;
    IconConfig& operator=(const IconConfig&) = delete;
    void initDefaultMappings();
    QMap<QString, QString> m_iconMappings;
    QString m_defaultIconPath;
};

#endif // ICON_CONFIG_H 
