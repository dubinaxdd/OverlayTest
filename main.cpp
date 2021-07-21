#include "mainwindow.h"

#include <QApplication>
#include<QTextCodec>
#include "Windows.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
