#ifndef UI___3_H
#define UI___3_H

#include <QWidget>

namespace Ui {
class ui_003;
}

class ui_003 : public QWidget
{
    Q_OBJECT

    friend class test_03;

public:
    explicit ui_003(QWidget *parent = nullptr);
    ~ui_003();

private:
    Ui::ui_003 *ui;
};

#endif // UI___3_H
