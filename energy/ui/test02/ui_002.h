#ifndef UI___2_H
#define UI___2_H

#include <QWidget>
#include "serial/serial_opera.h"

namespace Ui {
class ui_002;
}

class ui_002 : public QWidget
{
    Q_OBJECT

public:
    explicit ui_002(QWidget *parent = nullptr);
    ~ui_002();

    void init_UI();

private:
    Ui::ui_002 *ui;

    serial_opera* _opera;
};

#endif // UI___2_H
