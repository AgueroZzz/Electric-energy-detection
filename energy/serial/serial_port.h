#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <QObject>

class serial_port : public QObject
{
    Q_OBJECT
public:
    explicit serial_port(QObject *parent = nullptr);

signals:
};

#endif // SERIAL_PORT_H
