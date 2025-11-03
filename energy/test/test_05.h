#ifndef TEST__5_H
#define TEST__5_H

#include "test.h"
#include "ui/test05/ui_005.h"

class test_05 : public test
{
public:
    test_05(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_005* _ui_005;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_up_para;          // 递增数据
    QToolButton* _btn_down_para;          // 递减数据
    QToolButton* _btn_start_test;       // 开始实验
    QToolButton* _btn_switch_status;     // 切换状态
    QToolButton* _btn_end_test;       // 停止实验
    QToolButton* _btn_history;          // 历史数据
};

#endif // TEST__5_H
