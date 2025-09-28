#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QDebug>

class serial_port : public QObject
{
    Q_OBJECT
public:
    explicit serial_port(QStringList deploy, QObject *parent = nullptr);

    QThread _thread;

    enum index_deploy{
        s_name = 0,
        s_baudrate,
        s_parity,
        s_databits,
        s_stopbits,
        s_flowcontrol
    };

    // 串口状态
    bool serial_status;

signals:

public slots:
    void slot_thread_start();
    void slot_thread_stop();
    void slot_send_msg_to_serial(const QByteArray* msg);
    void slot_recv_msg_from_serial();

private:
    QSerialPort* _port = nullptr;

    QStringList _deploy;
};

#endif // SERIAL_PORT_H
