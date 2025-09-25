#ifndef TEST__1_H
#define TEST__1_H

#include "test.h"
#include "ui/test01/ui_001.h"
#include "ui/test01/ui_charts.h"

class test_01 : public test
{
public:
    test_01(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_btn();                        // 初始化顶部按钮
    void init_middle_widget();                  // 初始化中间widget
    void init_footer_widget();                  // 初始化底部widget
    void init_table();                          // 初始化表格

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    QWidget* _middle_widget;
    QWidget* _footer_widget;
    QWidget* _status_widget;

    // 顶部btn
    QToolButton* _btn_open_para;        // 打开参数按钮
    QToolButton* _btn_save_para;        // 保存参数按钮
    QToolButton* _btn_print_test;       // 打印测试记录
    QToolButton* _btn_power_calcu;      // 功率计算仪表
    QToolButton* _btn_shortout_calcu;   // 短路计算
    QToolButton* _btn_recover_para;     // 恢复默认值
    QToolButton* _btn_up_para;          // 递增数据
    QToolButton* _btn_down_para;          // 递减数据
    QToolButton* _btn_start_test;       // 开始实验
    QToolButton* _btn_end_test;       // 停止实验
    QToolButton* _btn_reset_test;     // 数据复位

    QTableWidget* _chart_table_widget;      // 右侧表格

    QTableWidget* _chart_foot_left_widget;      // 底部左侧表格
    QTableWidget* _chart_foot_middle_widget;      // 底部左侧表格
    QTableWidget* _chart_foot_right_widget;      // 底部左侧表格

    QComboBox* _Ux;
    QTextEdit* _delay_time;

    ui_001* _ui_001;                        // 左侧窗口测试类型ui
    ui_charts* _ui_charts;                  // 中间图表窗口ui
    // 默认单元格数据
    QList<QList<QVariant>> default_data_list;
};

#endif // TEST__1_H
