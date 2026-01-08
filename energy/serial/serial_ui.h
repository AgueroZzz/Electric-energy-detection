#ifndef SERIAL_UI_H
#define SERIAL_UI_H

#include <QWidget>
#include <QLabel>
#include <QSerialPortInfo>
#include "global/index.h"

namespace Ui {
class serial_ui;
}

class serial_ui : public QWidget
{
    Q_OBJECT

public:
    explicit serial_ui(QWidget *parent = nullptr);
    ~serial_ui();

    void setLed(QLabel* label, index_serial_status status = index_serial_status::serial_off, int size = 13);

public slots:
    void slot_refresh_port();
    void slot_serial_status_changed(index_serial_status status);

signals:
    void sig_serial_opera(index_serial_status status, QStringList deploy = QStringList());

private:
    Ui::serial_ui *ui;

    inline QString index_parity_change(QString parity){
        if(parity == "NONE"){
            return QString::number(0);
        }else if(parity == "ODD"){
            return QString::number(3);
        }else if(parity == "EVEN"){
            return QString::number(2);
        }else if(parity == "MARK"){
            return QString::number(5);
        }else if(parity == "SPACE"){
            return QString::number(4);
        }
        return QString::number(-1);
    }

    inline QString index_stop_change(QString stop){
        if(stop == "1"){
            return QString::number(1);
        }else if(stop == "1.5"){
            return QString::number(3);
        }else if(stop == "2"){
            return QString::number(2);
        }
        return QString::number(-1);
    }
};

#endif // SERIAL_UI_H
