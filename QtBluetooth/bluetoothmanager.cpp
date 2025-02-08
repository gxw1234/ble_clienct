#include "bluetoothmanager.h"
#include <QtDBus>
bluetoothmanager::bluetoothmanager(QObject *parent) : QObject(parent)
{

}

void bluetoothmanager::remove_pari_name()
{
    QDBusInterface manager("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", QDBusConnection::systemBus());
    QDBusMessage call = manager.call("GetManagedObjects");
    if (call.arguments().isEmpty()) {
        qDebug() << "Failed to get managed objects.";
        return;
    }

    qDebug() <<"++++++++";
    const QDBusArgument &arg = call.arguments().at(0).value<QDBusArgument>();
    QMap<QDBusObjectPath, QMap<QString, QVariantMap>> objects;
    arg >> objects;
    QString deviceInterface = "org.bluez.Device1";
    QString adapterPath = "/org/bluez/hci0"; // Use the proper adapter path here.

    // Iterate through all objects to find paired devices
    for (auto it = objects.constBegin(); it != objects.constEnd(); ++it) {
        auto deviceProperties = it.value().value(deviceInterface);
        if (!deviceProperties.isEmpty() && deviceProperties.contains("Paired") && deviceProperties.value("Paired").toBool()) {
            QString name = deviceProperties.value("Name", "unknown").toString();
            QString address = deviceProperties.value("Address", "unknown").toString();
            qDebug() << "Removing paired device:" << name << "[" << address << "]";

            // Creating the interface for the adapter to remove the device
            QDBusObjectPath devicePath(it.key());
            QDBusInterface adapter("org.bluez", adapterPath, "org.bluez.Adapter1", QDBusConnection::systemBus());
            // Call the "RemoveDevice" method on the adapter interface
            QDBusMessage response = adapter.call("RemoveDevice", QVariant::fromValue(devicePath));
            if (response.type() == QDBusMessage::ErrorMessage) {

                qDebug() << "Failed to remove device:" << name << "[" << address << "] Error:" << response.errorMessage();
                SendMessage("Failed to remove device:" + name + "[" + address + "] Error:" + response.errorMessage());

            } else {
                qDebug() << "Device removed successfully:" << name << "[" << address << "]";
                SendMessage("Device removed successfully:" + name + "[" + address + "]");
            }
        }
    }


}
void bluetoothmanager::SendMessage(QString msg)
{

    qDebug() << "==================++" <<msg;
    emit message(msg);
}
void bluetoothmanager::remove_pari_name_one()
{
    // 启动 bluetoothctl
        QProcess bluetoothctl;
        bluetoothctl.start("bluetoothctl");
        bluetoothctl.waitForStarted();

        // 发送 'paired-devices' 命令以获取所有已配对设备的列表
        bluetoothctl.write("devices\n");
        bluetoothctl.waitForBytesWritten();
        bluetoothctl.waitForReadyRead();

        // 读取 'paired-devices' 命令的输出
        QByteArray output = bluetoothctl.readAll();
        QString outputStr(output);
        bluetoothctl.write("quit\n"); // 退出 bluetoothctl
        bluetoothctl.waitForFinished();

        // 使用正则表达式提取设备地址
        QRegExp regex("Device (\\S+)");
        int pos = 0;
        QStringList deviceAddresses;
        while ((pos = regex.indexIn(outputStr, pos)) != -1) {
            deviceAddresses << regex.cap(1);
            pos += regex.matchedLength();
        }

        // 对于每个设备地址，使用 bluetoothctl 的 'remove' 命令移除设备
        foreach (const QString &address, deviceAddresses) {
            qDebug() << "Removing device:" << address;
            QProcess::execute("bluetoothctl", QStringList() << "remove" << address);
        }

        if (deviceAddresses.isEmpty()) {
            qDebug() << "No paired devices found to remove.";
        }


}
