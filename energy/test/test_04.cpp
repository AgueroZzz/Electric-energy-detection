#include "test_04.h"

#include "test/test_factory.h"
#include "ui_ui_004.h"

test_04::test_04(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();
}

void test_04::init_UI()
{
    _ui_004 = new ui_004();
    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_ui_004);

    setLayout(layout);
}

REGISTER_TEST(test_04, 3);
