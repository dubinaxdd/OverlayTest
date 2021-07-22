#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include<QTextCodec>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tmr = new QTimer();

    setWindowFlags( windowFlags() | Qt::Window | Qt::FramelessWindowHint  | /*Qt::Tool | Qt::WindowTransparentForInput |*/ Qt::WindowStaysOnTopHint  );
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
    this->ui->groupBox_2->setVisible(false);
    showFullScreen();

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString s = codec->toUnicode("MAinWindow"/*this->windowTitle().toLatin1()*/);
    LPCWSTR lps = (LPCWSTR)s.utf16();

    hWnd = FindWindowW(NULL, lps);

    checkSoulstorm();

   /* if (soulstorm) {

            qDebug() << "yep";
            SetForegroundWindow(soulstorm);
            SetWindowPos(soulstorm, HWND_TOPMOST, 0, 0, 1920, 1080, SWP_SHOWWINDOW | WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_TOPMOST | WS_DISABLED | WS_EX_NOACTIVATE | WS_MAXIMIZE);
            ShowWindow(soulstorm, SW_RESTORE);
    }
*/

  /*  HOOKPROC hkprcSysMsg;
    static HINSTANCE hinstDLL;
    static HHOOK hhookSysMsg;

    hinstDLL = LoadLibrary(TEXT("c:\\myapp\\sysmsg.dll"));
    hkprcSysMsg = (HOOKPROC)GetProcAddress(hinstDLL, "SysMessageProc");

    hhookSysMsg = SetWindowsHookEx(
                        WH_SYSMSGFILTER,
                        hkprcSysMsg,
                        hinstDLL,
                        0);
    */


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

void MainWindow::on_pushButton_clicked()
{
    //checkSoulstorm();
    //SetWindowLong(soulstorm, GWL_STYLE,/* SWP_SHOWWINDOW |*/ WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_TOPMOST/* | WS_DISABLED | WS_EX_NOACTIVATE | WS_MAXIMIZE*/);
    //SetWindowPos(soulstorm, HWND_TOPMOST, 0, 0, 0, 0,/* SWP_SHOWWINDOW |*/ WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_EX_TOPMOST/* | WS_DISABLED | WS_EX_NOACTIVATE *//*| WS_MAXIMIZE*/);
    if(soulstorm)
        ShowWindow(soulstorm, SW_RESTORE);

   // timeout();
    showFullScreen();
    this->ui->groupBox_2->setVisible(true);
    this->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    //SwitchToThisWindow(hWnd, true);
    //BringWindowToTop(soulstorm);

}


void MainWindow::on_pushButton_2_clicked()
{
   // checkSoulstorm();

    //tmr->stop();
    //showNormal();
    this->ui->groupBox_2->setVisible(false);
    //SetWindowLong(soulstorm, GWL_STYLE, soulstormSettings);
    //ShowWindow(soulstorm, SW_SHOWDEFAULT);

    //SetActiveWindow(soulstorm);
    //UpdateWindow(soulstorm);
    //timeout();
   // BringWindowToTop(soulstorm);
    //restoreTimer->start();


    this->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    if(soulstorm)
        SwitchToThisWindow(soulstorm, true);

    timeout();
}

void MainWindow::checkSoulstorm()
{
   // if (!soulstorm)
  //  {
        QTextCodec *codecc = QTextCodec::codecForName("UTF-8");
        QString ss = codecc->toUnicode("Dawn of War: Soulstorm");
        LPCWSTR lpss = (LPCWSTR)ss.utf16();

        soulstorm = FindWindowW(NULL, lpss);
   // }

    if (soulstorm)
         soulstormSettings = GetWindowLong(soulstorm, GWL_STYLE);
}
