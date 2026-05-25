#ifndef TEST__4_H
#define TEST__4_H

#include "test.h"
#include "ui/ui_004.h"
#include "charts/phasewave_chart.h"

// test04:谐波实验

class test_04 : public test
{
public:
    test_04(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();

private:
    ui_004* _ui_004;
    phasewave_chart* _v;
    phasewave_chart* _i;
};

#endif // TEST__4_H
