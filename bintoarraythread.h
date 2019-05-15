#ifndef BINTOARRAYTHREAD_H
#define BINTOARRAYTHREAD_H

#include <QThread>
#include <QtDebug>

class BinToArrayThread : public QThread
{
    Q_OBJECT
public:
    BinToArrayThread();
    ~BinToArrayThread();
    void run();
    QString binPath;
    QString savePath;

signals:
    void Progress(int);
    void ThreadExit();
};

#endif // BINTOARRAYTHREAD_H
