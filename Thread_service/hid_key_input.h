#ifndef HID_KEY_INPUT_H
#define HID_KEY_INPUT_H

#include <QThread>
#include <linux/input.h>
#include <QDebug>
#include <dirent.h>
#include <QFile>
#define DEV_INPUT_EVENT "/dev/input"
#define EVENT_DEV_NAME "event"
#include <fcntl.h>
#include <unistd.h>


class hid_key_input : public QThread
{
    Q_OBJECT

signals:
    void my_key_Signal(QString);

public:
    hid_key_input(QString parameter, QObject *parent = nullptr); // 带参数的构造函数
    bool read_stop = false;
    void stop();
private:
    QString scan_devices(QString);
    QString m_enev_name;
    QString key_value;
    QString map_key_name;

protected:
    void run() override;
};

#endif // HID_KEY_INPUT_H
