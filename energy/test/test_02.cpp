#include "test_02.h"

#include "test/test_factory.h"

test_02::test_02(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_widget();
}

void test_02::init_UI()
{
    _top_widget = new QWidget();
    _ui_002 = new ui_002();

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_ui_002);

    layout->setStretch(0, 1);
    layout->setStretch(1, 9);

    // 设置组件之间的距离
    layout->setSpacing(0);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

void test_02::init_top_widget()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();

    _btn_open_para    = createToolButton(":/icon/icon/open_file.svg",   "打开参数");
    _btn_save_para    = createToolButton(":/icon/icon/save_file.svg",   "保存参数");
    _btn_print_test   = createToolButton(":/icon/icon/print_file.svg",  "打印测试记录");

    _btn_up_para      = createToolButton(":/icon/icon/up.svg", "递增数据");
    _btn_down_para    = createToolButton(":/icon/icon/down.svg", "递减数据");
    _btn_reset_test   = createToolButton(":/icon/icon/data_recover.svg", "数据复位");
    _btn_start_test   = createToolButton(":/icon/icon/start.svg", "开始实验");
    _btn_end_test     = createToolButton(":/icon/icon/stop.svg", "停止实验");
    _btn_fdq          = createToolButton(":/icon/icon/chart_fdq.svg", "放大器");


    // 把按钮加到布局中
    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);
    btn_layout->addWidget(_btn_up_para);
    btn_layout->addWidget(_btn_down_para);
    btn_layout->addWidget(_btn_reset_test);
    btn_layout->addWidget(_btn_start_test);
    btn_layout->addWidget(_btn_end_test);
    btn_layout->addWidget(_btn_fdq);

    total_layout->addLayout(btn_layout);
    _top_widget->setLayout(total_layout);
    _top_widget->setObjectName("topWidget");
}


REGISTER_TEST(test_02, 1);
