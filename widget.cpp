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
            m_vkeyboard.sendKey(key.value());
        }
    }
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
