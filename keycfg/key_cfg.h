// ControlConfig.h
#ifndef CONTROLCONFIG_H
#define CONTROLCONFIG_H



class Configurator {
public:
    QVector<InputDialog::ControlData> getControls(const QString& config) {
        static std::map<QString, QVector<InputDialog::ControlData>> configMap = {
            {"ssss", {
                {"次数", InputDialog::LineEdit},
                {"延时时间", InputDialog::SpinBox},
                {"同步接口", InputDialog::CheckBox},
                {"参数", InputDialog::LineEdit}
            }},
            {"aaaa", {
                {"项1", InputDialog::LineEdit},
                {"项2", InputDialog::CheckBox},
                {"项3", InputDialog::SpinBox}
            }},
            // 添加更多配置...
        };

        auto it = configMap.find(config);
        if (it != configMap.end()) {
            return it->second;
        } else {
            // 处理未知配置的情况
            return {};
        }
    }
};
#endif // CONTROLCONFIG_H
