#include "phasewave_chart.h"

phasewave_chart::phasewave_chart(const QString &type, QWidget *parent)
    : QWidget{parent}
{
    if (type.compare(QLatin1String("voltage"), Qt::CaseInsensitive) == 0) {
        _cfg.amplitude = 14.1;                     // 与截图一致
        _cfg.title     = tr("电压波形图");
        _cfg.yMin      = -16.0;
        _cfg.yMax      =  16.0;
        _cfg.colorA    = Qt::yellow;
        _cfg.colorB    = Qt::green;
        _cfg.colorC    = Qt::red;
    } else { // current
        _cfg.amplitude = 1.4;
        _cfg.title     = tr("电流波形图");
        _cfg.yMin      = -1.6;
        _cfg.yMax      =  1.6;
        _cfg.colorA    = Qt::yellow;
        _cfg.colorB    = Qt::green;
        _cfg.colorC    = Qt::red;
    }

    initUI();

    onPhaseCheckChanged(0,   true);   // A相
    onPhaseCheckChanged(120, true);   // B相
    onPhaseCheckChanged(240, true);   // C相
}

void phasewave_chart::onPhaseCheckChanged(int phaseDeg, bool checked)
{
    QLineSeries *target = nullptr;
    if (phaseDeg == 0)          target = _seriesA;
    else if (phaseDeg == 120)   target = _seriesB;
    else if (phaseDeg == 240)   target = _seriesC;
    else return;

    if (checked) {
        // 生成并填充数据
        QVector<QPointF> data = generateSine(_cfg.amplitude, phaseDeg);
        target->replace(data);
    } else {
        target->clear();               // 隐藏
    }
}

void phasewave_chart::initUI()
{
    _chart = new QChart();
    _chart->legend()->hide();
    _chart->setTitle(_cfg.title);
    _chart->setAnimationOptions(QChart::NoAnimation);

    // ---------- X 轴（0~360°） ----------
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 360);
    axisX->setTitleText(tr("相位 (°"));
    axisX->setLabelFormat("%.0f");
    _chart->addAxis(axisX, Qt::AlignBottom);

    // ---------- Y 轴 ----------
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(_cfg.yMin, _cfg.yMax);
    axisY->setTitleText(tr("幅度"));
    axisY->setLabelFormat("%.1f");
    _chart->addAxis(axisY, Qt::AlignLeft);

    // ---------- 三个相位系列 ----------
    _seriesA = new QLineSeries;  _seriesA->setPen(QPen(_cfg.colorA, 2));
    _seriesB = new QLineSeries;  _seriesB->setPen(QPen(_cfg.colorB, 2));
    _seriesC = new QLineSeries;  _seriesC->setPen(QPen(_cfg.colorC, 2));

    _chart->addSeries(_seriesA);
    _chart->addSeries(_seriesB);
    _chart->addSeries(_seriesC);

    _seriesA->attachAxis(axisX);  _seriesA->attachAxis(axisY);
    _seriesB->attachAxis(axisX);  _seriesB->attachAxis(axisY);
    _seriesC->attachAxis(axisX);  _seriesC->attachAxis(axisY);

    // ---------- ChartView ----------
    _chartView = new QChartView(_chart, this);
    _chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->setContentsMargins(0,0,0,0);
    lay->addWidget(_chartView);
}

QVector<QPointF> phasewave_chart::generateSine(qreal amplitude, qreal phaseDeg, int points) const
{
    QVector<QPointF> vec;
    vec.reserve(points + 1);
    const qreal step = 360.0 / points;
    for (int i = 0; i <= points; ++i) {
        qreal deg = i * step + phaseDeg;
        // 防止越界（360° 与 0° 重合）
        if (deg >= 360.0) deg -= 360.0;
        qreal rad = qDegreesToRadians(deg);
        qreal val = amplitude * qSin(rad);
        vec.append(QPointF(deg, val));
    }
    return vec;
}
