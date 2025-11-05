#ifndef UI__1__H
#define UI__1__H

#include <QWidget>
#include <QTimer>

namespace Ui {
class ui_010;
}

class ui_010 : public QWidget
{
    Q_OBJECT

public:
    explicit ui_010(QWidget *parent = nullptr);
    ~ui_010();

private:
    Ui::ui_010 *ui;
};

#endif // UI__1__H
