#include <Windows.h>
#include <iostream>

class BoxLogger
{
    public:
        enum logTypes {err=3, warn=2, info=1, msg=0, null=-1};
        void Log(LPCSTR msg, LPCSTR capt, HWND hwnd, logTypes logType);
};