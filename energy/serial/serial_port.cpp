#include "serial_port.h"

serial_port::serial_port( QObject *parent)
    : QObject{parent}
{
    this->moveToThread(&_thread);
    QObject::connect(&_thread, &QThread::started, this, &serial_port::slot_thread_start, Qt::DirectConnection);
    QObject::connect(&_thread, &QThread::finished, this, &serial_port::slot_thread_stop, Qt::DirectConnection);
}

void serial_port::set_serial_status(index_serial_status status)
{
    if(_serial_status == status){
        return;
    }
    _serial_status = status;
    emit sig_serial_status_changed(status);
}

void serial_port::slot_serial_opera(index_serial_status status, QStringList deploy)
{
    if(status == index_serial_status::serial_off){
        serial_stop();
    }else if(status == index_serial_status::serial_on){
        serial_start(deploy);
    }
}

void serial_port::slot_thread_start()
{
    _port = new QSerialPort();

    QObject::connect(_port, &QSerialPort::errorOccurred, this, [=](QSerialPort::SerialPortError error){
        set_serial_status(index_serial_status::serial_off);
        if (error == QSerialPort::ResourceError) {
            qCritical() << "严重错误:" << _port->errorString();
        } else if (error != QSerialPort::NoError) {
            qWarning() << "串口错误:" << _port->errorString();
        }
    });
}

void serial_port::slot_thread_stop()
{
    if(_port->isOpen()){
        _port->close();
        _port->deleteLater();
        _port = nullptr;
    }
    _serial_status = index_serial_status::serial_off;
}

void serial_port::slot_send_msg_to_serial(const QByteArray *msg)
{

}

void serial_port::slot_recv_msg_from_serial()
{

}

void serial_port::serial_start(QStringList deploy)
{
    qDebug() << deploy;
    _port->setPortName(deploy[index_serial_deploy::serial_name]);
    _port->setBaudRate(deploy[index_serial_deploy::serial_baudrate].toUInt());
    _port->setParity(static_cast<QSerialPort::Parity>(deploy[index_serial_deploy::serial_parity].toUInt()));
    _port->setDataBits(static_cast<QSerialPort::DataBits>(deploy[index_serial_deploy::serial_data].toUInt()));
    _port->setStopBits(static_cast<QSerialPort::StopBits>(deploy[index_serial_deploy::serial_stop].toUInt()));
    _port->setFlowControl(static_cast<QSerialPort::FlowControl>(deploy[index_serial_deploy::serial_flow].toUInt()));

    if(!_port->open(QIODeviceBase::ReadWrite)){
        set_serial_status(index_serial_status::serial_off);
    }
    set_serial_status(index_serial_status::serial_on);
}

void serial_port::serial_stop()
{
    if(_port->isOpen()){
        _port->close();
    }
    _serial_status = index_serial_status::serial_off;
    return;
}
