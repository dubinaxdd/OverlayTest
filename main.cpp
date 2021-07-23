#include "mainwindow.h"

#include <QApplication>
#include<QTextCodec>
#include "Windows.h"
#include <QDebug>
#include <QKeyEvent>

HHOOK mouseHook = NULL;
HHOOK keyboardHook = NULL;

int KeyboardDelay = 0;
//Ui::MainWindow asdUi;
MainWindow* w = NULL;

void UpdateKeySate(BYTE *keystate, int keycode)
{
    keystate[keycode] = GetKeyState(keycode);
}


LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    switch( wParam )
    {
        case WM_LBUTTONDOWN:
        {
            //qDebug() << "Left click"; // Left click
            //Ui::MainWindow* asd = w.getUi();
            //groupBox_2->setVisible(true);
            break;
        }

        case WM_RBUTTONDOWN:
        {
           // qDebug() << "Right click"; // Left click
            break;

        }

        case WM_MOUSEMOVE:{
            //qDebug() << "mouse move";
            break;

        }
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);

    wchar_t buffer[5];

    BYTE keyboard_state[265];

    GetKeyboardState(keyboard_state);
    UpdateKeySate(keyboard_state, VK_SHIFT);
    UpdateKeySate(keyboard_state, VK_CAPITAL);
    UpdateKeySate(keyboard_state, VK_CONTROL);
    UpdateKeySate(keyboard_state, VK_MENU);

    HKL keyboard_layout = GetKeyboardLayout(0);
    char lpszName[0x100] = {0};

    DWORD dwMsg = 1;
    dwMsg += cKey.scanCode << 16;
    dwMsg += cKey.flags << 24;

    int i = GetKeyNameText(dwMsg, (LPTSTR)lpszName, 255);

    int result = ToUnicodeEx(cKey.vkCode, cKey.scanCode, keyboard_state, buffer, 4, 0, keyboard_layout);

    buffer[4] = L'\0';


    if(KeyboardDelay == 0)
    {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, cKey.vkCode, Qt::NoModifier, 0);
        QApplication::postEvent(w, event);
    }

    KeyboardDelay++;
    if(KeyboardDelay == 2)
        KeyboardDelay = 0;

    //qDebug()<<"key: " << cKey.vkCode << " " << QString::fromUtf16((ushort*)buffer) << " " << QString::fromUtf16((ushort*)lpszName);

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main(int argc, char *argv[])
{
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    if (mouseHook == NULL) {
        //qDebug() << "MouseHook failed";
    }

    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc , NULL, 0);
    if (keyboardHook == NULL) {
        //qDebug() << "KeyboardHook failed";
    }

    QApplication a(argc, argv);
    w = new MainWindow();
    w->show();

    return a.exec();
}
