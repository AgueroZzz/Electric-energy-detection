#include "test_24.h"
#include "ui_ui_024.h"
#include "test/test_factory.h"

test_24::test_24(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    _serial_ui = new serial_ui();
    serial_port* serial = new serial_port();
    _serialPort.reset(serial);
    serial->_thread.start();

    QObject::connect(_serial_ui, &serial_ui::sig_serial_opera, serial, &serial_port::slot_serial_opera, Qt::QueuedConnection);
    QObject::connect(serial, &serial_port::sig_serial_status_changed, _serial_ui, &serial_ui::slot_serial_status_changed, Qt::QueuedConnection);

    init_UI();
    init_top_widget();
    init_chart_widget();
    init_state_widget();

    _process_24 = new process_24();
    _process_24->setSerial(serial);
    QObject::connect(_process_24, &process::sig_state_changed, this, [this](QString text, QString color){
        _state_label->setText(text);
        _state_label->setStyleSheet(QString("color:%1; font-weight:bold;").arg(color));
    });

    QObject::connect(_process_24, &process::sig_update_runtime, this, [this](double sec){
        _runtime_second->setText(QString::number(sec, 'f', 2));
    });

    QObject::connect(_process_24, &process::sig_test_finished, this, [this](bool ok, QString reason){
        _btn_start_test->setChecked(false);
        if (!ok) {
            setState(TestState::Error);
            QMessageBox::warning(this, "测试异常", reason);
        } else {
            setState(TestState::Idle);
        }
    });
    // QObject::connect(_process_24, &process_24::sig_frame_parse_result, this, &test_24::slot_frame_parse_result, Qt::DirectConnection);
}

void test_24::init_UI()
{
    _top_widget = new QWidget();
    _ui_024 = new ui_024();
    _state_widget = new QWidget();

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_top_widget);
    layout->addWidget(_ui_024);
    layout->addWidget(_state_widget);

    layout->setStretch(0, 2);
    layout->setStretch(1, 15);
    layout->setStretch(2, 1);
    _state_widget->setMaximumHeight(40);

    // 设置组件之间的距离
    layout->setSpacing(0);
    layout->setContentsMargins(5, 2, 5, 2);

    setLayout(layout);
}

void test_24::init_top_widget()
{
    // 竖排排列
    QVBoxLayout* total_layout = new QVBoxLayout();

    // 第一排按钮横排排列
    QHBoxLayout* btn_layout = new QHBoxLayout();

    _btn_open_para    = createToolButton(":/icon/icon/open_file.svg",   "打开参数");
    _btn_save_para    = createToolButton(":/icon/icon/save_file.svg",   "保存参数");
    _btn_print_test   = createToolButton(":/icon/icon/print_file.svg",  "打印测试记录");
    _btn_serial_opera = createToolButton(":/icon/icon/serial.svg",      "串口操作");
    QObject::connect(_btn_serial_opera, &QToolButton::clicked, this, [=](){
        _serial_ui->raise();
        _serial_ui->show();
    });
    _btn_recover_para = createToolButton(":/icon/icon/recover.svg", "恢复默认值");
    _btn_up_para      = createToolButton(":/icon/icon/up.svg",      "递增数据");
    _btn_down_para    = createToolButton(":/icon/icon/down.svg",    "递减数据");
    _btn_test_group = new QButtonGroup();
    _btn_start_test   = createToolButton(":/icon/icon/start.svg",   "开始实验");
    _btn_start_test->setCheckable(true);
    QObject::connect(this, &test_24::sig_test_start, this, &test_24::slot_test_start, Qt::DirectConnection);
    QObject::connect(this, &test_24::sig_test_stop, this, &test_24::slot_test_stop, Qt::DirectConnection);
    QObject::connect(_btn_start_test, &QPushButton::clicked, this, [=](){
        emit sig_test_start();
    });
    _btn_end_test     = createToolButton(":/icon/icon/stop.svg",    "停止实验");
    QObject::connect(_btn_end_test, &QPushButton::clicked, this, [=](){
        emit sig_test_stop();
    });
    _btn_end_test->setCheckable(true);
    _btn_test_group->addButton(_btn_start_test);
    _btn_test_group->addButton(_btn_end_test);
    // 开始、停止按钮互斥
    _btn_test_group->setExclusive(true);

    // 把按钮加到布局中
    btn_layout->addWidget(_btn_open_para);
    btn_layout->addWidget(_btn_save_para);
    btn_layout->addWidget(_btn_print_test);
    btn_layout->addWidget(_btn_serial_opera);
    btn_layout->addWidget(_btn_recover_para);
    btn_layout->addWidget(_btn_up_para);
    btn_layout->addWidget(_btn_down_para);
    btn_layout->addWidget(_btn_start_test);
    btn_layout->addWidget(_btn_end_test);

    total_layout->addLayout(btn_layout);
    total_layout->setSpacing(2);
    total_layout->setContentsMargins(2, 0, 2, 0);
    _top_widget->setLayout(total_layout);
    _top_widget->setObjectName("topWidget");
    _top_widget->setMaximumHeight(60);
}

void test_24::init_chart_widget()
{
    QVBoxLayout* btn_layout = new QVBoxLayout(_ui_024->ui->btn_widget);
    _chart_btn_fdq = createToolButton(":/icon/icon/chart_fdq.svg", "放大器");
    _chart_btn_x = createToolButton(":/icon/icon/chart_x.svg", "背景X");
    _chart_btn_x->setCheckable(true);
    _chart_btn_x->setChecked(true);
    _chart_btn_o = createToolButton(":/icon/icon/chart_o.svg", "背景圆");
    _chart_btn_o->setCheckable(true);
    _chart_btn_o->setChecked(true);
    QButtonGroup* _group = new QButtonGroup();
    _chart_btn_xfl = createToolButton(":/icon/icon/chart_xiangfl.svg", "相分量");
    _chart_btn_xfl->setCheckable(true);
    _chart_btn_xfl->setChecked(true);
    _chart_btn_xdy = createToolButton(":/icon/icon/chart_xdy.svg", "线电压");
    _chart_btn_xdy->setCheckable(true);
    _chart_btn_xufl = createToolButton(":/icon/icon/chart_xufl.svg", "序分量");
    _chart_btn_xufl->setCheckable(true);
    _group->addButton(_chart_btn_xfl, 0);
    _group->addButton(_chart_btn_xdy, 1);
    _group->addButton(_chart_btn_xufl, 2);
    _group->setExclusive(true);

    btn_layout->addWidget(_chart_btn_fdq);
    btn_layout->addWidget(_chart_btn_x);
    btn_layout->addWidget(_chart_btn_o);
    btn_layout->addWidget(_chart_btn_xfl);
    btn_layout->addWidget(_chart_btn_xdy);
    btn_layout->addWidget(_chart_btn_xufl);

    QHBoxLayout* chart_layout = new QHBoxLayout(_ui_024->ui->chart_widget);
    _voltage = new ac_six_chart(_ui_024->tb_cl_values);
    QObject::connect(_chart_btn_fdq, &QToolButton::clicked, _voltage, &ac_six_chart::slot_onZoomOut);
    QObject::connect(_chart_btn_o, &QToolButton::clicked, _voltage, &ac_six_chart::slot_setShowGridCircles);
    QObject::connect(_chart_btn_x, &QToolButton::clicked, _voltage, &ac_six_chart::slot_setShowAxes);
    QObject::connect(_group, &QButtonGroup::idClicked, _voltage, &ac_six_chart::slot_onModeChanged);
    QObject::connect(_ui_024, &ui_024::sig_charts_refresh, _voltage, &ac_six_chart::slot_charts_refresh);
    chart_layout->addWidget(_voltage);
}

void test_24::init_state_widget()
{
    QHBoxLayout* _state_layout = new QHBoxLayout(_state_widget);
    _state_label = new QLabel("就绪");
    _state_layout->addWidget(_state_label);
    _state_layout->addStretch();
    QLabel* _runtime_first = new QLabel("运行时间(s):");
    _runtime_second = new QLabel("0.00");
    _state_layout->addWidget(_runtime_first);
    _state_layout->addWidget(_runtime_second);
    // 分割线
    QFrame* _frame = new QFrame();
    _frame->setFrameShape(QFrame::VLine);
    _frame->setFrameShadow(QFrame::Sunken);
    _frame->setLineWidth(1);
    _frame->setMidLineWidth(0);
    _state_layout->addWidget(_frame);

    QLabel* _kgl_label = new QLabel("开关量:");
    _state_layout->addWidget(_kgl_label);
    _led_A = new led("A");
    _led_B = new led("B");
    _led_C = new led("C");
    _led_R = new led("R");
    _led_a = new led("a");
    _led_b = new led("b");
    _led_c = new led("c");

    _state_layout->addWidget(_led_A);
    _state_layout->addWidget(_led_B);
    _state_layout->addWidget(_led_C);
    _state_layout->addWidget(_led_R);
    _state_layout->addWidget(_led_a);
    _state_layout->addWidget(_led_b);
    _state_layout->addWidget(_led_c);
}

void test_24::slot_test_start()
{

}

void test_24::slot_test_stop()
{

}

REGISTER_TEST(test_24, 23);
