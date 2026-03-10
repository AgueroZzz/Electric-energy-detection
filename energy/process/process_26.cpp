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
    _serial = serial;
    QObject::connect(this, &process_26::sig_send_msg_to_serial,
                     _serial, &serial_port::slot_send_msg_to_serial,
                     Qt::QueuedConnection);
    QObject::connect(_serial, &serial_port::sig_serial_readyRead,
                     this, &process_26::slot_serial_readyRead,
                     Qt::QueuedConnection);
}

void process_26::slot_start(QMap<QString, QList<QVariant> > map, test_type type, test_auto auto_type, QString delay)
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
    set_TestPhase(TestPhase::Idle);
    QObject::disconnect(this, &process_26::sig_phase_changed, this, &process_26::slot_phase_changed);
    timeoutTimer->stop();
    runtimeTimer->stop();
    QByteArray frame;
    frame.append(QByteArray::fromHex("0100"));      // 结束
    emit sig_send_msg_to_serial(frame);
    emit sig_state_changed("已停止", "#7f8c8d");
}

void process_26::slot_serial_readyRead()
{
    if(currentPhase != TestPhase::Running){
        return;
    }
    if(!frame_parse(_serial->get_serial_port_data())){
        set_TestPhase(TestPhase::Error);
        return;
    }

    set_TestPhase(TestPhase::Finishing);
}

void process_26::slot_phase_changed(TestPhase phase)
{
    if(phase == TestPhase::Idle){
        return;
    }else if(phase == TestPhase::Connecting){
        test_connect_to_device();
    }else if(phase == TestPhase::Running){
        test_send_para_to_device();
    }else if(phase == TestPhase::Finishing){
        qDebug() << "测试完成";
        return;
    }else if(phase == TestPhase::Error){
        return;
    }
}

void process_26::test_connect_to_device()
{
    connectRetryCount = 0;
    emit sig_state_changed("正在联机", "#e67e22");
    startTimestamp = QDateTime::currentMSecsSinceEpoch();
    runtimeTimer->start();

    attemptConnect();

    return;
}

void process_26::test_send_para_to_device()
{

}

void process_26::attemptConnect()
{
    if (connectRetryCount >= MAX_CONNECT_RETRY) {
        currentPhase = TestPhase::Error;
        runtimeTimer->stop();
        emit sig_state_changed("联机失败", "#c0392b");
        emit sig_test_finished(false, "连续3次联机未成功");
        return;
    }

    QByteArray cmd = QByteArray::fromHex("01FF");
    _serial->clear_serial();
    emit sig_send_msg_to_serial(cmd);

    timeoutTimer->start(_delay_time);
}

bool process_26::frame_parse(QByteArray frame)
{
    QStringList results;
    quint8 dataCount = quint8(frame[0]);
    if(frame.size() != (dataCount + 1)){
        return false;             // 帧长度=数据位+1
    }
    quint8 type = quint8(frame[1]);
    if(type == static_cast<quint8>(FrameType::f_action)){           // 动作帧
        results << "action";
    }else if(type == static_cast<quint8>(FrameType::f_return)){     // 返回帧
        results << "return";
    }else{
        return false;             // 非法帧
    }
    quint8 portByte = quint8(frame[2]);
    QString port = parsePort(portByte);
    if (port == "UnKnow") {
        return false;             // 未知端口，丢弃
    }
    results << port;
    quint32 actionTimeMs = parseActionTime(frame);
    results << QString::number(actionTimeMs);

    emit sig_frame_parse_result(results);

    return true;
}

void process_26::slot_onTimeout()
{
    _frame = _serial->get_serial_port_data();
    if(_frame == QByteArray::fromHex("AA")){
        timeoutTimer->stop();
        set_TestPhase(TestPhase::Running);
        emit sig_state_changed("联机成功", "#27ae60");
        return;
    }
    connectRetryCount++;
    _serial->clear_serial();
    attemptConnect();
}
