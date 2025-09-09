#ifndef TEST_H
#define TEST_H

// 所有测试基类

#include <QObject>

class test : public QObject
{
    Q_OBJECT
public:
    explicit test(quint16 test_id, QObject *parent = nullptr);

signals:

private:
    quint16 _current_test_id;
};

#endif // TEST_H
