#include "test_02.h"

test_02::test_02(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();
}

void test_02::init_UI()
{
    _top_widget = new QWidget();
    _middle_widget = new QWidget();
    _footer_widget = new QWidget();

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_middle_widget);
    layout->addWidget(_footer_widget);

    // 设置比例（5 : 65 : 30）
    layout->setStretch(0, 5);   // top
    layout->setStretch(1, 65);  // middle.
    layout->setStretch(2, 30);  // bottom

    // 设置组件之间的距离
    layout->setSpacing(1);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}
