#ifndef DC_CHART_H
#define DC_CHART_H

#include <QWidget>
#include <QMap>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QVariant>

// 直流电矢量图
class dc_chart : public QWidget
{
    Q_OBJECT
public:
    explicit dc_chart(const QMap<QString, QList<QVariant>>& initialMap = {},
                      QWidget *parent = nullptr);

    void updateValues(const QMap<QString, QList<QVariant>>& data);

public slots:
    void slot_set_scale();
    void slot_charts_refresh(const QMap<QString ,QList<QVariant>>& map);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    // 存储所有通道的数据
    QMap<QString, QList<QVariant>> _sycs;
    // 通道显示顺序（可以调整顺序）
    QStringList _channelOrder = {"UA", "UB", "UC", "IA", "IB", "IC"};
    // 当前真正要显示的通道（过滤后）
    QStringList _activeChannels;

    // 颜色定义
    QColor colorVoltage{255, 220, 80};      // 电压 - 偏黄色
    QColor colorCurrentPos{120, 220, 120};  // 电流正向 - 绿色
    QColor colorCurrentNeg{220, 100, 100};  // 电流负向 - 红色

    // 动态计算的布局参数（paintEvent 中更新）
    double _zeroX             = 0.0;
    double _maxBarLength      = 0.0;
    double _channelLabelWidth = 0.0;
    double _barHeight         = 0.0;
    double _barSpacing        = 0.0;
    double _yStart            = 0.0;

    // 比例尺
    double _zoomFactor = 1.0;
    const double _zoomStep = 1.35;       // 每次放大 ×1.35
    const double _maxZoom  = 10.0;       // 上限

private:
    void drawBackground(QPainter &p);
    void drawZeroLine(QPainter &p);
    void drawBarsAndValues(QPainter &p);
    void updateActiveChannels();


};

#endif // DC_CHART_H
