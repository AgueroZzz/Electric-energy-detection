#ifndef TEST__6_H
#define TEST__6_H

#include "test.h"
#include "ui/test06/ui_006.h"

class test_06 : public test
{
public:
    test_06(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_006* _ui_006;

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

#endif // TEST__6_H
