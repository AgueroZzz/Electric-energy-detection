#ifndef AC_CHART_H
#define AC_CHART_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QColor>
#include <QMap>
#include <QPainter>

// 交流电矢量图
struct Phasor
{
    double magnitude;   // 幅值
    double phase;       // 相位(°)
    QColor color;       // 颜色
    QString label;
    bool visible = true;
};

class ac_chart : public QWidget
{
    Q_OBJECT
public:
    explicit ac_chart(QWidget *parent = nullptr);

    // 设置所有相量数据
    void setPhasors(const QMap<QString, Phasor>& phasors);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    // 控制是否显示同心圆网格
    void slot_setShowGridCircles(bool show);

    // 控制是否显示X/Y坐标轴
    void slot_setShowAxes(bool show);

    // 显示模式切换
    void slot_onModeChanged(int Id);

    // 数据更新
    void slot_updatePhasorDisplay(const QMap<QString, QPair<double, double>>& data);

    // 量程
    void slot_onZoomOut();

private:
    QMap<QString, Phasor> _phasors;     // 当前所有相量
    double _maxMagnitude = 200.0;
    double _baseScale = 200.0;          // 初始量程
    double _currentScale = 200.0;       // 当前量程
    double _minScale = 100.0;            // 最小量程
    const QVector<double> _scaleLevels = {200.0, 150.0, 100.0};  // 缩小序列
    bool _showGridCircles = true;       // 是否显示同心圆
    bool _showAxes = true;              // 是否显示坐标轴

    void drawGrid(QPainter& painter, const QRect& rect);
    void drawPhasor(QPainter& painter, const QRect& rect, const Phasor& p, const QPointF& center);
    void initUI();

    // 数据初始化
    void initPhasors_Phase();
    void initPhasors_Line();
    void initPhasors_Sequence();

    // 更新
    void updatePhasorDisplay();
};

#endif // AC_CHART_H
