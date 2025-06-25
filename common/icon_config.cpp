#include "icon_config.h"
#include <QDebug>

IconConfig::IconConfig()
{
    m_defaultIconPath = ICON_PATH("add.png");
    initDefaultMappings();
}

IconConfig& IconConfig::getInstance()
{
    static IconConfig instance;
    return instance;
}

void IconConfig::initDefaultMappings()
{

    m_iconMappings["延时"] = ICON_PATH("Delay_ico.png");
    m_iconMappings["随机延时"] = ICON_PATH("Random_delay_ico.png");
    m_iconMappings["扫描"] = ICON_PATH("Bluetooth_disconnect.png");
    m_iconMappings["连接"] = ICON_PATH("Bluetooth_connect.png");
    m_iconMappings["断开"] = ICON_PATH("Bluetooth_scan.png");
    m_iconMappings["配对"] = ICON_PATH("Bluetooth_per.png");
    m_iconMappings["取消配对"] = ICON_PATH("Bluetooth_deper.png");
    m_iconMappings["上电"] = ICON_PATH("Power_on.png");
    m_iconMappings["断电"] = ICON_PATH("Power_off.png");
    m_iconMappings["读取LED"] = ICON_PATH("led_ico.png");
    m_iconMappings["设置电压"] = ICON_PATH("Setthe_voltage.png");
    m_iconMappings["开始循环"] = ICON_PATH("Start_the_cycle.png");
    m_iconMappings["停止循环"] = ICON_PATH("Stop_the_cycle.png");
    m_iconMappings["断言"] = ICON_PATH("Assertion_p.png");
    
}

QString IconConfig::getIconPath(const QString& functionName) const
{

    if (m_iconMappings.contains(functionName)) {
        return m_iconMappings[functionName];
    }
    for (auto it = m_iconMappings.begin(); it != m_iconMappings.end(); ++it) {
        if (functionName.contains(it.key(), Qt::CaseInsensitive)) {
            return it.value();
        }
    }
    return m_defaultIconPath;
}

QIcon IconConfig::getIcon(const QString& functionName) const
{
    QString iconPath = getIconPath(functionName);
    return QIcon(iconPath);
}

void IconConfig::addIconMapping(const QString& functionName, const QString& iconPath)
{
    m_iconMappings[functionName] = iconPath;
}

void IconConfig::removeIconMapping(const QString& functionName)
{
    m_iconMappings.remove(functionName);
}

void IconConfig::clearMappings()
{
    m_iconMappings.clear();
    initDefaultMappings(); 
}

QMap<QString, QString> IconConfig::getAllMappings() const
{
    return m_iconMappings;
} 
