#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <cmath>

struct floatNum
{
    char    signPart;
    QString commaPart;
    QString intPart;
    QString floatPart;
    int     Int;
    float   Float;
    int     shiftComma;
    int     spaceForFloat;
};

QString getIntBin(int num);
QString getFloatBin(float num,const int spaceForFloat);
QString logicNOT(QString binNum);
QString setSpaceBetweenBits(QString binNum,int space);
QString addCharToString(QString binNum,const char ch,const int amountChars);
QString getAssemblyNum(floatNum& fNum);

void workingWithSignPart(floatNum& fNum,float& num);
void workingWithIntPart(floatNum& fNum,const float num);
void workingWithFloatPart(floatNum& fNum,const float num);
void workingWithCommaPart(floatNum& fNum,const float num);

#endif // ALGORITHM_H
