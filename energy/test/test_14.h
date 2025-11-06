#ifndef TEST_14_H
#define TEST_14_H

#include "test.h"
#include "ui/test14/ui_014.h"

class test_14 : public test
{
public:
    test_14(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_014* _ui_014;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_error_head;       // 进入故障前状态
    QToolButton* _btn_error_in;         // 进入故障状态
    QToolButton* _btn_end_test;         // 停止实验
    QToolButton* _btn_fd;               // 放大
    QToolButton* _btn_sx;               // 缩小
    QToolButton* _btn_recover;          // 还原
};

#endif // TEST_14_H
