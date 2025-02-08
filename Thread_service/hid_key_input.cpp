#include "hid_key_input.h"

#include "common/map_file.h"
int is_event_device(const struct dirent *dir) {

    return strncmp(EVENT_DEV_NAME, dir->d_name, 5) == 0;
}


hid_key_input::hid_key_input(QString parameter, QObject *parent)
    : QThread(parent), m_enev_name(parameter)
{


}

void hid_key_input::stop()
{

    read_stop =true;
}

QString hid_key_input::scan_devices(QString)
{
    struct dirent **namelist;
    int ndev;
    QString filePath;
    ndev = scandir(DEV_INPUT_EVENT, &namelist, is_event_device, versionsort);
    for (int i = 0; i < ndev; i++)
      {
          QString fileName = QString::fromStdString(namelist[i]->d_name);
//          QString filePath = DEV_INPUT_EVENT + "/" + fileName;
          filePath = QString("%1/%2").arg(DEV_INPUT_EVENT).arg(fileName);
//          filenames.append(filePath);
//          qDebug() <<"fileName"<<fileName;
          QFile file(filePath);
          if (!file.open(QIODevice::ReadOnly))
              continue;
          int fd = file.handle();
          char name[256] = "???";
          ioctl(fd, EVIOCGNAME(sizeof(name)), name);
//           qDebug() <<"name"<<name;
          if (QString(name).contains(m_enev_name)) {
//                  qDebug() << "Broadcast_Name is in name";
//                  break;
             }
          file.close();
          free(namelist[i]);
      }
      free(namelist);
    return filePath;
}

void hid_key_input::run()
{
    int fd;
    QString filePath = scan_devices(m_enev_name);
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);
        fd = file.handle();
        ioctl(fd, EVIOCGRAB, 1);
        struct input_event ev[64];
        int  rd ,i;
        fd_set rdfs;

        FD_ZERO(&rdfs);
        FD_SET(fd, &rdfs);
        struct timeval tv;
        int timeout_milliseconds = 100;
        tv.tv_sec = 2;
        tv.tv_usec =  (timeout_milliseconds % 1000) * 1000;

        while (!this->read_stop) {
            int retval = select(fd + 1, &rdfs, NULL, NULL,  &tv);
            if (retval)
            {
                rd = read(fd, ev, sizeof(ev));
                for (i = 0; i < rd / sizeof(struct input_event); i++) {
                    unsigned int type, code;
                    type = ev[i].type;
                    code = ev[i].code;
                    if (type != EV_SYN) {
                        if (type == EV_MSC && (code == MSC_RAW || code == MSC_SCAN))
                        {
                            key_value = QString::number(ev[i].value, 16);
                            qDebug() <<"key_value" <<key_value;
                        }
                        else {
                            int ev_value =  ev[i].value;
                            switch (ev_value) {
                                case 1:
                                    qDebug() << "==close==3";
                                    if (mapping_kye.contains(key_value)) {
                                        map_key_name =mapping_kye[key_value];
                                        emit my_key_Signal(map_key_name);
                                    }
                                    qDebug() << "==close==4";
                                    break;
                                case 2:
                                    break;
                                case 0:
                                    emit my_key_Signal("按键抬起");
                                    break;
                                default:
                                    break;
                                }
                        }
                    }
                }
            }
            else {
                QThread::msleep(100);
            }
        }
        qDebug() << "==close==1";
        ioctl(fd, EVIOCGRAB, 0);
        qDebug() << "==close==2";
        file.close();
        read_stop =false;
    }
    else {
        qDebug () << "设备未找到";
    }
}
