#ifndef PHASEWAVE_CHART_H
#define PHASEWAVE_CHART_H

#include <QWidget>
#include <QMap>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QtMath>
#include <QVBoxLayout>

struct config{
    qreal amplitude;
    QString title;
    qreal yMin, yMax;
    QColor colorA, colorB, colorC;
};

// 电流/电压波形图
class phasewave_chart : public QWidget
{
    Q_OBJECT
public:
    explicit phasewave_chart(const QString &type, QWidget *parent = nullptr);

signals:

public slots:
    void slot_phase_a_checked(bool checked){ onPhaseCheckChanged(0, checked); };
    void slot_phase_b_checked(bool checked){ onPhaseCheckChanged(120, checked); };
    void slot_phase_c_checked(bool checked){ onPhaseCheckChanged(240, checked); };

private slots:
    void onPhaseCheckChanged(int phaseDeg, bool checked);

private:
    QLineSeries* _seriesA;
    QLineSeries* _seriesB;
    QLineSeries* _seriesC;

    QChart* _chart;
    QChartView* _chartView;

    config _cfg;

    void initUI();
    QVector<QPointF> generateSine(qreal amplitude, qreal phaseDeg, int points = 360) const;
};

#endif // PHASEWAVE_CHART_H
