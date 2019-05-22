#ifndef BINTOARRAYTHREAD_H
#define BINTOARRAYTHREAD_H

#include <QThread>
#include <QtDebug>

class ConvertToArray_Thread : public QThread
{
    Q_OBJECT
public:
    ConvertToArray_Thread();
    ~ConvertToArray_Thread();
    void run();
    QString binPath;
    QString savePath;
    QString headText;
    QString endText;

signals:
    void Progress(int);
    void ThreadExit();
};

#endif // BINTOARRAYTHREAD_H
