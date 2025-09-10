#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(quint16 test_id, QWidget *parent = nullptr);
    ~test();

private:
    // Ui::test *ui;

    quint16 _test_id;
};

#endif // TEST_H
