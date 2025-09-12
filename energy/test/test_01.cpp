#include "test_01.h"

test_01::test_01(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_btn();
}

void test_01::init_UI()
{
    _top_widget = new QWidget();
    _middle_widget = new QWidget();
    _footer_widget = new QWidget();

    // 设置背景颜色方便看效果
    _middle_widget->setStyleSheet("background-color: lightgreen;");
    _footer_widget->setStyleSheet("background-color: lightcoral;");

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_middle_widget);
    layout->addWidget(_footer_widget);

    // 设置比例（5 : 65 : 30）
    layout->setStretch(0, 5);   // top
    layout->setStretch(1, 65);  // middle0.
    layout->setStretch(2, 30);  // bottom

    setLayout(layout);
}

void test_01::init_top_btn()
{
    QHBoxLayout* btn_layout = new QHBoxLayout();
    QPushButton* _btn_open_para = new QPushButton();        // 打开参数按钮
    QPushButton* _btn_save_para = new QPushButton();        // 保存参数按钮
    QPushButton* _btn_print_test = new QPushButton();       // 打印测试记录

    QFrame *separator1 = new QFrame(this);
    separator1->setFrameShape(QFrame::VLine); // 垂直线
    separator1->setFrameShadow(QFrame::Sunken);
    separator1->setLineWidth(1);
    separator1->setMidLineWidth(0);
    separator1->setFixedWidth(2); // 设置固定宽度
    separator1->setStyleSheet("background-color: #000000;"); // 可选样式

    QPushButton* _btn_power_calcu = new QPushButton();      // 功率计算仪表
    QPushButton* _btn_shortout_calcu = new QPushButton();   // 短路计算

    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);

    btn_layout->addWidget(separator1);

    btn_layout->addWidget(_btn_power_calcu);
    btn_layout->addWidget(_btn_shortout_calcu);

    btn_layout->addWidget(separator1);

    _top_widget->setLayout(btn_layout);
}
