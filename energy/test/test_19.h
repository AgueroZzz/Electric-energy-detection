#ifndef TEST_19_H
#define TEST_19_H

#include "test.h"
#include "ui/test19/ui_019.h"

class test_19 : public test
{
public:
    test_19(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_019* _ui_019;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_error_head;       // 进入故障前状态
    QToolButton* _btn_error_in;         // 开始故障
    QToolButton* _btn_error_recover;    // 故障恢复
    QToolButton* _btn_end_test;         // 停止实验
    QToolButton* _btn_reset_test;     // 数据复位
};

#endif // TEST_19_H
