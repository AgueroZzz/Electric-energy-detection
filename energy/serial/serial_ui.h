#ifndef SERIAL_UI_H
#define SERIAL_UI_H

#include <QWidget>
#include <QLabel>
#include <QSerialPortInfo>

namespace Ui {
class serial_ui;
}

class serial_ui : public QWidget
{
    Q_OBJECT

public:
    explicit serial_ui(QWidget *parent = nullptr);
    ~serial_ui();

    void setLed(QLabel* label, int color = 1, int size = 13);

public slots:
    void slot_refresh_port();

private:
    Ui::serial_ui *ui;
};

#endif // SERIAL_UI_H
