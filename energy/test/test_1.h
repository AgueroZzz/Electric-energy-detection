#ifndef TEST_1_H
#define TEST_1_H

// test_1:三相交流电流/电压实验

#include "test.h"
#include <QWidget>

namespace Ui {
class test_1;
}

class test_1 : public test
{
    Q_OBJECT

public:
    explicit test_1(quint16 test_id, QWidget *parent = nullptr);
    ~test_1();

private:
    Ui::test_1 *ui;

    void init_UI();

    QWidget* headerWidget;
    QWidget* contontWidget;
    QWidget* footerWidget;
};

#endif // TEST_1_H
