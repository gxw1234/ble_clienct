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

// 新增：根据文本内容统一处理图标分类逻辑
QString IconConfig::getIconPathByText(const QString& text) const
{
    // 功能模块的关键字列表 - 支持带参数的功能模块
    QStringList functionKeywords = {"延时", "随机延时", "扫描", "连接", "断开", "配对", 
                                   "取消配对", "上电", "断电", "读取LED", "设置电压", 
                                   "开始循环", "停止循环", "断言"};
    
    // 检查是否为功能模块 - 模糊匹配，支持带参数
    for (const QString& keyword : functionKeywords) {
        if (text.contains(keyword)) {  // 改回模糊匹配，支持带参数的功能模块
            return getIconPath(text);
        }
    }
    
    // 非功能模块根据具体内容设置不同的统一图标
    if (text.contains("按下")) {
        // 单键按下模块
        return ICON_KEY_UNDE;
    } else if (text.contains("抬起")) {
        // 按键释放模块
        return ICON_KEY_UP;
    } else if (text.contains("触发")) {
        // 触发模块
        return ICON_KEY_UP_UNDE;
    } else if (text.contains("组合")) {
        // 组合按键模块
        return ICON_KEY_M;
    } else if (text.contains("读取")) {
        // 读取模块
        return ICON_READ;
    } else if (text.contains("设置") || text.contains("配置")) {
        // 设置/配置模块
        return ICON_CONFIGURE;
    } else {
        // 默认统一图标
        return ICON_KEY;
    }
}

QIcon IconConfig::getIconByText(const QString& text) const
{
    QString iconPath = getIconPathByText(text);
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

// 新增：获取特定类型的图标
QString IconConfig::getTabIconPath(const QString& tabType) const
{
    if (tabType == "feature") {
        return ICON_FEATURE;
    } else if (tabType == "key_press") {
        return ICON_KEY_UNDE;
    } else if (tabType == "key") {
        return ICON_KEY_UP;
    } else if (tabType == "trigger") {
        return ICON_KEY_UP_UNDE;
    } else if (tabType == "combination") {
        return ICON_KEY;
    } else if (tabType == "read") {
        return ICON_READ;
    } else if (tabType == "set_parameters") {
        return ICON_KEY_M;
    }
    return ICON_KEY; // 默认图标
}

QIcon IconConfig::getTabIcon(const QString& tabType) const
{
    QString iconPath = getTabIconPath(tabType);
    return QIcon(iconPath);
}

QString IconConfig::getComboBoxIconPath(const QString& itemType) const
{
    if (itemType == "Feature") {
        return ICON_FEATURE;
    } else if (itemType == "edition") {
        return ICON_EDITION;
    } else if (itemType == "key_unde") {
        return ICON_KEY_UNDE;
    } else if (itemType == "key_up") {
        return ICON_KEY_UP;
    } else if (itemType == "key_up_unde") {
        return ICON_KEY_UP_UNDE;
    } else if (itemType == "key_m") {
        return ICON_KEY_M;
    }
    return ICON_KEY; // 默认图标
}

QIcon IconConfig::getComboBoxIcon(const QString& itemType) const
{
    QString iconPath = getComboBoxIconPath(itemType);
    return QIcon(iconPath);
} 
