#include "ckey.h"
#include <QDebug>
ckey::ckey(QChar name) : m_name(name) {}
ckey::ckey(){}
bool ckey::contains(QPointF point)
{
    return m_bounds.contains(point);
}
void ckey::setName(QChar name)
{
    m_name = name;
}
void ckey::setBounds(QRectF bounds)
{
    m_bounds = bounds;
}
void ckey::setClicked(bool clicked)
{
    m_clicked = clicked;
}
QChar ckey::getName()
{
    return m_name;
}
void ckey::render(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    if (m_clicked)
    {
        painter.setPen(Qt::white);
    }
    else
    {
        painter.setPen(Qt::green);
    }
    painter.drawRoundedRect(m_bounds, 10.0f, 10.0f);
    painter.setFont(QFont("Arial", 32));
    painter.setPen(Qt::green);
    painter.drawText(m_bounds, Qt::AlignCenter, m_name);
}
