#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QDebug>
#include "global/index.h"

class serial_port : public QObject
{
    Q_OBJECT
public:
    explicit serial_port(QObject *parent = nullptr);

    QThread _thread;

    index_serial_status _serial_status = index_serial_status::serial_off;   // 线程启动时默认串口关闭

    void set_serial_status(index_serial_status status);

signals:
    void sig_serial_status_changed(index_serial_status status);

public slots:
    void slot_serial_opera(index_serial_status status, QStringList deploy);
    void slot_thread_start();
    void slot_thread_stop();
    void slot_send_msg_to_serial(const QByteArray* msg);
    void slot_recv_msg_from_serial();

private:
    QSerialPort* _port = nullptr;

    void serial_start(QStringList deploy);
    void serial_stop();
};

#endif // SERIAL_PORT_H
