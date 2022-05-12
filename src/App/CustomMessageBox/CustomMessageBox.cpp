#include <CustomMessageBox.h>

void CustomMessageBox(HWND h_CMB, HINSTANCE hInst, LPCSTR MessageToDisplay, LPCSTR CustomMessageBoxTitle, int MBchoosenstyles, LPSTR MAKEINTRES)
{
    MSGBOXPARAMS msgbox = {0};
    msgbox.cbSize = sizeof(MSGBOXPARAMS);
    msgbox.hwndOwner = h_CMB;
    msgbox.hInstance = hInst;
    msgbox.lpszText = MessageToDisplay;
    msgbox.lpszCaption = CustomMessageBoxTitle;
    msgbox.dwStyle = MBchoosenstyles | MB_SETFOREGROUND;  
    msgbox.lpszIcon = MAKEINTRESOURCE(MAKEINTRES);

    MessageBoxIndirect(&msgbox);
}