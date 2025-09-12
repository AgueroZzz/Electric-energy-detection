#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

class component : public QObject
{
    Q_OBJECT
public:
    explicit component(QObject *parent = nullptr);

signals:
};

#endif // COMPONENT_H
