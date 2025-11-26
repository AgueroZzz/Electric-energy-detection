#ifndef LED_H
#define LED_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSvgWidget>

class led : public QWidget
{
    Q_OBJECT
public:
    explicit led(const QString& name, QWidget *parent = nullptr);

public slots:
    void slot_state_changed(bool change_state);

private:
    QString _led_name;
    QString _led_on_dir = ":/led/led/led_on.svg";
    QString _led_off_dir = ":/led/led/led_off.svg";

    QLabel* _label;
    QSvgWidget* _led_svg;

    bool _current_state = false;

    void initUI();

};

#endif // LED_H
