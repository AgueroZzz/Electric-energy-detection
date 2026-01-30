#include "process_1.h"

process_1::process_1(QObject *parent)
    : process{parent}
{
    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &process_1::slot_onTimeout);

    runtimeTimer = new QTimer();
    runtimeTimer->setInterval(100);
    connect(runtimeTimer, &QTimer::timeout, this, &process_1::slot_updateRuntime);
}

void process_1::setSerial(serial_port *serial)
{
    _serial.reset(serial);  // 使用 reset 设置共享指针
    QObject::connect(this, &process_1::sig_send_msg_to_serial, _serial.data(), &serial_port::slot_send_msg_to_serial, Qt::QueuedConnection);
    QObject::connect(_serial.data(), &serial_port::sig_serial_readyRead, this, &process_1::slot_serial_readyRead, Qt::QueuedConnection);
}

void process_1::slot_start(QMap<QString, QList<QVariant> > map, t1_test_type type, t1_logic_type logic, t1_test_auto t_auto, t1_test_auto_tpye t_a_t, QString delay)
{
    if (isRunning()) return;

    _parameter = map;
    _type = type;
    _logic = logic;
    _auto = t_auto;
    _auto_type = t_a_t;
    _delay_time = delay.toUInt();
    QObject::connect(this, &process_1::sig_phase_changed, this, &process_1::slot_phase_changed, Qt::DirectConnection);
    set_TestPhase(TestPhase::Connecting);
}

void process_1::slot_stop()
{
    timeoutTimer->stop();
    runtimeTimer->stop();
    QByteArray frame;
    frame.append(QByteArray::fromHex("0100"));      // 结束
    emit sig_send_msg_to_serial(frame);
    currentPhase = TestPhase::Idle;
    emit sig_state_changed("已停止", "#7f8c8d");
}

void process_1::slot_serial_readyRead()
{
    if(currentPhase != TestPhase::Running){
        return;
    }
    qDebug() << _serial->get_serial_port_data();
    frame_parse(_serial->get_serial_port_data());
}

void process_1::attemptConnect()
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

void process_1::frame_parse(QByteArray frame)
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

void process_1::test_connect_to_device()
{
    connectRetryCount = 0;
    emit sig_state_changed("正在联机", "#e67e22");
    startTimestamp = QDateTime::currentMSecsSinceEpoch();
    runtimeTimer->start();

    attemptConnect();

    return;
}

void process_1::test_send_para_to_device()
{
    QByteArray frame;
    frame.append(QByteArray::fromHex("2202"));      // 字节数+交流实验
    frame.append(QByteArray::fromHex("FF14"));      // 暂时未知
    frame.append(intToLittleEndianHex(int(_parameter["Ux"][index_map::map_value].toFloat() * 250)));        // Ux幅值
    frame.append(intToLittleEndianHex(int(_parameter["Ux"][index_map::map_phase].toFloat())));              // Ux相位
    frame.append(intToLittleEndianHex(int(_parameter["UA"][index_map::map_value].toFloat() * 250)));        // UA幅值
    frame.append(intToLittleEndianHex(int(_parameter["UA"][index_map::map_phase].toFloat())));              // UA相位
    frame.append(intToLittleEndianHex(int(_parameter["UB"][index_map::map_value].toFloat() * 250)));        // UB幅值
    frame.append(intToLittleEndianHex(int(_parameter["UB"][index_map::map_phase].toFloat())));              // UB相位
    frame.append(intToLittleEndianHex(int(_parameter["UC"][index_map::map_value].toFloat() * 250)));        // UC幅值
    frame.append(intToLittleEndianHex(int(_parameter["UC"][index_map::map_phase].toFloat())));              // UC相位
    frame.append(intToLittleEndianHex(int(_parameter["IA"][index_map::map_value].toFloat() * 1066)));        // IA幅值
    frame.append(intToLittleEndianHex(int(_parameter["IA"][index_map::map_phase].toFloat())));              // IA相位
    frame.append(intToLittleEndianHex(int(_parameter["IB"][index_map::map_value].toFloat() * 1066)));        // IB幅值
    frame.append(intToLittleEndianHex(int(_parameter["IB"][index_map::map_phase].toFloat())));              // IB相位
    frame.append(intToLittleEndianHex(int(_parameter["IC"][index_map::map_value].toFloat() * 1066)));        // IC幅值
    frame.append(intToLittleEndianHex(int(_parameter["IC"][index_map::map_phase].toFloat())));              // IC相位
    frame.append(intToLittleEndianHex(int(_parameter["Hz"][index_map::map_value].toFloat() * 100)));              // 频率
    frame.append(QByteArray::fromHex("00"));                                                                // 结束符？

    emit sig_state_changed("测试中", "#e67e22");
    emit sig_send_msg_to_serial(frame);
}

void process_1::slot_onTimeout()
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

void process_1::slot_updateRuntime()
{
    double sec = (QDateTime::currentMSecsSinceEpoch() - startTimestamp) / 1000.0;
    emit sig_update_runtime(sec);
}

void process_1::slot_phase_changed(TestPhase phase)
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
