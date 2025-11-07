#ifndef TEST_18_H
#define TEST_18_H

#include "test.h"
#include "ui/test18/ui_018.h"

class test_18 : public test
{
public:
    test_18(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_018* _ui_018;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_error_head;       // 进入故障前状态
    QToolButton* _btn_end_test;         // 停止实验
};

#endif // TEST_18_H
