#ifndef TEST__2_H
#define TEST__2_H

#include "test.h"
#include "ui/test02/ui_002.h"
#include "charts/dc_chart.h"

class test_02 : public test
{
public:
    test_02(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    void init_chart_widget();                   // 初始化图像

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_002* _ui_002;
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
    QToolButton* _btn_fdq;              // 放大器
};

#endif // TEST__2_H
