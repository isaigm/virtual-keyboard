#include "uinputvkeyboard.h"
#include <stdexcept>
#include <linux/uinput.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
uinputvkeyboard::~uinputvkeyboard()
{
    ioctl(m_fd, UI_DEV_DESTROY);
    close(m_fd);
}
uinputvkeyboard::uinputvkeyboard()
{
    struct uinput_setup usetup;
    m_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (m_fd < 0)
    {
        printf("%s\n", strerror(errno));
        throw std::runtime_error(strerror(errno));
    }
    ioctl(m_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_Q);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_W);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_E);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_R);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_T);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_Y);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_U);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_I);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_O);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_P);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_A);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_S);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_D);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_F);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_G);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_H);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_J);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_K);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_L);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_SEMICOLON);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_Z);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_X);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_C);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_V);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_B);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_N);
    ioctl(m_fd, UI_SET_KEYBIT, KEY_M);
    m_tableCodes['q'] = KEY_Q;
    m_tableCodes['w'] = KEY_W;
    m_tableCodes['e'] = KEY_E;
    m_tableCodes['r'] = KEY_R;
    m_tableCodes['t'] = KEY_T;
    m_tableCodes['y'] = KEY_Y;
    m_tableCodes['u'] = KEY_U;
    m_tableCodes['i'] = KEY_I;
    m_tableCodes['o'] = KEY_O;
    m_tableCodes['p'] = KEY_P;
    m_tableCodes['a'] = KEY_A;
    m_tableCodes['s'] = KEY_S;
    m_tableCodes['d'] = KEY_D;
    m_tableCodes['f'] = KEY_F;
    m_tableCodes['g'] = KEY_G;
    m_tableCodes['h'] = KEY_H;
    m_tableCodes['j'] = KEY_J;
    m_tableCodes['k'] = KEY_K;
    m_tableCodes['l'] = KEY_L;
    m_tableCodes[QChar(u'ñ')] = KEY_SEMICOLON;
    m_tableCodes['z'] = KEY_Z;
    m_tableCodes['x'] = KEY_X;
    m_tableCodes['c'] = KEY_C;
    m_tableCodes['v'] = KEY_V;
    m_tableCodes['b'] = KEY_B;
    m_tableCodes['n'] = KEY_N;
    m_tableCodes['m'] = KEY_M;
    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor  = 0x1234;
    usetup.id.product = 0x5678;
    strcpy(usetup.name, "virtual-keyboard");
    ioctl(m_fd, UI_DEV_SETUP, &usetup);
    ioctl(m_fd, UI_DEV_CREATE);
    sleep(1);
}
int uinputvkeyboard::qcharToCode(QChar ch)
{
    if (m_tableCodes.contains(ch))
    {
        return m_tableCodes[ch];
    }
    return -1;
}

void uinputvkeyboard::emitKey(int type, int code, int val)
{
    struct input_event ie;
    ie.type = type;
    ie.code = code;
    ie.value = val;
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;
    write(m_fd, &ie, sizeof(ie));
}
void uinputvkeyboard::sendKey(QChar key)
{
    int code = qcharToCode(key);
    emitKey(EV_KEY, code, 1);
    emitKey(EV_SYN, SYN_REPORT, 0);
    emitKey(EV_KEY, code, 0);
    emitKey(EV_SYN, SYN_REPORT, 0);
}
