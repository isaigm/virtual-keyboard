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
    // Owns a file descriptor: a copy would close/destroy the device twice.
    uinputvkeyboard(const uinputvkeyboard &) = delete;
    uinputvkeyboard &operator=(const uinputvkeyboard &) = delete;
    virtual void sendKey(QChar key);
    virtual int qcharToCode(QChar ch);
private:
    int m_fd;
    void emitKey(int type, int code, int val);
    std::map<QChar, int> m_tableCodes;
};

#endif // UINPUTVKEYBOARD_H
