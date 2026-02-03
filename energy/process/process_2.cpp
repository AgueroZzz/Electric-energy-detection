#include "process_2.h"

process_2::process_2(QObject *parent)
    : process{parent}
{
    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &process_2::slot_onTimeout);

    runtimeTimer = new QTimer();
    runtimeTimer->setInterval(100);
    connect(runtimeTimer, &QTimer::timeout, this, &process_2::slot_updateRuntime);
}

void process_2::setSerial(serial_port *serial)
{
    _serial.reset(serial);  // 使用 reset 设置共享指针
    QObject::connect(this, &process_2::sig_send_msg_to_serial, _serial.data(), &serial_port::slot_send_msg_to_serial, Qt::QueuedConnection);
    QObject::connect(_serial.data(), &serial_port::sig_serial_readyRead, this, &process_2::slot_serial_readyRead, Qt::QueuedConnection);
}

void process_2::slot_start(QMap<QString, QList<QVariant>> map, t2_test_type type, t2_test_auto auto_type, QString delay)
{
    if (isRunning()) return;

    _parameter = map;
    _type = type;
    _auto_type = auto_type;
    _delay_time = delay.toUInt();
    QObject::connect(this, &process_2::sig_phase_changed, this, &process_2::slot_phase_changed, Qt::DirectConnection);
    set_TestPhase(TestPhase::Connecting);
}

void process_2::slot_stop()
{
    timeoutTimer->stop();
    runtimeTimer->stop();
    QByteArray frame;
    frame.append(QByteArray::fromHex("0100"));      // 结束
    emit sig_send_msg_to_serial(frame);
    currentPhase = TestPhase::Idle;
    emit sig_state_changed("已停止", "#7f8c8d");
}

void process_2::slot_serial_readyRead()
{
    if(currentPhase != TestPhase::Running){
        return;
    }
    qDebug() << _serial->get_serial_port_data().toHex();
    frame_parse(_serial->get_serial_port_data());
}

void process_2::slot_phase_changed(TestPhase phase)
{
    if(phase == TestPhase::Idle){
        return;
    }else if(phase == TestPhase::Connecting){
        test_connect_to_device();
    }else if(phase == TestPhase::Running){
        test_send_para_to_device();
    }else if(phase == TestPhase::Finishing){

    }else if(phase == TestPhase::Error){
        return;
    }
}

void process_2::test_connect_to_device()
{
    connectRetryCount = 0;
    emit sig_state_changed("正在联机", "#e67e22");
    startTimestamp = QDateTime::currentMSecsSinceEpoch();
    runtimeTimer->start();

    attemptConnect();

    return;
}

void process_2::test_send_para_to_device()
{
    QByteArray frame;
    frame.append(QByteArray::fromHex("230F"));      // 字节数+直流实验
    frame.append(QByteArray::fromHex("FE14FF"));      // 暂时未知
    frame.append(QByteArray::fromHex("0000"));        // Ux幅值
    frame.append(QByteArray::fromHex("0000"));        // Ux相位
    frame.append(intToLittleEndianHex(int(_parameter["UA"][index_map::map_value].toFloat() * 177)));        // Ua幅值
    frame.append(QByteArray::fromHex("0000"));        // Ua相位
    frame.append(intToLittleEndianHex(int(_parameter["UB"][index_map::map_value].toFloat() * 177)));        // Ub幅值
    frame.append(QByteArray::fromHex("0000"));        // Ub相位
    frame.append(intToLittleEndianHex(int(_parameter["UC"][index_map::map_value].toFloat() * 177)));        // Uc幅值
    frame.append(QByteArray::fromHex("0000"));        // Uc相位
    frame.append(intToLittleEndianHex(int(_parameter["IA"][index_map::map_value].toFloat() * 755)));        // Ia幅值
    frame.append(QByteArray::fromHex("0000"));        // Ia相位
    frame.append(intToLittleEndianHex(int(_parameter["IB"][index_map::map_value].toFloat() * 755)));        // Ib幅值
    frame.append(QByteArray::fromHex("0000"));        // Ib相位
    frame.append(intToLittleEndianHex(int(_parameter["IC"][index_map::map_value].toFloat() * 755)));        // Ic幅值
    frame.append(QByteArray::fromHex("0000"));        // Ic相位
    frame.append(QByteArray::fromHex("8813"));              // 频率:固定？
    frame.append(QByteArray::fromHex("00"));                                                                // 结束符？
    emit sig_state_changed("测试中", "#e67e22");
    emit sig_send_msg_to_serial(frame);
}

void process_2::attemptConnect()
{
    if (connectRetryCount >= MAX_CONNECT_RETRY) {
        currentPhase = TestPhase::Error;
        runtimeTimer->stop();
        emit sig_state_changed("联机失败", "#c0392b");
        emit sig_test_finished(false, "连续3次联机未成功");
        return;
    }

    QByteArray cmd = QByteArray::fromHex("01FF");
    emit sig_send_msg_to_serial(cmd);

    timeoutTimer->start(_delay_time);
}

void process_2::frame_parse(QByteArray frame)
{
    QStringList results;
    quint8 dataCount = quint8(frame[0]);
    if(frame.size() != (dataCount + 1)){
        return;             // 帧长度=数据位+1
    }
    quint8 type = quint8(frame[1]);
    if(type == static_cast<quint8>(FrameType::f_action)){           // 动作帧
        results << "action";
    }else if(type == static_cast<quint8>(FrameType::f_return)){     // 返回帧
        results << "return";
    }else{
        return;             // 非法帧
    }
    quint8 portByte = quint8(frame[2]);
    QString port = parsePort(portByte);
    if (port == "UnKnow") {
        return;             // 未知端口，丢弃
    }
    results << port;
    quint32 actionTimeMs = parseActionTime(frame);
    results << QString::number(actionTimeMs);

    emit sig_frame_parse_result(results);
}

void process_2::slot_onTimeout()
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
