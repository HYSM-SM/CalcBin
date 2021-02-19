#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memory.h"
#include "algorithm.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("bin.ico"));

    printBinDisplayMemory();
    printBinDisplay();
    pressDot = false;

    CopyMemory = new QShortcut(this);
    CopyMemory->setKey(Qt::CTRL + Qt::Key_M);
    connect(CopyMemory,SIGNAL(activated()),this, SLOT(pasteInBufferMemory()));

    CopyAlgorithm = new QShortcut(this);
    CopyAlgorithm->setKey(Qt::CTRL + Qt::Key_A);
    connect(CopyAlgorithm,SIGNAL(activated()),this, SLOT(pasteInBufferAlgorithm()));
}

void MainWindow::pasteInBufferMemory()
{
    QString buffer = ui->BinDisplayMemory->text();
    buffer.remove(0,Memory.size());
    buffer.remove(35,buffer.size());
    QApplication::clipboard()->setText(buffer);
}

void MainWindow::pasteInBufferAlgorithm()
{
    QString buffer = ui->BinDisplay->text();
    buffer.remove(0,Algorithm.size());
    buffer.remove(35,buffer.size());
    QApplication::clipboard()->setText(buffer);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    pressDot = (ui->Display->text().contains('.')) ? true : false ;
    if(ui->Display->text().size() == 1 && ui->Display->text().at(0) == '-' && (key == DOT || key == COMMA))
        return;

    if(key >= '0' && key <= '9')
        ui->Display->setText(ui->Display->text() + QString::number(key - 48));

    else if((key == COMMA || key == DOT) && !pressDot && ui->Display->text().size() > 0)
        ui->Display->setText(ui->Display->text() + '.');

    else if(key == DELETE)
        ui->Display->setText(ui->Display->text().left(ui->Display->text().size()- 1));

    else if(key == MINUS && ui->Display->text().size() == 0)
        ui->Display->setText(ui->Display->text() + '-');

    else if(key == ENTER || key == RETURN)
    {
        if(ui->Display->text().size() > 0 && ui->Display->text().at(ui->Display->text().size() - 1) == '.') // example 12. or 0.
            return;
        numberToBin();
    }
}

void MainWindow::numberToBin()
{
    if(pressDot)
    {
        float num = ui->Display->text().toFloat();
        if(ui->Display->text().size() > 0 && num == 0) // example 0.000000000
            return;
        if(num < MAX_FLOAT_NUM && num > MIN_FLOAT_NUM)
        {
        floatToBinMemory();
        floatToBin();
        }
        else
            errorFloat(num);
    }
    else
    {
        int num = ui->Display->text().toInt();
        if(num < MAX_INT_NUM && num > MIN_INT_NUM)
        {
        intToBinMemory();
        intToBin();
        }
        else
            errorInt(num);
    }
}


void MainWindow::errorFloat(const float num)
{
    if(num > MAX_FLOAT_NUM)
     {
        printError("Incorrect input(big number)");
     }
    else if(num < MIN_FLOAT_NUM)
     {
        printError("Incorrect input(small number)");
     }
}

void MainWindow::errorInt(const int num)
{
    if(num >= MAX_INT_NUM)
    {
        printError("Incorrect input(big number)");
    }
    else if(num <= MIN_INT_NUM)
    {
        printError("Incorrect input(small number)");
    }
}


void MainWindow::printError(const QString error)
{
    ui->BinDisplay->setText(error);
    ui->BinDisplayMemory->setText(error);
}

MainWindow::~MainWindow()
{
    delete ui;
}

