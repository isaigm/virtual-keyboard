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
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
private:
    void disableCurrentKey();
    keyboard m_keyboard;
    x11vkeyboard m_vkeyboard;
    bool m_enabledTimer {false};
    bool m_stillActive  {false};
    int m_currKeyPressed {-1};
    const int width {520};
    const int height {256};

    Ui::Widget *ui;
private slots:
    void exitSlot();

};
#endif // WIDGET_H
