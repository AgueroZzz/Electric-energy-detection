#ifndef DC_CHART_H
#define DC_CHART_H

#include <QWidget>
#include <QMap>
#include <QColor>
#include <QPen>
#include <QPainter>

// 直流电矢量图
class dc_chart : public QWidget
{
    Q_OBJECT
public:
    explicit dc_chart(QWidget *parent = nullptr);

    void setValue(const QMap<QString, double>& values);

signals:

public slots:
    void slot_set_scale();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, double> _values;      // 参数
    // 通道 → 颜色映射（与界面保持一致）
    static const QMap<QString, QColor> CHANNEL_COLOR;
    double _max_values;                 // 上限值
    double _min_values;                 // 下限值
    double _scale;
    int _scaleIndex = 0;
    QList<double> _scale_list = {1.0, 1.5, 2.0, 3.0};

    void drawBar(QPainter &p, const QRect &rect,
                 double value, double maxAbs, const QColor &color);
    void initUI();


};

#endif // DC_CHART_H
