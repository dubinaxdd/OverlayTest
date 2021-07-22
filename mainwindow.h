#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Windows.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   void timeout();

   void on_pushButton_clicked();

   void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QTimer* tmr;

    HWND hWnd;
    HWND soulstorm;
    LONG soulstormSettings;

    void checkSoulstorm();




};
#endif // MAINWINDOW_H
