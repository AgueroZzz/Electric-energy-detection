#include "test.h"
// #include "ui_test.h"

test::test(quint16 test_id, QWidget *parent)
    : QWidget(parent)
    // , ui(new Ui::test)
    , _test_id(test_id)
{
    // ui->setupUi(this);
}

test::~test()
{
    // delete ui;
}
