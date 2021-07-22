#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include<QTextCodec>
#include "Windows.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tmr = new QTimer();

    setWindowFlags( windowFlags() | Qt::Window | Qt::FramelessWindowHint  | Qt::Tool | Qt::WindowTransparentForInput | Qt::WindowStaysOnTopHint  );
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_MSWindowsUseDirect3D);
    setAttribute(Qt::WA_ShowWithoutActivating);

    /*
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString s = codec->toUnicode("Dawn of War: Soulstorm");
        LPCWSTR lps = (LPCWSTR)s.utf16();

        hWnd = FindWindowW(NULL, lps);

        if (hWnd) {
            SetForegroundWindow(hWnd);
            SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 1920, 1080, SWP_SHOWWINDOW | WS_POPUP | WS_VISIBLE );
            ShowWindow(hWnd, SW_RESTORE);
        }*/




   /* if (hWnd) {
        SetForegroundWindow(hWnd);
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 1920, 1080, SWP_SHOWWINDOW | WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_TOPMOST );
        ShowWindow(hWnd, SW_RESTORE);
    }*/

    showFullScreen();

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString s = codec->toUnicode(this->windowTitle().toLatin1());
    LPCWSTR lps = (LPCWSTR)s.utf16();

    hWnd = FindWindowW(NULL, lps);

    tmr->setInterval(700);
    connect(tmr, &QTimer::timeout, this, &MainWindow::timeout, Qt::QueuedConnection);

    tmr->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeout()
{
    //TODO
    //Костыль для того чтоб форма всегда была с верху сса,
    //ибо директикс сса по таймеру обновляет флаги стиля окна, конкретнро WS_EX_TOPMOST
    //установка флага Qt::WindowStaysOnTopHint на кородкое время выводет икно повер сса
    //Соответственно затираем флаг и выставлем заного по таймеру.
    //Время устанавливаемое таймеру возможно придется менять из за разницы систем, надо тестить

    /* setWindowFlag( Qt::WindowStaysOnTopHint, false);
     setWindowFlag( Qt::WindowStaysOnTopHint, true);
     showFullScreen();*/

    if (hWnd){
        qDebug() << "yep";
        BringWindowToTop(hWnd);
    }

    showFullScreen();
}
