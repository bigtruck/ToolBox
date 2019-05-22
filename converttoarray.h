#ifndef BINTOARRAY_H
#define BINTOARRAY_H

#include <QWidget>
#include <QThread>

#include "converttoarray_thread.h"
namespace Ui {
class ConvertToArray;
}

class ConvertToArray : public QWidget
{
    Q_OBJECT

public:
    explicit ConvertToArray(QWidget *parent = nullptr);
    ~ConvertToArray();

private:
    Ui::ConvertToArray *ui;

public slots:
    void pbClick_OpenBin();
    void pbClick_CreatCFile();
    void convertDone();
    void convertProgress(int);

public:
    QString binFilePath ;
};

#endif // BINTOARRAY_H
