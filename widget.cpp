#include "widget.h"
#include "./ui_widget.h"
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(width, height);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    setFocusPolicy(Qt::NoFocus);
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
                m_vkeyboard.sendKey(key.value());
            }
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
