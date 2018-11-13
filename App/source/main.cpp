#include <win32/sgePlatformNativeWin32.h>

using namespace sge;

int main()
{
    sgePlatformWin32Native win(0);
    while (!win.IsClosed())
    {
        win.ProcessEvents();
    }
    return 0;
}