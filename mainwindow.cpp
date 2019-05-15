#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bintoarray.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pbClick_BinToArray()
{
    BinToArray *binToArray = new BinToArray();
    binToArray->setAttribute(Qt::WA_QuitOnClose,false);
    binToArray->setAttribute(Qt::WA_DeleteOnClose,true);
    binToArray->setWindowTitle(tr("Bin To Array"));
    binToArray->show();
}

void MainWindow::pbClick_MidiToArray()
{

}
