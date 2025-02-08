#include "input_event.h"
#include <QDebug>
#include <dirent.h>
#include <QFile>
#define DEV_INPUT_EVENT "/dev/input"
#define EVENT_DEV_NAME "event"
#include <fcntl.h>
#include <unistd.h>
#include "map_file.h"

int is_event_device(const struct dirent *dir) {

    return strncmp(EVENT_DEV_NAME, dir->d_name, 5) == 0;
}




void Input_event::run()
{

    int fd;
    QString filePath = scan_devices(m_enev_name);
    if (!filePath.isEmpty()) {
        qDebug()<<"filePath"<<filePath;
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);
        fd = file.handle();
        ioctl(fd, EVIOCGRAB, 1);
        struct input_event ev[64];
        int  rd ,i;
        fd_set rdfs;

        FD_ZERO(&rdfs);
        FD_SET(fd, &rdfs);
        while (!read_stop) {

            select(fd + 1, &rdfs, NULL, NULL, NULL);
            rd = read(fd, ev, sizeof(ev));
            for (i = 0; i < rd / sizeof(struct input_event); i++) {
                unsigned int type, code;
                type = ev[i].type;
                code = ev[i].code;
                if (type == EV_SYN) {
                    if (code == SYN_MT_REPORT)
                        qDebug() << "type1"<<type<<"code" <<code;
                    else if (code == SYN_DROPPED)
                        qDebug() << "type2"<<type<<"code" <<code;
                    else
                        qDebug() << "type3"<<type<<"code" <<code;

                } else {

                    if (type == EV_MSC && (code == MSC_RAW || code == MSC_SCAN))
                    {

                        key_value = QString::number(ev[i].value, 16);
                        qDebug() << "key_value" <<key_value;
                    }
                    else {
                        if (ev[i].value ==0)
                        {
                            if (mapping_kye.contains(key_value)) {
                                map_key_name =mapping_kye[key_value];
//                                emit onKeyresultenev(map_key_name);
                            }
                        }
                        else if ( ev[i].value ==1) {

                            emit my_start_Signal2();


                        }
                    }
            }
            }
            QThread::msleep(100);
        }
        file.close();
    }

    else {

        qDebug () << "设备未找到";
    }

}



QString Input_event::scan_devices(QString Broadcast_Name)
{
    struct dirent **namelist;
    int ndev;


    QString filePath;

    ndev = scandir(DEV_INPUT_EVENT, &namelist, is_event_device, versionsort);
    qDebug()<< "ndev " <<ndev;

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
          if (QString(name).contains(Broadcast_Name)) {
                  qDebug() << "Broadcast_Name is in name";
                  break;
             }
          qDebug() <<"name"<<name;
          file.close();
          free(namelist[i]);
      }
      free(namelist);
    return filePath;
}




//Input_event::Input_event(QString enev_name,QObject *parent)
//{

//    m_enev_name =enev_name;

//}
