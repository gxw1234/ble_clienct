#ifndef ICON_CONFIG_H
#define ICON_CONFIG_H

#include <QString>
#include <QMap>
#include <QIcon>

#define ICON_PATH_PREFIX ":/images/images/"
#define ICON_PATH(iconName) ICON_PATH_PREFIX iconName

// 常用图标路径常量
#define ICON_KEY_UNDE ICON_PATH("key_unde.png")
#define ICON_KEY_UP ICON_PATH("key_up.png")
#define ICON_KEY_UP_UNDE ICON_PATH("key_up_unde.png")
#define ICON_KEY_M ICON_PATH("key_m.png")
#define ICON_READ ICON_PATH("read.png")
#define ICON_CONFIGURE ICON_PATH("configure_ui.png")
#define ICON_KEY ICON_PATH("key.png")
#define ICON_FEATURE ICON_PATH("Feature.png")
#define ICON_EDITION ICON_PATH("edition.png")

class IconConfig
{
public:
    static IconConfig& getInstance();
    QString getIconPath(const QString& functionName) const;
    QIcon getIcon(const QString& functionName) const;
    
    // 新增：根据文本内容统一处理图标分类逻辑
    QString getIconPathByText(const QString& text) const;
    QIcon getIconByText(const QString& text) const;
    
    // 新增：获取特定类型的图标
    QString getTabIconPath(const QString& tabType) const;
    QIcon getTabIcon(const QString& tabType) const;
    QString getComboBoxIconPath(const QString& itemType) const;
    QIcon getComboBoxIcon(const QString& itemType) const;
    
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
