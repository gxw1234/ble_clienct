#include "cmdanalyze.h"

Cmdanalyze::Cmdanalyze(QObject *parent) : QObject(parent)
{

}

QString Cmdanalyze::setvoltage(int number)
{
    QString FTAG = "58 46";
    QString TYPE = "F0";
    QString REG = "00";
    QString CMD = "04 00";
    QString DATA = bytests(number) + " ";
    QString DCHK = rcc(TYPE + " " + REG + " " + CMD + " " + DATA);
    QString FUID = "00";
    QString FLEN = "0D 00";
    QString LCHK = rcc(FTAG + " " + FLEN + " " + FUID) + " ";
    return FTAG + " " + FLEN + " " + FUID + " " + LCHK +  TYPE + " " + REG + " " + CMD + " " + DATA + DCHK;

}

QString Cmdanalyze::setled(int number)
{
    QString FTAG = "58 46";
    QString TYPE = "F0";
    QString REG = "00";
    QString CMD = "06 01 00";
    QString DATA = bytests(number) + " ";
    QString DCHK = rcc(TYPE + " " + REG + " " + CMD + " " + DATA);
    QString FUID = "00";
    QString FLEN = "0E 00";
    QString LCHK = rcc(FTAG + " " + FLEN + " " + FUID) + " ";
    return FTAG + " " + FLEN + " " + FUID + " " + LCHK +  TYPE + " " + REG + " " + CMD + " " + DATA + DCHK;

}

QString Cmdanalyze::Read_power(int number)
{
    QString FTAG = "58 46";
    QString TYPE = "F0";
    QString REG = "00";
    QString CMD = "08 00 01";
    QString DATA = bytests(number) + " ";
    QString DCHK = rcc(TYPE + " " + REG + " " + CMD + " " + DATA);
    QString FUID = "00";
    QString FLEN = "0E 00";
    QString LCHK = rcc(FTAG + " " + FLEN + " " + FUID) + " ";
    return FTAG + " " + FLEN + " " + FUID + " " + LCHK +  TYPE + " " + REG + " " + CMD + " " + DATA + DCHK;

}




QString Cmdanalyze::key_down(int number)
{
    QString FTAG = "58 46";
    QString TYPE = "F0";
    QString REG = "00";
    QString CMD = "03 00 01 01";
    QString DATA =   QString("%1").arg(number, 2, 16, QChar('0')).toUpper()  + " ";
    QString DCHK = rcc(TYPE + " " + REG + " " + CMD + " " + DATA);
    QString FUID = "00";
    QString FLEN = "0E 00";
    QString LCHK = rcc(FTAG + " " + FLEN + " " + FUID) + " ";
    return FTAG + " " + FLEN + " " + FUID + " " + LCHK +  TYPE + " " + REG + " " + CMD + " " + DATA + DCHK;

}

QString Cmdanalyze::key_upward(int number)
{
    QString FTAG = "58 46";
    QString TYPE = "F0";
    QString REG = "00";
    QString CMD = "03 00 00 01";
    QString DATA =   QString("%1").arg(number, 2, 16, QChar('0')).toUpper()  + " ";
    QString DCHK = rcc(TYPE + " " + REG + " " + CMD + " " + DATA);
    QString FUID = "00";
    QString FLEN = "0E 00";
    QString LCHK = rcc(FTAG + " " + FLEN + " " + FUID) + " ";
    return FTAG + " " + FLEN + " " + FUID + " " + LCHK +  TYPE + " " + REG + " " + CMD + " " + DATA + DCHK;

}

QString Cmdanalyze::rcc(const QString &data)
{
    bool ok;
    int uchar_checksum = 0;
    QStringList list_data = data.trimmed().split(" ");
    foreach (const QString &i, list_data) {
        uchar_checksum += i.toInt(&ok, 16);
        if (!ok) {
            return QString();
        }
    }
    QString rcc = QString("%1").arg((1 << 28) - uchar_checksum, 0, 16).right(2).toUpper();
    return rcc;

}

QString Cmdanalyze::bytests(int number)
{
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << static_cast<quint16>(number);
    QStringList hexList;
    for (char byte : bytes) {
        hexList << QString::number(byte & 0xFF, 16).rightJustified(2, '0').toUpper();
    }

    return hexList.join(" ");

}



