#include <stdint.h>
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

struct
{
    int WARNING = 0x30;
    int INFORMATION = 0x40;
    int ERR = 0x50;
} CMB_ICNS;

void CustomMessageBox(HWND h_CMB, HINSTANCE hInst, LPCSTR MessageToDisplay, LPCSTR CustomMessageBoxTitle, int MBchoosenstyles, LPSTR MAKEINTRES);