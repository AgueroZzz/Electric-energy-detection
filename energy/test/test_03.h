#ifndef TEST__3_H
#define TEST__3_H

#include "test.h"
#include "ui/test03/ui_003.h"
#include "charts/ac_chart.h"
#include "charts/dc_chart.h"

class test_03 : public test
{
public:
    test_03(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    void init_chart_widget();                   // 初始化图像

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_003* _ui_003;
    QWidget* _status_widget;
    ac_chart* _ac;
    dc_chart* _dc;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_up_para;          // 递增数据
    QToolButton* _btn_down_para;          // 递减数据
    QToolButton* _btn_start_test;       // 开始实验
    QToolButton* _btn_end_test;       // 停止实验
    QToolButton* _btn_reset_test;     // 数据复位
};

#endif // TEST__3_H
