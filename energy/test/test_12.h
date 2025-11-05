#ifndef TEST_12_H
#define TEST_12_H

#include "test.h"
#include "ui/test12/ui_012.h"

class test_12 : public test
{
public:
    test_12(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_012* _ui_012;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_error_head;       // 进入故障前状态
    QToolButton* _btn_error_in;         // 进入故障状态
    QToolButton* _btn_end_test;         // 停止实验
    QToolButton* _btn_vector;           // 矢量图
};

#endif // TEST_12_H
