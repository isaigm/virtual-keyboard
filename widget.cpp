#include "widget.h"
#include "./ui_widget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
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

    m_highlightTimer.setSingleShot(true);
    m_highlightTimer.setInterval(100);
    connect(&m_highlightTimer, &QTimer::timeout, this, &Widget::disableCurrentKey);
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::MouseButton::LeftButton) return;
    QPoint pos = event->pos();
    auto key = m_keyboard.getPressedKey(pos);
    if (key == std::nullopt) return;
    // Every press is sent, even if the previous key is still highlighted:
    // the highlight is only visual feedback and must not block typing.
    m_highlightTimer.stop();
    m_keyboard.disableKey(m_currKeyPressed);
    auto [keyIndex, name] = key.value();
    m_vkeyboard.sendKey(name);
    m_currKeyPressed = keyIndex;
    m_keyboard.enableKey(keyIndex);
    repaint();
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::MouseButton::LeftButton) return;
    if (m_currKeyPressed < 0) return;
    m_highlightTimer.start();   // (re)starts the 100 ms countdown
}
void Widget::disableCurrentKey()
{
    m_keyboard.disableKey(m_currKeyPressed);
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
