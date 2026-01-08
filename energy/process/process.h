#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>

// 测试过程父类

class process : public QObject
{
    Q_OBJECT
public:
    explicit process(QObject *parent = nullptr);

signals:
};

#endif // PROCESS_H
