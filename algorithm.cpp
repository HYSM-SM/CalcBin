#include "algorithm.h"

//------------------------------------------------------------------------------------------------ START FLOAT NUM

void MainWindow::floatToBin()
{
    QString binNum;
    floatNum fNum;
    float num = ui->Display->text().toFloat();

    workingWithSignPart(fNum,num);
    workingWithIntPart(fNum,num);
    workingWithCommaPart(fNum,num);
    workingWithFloatPart(fNum,num);

    binNum = getAssemblyNum(fNum);
    if(binNum.size() > FOUR_BYTE)
        binNum.remove(0,1);
    binNum = setSpaceBetweenBits(binNum,SPACEBIT);
    printBinDisplay(binNum);
}

void workingWithSignPart(floatNum& fNum,float& num)
{
    fNum.signPart = (num < 0) ? '1' : '0' ;
    if(fNum.signPart == '1') num *= -1;
}

void workingWithIntPart(floatNum &fNum,const float num)
{
    fNum.Int = num;
    fNum.intPart = getIntBin(fNum.Int);
    fNum.intPart.remove(fNum.intPart.size() - 1,fNum.intPart.size());
}

void workingWithCommaPart(floatNum &fNum,const float num)
{
    float intSize;
    if(num < 1)
        intSize = log2(num - fNum.Int);
    else
        intSize = fNum.intPart.size();
    fNum.shiftComma = intSize + MAX_SIGN_BYTE_NUMBER;
    fNum.commaPart = getIntBin(fNum.shiftComma);
    fNum.commaPart = addCharToString(fNum.commaPart,'0',8);
}

void workingWithFloatPart(floatNum &fNum,const float num)
{
    fNum.Float = num - fNum.Int;
    if(num < 1)
        fNum.spaceForFloat = (MAX_SIGN_BYTE_NUMBER - fNum.shiftComma) + THREE_BYTE;
    else
        fNum.spaceForFloat = THREE_BYTE - fNum.intPart.size();

    fNum.floatPart = getFloatBin(fNum.Float,fNum.spaceForFloat);

    if(num < 1)
    {
        while(fNum.floatPart.size() != THREE_BYTE)
            fNum.floatPart.remove(0,1);
    }
    std::reverse(fNum.floatPart.begin(),fNum.floatPart.end());
}

QString getFloatBin(float num,const int spaceForFloat)
{
    QString Float;
    for(int i = 0; i < spaceForFloat; i++)
    {
        num *= 2;
        if(num < 1) Float += '0';
        else
        {
            num -= 1;
            Float += '1';
        }
    }
    return Float;
}

QString getAssemblyNum(floatNum& fNum)
{
    QString answer;
    answer += fNum.signPart;
    std::reverse(fNum.commaPart.begin(),fNum.commaPart.end());
    answer += fNum.commaPart;
    std::reverse(fNum.intPart.begin(),fNum.intPart.end());
    answer += fNum.intPart;
    std::reverse(fNum.floatPart.begin(),fNum.floatPart.end());
    answer += fNum.floatPart;
    std::reverse(answer.begin(),answer.end());
    return answer;
}
//------------------------------------------------------------------------------------------------ END FLOAT NUM

//------------------------------------------------------------------------------------------------ START COMMON FUNCTIONS
QString setSpaceBetweenBits(const QString binNum,const int space)
{
    QString changeBinNum;
    for(int i = 0; i < binNum.size(); i++)
    {
        if(i != 0 && i % space == 0) changeBinNum += ' ';
        changeBinNum += binNum[i];
    }
    return changeBinNum;
}

void MainWindow::printBinDisplay(const QString number)
{
    ui->BinDisplay->setText(Algorithm + number + bitIndex);
}

//------------------------------------------------------------------------------------------------ END COMMON FUNCTIONS

//------------------------------------------------------------------------------------------------ STARTN INT NUM

QString logicNOT(QString binNum)
{
    for(int i = 0; i < binNum.size(); i++)
    {
        if(binNum[i] == "1") binNum[i] = '0';
        else
            binNum[i] = '1';
    }
    return binNum;
}

QString addCharToString(QString binNum,const char ch,const int amountChars)
{
    if(amountChars <= binNum.size())
    {
        return binNum;
    }
    for(int i = binNum.size(); i < amountChars; i++)
        binNum += ch;
    return binNum;
}

QString getIntBin(int num)
{
    QString binNum;
    while(num)
    {
        if(num % 2 != 0)
        {
            binNum += "1";
            num -=1;
        }
        else
            binNum += "0";
        num /=2;
    }
    return binNum;
}

void MainWindow::intToBin()
{
    int num = ui->Display->text().toInt();
    bool sign = (num < 0) ? true : false ;

    if(sign)
    {
        num *= -1;
        num -=1;
    }

    QString binNum = getIntBin(num);
    binNum = addCharToString(binNum,'0',FOUR_BYTE);
    if(sign)
    {
        binNum = logicNOT(binNum);
    }
    std::reverse(binNum.begin(),binNum.end());
    binNum = setSpaceBetweenBits(binNum,SPACEBIT);

    printBinDisplay(binNum);
}

//------------------------------------------------------------------------------------------------ END INT NUM
