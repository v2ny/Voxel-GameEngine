#include <BoxLogger.h>

void BoxLogger::Log(LPCSTR msg, LPCSTR capt, HWND hwnd, logTypes logType)
{   
    if(msg == nullptr || capt == nullptr || logType == this->null)
    {
        MessageBox(hwnd, "Error: msg, capt or logType is null!", "BoxLogger ERR", MB_OKCANCEL || MB_ICONERROR);
        std::exit(-1);
    }
    if(logType == this->err)
    {
        MessageBox(hwnd, msg, capt, MB_OKCANCEL | MB_ICONERROR);
    }
    else if(logType == this->warn)
    {
        MessageBox(hwnd, msg, capt, MB_OKCANCEL | MB_ICONWARNING);
    }
    else if(logType == this->info)
    {
        MessageBox(hwnd, msg, capt, MB_OKCANCEL | MB_ICONINFORMATION);
    }
    else if(logType == this->msg)
    {
        MessageBox(hwnd, msg, capt, MB_OKCANCEL | MB_ICONEXCLAMATION);
    }
}