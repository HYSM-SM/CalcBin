#include "memory.h"

QString MainWindow::translate(const int pNum)
{
     QString binNum;
     for(int i = 0; i < FOUR_BYTE; i++)
     {
         if(i != 0 && i % SPACEBIT == 0)
             binNum += " ";
         if(pNum &(1 << i))
             binNum += "1";
         else
             binNum += "0";
     }
     return binNum;
}

void MainWindow::intToBinMemory()
{
    int num = ui->Display->text().toInt();
    int *pNum = reinterpret_cast<int*>(&num);
    QString binNum = translate(*pNum);
    std::reverse(binNum.begin(),binNum.end());
    printBinDisplayMemory(binNum);
}

void MainWindow::floatToBinMemory()
{
    float num = ui->Display->text().toFloat();
    int *pNum = reinterpret_cast<int*>(&num);
    QString binNum = translate(*pNum);
    printBinDisplayMemory(binNum);
}

void MainWindow::printBinDisplayMemory(const QString number)
{
    ui->BinDisplayMemory->setText(Memory + number + bitIndex);
}
