#include "test_01.h"

#include "test/test_factory.h"
#include "ui_ui_001.h"

test_01::test_01(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();

    init_top_widget();

    init_chart_widget();

    setWindowTitle("三相交流电压/电流试验");
}

void test_01::init_UI()
{
    _top_widget = new QWidget();
    _ui_001 = new ui_001();

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_ui_001);

    layout->setStretch(0, 1);
    layout->setStretch(1, 9);

    // 设置组件之间的距离
    layout->setSpacing(0);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

void test_01::init_top_widget()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();

    _btn_open_para    = createToolButton(":/icon/icon/open_file.svg",   "打开参数");
    _btn_save_para    = createToolButton(":/icon/icon/save_file.svg",   "保存参数");
    _btn_print_test   = createToolButton(":/icon/icon/print_file.svg",  "打印测试记录");
    _btn_power_calcu  = createToolButton(":/icon/icon/power_calc.svg",     "功率计算仪表");
    _btn_shortout_calcu = createToolButton(":/icon/icon/short_calc.svg","短路计算仪表");
    _btn_recover_para = createToolButton(":/icon/icon/recover.svg", "恢复默认值");
    _btn_up_para      = createToolButton(":/icon/icon/up.svg",      "递增数据");
    _btn_down_para    = createToolButton(":/icon/icon/down.svg",    "递减数据");
    _btn_start_test   = createToolButton(":/icon/icon/start.svg",   "开始实验");
    _btn_end_test     = createToolButton(":/icon/icon/stop.svg",    "停止实验");
    _btn_reset_test   = createToolButton(":/icon/icon/data_recover.svg",    "数据复位");

    // 把按钮加到布局中
    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);
    btn_layout->addWidget(_btn_power_calcu);
    btn_layout->addWidget(_btn_shortout_calcu);
    btn_layout->addWidget(_btn_recover_para);
    btn_layout->addWidget(_btn_up_para);
    btn_layout->addWidget(_btn_down_para);
    btn_layout->addWidget(_btn_start_test);
    btn_layout->addWidget(_btn_end_test);
    btn_layout->addWidget(_btn_reset_test);

    total_layout->addLayout(btn_layout);
    _top_widget->setLayout(total_layout);
    _top_widget->setObjectName("topWidget");
}

void test_01::init_chart_widget()
{
    QVBoxLayout* btn_layout = new QVBoxLayout(_ui_001->ui->btn_widget);
    _chart_btn_dc = createToolButton(":/icon/icon/chart_dc.svg", "对称输出");
    _chart_btn_fdq = createToolButton(":/icon/icon/chart_fdq.svg", "放大器");
    // _chart_btn_fdq->setCheckable(true);
    _chart_btn_x = createToolButton(":/icon/icon/chart_x.svg", "背景X");
    _chart_btn_x->setCheckable(true);
    _chart_btn_o = createToolButton(":/icon/icon/chart_o.svg", "背景圆");
    _chart_btn_o->setCheckable(true);
    QButtonGroup* _group = new QButtonGroup();
    _chart_btn_xfl = createToolButton(":/icon/icon/chart_xiangfl.svg", "相分量");
    _chart_btn_xfl->setCheckable(true);
    _chart_btn_xdy = createToolButton(":/icon/icon/chart_xdy.svg", "线电压");
    _chart_btn_xdy->setCheckable(true);
    _chart_btn_xufl = createToolButton(":/icon/icon/chart_xufl.svg", "序分量");
    _chart_btn_xufl->setCheckable(true);
    _group->addButton(_chart_btn_xfl, 0);
    _group->addButton(_chart_btn_xdy, 1);
    _group->addButton(_chart_btn_xufl, 2);
    _group->setExclusive(true);

    btn_layout->addWidget(_chart_btn_dc);
    btn_layout->addWidget(_chart_btn_fdq);
    btn_layout->addWidget(_chart_btn_x);
    btn_layout->addWidget(_chart_btn_o);
    btn_layout->addWidget(_chart_btn_xfl);
    btn_layout->addWidget(_chart_btn_xdy);
    btn_layout->addWidget(_chart_btn_xufl);

    QHBoxLayout* chart_layout = new QHBoxLayout(_ui_001->ui->chart_widget);
    _voltage = new ac_chart();
    QObject::connect(_chart_btn_fdq, &QToolButton::clicked, _voltage, &ac_chart::slot_onZoomOut);
    QObject::connect(_chart_btn_o, &QToolButton::clicked, _voltage, &ac_chart::slot_setShowGridCircles);
    QObject::connect(_chart_btn_x, &QToolButton::clicked, _voltage, &ac_chart::slot_setShowAxes);
    chart_layout->addWidget(_voltage);
}

REGISTER_TEST(test_01, 0);
