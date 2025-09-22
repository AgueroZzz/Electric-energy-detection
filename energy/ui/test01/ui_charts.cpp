#include "ui_charts.h"
#include "ui_ui_charts.h"

ui_charts::ui_charts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_charts)
{
    ui->setupUi(this);

    initUI();

    initRadar();

    initSeries();
}

ui_charts::~ui_charts()
{
    delete ui;
}

void ui_charts::updateData(qreal Ia, qreal angleIa, qreal Ib, qreal angleIb, qreal Ic, qreal angleIc, qreal Ua, qreal angleUa, qreal Ub, qreal angleUb, qreal Uc, qreal angleUc)
{
    // IA
    m_seriesIa->clear();
    m_seriesIa->append(angleIa, 0);
    m_seriesIa->append(angleIa, Ia);

    // IB
    m_seriesIb->clear();
    m_seriesIb->append(angleIb, 0);
    m_seriesIb->append(angleIb, Ib);

    // IC
    m_seriesIc->clear();
    m_seriesIc->append(angleIc, 0);
    m_seriesIc->append(angleIc, Ic);

    // UA
    m_seriesUa->clear();
    m_seriesUa->append(angleUa, 0);
    m_seriesUa->append(angleUa, Ua);

    // UB
    m_seriesUb->clear();
    m_seriesUb->append(angleUb, 0);
    m_seriesUb->append(angleUb, Ub);

    // UC
    m_seriesUc->clear();
    m_seriesUc->append(angleUc, 0);
    m_seriesUc->append(angleUc, Uc);
}

void ui_charts::initUI()
{
    ui->all_layout->setStretch(0, 8);
    ui->all_layout->setStretch(1, 2);

    // chartView放到UI中的 charts_widget
    QVBoxLayout *layout = new QVBoxLayout(ui->charts_widget);
    layout->setContentsMargins(0, 0, 0, 0);

    QChartView *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);

    // 创建 chart
    m_chart = new QPolarChart();
    chartView->setChart(m_chart);
}

void ui_charts::initRadar()
{
    // 径向轴（电流/电压幅值）
    m_radialAxis = new QValueAxis();
    m_radialAxis->setRange(0, 100);   // 初始范围，可以后续动态调节
    m_radialAxis->setTickCount(6);
    m_radialAxis->setLabelFormat("%d");
    m_chart->addAxis(m_radialAxis, QPolarChart::PolarOrientationRadial);

    // 角度轴（相角）
    m_angularAxis = new QValueAxis();
    m_angularAxis->setRange(0, 360);
    m_angularAxis->setTickCount(13);   // 每 30°
    m_chart->addAxis(m_angularAxis, QPolarChart::PolarOrientationAngular);

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
}

void ui_charts::initSeries()
{
    // 三相电流
    m_seriesIa = new QLineSeries();
    m_seriesIb = new QLineSeries();
    m_seriesIc = new QLineSeries();

    m_seriesIa->setName("Ia");
    m_seriesIb->setName("Ib");
    m_seriesIc->setName("Ic");

    // 三相电压
    m_seriesUa = new QLineSeries();
    m_seriesUb = new QLineSeries();
    m_seriesUc = new QLineSeries();

    m_seriesUa->setName("Ua");
    m_seriesUb->setName("Ub");
    m_seriesUc->setName("Uc");

    // 加到 chart
    m_chart->addSeries(m_seriesIa);
    m_chart->addSeries(m_seriesIb);
    m_chart->addSeries(m_seriesIc);
    m_chart->addSeries(m_seriesUa);
    m_chart->addSeries(m_seriesUb);
    m_chart->addSeries(m_seriesUc);

    // 绑定坐标轴
    QList<QLineSeries*> allSeries = {m_seriesIa, m_seriesIb, m_seriesIc,
                                      m_seriesUa, m_seriesUb, m_seriesUc};
    for (auto series : allSeries) {
        series->attachAxis(m_radialAxis);
        series->attachAxis(m_angularAxis);

        // 初始点（幅值为0，角度为0）
        series->append(0, 0);
    }
}

void ui_charts::initBtn()
{

}
