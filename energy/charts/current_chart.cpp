#include "current_chart.h"

current_chart::current_chart(QWidget *parent)
    :QChartView(new QChart(), parent)
{
    setRenderHint(QPainter::Antialiasing);
    init_chart();
}

void current_chart::slot_update_chart(const QVector<double> &values)
{
    if (values.size() != 6) {
        qWarning() << "BarChartWidget::updateChart 需要 6 个数值，实际收到"
                   << values.size();
        return;
    }

    // 前 3 个是电压 UA、UB、UC
    for (int i = 0; i < 3; ++i)
        m_setU->replace(i, values[i]);

    // 后 3 个是电流 IA、IB、IC
    for (int i = 0; i < 3; ++i)
        m_setI->replace(i, values[i + 3]);

    // 自动调节 Y 轴范围（可选）
    double maxAbs = 0;
    for (double v : values)
        maxAbs = qMax(maxAbs, qAbs(v));

    const double margin = maxAbs * 0.1;   // 上下留 10% 余量
    m_axisY->setRange(-maxAbs - margin, maxAbs + margin);
}

void current_chart::init_chart()
{
    // ---------- 1. 创建两个 BarSet ----------
    m_setU = new QBarSet("电压 (U)");
    m_setI = new QBarSet("电流 (I)");

    // 初始值全为 0
    *m_setU << 0 << 0 << 0;
    *m_setI << 0 << 0 << 0;

    // ---------- 2. BarSeries ----------
    m_series = new QBarSeries(this);
    m_series->append(m_setU);
    m_series->append(m_setI);

    // ---------- 3. Chart ----------
    QChart *chart = this->chart();
    chart->addSeries(m_series);
    chart->setTitle("UA/UB/UC   IA/IB/IC 实时柱状图");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // ---------- 4. X 轴（类别） ----------
    QStringList categories = {"A相", "B相", "C相"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis(this);
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);

    // ---------- 5. Y 轴 ----------
    m_axisY = new QValueAxis(this);
    m_axisY->setRange(-500, 500);
    m_axisY->setTitleText("数值");
    chart->addAxis(m_axisY, Qt::AlignLeft);
    m_series->attachAxis(m_axisY);

    // ---------- 6. 图例 ----------
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}
