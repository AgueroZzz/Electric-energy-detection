 #include "process_26.h"

process_26::process_26(QObject *parent)
    : process{parent}
{
    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &process_26::slot_onTimeout);

    runtimeTimer = new QTimer();
    runtimeTimer->setInterval(100);
    connect(runtimeTimer, &QTimer::timeout, this, &process_26::slot_updateRuntime);
}

void process_26::setSerial(serial_port *serial)
{
    _serial.reset(serial);  // 使用 reset 设置共享指针
    QObject::connect(this, &process_26::sig_send_msg_to_serial, _serial.data(), &serial_port::slot_send_msg_to_serial, Qt::QueuedConnection);
    QObject::connect(_serial.data(), &serial_port::sig_serial_readyRead, this, &process_26::slot_serial_readyRead, Qt::QueuedConnection);
}

void process_26::slot_start(QMap<QString, QList<QVariant> > map, t26_test_type type, t26_test_auto auto_type, QString delay)
{
    if (isRunning()) return;
    QObject::connect(this, &process_26::sig_phase_changed, this, &process_26::slot_phase_changed, Qt::DirectConnection);
    _parameter = map;
    _type = type;
    _auto_type = auto_type;
    _delay_time = delay.toUInt();
    qDebug() << _delay_time;
    set_TestPhase(TestPhase::Connecting);
}

void process_26::slot_stop()
{

}
