#ifndef TEST_25_H
#define TEST_25_H

#include "test.h"
#include "ui/test25/ui_025.h"



class test_25 : public test
{
public:
    test_25(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_widget();                     // 初始化顶部按钮

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    ui_025* _ui_025;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录

    QToolButton* _btn_error_head;       // 进入故障前状态
    QToolButton* _btn_end_test;         // 停止实验
    QButtonGroup* _btn_test_group;
};

#endif // TEST_25_H
