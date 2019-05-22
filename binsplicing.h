#ifndef BINSPLICING_H
#define BINSPLICING_H

#include <QWidget>

namespace Ui {
class BinSplicing;
}

class BinSplicing : public QWidget
{
    Q_OBJECT

public:
    explicit BinSplicing(QWidget *parent = nullptr);
    ~BinSplicing();

private:
    Ui::BinSplicing *ui;
};

#endif // BINSPLICING_H
