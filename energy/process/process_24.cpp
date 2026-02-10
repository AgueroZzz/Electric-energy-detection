#include "process_24.h"

process_24::process_24(QObject *parent)
    : process{parent}
{}

void process_24::setSerial(serial_port *serial)
{
    _serial.reset(serial);  // 使用 reset 设置共享指针
    QObject::connect(this, &process_24::sig_send_msg_to_serial, _serial.data(), &serial_port::slot_send_msg_to_serial, Qt::QueuedConnection);
    QObject::connect(_serial.data(), &serial_port::sig_serial_readyRead, this, &process_24::slot_serial_readyRead, Qt::QueuedConnection);
}

void process_24::slot_start(QMap<QString, QList<QVariant> > map, t24_test_type type, t24_test_auto auto_type, QString delay)
{

}

void process_24::slot_stop()
{

}

void process_24::slot_serial_readyRead()
{

}

void process_24::slot_phase_changed(TestPhase phase)
{

}

void process_24::slot_onTimeout()
{

}
