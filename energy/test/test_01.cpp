#include "test_01.h"

test_01::test_01(quint16 test_id, QWidget *parent)
    : test(test_id, parent)
{
    init_UI();
}

void test_01::init_UI()
{
    setStyleSheet("background-color: red;");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("Test_01 Widget", this);
    label->setStyleSheet("font-size: 20px; color: white;");
    layout->addWidget(label);
    qDebug() << "test_01 init_UI completed";
}
