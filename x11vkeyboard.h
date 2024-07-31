#ifndef X11VKEYBOARD_H
#define X11VKEYBOARD_H

#include "virtualkeyboard.h"
#include <X11/keysymdef.h>
#include <QChar>
#include <map>
class x11vkeyboard : public virtualkeyboard
{
public:
    x11vkeyboard();
    virtual int qcharToCode(QChar ch);
    virtual void sendKey(QChar key);
private:
    std::map<QChar, int> m_tableCodes;

};

#endif // X11VKEYBOARD_H
