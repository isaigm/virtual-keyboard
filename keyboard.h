#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>
#include <QString>
#include <optional>
#include "ckey.h"
class keyboard
{
public:
    keyboard();
    std::optional<QChar> getPressedKey(QPointF point);
    void render(QPainter &painter);
private:
    const QString NAMES = "qwertyuiopasdfghjklñzxcvbnm";
    const int kWidth = 64;
    const int kHeight = 64;
    const int totalRows = 3;
    std::vector<ckey> m_keys;
};
#endif // KEYBOARD_H
