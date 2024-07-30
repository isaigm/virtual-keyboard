#include "keyboard.h"
#include <QDebug>
keyboard::keyboard() : m_keys(NAMES.size()) {
    for(size_t i = 0; i < NAMES.size(); i++)
    {
        auto &key = m_keys[i];
        key.setName(NAMES.at(i));
    }
    int keysPerCol = NAMES.size() / totalRows;
    float xmargin = 1.0f;
    float ymargin = 32.0f;
    float mx = 10.0f;
    float my = 10.0f;
    for (int i = 0; i < totalRows; i++)
    {
        for (int j = 0; j < keysPerCol; j++)
        {
            QRectF bounds;
            QPointF pos(mx + j * (xmargin + kWidth), my + i * (ymargin + kHeight));
            bounds.setTopLeft(pos);
            bounds.setWidth(kWidth);
            bounds.setHeight(kHeight);
            m_keys[j + i * keysPerCol].setBounds(bounds);
        }
    }
}
void keyboard::render(QPainter &painter)
{
    for(auto &key: m_keys)
    {
        key.render(painter);
    }
}
std::optional<QChar> keyboard::getPressedKey(QPointF point)
{
    for (auto &key: m_keys)
    {
        if (key.contains(point)) return std::make_optional(key.getName());
    }
    return std::nullopt;
}
