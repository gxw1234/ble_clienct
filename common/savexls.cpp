#include "savexls.h"

savexls::savexls(QObject *parent):QObject(parent)
{

}

void savexls::save_xls(QString path , bool result,  QList<ReportInfo>  m_reportInfolist )
{

    QXlsx::Document xlsx;
    QXlsx::Format format;
    format.setFontSize(10);

    xlsx.write("A1", "标题", format);
    xlsx.write("B1", "测试结果", format);
    xlsx.write("C1", "测试次数", format);
    xlsx.write("D1", "正常次数", format);
    xlsx.write("E1", "合格率", format);
    xlsx.write("F1", "测试内容", format);
    xlsx.write("G1", "log", format);



    int row = 2;
    for (const auto& reportInfo : m_reportInfolist)
    {
        xlsx.write(row, 1, reportInfo.title, format);

        if (reportInfo.passfrequency ==reportInfo.Totalfrequency ){
            xlsx.write(row, 2, "pass", format);

        }
        else {
             xlsx.write(row, 2, "fail", format);
        }
        xlsx.write(row, 3, reportInfo.Totalfrequency, format);

        xlsx.write(row, 4, reportInfo.passfrequency, format);

        xlsx.write(row, 5, reportInfo.Passrate, format);

        xlsx.write(row, 6, reportInfo.caselist, format);

        xlsx.write(row,7, reportInfo.textlog, format);

        row++; // 移动到下一行
    }




    xlsx.saveAs(path);

}

void savexls::save_row_xls(QString path,QString pathtxt ,ReportInfo reportInfo)
{

    QXlsx::Document xlsx;
    QXlsx::Format format;
    format.setFontSize(10);

    xlsx.write("A1", "标题", format);
    xlsx.write("B1", "测试结果", format);
    xlsx.write("C1", "测试次数", format);
    xlsx.write("D1", "正常次数", format);
    xlsx.write("E1", "合格率", format);
    xlsx.write("F1", "测试内容", format);
    xlsx.write("G1", "log", format);



    int row = 2; // 从第二行开始写入数据

    xlsx.write(row, 1, reportInfo.title, format);

    if (reportInfo.passfrequency ==reportInfo.Totalfrequency ){
        xlsx.write(row, 2, "pass", format);

    }
    else {
         xlsx.write(row, 2, "fail", format);
    }
    xlsx.write(row, 3, reportInfo.Totalfrequency, format);

    xlsx.write(row, 4, reportInfo.passfrequency, format);

    xlsx.write(row, 5, reportInfo.Passrate, format);

    xlsx.write(row, 6, reportInfo.caselist, format);

//    xlsx.write(row,7, reportInfo.textlog, format);
    xlsx.saveAs(path);


    QFile file(pathtxt);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << reportInfo.textlog << endl;
        file.close();
    }


}


