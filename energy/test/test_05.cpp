#include "test_05.h"

#include "test/test_factory.h"

test_05::test_05(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_widget();
}

void test_05::init_UI()
{
    _top_widget = new QWidget();
    _ui_005 = new ui_005();

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_ui_005);

    layout->setStretch(0, 1);
    layout->setStretch(1, 9);

    // 设置组件之间的距离
    layout->setSpacing(0);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

void test_05::init_top_widget()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();
    total_layout->setSpacing(3);

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();
    btn_layout->setContentsMargins(3, 3, 3, 3);

    _btn_open_para    = createToolButton(":/icon/icon/open_file.svg",   "打开参数");
    _btn_save_para    = createToolButton(":/icon/icon/save_file.svg",   "保存参数");
    _btn_print_test   = createToolButton(":/icon/icon/print_file.svg",  "打印测试记录");
    _btn_up_para      = createToolButton(":/icon/icon/up.svg", "插入状态");
    _btn_down_para    = createToolButton(":/icon/icon/down.svg", "删除状态");
    _btn_start_test   = createToolButton(":/icon/icon/start.svg", "开始实验");
    _btn_switch_status = createToolButton(":/icon/icon/switch.svg", "切换状态");
    _btn_end_test     = createToolButton(":/icon/icon/stop.svg", "停止实验");
    _btn_history      = createToolButton(":/icon/icon/test_history.svg", "历史数据");


    // 把按钮加到布局中
    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);
    btn_layout->addWidget(_btn_up_para);
    btn_layout->addWidget(_btn_down_para);
    btn_layout->addWidget(_btn_start_test);
    btn_layout->addWidget(_btn_switch_status);
    btn_layout->addWidget(_btn_end_test);
    btn_layout->addWidget(_btn_history);

    total_layout->addLayout(btn_layout);
    _top_widget->setLayout(total_layout);
    _top_widget->setObjectName("topWidget");
}

REGISTER_TEST(test_05, 4);
