#include "datetimeutil.h"



QString DateTimeUtil::getCurrentFormattedTime() {
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("yyyy-MM-dd HH:mm:ss:zzz");
    formattedTime += ":    ";
    return formattedTime;
}
