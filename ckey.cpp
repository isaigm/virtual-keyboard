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
QChar ckey::getName()
{
    return m_name;
}
void ckey::render(QPainter &painter)
{
    painter.setPen(Qt::green);
    painter.setFont(QFont("Arial", 32));
    painter.drawRoundedRect(m_bounds, 10.0f, 10.0f);
    painter.drawText(m_bounds, Qt::AlignCenter, m_name);
}
