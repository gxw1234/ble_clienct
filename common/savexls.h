#ifndef SAVEXLS_H
#define SAVEXLS_H

#include <iostream>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QVariant>
#include <QtCore>
#include <QtGlobal>
using namespace std;

// [0] include QXlsx headers
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxchartsheet.h"
#include "xlsxdocument.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


struct ReportInfo {
    QString Totalfrequency;
    QString passfrequency;
    QString Passrate;
    QString title;
    QString caselist;
    QString textlog;
    ReportInfo(QString Totalfrequency, QString passfrequency,QString Passrate,QString title,QString caselist,QString textlog)
        : Totalfrequency(Totalfrequency), passfrequency(passfrequency),Passrate(Passrate),title(title),caselist(caselist),textlog(textlog) {}
};






class savexls: public QObject
{
    Q_OBJECT


private:
     QList<ReportInfo> ReportInfolist;
public:
     explicit savexls(QObject *parent = nullptr);
     void save_xls(QString path, bool result, QList<ReportInfo>  m_reportInfolist);
     void save_row_xls(QString path,QString pathtxt,ReportInfo reportInfo);
    QXlsx::Document xlsxW;


};

#endif // SAVEXLS_H
