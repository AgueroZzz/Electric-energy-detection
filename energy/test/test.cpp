#include "test.h"

test::test(quint16 test_id, QWidget *parent)
    :QWidget(parent), _test_id(test_id)
{

}

test::~test()
{
}

void test::set_qss()
{
    QFile file(":/qss/style.qss");
    if(file.open(QFile::ReadOnly)){
        QString styleSheet = QLatin1String(file.readAll());
        setStyleSheet(styleSheet);
        file.close();
    }
}
