#include "bintoarraythread.h"
#include <QDebug>
#include <QFile>
//#include <cstdlib>
#include <cstdio>

//#define READ_INFILE_BUFFER_SIZE     (1024*1024)


BinToArrayThread::BinToArrayThread()
{
    binPath.clear();
    savePath.clear();
}

BinToArrayThread::~BinToArrayThread()
{

}

void BinToArrayThread::run()
{
//    qDebug(this->binPath.toUtf8());
//    qDebug(this->savePath.toUtf8());
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
    qint64 inSize = inFile.size();
    qint64 readSize;
    QString inStr;
    qint64 outIndex;
    while( inSize)
    {
        arrayReadBuff.clear();
        inStr.clear();
        arrayReadBuff = inFile.read(1024 * 1024);
        readSize = arrayReadBuff.length();
        if(inSize >= readSize) inSize -= readSize;
        else inSize = 0 ;
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
            inStr.append(QString("%1%2,").arg("0x").arg(ch,2,16,QLatin1Char('0')));
        }
        QByteArray arrayOut = inStr.toLatin1();
        outFile.write(arrayOut,arrayOut.length());
    }
    inFile.close();
    outFile.close();
    qDebug("exit");
    emit ThreadExit();
}



