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
    char *inBuffer = (char *)malloc(1024*1024);
    char *outBuffer = (char *)malloc(1024*1024*6);
    char *startAddr = outBuffer;
    if (inBuffer == nullptr || outBuffer == nullptr)
	{
		return;
	}
    qint64 inSize = inFile.size();
    qint64 readSize;
    QString inStr;
    qint64 outIndex;
    while( inSize)
    {
        readSize = inFile.read(inBuffer,1024*1024);
        if(inSize >= readSize) inSize -= readSize;
        else inSize = 0 ;
        outIndex = 0 ;
        for (qint64 i=0; i<readSize; i++)
        {
            if(0 == (i % 16))
            {
#ifdef Q_OS_WIN
                *outBuffer++ = '\r';
#endif
                *outBuffer++ = '\n';
            }
            outIndex = sprintf(outBuffer,"0x%02X,",(unsigned char)inBuffer[i]);
            outBuffer += outIndex;
        }
    }
    free(inBuffer);
    free(outBuffer);
    inFile.close();
    outFile.write(startAddr,outBuffer - startAddr);
    outFile.close();
    //qDebug("exit");
    qDebug() << "thread exit";
    emit ThreadExit();
}



