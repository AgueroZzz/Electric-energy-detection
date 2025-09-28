#ifndef TEST__2_H
#define TEST__2_H

#include "test.h"

class test_02 : public test
{
public:
    test_02(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI() override;

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    QWidget* _middle_widget;
    QWidget* _footer_widget;
    QWidget* _status_widget;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_up_para;          // 递增数据
    QToolButton* _btn_down_para;          // 递减数据
    QToolButton* _btn_start_test;       // 开始实验
    QToolButton* _btn_end_test;       // 停止实验
    QToolButton* _btn_reset_test;     // 数据复位
    QToolButton* _btn_;
};

#endif // TEST__2_H
