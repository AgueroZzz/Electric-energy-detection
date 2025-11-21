#ifndef TOOL_LED_H
#define TOOL_LED_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QColor>
#include <QPainter>
#include <QPen>

class tool_led : public QWidget
{
    Q_OBJECT
public:
    explicit tool_led(const QString& text, QWidget *parent = nullptr);

signals:
    void sig_state_changed(bool state);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString _label_text;
    QLabel* _label;
    QWidget* _led_widget;
    bool _state;
    QColor _on_color;
    QColor _off_color;

    void initUI();
};

#endif // TOOL_LED_H
