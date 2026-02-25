#ifndef AC_I_SIX_CHART_H
#define AC_I_SIX_CHART_H

#include <QWidget>
#include <QPainter>
#include <QMap>
#include <QVariant>
#include <QVector>
#include <complex>

struct Phasor
{
    double magnitude = 0.0;     // 幅值（有效值）
    double phase = 0.0;         // 相位(°)
    QColor color;
    QString label;
    bool visible = false;
};

class ac_six_chart : public QWidget
{
    Q_OBJECT
public:
    explicit ac_six_chart(const QMap<QString, QList<QVariant>>& initialMap = {},
                                  QWidget *parent = nullptr);

    // 手动设置所有相量（一般不直接调用）
    void setPhasors(const QMap<QString, Phasor>& phasors);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    // 数据刷新槽函数（最常用）
    void slot_charts_refresh(const QMap<QString, QList<QVariant>>& map);

    // 显示同心圆网格
    void slot_setShowGridCircles(bool show);

    // 显示X/Y坐标轴
    void slot_setShowAxes(bool show);

    // 模式切换：0=相电流，1=线电流，2=序分量
    void slot_onModeChanged(int mode);

    // 缩小比例尺（放大图形）
    void slot_onZoomOut();

private:
    // 所有支持的电流相量
    QMap<QString, Phasor> _phasors;

    // 显示控制
    double _maxMagnitude = 50.0;           // 当前显示的最大刻度值
    double _currentScale = 5.0;           // 用户选择的基准量程
    const QVector<double> _scaleLevels {50, 25, 15, 10, 5};

    bool _showGridCircles = true;
    bool _showAxes = true;

    int _mode = 0;   // 0:相电流  1:线电流  2:序分量

private:
    void initAllPhasors();

    // 从输入map解析 IA/IB/IC / Ia/Ib/Ic / I0/I+/I-/Io/i+/i-
    void parsePhasorsFromMap(const QMap<QString, QList<QVariant>>& map);

    // 计算派生量
    void calculateDerivedPhasors();

    // 根据当前模式设置哪些相量可见
    void updateVisiblePhasors();

    // 更新显示范围并重绘
    void updateDisplay();

    void drawGrid(QPainter& painter, const QRect& drawRect);
    void drawPhasor(QPainter& painter, const QRect& drawRect,
                    const Phasor& p, const QPointF& center);

    // 辅助：字符串标准化（处理大小写、0/零 等）
    QString normalizeKey(const QString& key) const;
};

#endif // AC_I_SIX_CHART_H
