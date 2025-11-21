#include "tool_led.h"

tool_led::tool_led(const QString &text, QWidget *parent)
    : QWidget{parent}, _label_text(text)
{
    initUI();
}

void tool_led::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 绘制LED部件
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 计算LED在窗口中的位置
    QPoint ledPos = _led_widget->pos();
    QRect ledRect(ledPos.x(), ledPos.y(), 16, 16);

    // 绘制LED背景（外圆）
    painter.setPen(QPen(Qt::darkGray, 1.5));
    painter.setBrush(Qt::lightGray);
    painter.drawEllipse(ledRect);

    // 根据状态绘制LED内圆
    QRect innerRect = ledRect.adjusted(3, 3, -3, -3);

    if (_state) {
        // 亮起状态 - 使用径向渐变创建发光效果
        QRadialGradient gradient(ledRect.center(), 16 / 2);
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(0.6, _on_color.lighter(150));
        gradient.setColorAt(0.9, _on_color);
        gradient.setColorAt(1, _on_color.darker(150));

        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(innerRect);

        // 添加高光效果
        QRadialGradient highlight(innerRect.topLeft() + QPoint(innerRect.width()/3, innerRect.height()/3),
                                  innerRect.width()/4);
        highlight.setColorAt(0, QColor(255, 255, 255, 180));
        highlight.setColorAt(1, QColor(255, 255, 255, 0));

        painter.setBrush(highlight);
        painter.drawEllipse(innerRect);
    } else {
        // 关闭状态
        QRadialGradient gradient(ledRect.center(), 16 / 2);
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(0.6, _off_color.lighter(120));
        gradient.setColorAt(0.9, _off_color);
        gradient.setColorAt(1, _off_color.darker(120));

        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(innerRect);
    }
}

void tool_led::initUI()
{
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(5, 2, 5, 2);
    layout->setSpacing(10);

    _label = new QLabel(_label_text);
    _label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    _led_widget = new QWidget();
    _led_widget->setCursor(Qt::PointingHandCursor);

    layout->addWidget(_label);
    layout->addWidget(_led_widget);
    layout->addStretch();

    setLayout(layout);
}
