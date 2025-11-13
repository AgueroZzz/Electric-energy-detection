#include "test_04.h"

#include "test/test_factory.h"
#include "ui_ui_004.h"

test_04::test_04(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_widget();

    init_chart_widget();
}

void test_04::init_UI()
{
    _top_widget = new QWidget();
    _ui_004 = new ui_004();

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_ui_004);

    layout->setStretch(0, 1);
    layout->setStretch(1, 9);

    // 设置组件之间的距离
    layout->setSpacing(0);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

void test_04::init_top_widget()
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

    _btn_up_para      = createToolButton(":/icon/icon/up.svg", "单步增1");
    _btn_down_para    = createToolButton(":/icon/icon/down.svg", "单步减1");
    _btn_reset_test   = createToolButton(":/icon/icon/data_recover.svg", "数据复位");
    _btn_start_test   = createToolButton(":/icon/icon/start.svg", "开始实验");
    _btn_end_test     = createToolButton(":/icon/icon/stop.svg", "停止实验");


    // 把按钮加到布局中
    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);
    btn_layout->addWidget(_btn_up_para);
    btn_layout->addWidget(_btn_down_para);
    btn_layout->addWidget(_btn_reset_test);
    btn_layout->addWidget(_btn_start_test);
    btn_layout->addWidget(_btn_end_test);

    total_layout->addLayout(btn_layout);
    _top_widget->setLayout(total_layout);
    _top_widget->setObjectName("topWidget");
}

void test_04::init_chart_widget()
{
    _v = new phasewave_chart("voltage");
    _i = new phasewave_chart("current");
    QHBoxLayout* v_layout = new QHBoxLayout(_ui_004->ui->v_chart);
    v_layout->addWidget(_v);
    QHBoxLayout* i_layout = new QHBoxLayout(_ui_004->ui->i_chart);
    i_layout->addWidget(_i);

    QObject::connect(_ui_004->ui->cb_ua, &QCheckBox::toggled, _v, &phasewave_chart::slot_phase_a_checked);
    QObject::connect(_ui_004->ui->cb_ub, &QCheckBox::toggled, _v, &phasewave_chart::slot_phase_b_checked);
    QObject::connect(_ui_004->ui->cb_uc, &QCheckBox::toggled, _v, &phasewave_chart::slot_phase_c_checked);

    QObject::connect(_ui_004->ui->cb_ia, &QCheckBox::toggled, _i, &phasewave_chart::slot_phase_a_checked);
    QObject::connect(_ui_004->ui->cb_ib, &QCheckBox::toggled, _i, &phasewave_chart::slot_phase_b_checked);
    QObject::connect(_ui_004->ui->cb_ic, &QCheckBox::toggled, _i, &phasewave_chart::slot_phase_c_checked);
}

REGISTER_TEST(test_04, 3);
