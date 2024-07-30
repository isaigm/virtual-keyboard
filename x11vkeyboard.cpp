#include "x11vkeyboard.h"
#include <QtX11Extras/qx11info_x11.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

x11vkeyboard::x11vkeyboard() {}
void x11vkeyboard::sendKey(QChar key)
{
    //XTestFakeKeyEvent(QX11Info::display(), 0, true, 0);
    //XSync(QX11Info::display(), False);
    //XTestFakeKeyEvent(QX11Info::display(), 0, false, 0);
    //XSync(QX11Info::display(), False);
}
int x11vkeyboard::qcharToCode(QChar ch)
{
    return -1;
}

