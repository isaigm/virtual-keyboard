#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>
#include <QString>
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
    const QString NAMES = "qwertyuiopasdfghjklñzxcvbnm";
    const int kWidth = 64;
    const int kHeight = 64;
    const int totalRows = 3;
    std::vector<ckey> m_keys;
};
#endif // KEYBOARD_H
