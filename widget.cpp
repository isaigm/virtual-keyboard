#include "widget.h"
#include "./ui_widget.h"
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>
#include <linux/uinput.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include "keyboard.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(width, height);
    struct uinput_setup usetup;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0)
    {
        printf("%s\n", strerror(errno));
        exit(1);
    }

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, KEY_W);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234;  /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
    strcpy(usetup.name, "Example device");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    //setWindowFlags(Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);

    setFocusPolicy(Qt::NoFocus);



}
void Widget::emit_key(int fd, int type, int code, int val)
{
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(fd, &ie, sizeof(ie));
}
bool Widget::event(QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEv = static_cast<QMouseEvent *>(event);
        if (mouseEv->button() == Qt::MouseButton::LeftButton) {
            QPoint pos = mouseEv->pos();
            auto key = m_keyboard.getPressedKey(pos);
            if (key != std::nullopt)
            {
                qDebug() << key.value() << "\n";

            }
            //emit_key(fd, EV_KEY, KEY_W, 1);
            //emit_key(fd, EV_SYN, SYN_REPORT, 0);
            //emit_key(fd, EV_KEY, KEY_W, 0);
            //emit_key(fd, EV_SYN, SYN_REPORT, 0);
            return true;
        }
    }

    return QWidget::event(event);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_keyboard.render(painter);
}

Widget::~Widget()
{
    delete ui;
}
