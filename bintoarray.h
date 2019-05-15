#ifndef BINTOARRAY_H
#define BINTOARRAY_H

#include <QWidget>
#include <QThread>

#include "bintoarraythread.h"
namespace Ui {
class BinToArray;
}

class BinToArray : public QWidget
{
    Q_OBJECT

public:
    explicit BinToArray(QWidget *parent = nullptr);
    ~BinToArray();

private:
    Ui::BinToArray *ui;

public slots:
    void pbClick_OpenBin();
    void pbClick_CreatCFile();
private slots:
    void threadExit11();

public:
    QString binFilePath ;
    BinToArrayThread *thread ;
};

#endif // BINTOARRAY_H
