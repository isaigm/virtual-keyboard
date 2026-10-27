#include "x11vkeyboard.h"
#include <QDebug>   // Qt headers must come before X11 ones (Bool/Status macros)
#include <QtX11Extras/qx11info_x11.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

x11vkeyboard::x11vkeyboard()
{
    m_tableCodes['q'] = 24;
    m_tableCodes['w'] = 25;
    m_tableCodes['e'] = 26;
    m_tableCodes['r'] = 27;
    m_tableCodes['t'] = 28;
    m_tableCodes['y'] = 29;
    m_tableCodes['u'] = 30;
    m_tableCodes['i'] = 31;
    m_tableCodes['o'] = 32;
    m_tableCodes['p'] = 33;
    m_tableCodes['a'] = 38;
    m_tableCodes['s'] = 39;
    m_tableCodes[u'ñ'] = 47;
    m_tableCodes['d'] = 40;
    m_tableCodes['f'] = 41;
    m_tableCodes['g'] = 42;
    m_tableCodes['h'] = 43;
    m_tableCodes['j'] = 44;
    m_tableCodes['k'] = 45;
    m_tableCodes['l'] = 46;
    m_tableCodes['z'] = 52;
    m_tableCodes['x'] = 53;
    m_tableCodes['c'] = 54;
    m_tableCodes['v'] = 55;
    m_tableCodes['b'] = 56;
    m_tableCodes['n'] = 57;
    m_tableCodes['m'] = 58;
}
void x11vkeyboard::sendKey(QChar key)
{
    int code = qcharToCode(key);
    if (code < 0)
    {
        qWarning() << "x11vkeyboard: no keycode for" << key;
        return;
    }
    // Under Wayland Qt does not use X11 and display() is nullptr;
    // passing it to XTest would segfault.
    Display *dpy = QX11Info::display();
    if (dpy == nullptr)
    {
        qWarning("x11vkeyboard: not running on X11 (Wayland session?), key not sent");
        return;
    }
    XTestFakeKeyEvent(dpy, code, True, 0);
    XSync(dpy, False);
    XTestFakeKeyEvent(dpy, code, False, 0);
    XSync(dpy, False);
}
int x11vkeyboard::qcharToCode(QChar ch)
{
    auto it = m_tableCodes.find(ch);
    return it != m_tableCodes.end() ? it->second : -1;
}

