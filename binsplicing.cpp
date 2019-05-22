#include "binsplicing.h"
#include "ui_binsplicing.h"

BinSplicing::BinSplicing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BinSplicing)
{
    ui->setupUi(this);
}

BinSplicing::~BinSplicing()
{
    delete ui;
}
