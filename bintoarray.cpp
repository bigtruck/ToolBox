#include "bintoarray.h"
#include "ui_bintoarray.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include "bintoarraythread.h"

BinToArray::BinToArray(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BinToArray)
{
    ui->setupUi(this);
    binFilePath.clear();
}

BinToArray::~BinToArray()
{
    delete ui;
}

void BinToArray::pbClick_OpenBin()
{
    binFilePath.clear();
    binFilePath = QFileDialog::getOpenFileName(this,tr("打开bin文件"),QCoreApplication::applicationDirPath(),tr("bin文件(*.bin);;全部文件(*.*)"));
    if(!binFilePath.isEmpty())
    {
        ui->tl_FilePath->setText(binFilePath);
    }
}

void BinToArray::pbClick_CreatCFile()
{
    if(binFilePath.isEmpty())
    {
        QMessageBox::warning(this,tr("错误"),tr("未选择 bin 文件"));
        return;
    }
    QString savePath = QFileDialog::getSaveFileName(this,tr("保存文件"),QCoreApplication::applicationDirPath(),tr("h文件(*.h);;(*.*)"));
    if(savePath.isEmpty())
    {
        //QMessageBox::information(this,tr("tt"),savePath);
        return ;
    }
//    BinToArrayThread *thread = new BinToArrayThread;
    thread = new BinToArrayThread();
    thread->binPath = binFilePath;
    thread->savePath = savePath;
    connect(thread, SIGNAL(ThreadExit), this, SLOT(threadExit11));
    thread->start(QThread::HighPriority);
}

void BinToArray::threadExit11()
{
    qDebug() << "signel thread Exit";
    QMessageBox::information(this,tr("完成"),tr("完成"));
}
