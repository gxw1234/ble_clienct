#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H
#include <QThread>
#include <linux/input.h>
class Input_event : public QThread
{

    Q_OBJECT
protected:
    void run() override;

private:
    char *filename;


signals:

    void my_start_Signal2();
public:
    Input_event(const QString& str , QObject* parent = nullptr);
    QString scan_devices(QString);
    bool read_stop = false;
    QString m_enev_name;
    QString key_value;
    QString map_key_name;

signals:

};

#endif // INPUT_EVENT_H
