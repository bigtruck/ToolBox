#include "converttoarray.h"
#include "ui_converttoarray.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include "converttoarray_thread.h"


#define HEAD_TEXT "#ifndef __XXXX\r\n#define __XXXX\r\n\r\nconst unsigned char dat_array[]={\r\n"
#define END_TEXT "\r\n};\r\n#endif"

ConvertToArray::ConvertToArray(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConvertToArray)
{
    ui->setupUi(this);
    binFilePath.clear();
    ui->te_CFileHead->setText(HEAD_TEXT);
    ui->te_CFileEnd->setText(END_TEXT);
    ui->pb_Convert->setValue(ui->pb_Convert->minimum());
}

ConvertToArray::~ConvertToArray()
{
    delete ui;
}

void ConvertToArray::pbClick_OpenBin()
{
    binFilePath.clear();
    binFilePath = QFileDialog::getOpenFileName(this,tr("打开bin文件"),QCoreApplication::applicationDirPath(),tr("bin文件(*.bin);;全部文件(*.*)"));
    if(!binFilePath.isEmpty())
    {
        ui->tl_FilePath->setText(binFilePath);
    }
}

void ConvertToArray::pbClick_CreatCFile()
{
    if(binFilePath.isEmpty())
    {
        QMessageBox::warning(this,tr("错误"),tr("未选择 bin 文件"));
        return;
    }
    QString savePath = QFileDialog::getSaveFileName(this,tr("保存文件"),QCoreApplication::applicationDirPath(),tr("h文件(*.h);;(*.*)"));
    if(savePath.isEmpty())
    {
        QMessageBox::warning(this,tr("错误"),tr("保存位置错误"));
        return ;
    }
    ui->pb_Convert->setValue(0);
    ConvertToArray_Thread *thread = new ConvertToArray_Thread;
    thread = new ConvertToArray_Thread();
    thread->binPath = binFilePath;
    thread->savePath = savePath;
    thread->headText = ui->te_CFileHead->toPlainText();
    thread->endText = ui->te_CFileEnd->toPlainText();
    connect(thread, SIGNAL(Progress(int)), this, SLOT(convertProgress(int)));
    connect(thread, SIGNAL(ThreadExit()), this, SLOT(convertDone()));
    thread->start(QThread::HighPriority);

    ui->pb_OpenBin->setEnabled(false);
    ui->pb_CreateCFile->setEnabled(false);
    ui->te_CFileEnd->setEnabled(false);
    ui->te_CFileHead->setEnabled(false);
}

void ConvertToArray::convertProgress(int progress)
{
    ui->pb_Convert->setValue(progress);
}

void ConvertToArray::convertDone()
{
    qDebug() << "signel thread Exit";
    ui->pb_Convert->setValue(ui->pb_Convert->maximum());
    QMessageBox::information(this,tr("完成"),tr("完成"));
    ui->pb_OpenBin->setEnabled(true);
    ui->pb_CreateCFile->setEnabled(true);
    ui->te_CFileEnd->setEnabled(true);
    ui->te_CFileHead->setEnabled(true);

}
