#ifndef TEST__3_H
#define TEST__3_H

#include "test.h"

class test_03 : public test
{
public:
    test_03(quint16 test_id, QWidget *parent = nullptr);

private:
    void init_UI();
};

#endif // TEST__3_H
