#ifndef UI___1_H
#define UI___1_H

#include <QWidget>

namespace Ui {
class ui_001;
}

class ui_001 : public QWidget
{
    Q_OBJECT

    friend class test_01;

public:
    explicit ui_001(QWidget *parent = nullptr);
    ~ui_001();

private:
    Ui::ui_001 *ui;
};

#endif // UI___1_H
