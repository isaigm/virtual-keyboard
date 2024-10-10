#include "widget.h"
#include "./ui_widget.h"
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>
#include <QTimer>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    auto bounds = m_keyboard.getBounds();
    int verticalSpace = 64;
    int windowHeight  = bounds.height() + verticalSpace;
    setFixedSize(bounds.width(), windowHeight);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    setFocusPolicy(Qt::NoFocus);
    auto geom = ui->closeBtn->geometry();
    ui->closeBtn->setGeometry(bounds.width() / 2 - geom.width() / 2, bounds.height() + verticalSpace / 2 - geom.height() / 2, geom.width(), geom.height());
    QObject::connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(exitSlot()));
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        QPoint pos = event->pos();
        auto key = m_keyboard.getPressedKey(pos);
        if (key != std::nullopt)
        {
            auto [keyIndex, name] = key.value();
            m_vkeyboard.sendKey(name);
            m_currKeyPressed = keyIndex;
            m_keyboard.enableKey(keyIndex);
            repaint();
        }
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (m_currKeyPressed > 0 && !m_enabledTimer)
        {
            m_enabledTimer = true;
            QTimer::singleShot(100, this, &Widget::disableCurrentKey);
        }
    }
}
void Widget::disableCurrentKey()
{
    m_keyboard.disableKey(m_currKeyPressed);
    m_enabledTimer = false;
    m_currKeyPressed = -1;
    repaint();
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_keyboard.render(painter);
}
void Widget::exitSlot()
{
    close();
}
Widget::~Widget()
{
    delete ui;
}
