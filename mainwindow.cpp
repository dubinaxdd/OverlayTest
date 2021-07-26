#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include<QTextCodec>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    tmr = new QTimer();

    setWindowFlags( windowFlags() | Qt::Window | Qt::FramelessWindowHint  | Qt::Tool | Qt::WindowTransparentForInput | Qt::WindowStaysOnTopHint  );
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_MSWindowsUseDirect3D);
    setAttribute(Qt::WA_ShowWithoutActivating);



    QTextCodec *codecc = QTextCodec::codecForName("UTF-8");
    QString ssc = codecc->toUnicode("Dawn of War: Soulstorm");
    LPCWSTR lpss = (LPCWSTR)ssc.utf16();

    soulstorm = FindWindowW(NULL, lpss);



    if (soulstorm) {
        SetForegroundWindow(soulstorm);
        SetWindowPos(soulstorm, HWND_TOPMOST, 0, 0, 0, 0, WS_EX_TRANSPARENT | WS_VISIBLE );
        //ShowWindow(hWnd, SW_RESTORE);
    }


   /* if (hWnd) {
        SetForegroundWindow(hWnd);
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 1920, 1080, SWP_SHOWWINDOW | WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_TOPMOST );
        ShowWindow(hWnd, SW_RESTORE);
    }*/


    this->ui->groupBox_2->setVisible(false);
    showFullScreen();

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString s = codec->toUnicode("MAinWindow"/*this->windowTitle().toLatin1()*/);
    LPCWSTR lps = (LPCWSTR)s.utf16();

    hWnd = FindWindowW(NULL, lps);


    checkSoulstorm();

  /*  if (soulstorm) {

            qDebug() << "yep";
            SetForegroundWindow(soulstorm);
            SetWindowPos(soulstorm, HWND_TOPMOST, 0, 0, 1920, 1080, SWP_SHOWWINDOW | WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_TOPMOST | WS_DISABLED | WS_EX_NOACTIVATE | WS_MAXIMIZE);
            ShowWindow(soulstorm, SW_RESTORE);
    }*/



    blockTmr = new QTimer();
    blockTmr->setInterval(10000);
    connect(blockTmr, &QTimer::timeout, this, &MainWindow::blockTimout, Qt::QueuedConnection);
    blockTmr->start();


    tmr->setInterval(100);
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

    if (hWnd){
        BringWindowToTop(hWnd);
    }


    //не удалять
   // showFullScreen();


}

void MainWindow::blockTimout()
{
    //SetWindowPos(soulstorm, HWND_TOPMOST, 0, 0, 0, 0, GetWindowLong(soulstorm, GWL_EXSTYLE) | WS_EX_TRANSPARENT | WS_VISIBLE | WS_EX_NOACTIVATE  );
    //SetWindowLongW(soulstorm, GWL_EXSTYLE, GetWindowLong(soulstorm, GWL_EXSTYLE) | /*WS_EX_TRANSPARENT |*/ WS_EX_NOACTIVATE);
    //ShowWindow(soulstorm, SW_RESTORE);

  //  BlockInput(false);
}

void MainWindow::on_pushButton_clicked()
{
    showOverlay();
}

void MainWindow::checkSoulstorm()
{

    QTextCodec *codecc = QTextCodec::codecForName("UTF-8");
    QString ss = codecc->toUnicode("Dawn of War: Soulstorm");
    LPCWSTR lpss = (LPCWSTR)ss.utf16();

    soulstorm = FindWindowW(NULL, lpss);

    if (soulstorm)
         soulstormSettings = GetWindowLong(soulstorm, GWL_STYLE);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == 192)
    {
        showOverlay();
    }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (event->type() == QEvent::Type::MouseButtonPress)
    {
        if (event->button() == Qt::MouseButton::LeftButton)
        {
            if(event->pos().x() >= this->ui->pushButton->x()
            && event->pos().x() <= this->ui->pushButton->x() + this->ui->pushButton->width()
            && event->pos().y() >= this->ui->pushButton->y()
            && event->pos().y() <= this->ui->pushButton->y() + this->ui->pushButton->height())
            {
                this->ui->pushButton->click();
            }
        }

    }
    qDebug() << "baneblade";

    QMainWindow::mousePressEvent(event);
}

void MainWindow::showOverlay()
{
    if(showFullOverlay)
    {
        EnableWindow(soulstorm, true);
        //BlockInput(false);
        showFullOverlay = false;
        this->ui->groupBox_2->setVisible(false);
        this->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    }
    else
    {
       // BlockInput(true);
        EnableWindow(soulstorm, false);
        showFullOverlay = true;
        this->ui->groupBox_2->setVisible(true);
        this->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    }

}
