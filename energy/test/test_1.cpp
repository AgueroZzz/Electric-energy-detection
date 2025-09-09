#include "test_1.h"
#include "ui_test_1.h"

test_1::test_1(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{

}

test_1::~test_1()
{
    delete ui;
}

void test_1::init_UI()
{

}
