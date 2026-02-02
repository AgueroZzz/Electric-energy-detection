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
    _serial_status = status;
    emit sig_serial_status_changed(status);
}

void serial_port::clear_serial()
{
    if(_port->isOpen()){
        _port->clear();
    }
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

    QObject::connect(_port, &QSerialPort::readyRead, this, &serial_port::slot_readReady, Qt::DirectConnection);
}

void serial_port::slot_thread_stop()
{
    if(_port->isOpen()){
        _port->close();
    }
    _port->deleteLater();
    _port = nullptr;
    _serial_status = index_serial_status::serial_off;
}

void serial_port::slot_send_msg_to_serial(const QByteArray& msg)
{
    if(!_port || !_port->isOpen()){
        qDebug() << "串口未开启";
        return;
    }

    if(msg.isEmpty()){
        qDebug() << "发送数据为空";
        return;
    }

    quint64 bytesWritten = _port->write(msg);

    if (bytesWritten == -1) {
        qWarning() << "发送失败:" << _port->errorString();
    } else if (bytesWritten < msg.size()) {
        qWarning() << "发送不完整，只写了" << bytesWritten << "字节，共" << msg.size();
    } else {
        qDebug() << "已发送:" << msg.size() << "字节 →" << msg.toHex(' ').toUpper();
    }
}

void serial_port::slot_readReady()
{
    if(!_port)
        return;
    _serial_data = _port->readAll();

    if(_serial_data.isEmpty())
        return;
    emit sig_serial_readyRead();
    qDebug() << "收到并覆盖 _serial_data:" << _serial_data.toHex(' ').toUpper();
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
    set_serial_status(index_serial_status::serial_off);
    return;
}
