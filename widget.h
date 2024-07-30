#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "keyboard.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *);
private:
    int fd;
    void emit_key(int fd, int type, int code, int val);
    keyboard m_keyboard;
    const int width = 600;
    const int height = 300;

    Ui::Widget *ui;
};
#endif // WIDGET_H
