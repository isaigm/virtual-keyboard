#ifndef UINPUTVKEYBOARD_H
#define UINPUTVKEYBOARD_H
#include "virtualkeyboard.h"
#include <map>
#include <QChar>
class uinputvkeyboard : public virtualkeyboard
{
public:
    uinputvkeyboard();
    ~uinputvkeyboard();
    virtual void sendKey(QChar key);
    virtual int qcharToCode(QChar ch);
private:
    int m_fd;
    void emitKey(int type, int code, int val);
    std::map<QChar, int> m_tableCodes;
};

#endif // UINPUTVKEYBOARD_H
