#include "test.h"

test::test(quint16 test_id, QObject *parent)
    :QObject{parent}, _current_test_id(test_id)
{

}
