#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include "uinputvkeyboard.h"
#include "x11vkeyboard.h"
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
    keyboard m_keyboard;
    x11vkeyboard m_vkeyboard;
    const int width = 520;
    const int height = 256;

    Ui::Widget *ui;
private slots:
    void exitSlot();

};
#endif // WIDGET_H
