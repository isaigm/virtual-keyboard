#include "keyboard.h"
#include <algorithm>
#include <QDebug>
keyboard::keyboard()
{
    // The widest row sets the keyboard width; shorter rows are centered.
    int maxKeys = 0;
    for (const QString &row : ROWS)
    {
        maxKeys = std::max(maxKeys, int(row.size()));
    }
    float maxRowWidth = maxKeys * kWidth + (maxKeys - 1) * xmargin;

    for (int i = 0; i < ROWS.size(); i++)
    {
        const QString &row = ROWS.at(i);
        float rowWidth = row.size() * kWidth + (row.size() - 1) * xmargin;
        float x0 = padding + (maxRowWidth - rowWidth) / 2.0f;
        float y  = padding + i * (kHeight + ymargin);
        for (int j = 0; j < row.size(); j++)
        {
            ckey key(row.at(j));
            key.setBounds(QRectF(x0 + j * (kWidth + xmargin), y, kWidth, kHeight));
            m_keys.push_back(key);
        }
    }
    float totalHeight = ROWS.size() * kHeight + (ROWS.size() - 1) * ymargin;
    m_bounds = QRectF(0.0f, 0.0f, maxRowWidth + 2 * padding, totalHeight + 2 * padding);
}
void keyboard::enableKey(int index)
{
    if (index >= 0 && index < int(m_keys.size()))
    {
        m_keys[index].setClicked(true);
    }
}

void keyboard::disableKey(int index)
{
    if (index >= 0 && index < int(m_keys.size()))
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
    for (int i = 0; i < int(m_keys.size()); i++)
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
