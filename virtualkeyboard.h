#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H
#include <QChar>
class virtualkeyboard
{
public:
    virtualkeyboard();
    virtual int qcharToCode(QChar ch) = 0;
    virtual void sendKey(QChar key) = 0;
};

#endif // VIRTUALKEYBOARD_H
