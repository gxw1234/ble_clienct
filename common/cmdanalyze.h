#ifndef CMDANALYZE_H
#define CMDANALYZE_H
#include <QApplication>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
class Cmdanalyze: public QObject
{
    Q_OBJECT
public:

    explicit Cmdanalyze(QObject *parent = nullptr);
    QString setvoltage(int number);
    QString Read_power(int number);
    QString setled(int number);
    QString key_down(int number);
    QString key_upward(int number);
private:
    QString rcc(const QString &data) ;
    QString bytests(int number);

};

#endif // CMDANALYZE_H
