#ifndef UI___2_H
#define UI___2_H

#include <QWidget>

namespace Ui {
class ui_002;
}

class ui_002 : public QWidget
{
    Q_OBJECT

    friend class test_02;

public:
    explicit ui_002(QWidget *parent = nullptr);
    ~ui_002();

private:
    Ui::ui_002 *ui;
};

#endif // UI___2_H
