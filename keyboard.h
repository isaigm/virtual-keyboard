#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>
#include <QString>
#include <QStringList>
#include <optional>
#include "ckey.h"
class keyboard
{
public:
    struct key_t
    {
        int index;
        QChar name;
    };

    keyboard();
    void enableKey(int index);
    void disableKey(int index);
    std::optional<key_t> getPressedKey(QPointF point);
    QRectF getBounds();
    void render(QPainter &painter);
private:
    QRectF m_bounds;
    // One string per row, in QWERTY order. Rows may have different lengths.
    const QStringList ROWS = {"qwertyuiop", "asdfghjklñ", "zxcvbnm"};
    const float kWidth  = 64.0f;
    const float kHeight = 64.0f;
    const float xmargin = 8.0f;    // horizontal gap between keys
    const float ymargin = 32.0f;   // vertical gap between rows
    const float padding = 8.0f;    // empty border so key outlines are not clipped
    std::vector<ckey> m_keys;
};
#endif // KEYBOARD_H
