#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <Windows.h>
#include <QDebug>

class timestramp{
private:
    LARGE_INTEGER m_litmp;
    LONGLONG QPart2;
    LONGLONG QPart1;
    double dfMinus, dfFreq, dfTim;
public:
    timestramp(){
        //qDebug() << "constructor";
        QueryPerformanceFrequency(&m_litmp);
        dfFreq = (double)m_litmp.QuadPart;
        QueryPerformanceCounter(&m_litmp);
        //qDebug() << dfFreq;
        QPart1 = m_litmp.QuadPart;
        //qDebug() << QPart1;
    }

    ~timestramp(){
        //qDebug() << "Destructor";
        QueryPerformanceCounter(&m_litmp);
        QPart2 = m_litmp.QuadPart;
        dfMinus = (double)(QPart2 - QPart1);
        dfTim = dfMinus / dfFreq * 1000;

        //显示时间
        QString msg4 = "time:", msg3, msg5 = "ms";
        //msg3.asprintf("%10.9f", dfTim);
        QString st = msg4 + QString::number(dfTim) + msg5;

        qDebug() << st;

        //fprintf(g_fp, "%s\n", st);
    }
};


#endif // TIMESTAMP_H
