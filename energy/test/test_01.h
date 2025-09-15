#ifndef TEST__1_H
#define TEST__1_H

#include "test.h"

class test_01 : public test
{
public:
    test_01(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

    void init_top_btn();
    void init_middle_widget();

    // 顶部/中部/底部Widget
    QWidget* _top_widget;
    QWidget* _middle_widget;
    QWidget* _footer_widget;
};

#endif // TEST__1_H
