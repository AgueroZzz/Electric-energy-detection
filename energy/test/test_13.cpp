#include "test_13.h"

#include "test/test_factory.h"

test_13::test_13(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_widget();
}

void test_13::init_UI()
{
    _top_widget = new QWidget();
    _ui_013 = new ui_013();

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_ui_013);

    layout->setStretch(0, 1);
    layout->setStretch(1, 9);

    // 设置组件之间的距离
    layout->setSpacing(0);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

void test_13::init_top_widget()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();
    total_layout->setSpacing(3);

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();
    btn_layout->setContentsMargins(0, 0, 0, 0);
    btn_layout->setSpacing(5);

    _btn_open_para    = createToolButton(":/icon/icon/open_file.svg",   "打开参数");
    _btn_save_para    = createToolButton(":/icon/icon/save_file.svg",   "保存参数");
    _btn_print_test   = createToolButton(":/icon/icon/print_file.svg",  "打印测试记录");
    _btn_error_head   = createToolButton(":/icon/icon/start.svg", "开始试验");
    _btn_end_test     = createToolButton(":/icon/icon/stop.svg", "停止实验");
    _btn_fd           = createToolButton(":/icon/icon/chart_fdq.svg", "放大");
    _btn_sx           = createToolButton(":/icon/icon/chart_sxq.svg", "缩小");
    _btn_recover      = createToolButton(":/icon/icon/recover.svg", "还原");


    // 把按钮加到布局中
    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);
    btn_layout->addWidget(_btn_error_head);
    btn_layout->addWidget(_btn_end_test);
    btn_layout->addWidget(_btn_fd);
    btn_layout->addWidget(_btn_sx);
    btn_layout->addWidget(_btn_recover);

    total_layout->addLayout(btn_layout);
    _top_widget->setLayout(total_layout);
    _top_widget->setObjectName("topWidget");
}

REGISTER_TEST(test_13, 12);
