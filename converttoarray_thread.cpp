#include "converttoarray_thread.h"
#include <QDebug>
#include <QFile>

#define READ_INFILE_BUFFER_SIZE     (1024*512)


ConvertToArray_Thread::ConvertToArray_Thread()
{
    binPath.clear();
    savePath.clear();
}

ConvertToArray_Thread::~ConvertToArray_Thread()
{

}

void ConvertToArray_Thread::run()
{
    qDebug() << this->binPath.toUtf8();
    qDebug() << this->savePath.toUtf8();

    if(this->binPath.isEmpty())
    {
        return ;
    }
    if(this->savePath.isEmpty())
    {
        return ;
    }

    QFile inFile(binPath);
    QFile outFile(savePath);

    if(!inFile.open(QIODevice::ReadOnly))
    {
        return ;
    }
    if(!outFile.open(QIODevice::WriteOnly))
    {
        return ;
    }

    QByteArray arrayReadBuff;

    QString outStr ;
    qint64 totalSize = inFile.size();
    qint64 readSize;
    QString inStr;
    qint64 outIndex;
    qint64 prog_total = totalSize;
    qint64 prog_deal = 0 ;

    outFile.write(headText.toUtf8(),headText.length());
    while( totalSize)
    {
        arrayReadBuff.clear();
        inStr.clear();
        arrayReadBuff = inFile.read(READ_INFILE_BUFFER_SIZE);
        readSize = arrayReadBuff.length();
        if(totalSize >= readSize) totalSize -= readSize;
        else totalSize = 0 ;
        outIndex = 0 ;
        for (quint32 i=0; i<readSize; i++)
        {
            if(0 == (i % 16))
            {
#ifdef Q_OS_WIN
                inStr.append("\r\n");
#else
                inStr.append("\n");
#endif
            }
            unsigned char ch = arrayReadBuff[i];
            inStr.append(QString("0x%1,").arg(ch,2,16,QLatin1Char('0')));
        }

        QByteArray arrayOut = inStr.toLatin1();
        outFile.write(arrayOut,arrayOut.length());
        prog_deal += readSize;
        emit Progress((int)((prog_deal * 100 / prog_total)));
    }
    outFile.write(endText.toUtf8(),endText.length());
    inFile.close();
    outFile.close();
    qDebug("exit");
    emit ThreadExit();
}



