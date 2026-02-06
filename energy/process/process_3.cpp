#include "process_3.h"

process_3::process_3(QObject *parent)
    : process{parent}
{
    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &process_3::slot_onTimeout);

    runtimeTimer = new QTimer();
    runtimeTimer->setInterval(100);
    connect(runtimeTimer, &QTimer::timeout, this, &process_3::slot_updateRuntime);
}

void process_3::setSerial(serial_port *serial)
{
    _serial.reset(serial);  // 使用 reset 设置共享指针
    QObject::connect(this, &process_3::sig_send_msg_to_serial, _serial.data(), &serial_port::slot_send_msg_to_serial, Qt::QueuedConnection);
    QObject::connect(_serial.data(), &serial_port::sig_serial_readyRead, this, &process_3::slot_serial_readyRead, Qt::QueuedConnection);
}

void process_3::slot_start(QMap<QString, QList<QVariant> > map, t3_test_type type, t3_test_auto auto_type, QString delay)
{
    qDebug() << map;
    if (isRunning()) return;

    _parameter = map;
    _type = type;
    _auto_type = auto_type;
    _delay_time = delay.toUInt();
    QObject::connect(this, &process_3::sig_phase_changed, this, &process_3::slot_phase_changed, Qt::DirectConnection);
    set_TestPhase(TestPhase::Connecting);
}

void process_3::slot_stop()
{
    timeoutTimer->stop();
    runtimeTimer->stop();
    QByteArray frame;
    frame.append(QByteArray::fromHex("0100"));      // 结束
    emit sig_send_msg_to_serial(frame);
    currentPhase = TestPhase::Idle;
    emit sig_state_changed("已停止", "#7f8c8d");
}

void process_3::slot_serial_readyRead()
{
    if(currentPhase != TestPhase::Running){
        return;
    }
    qDebug() << _serial->get_serial_port_data().toHex();
    frame_parse(_serial->get_serial_port_data());
}

void process_3::slot_phase_changed(TestPhase phase)
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

void process_3::test_connect_to_device()
{
    connectRetryCount = 0;
    emit sig_state_changed("正在联机", "#e67e22");
    startTimestamp = QDateTime::currentMSecsSinceEpoch();
    runtimeTimer->start();

    attemptConnect();

    return;
}

void process_3::test_send_para_to_device()
{
    QByteArray frame;
    frame.append(QByteArray::fromHex("220F"));      // 字节数+直流实验
    frame.append(QByteArray::fromHex("F014C8"));      // 暂时未知
    frame.append(intToLittleEndianHex(int(_parameter["UX"][index_map::map_value].toFloat() * 176.8)));      // Ux幅值
    frame.append(intToLittleEndianHex(int(_parameter["UX"][index_map::map_phase].toFloat())));              // Ux相位
    frame.append(create_single_port_frame("UA", _parameter["UA"][index_map::map_e_type].toString()));       // UA幅值+相位
    frame.append(create_single_port_frame("UB", _parameter["UB"][index_map::map_e_type].toString()));       // UB幅值+相位
    frame.append(create_single_port_frame("UC", _parameter["UC"][index_map::map_e_type].toString()));       // UC幅值+相位
    frame.append(create_single_port_frame("IA", _parameter["IA"][index_map::map_e_type].toString()));       // IA幅值+相位
    frame.append(create_single_port_frame("IB", _parameter["IB"][index_map::map_e_type].toString()));       // IB幅值+相位
    frame.append(create_single_port_frame("IC", _parameter["IC"][index_map::map_e_type].toString()));       // IC幅值+相位
    frame.append(intToLittleEndianHex(int(_parameter["HZ"][index_map::map_value].toFloat() * 100)));
    qDebug() << frame;
    emit sig_state_changed("测试中", "#e67e22");
    emit sig_send_msg_to_serial(frame);
}

void process_3::attemptConnect()
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

void process_3::frame_parse(QByteArray frame)
{

}

QByteArray process_3::create_single_port_frame(QString port_name, QString port_type)
{
    QByteArray frame;
    // DC下U的系数为176.8    AC下U的系数为250
    if(port_name.contains("U")){
        if(port_type == "AC"){
            frame.append(intToLittleEndianHex(int(_parameter[port_name][index_map::map_value].toFloat()) * 250));
            frame.append(intToLittleEndianHex(int(_parameter[port_name][index_map::map_phase].toFloat())));
        }else{
            frame.append(intToLittleEndianHex(int(_parameter[port_name][index_map::map_value].toFloat()) * 176.8));
            frame.append(QByteArray::fromHex("0000"));
        }
    }
    // DC下I的系数为755      AC下I的系数为1066.67
    else{
        if(port_type == "AC"){
            frame.append(intToLittleEndianHex(int(_parameter[port_name][index_map::map_value].toFloat()) * 1066.67));
            frame.append(intToLittleEndianHex(int(_parameter[port_name][index_map::map_phase].toFloat())));
        }else{
            frame.append(intToLittleEndianHex(int(_parameter[port_name][index_map::map_value].toFloat()) * 755));
            frame.append(QByteArray::fromHex("0000"));
        }
    }
    return frame;
}

void process_3::slot_onTimeout()
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
