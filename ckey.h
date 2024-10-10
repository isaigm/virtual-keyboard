#ifndef CKEY_H
#define CKEY_H
#include <QPainter>
#include <QChar>
class ckey
{
public:
    ckey(QChar name);
    ckey();
    bool  contains(QPointF point);
    QChar getName();
    void  setName(QChar name);
    void  setBounds(QRectF bounds);
    void  render(QPainter &painter);
    void  setClicked(bool clicked);
private:
    QChar m_name;
    QRectF m_bounds;
    bool m_clicked {false};
};
#endif // CKEY_H
