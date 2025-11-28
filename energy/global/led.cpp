#include "led.h"

led::led(const QString &name, QWidget *parent)
    : QWidget{parent}, _led_name(name)
{
    initUI();
}

void led::slot_state_changed(bool change_state)
{
    if(change_state != _current_state){
        _current_state = change_state;
        if(_current_state){
            _led_svg->load(_led_on_dir);
        }else{
            _led_svg->load(_led_off_dir);
        }
    }
}

void led::initUI()
{
    QHBoxLayout* _layout = new QHBoxLayout(this);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(2);

    _led_svg = new QSvgWidget(_led_off_dir);
    _led_svg->setFixedSize(24, 24);

    _label = new QLabel(_led_name);
    // _label->setFixedSize(24, 24);
    _label->setStyleSheet("font-size: 18px;");

    _layout->addWidget(_label);
    _layout->addWidget(_led_svg);

    _layout->setAlignment(Qt::AlignCenter);
}
