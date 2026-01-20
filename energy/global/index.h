#ifndef INDEX_H
#define INDEX_H

// 串口状态索引
enum index_serial_status{
    serial_off = 0,         // 串口关闭
    serial_on = 1           // 串口开启
};

// 串口配置索引
enum index_serial_deploy{
    serial_name = 0,        // 串口名称
    serial_baudrate = 1,    // 串口波特率
    serial_data = 2,        // 串口数据位
    serial_flow = 3,        // 串口流控制
    serial_parity = 4,      // 串口校验位
    serial_stop = 5         // 串口停止位
};

//

#endif // INDEX_H
