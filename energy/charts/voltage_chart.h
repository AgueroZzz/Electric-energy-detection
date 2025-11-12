#ifndef VOLTAGE_CHART_H
#define VOLTAGE_CHART_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QColor>
#include <QMap>
#include <QPainter>

// 电压相量图

struct Phasor
{
    double magnitude;   // 幅值
    double phase;       // 相位(°)
    QColor color;       // 颜色
    QString label;
    bool visible = true;
};

class voltage_chart : public QWidget
{
    Q_OBJECT
public:
    explicit voltage_chart(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

public slots:
    // 设置所有相量数据
    void slot_setPhasors(const QMap<QString, Phasor>& phasors);

    // 手动设置最大刻度（用于自动缩放）
    void slot_setMaxScale(double maxValue);

    // 控制是否显示同心圆网格
    void slot_setShowGridCircles(bool show);

    // 控制是否显示X/Y坐标轴
    void slot_setShowAxes(bool show);

    // 放大/缩小所有相量幅值（用于“放大器”功能）
    void slot_multiplyAllMagnitudes(double factor);

private:
    QMap<QString, Phasor> _phasors;     // 当前所有相量
    double _maxMagnitude = 200.0;       // 坐标轴最大刻度（自动调整）
    bool _showGridCircles = true;       // 是否显示同心圆
    bool _showAxes = true;              // 是否显示坐标轴

    void drawGrid(QPainter& painter, const QRect& rect);
    void drawPhasor(QPainter& painter, const QRect& rect, const Phasor& p, const QPointF& center);
};

#endif // VOLTAGE_CHART_H
