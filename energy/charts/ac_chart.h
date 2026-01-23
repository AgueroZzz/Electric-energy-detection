#ifndef AC_CHART_H
#define AC_CHART_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QColor>
#include <QMap>
#include <QPainter>
#include <QVariant>

// 交流电矢量图
struct Phasor
{
    double magnitude;   // 幅值（有效值）
    double phase;       // 相位(°)
    QColor color;       // 颜色
    QString label;
    bool visible = true;
};

class ac_chart : public QWidget
{
    Q_OBJECT
public:
    explicit ac_chart(const QMap<QString, QList<QVariant>>& initialMap = {},
                      QWidget *parent = nullptr);

    // 设置所有相量数据
    void setPhasors(const QMap<QString, Phasor>& phasors);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    // 数据更新
    void slot_charts_refresh(const QMap<QString, QList<QVariant>>& map);

    // 控制是否显示同心圆网格
    void slot_setShowGridCircles(bool show);

    // 控制是否显示X/Y坐标轴
    void slot_setShowAxes(bool show);

    // 显示模式切换（0: 相分量, 1: 线电压, 2: 序分量）
    void slot_onModeChanged(int id);

    // 量程
    void slot_onZoomOut();

private:
    QMap<QString, Phasor> _phasors;     // 存储所有相量数据（UA~IC + 派生量）

    double _maxMagnitude = 50.0;
    double _baseScale    = 10.0;
    double _currentScale = 20.0;
    double _minScale     = 10.0;
    const QVector<double> _scaleLevels = {50.0, 40.0, 30.0, 20.0, 10.0};

    bool _showGridCircles = true;       // 是否显示同心圆
    bool _showAxes = true;              // 是否显示坐标轴

    int _mode = 0;  // 当前显示模式：0-相分量, 1-线电压, 2-序分量

    void drawGrid(QPainter& painter, const QRect& rect);
    void drawPhasor(QPainter& painter, const QRect& rect, const Phasor& p, const QPointF& center);

    // 初始化所有相量的默认值（颜色、标签、初始0值）
    void initAllPhasors();

    // 从 map 解析并更新基本相量（UA, UB, UC, IA, IB, IC）
    void parseBasicPhasorsFromMap(const QMap<QString, QList<QVariant>>& map);

    // 计算派生相量（UAB, UBC, UCA, U0, U+, U-, I0, I+, I-）
    void calculateDerivedPhasors();

    // 根据当前 _mode 设置哪些相量可见
    void updateVisiblePhasors();

    // 更新显示（计算最大量程、重绘）
    void updatePhasorDisplay();
};

#endif // AC_CHART_H
