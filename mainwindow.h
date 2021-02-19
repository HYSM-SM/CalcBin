#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QShortcut>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>

//-------------------------------- key codes
#define ENTER                16777221
#define RETURN               16777220
#define DELETE               16777219
#define COMMA                44
#define DOT                  46
#define MINUS                45
//-------------------------------- bit
#define SPACEBIT             8
#define MAX_SIGN_BYTE_NUMBER 127
#define THREE_BYTE           23
#define FOUR_BYTE            32
//-------------------------------- input number
#define MAX_FLOAT_NUM        1048575.0
#define MIN_FLOAT_NUM        -1048575.0
#define MAX_INT_NUM          2147483647
#define MIN_INT_NUM          -2147483648

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

//-------------------------------------------------------------------------------------- Memory
    void intToBinMemory();
    void floatToBinMemory();
    void printBinDisplayMemory(const QString number = "00000000 00000000 00000000 00000000");
    QString translate(const int pNum);
//--------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------- Algorithm
    void printBinDisplay(const QString number = "00000000 00000000 00000000 00000000");
    void intToBin();
    void floatToBin();
//--------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------- GLOBAL
    void keyPressEvent(QKeyEvent *event);
    void numberToBin();                    //main function
    void errorFloat(const float num);
    void errorInt(const int num);
    void printError(const QString error);
    void pasteInBufferMemory();
    void pasteInBufferAlgorithm();
//--------------------------------------------------------------------------------------

private:
    Ui::MainWindow *ui;

    QShortcut *CopyMemory;
    QShortcut *CopyAlgorithm;
    const QString bitIndex = "\n31                15              0";
    const QString Memory = "Reading from memory\n";
    const QString Algorithm = "Algorithm\n";
    bool pressDot;
};

#endif // MAINWINDOW_H
