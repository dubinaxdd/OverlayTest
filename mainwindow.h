#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Windows.h"
#include <QKeyEvent>

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

private:
    Ui::MainWindow *ui;

    QTimer* tmr;

    HWND hWnd;
    HWND soulstorm;
    LONG soulstormSettings;

    bool showFullOverlay = false;

    void checkSoulstorm();

    void keyPressEvent(QKeyEvent *event) override;
    void showOverlay();




};
#endif // MAINWINDOW_H
