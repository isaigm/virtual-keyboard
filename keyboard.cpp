#include "keyboard.h"
#include <QDebug>
keyboard::keyboard() : m_keys(NAMES.size()) {
    for(size_t i = 0; i < NAMES.size(); i++)
    {
        auto &key = m_keys[i];
        key.setName(NAMES.at(i));
    }
    int keysPerCol = NAMES.size() / totalRows;
    float xmargin = 8.0f;
    float ymargin = 32.0f;
    float mx = 0.0f;
    float my = 0.0f;
    float topleftx = mx;
    float toplefty = my;
    float bottomrightx = topleftx + (keysPerCol - 1) * (xmargin + kWidth) + kWidth;
    float bottomrighty = toplefty + (totalRows - 1) * (ymargin + kHeight) + kHeight;
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
    m_bounds.setTopLeft({topleftx, toplefty});
    m_bounds.setBottomRight({bottomrightx, bottomrighty});
}
void keyboard::enableKey(int index)
{
    if (index < m_keys.size() && index >= 0)
    {
        m_keys[index].setClicked(true);
    }
}

void keyboard::disableKey(int index)
{
    if (index < m_keys.size() && index >= 0)
    {
        m_keys[index].setClicked(false);
    }
}

void keyboard::render(QPainter &painter)
{
    for(auto &key: m_keys)
    {
        key.render(painter);
    }
}
std::optional<keyboard::key_t> keyboard::getPressedKey(QPointF point)
{
    for (int i = 0; i < m_keys.size(); i++)
    {
        auto &key = m_keys[i];
        if (key.contains(point)) return std::make_optional(keyboard::key_t{i, key.getName()});

    }
    return std::nullopt;
}
QRectF keyboard::getBounds()
{
    return m_bounds;
}
