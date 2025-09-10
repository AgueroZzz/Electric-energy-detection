#ifndef TEST__1_H
#define TEST__1_H

#include "test.h"

class test_01 : public test
{
public:
    test_01(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    QWidget* headWidget;
};

#endif // TEST__1_H
