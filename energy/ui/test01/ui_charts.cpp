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

    initBtn();
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

    // ✅ 背景深灰
    m_chart->setBackgroundBrush(QBrush(QColor(45, 45, 45)));
    m_chart->setBackgroundPen(Qt::NoPen);

    // ✅ 绘图区浅灰
    m_chart->setPlotAreaBackgroundBrush(QBrush(QColor(70, 70, 70)));
    m_chart->setPlotAreaBackgroundVisible(true);
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

    // ✅ 坐标轴文字颜色
    m_radialAxis->setLabelsColor(Qt::white);
    m_angularAxis->setLabelsColor(Qt::white);

    // ✅ 网格线颜色
    m_radialAxis->setGridLineColor(QColor(120, 120, 120));
    m_angularAxis->setGridLineColor(QColor(120, 120, 120));

    // 图例
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
    m_chart->legend()->setLabelColor(Qt::white);
}

void ui_charts::initSeries()
{
    // 三相电流
    m_seriesIa = new QLineSeries(); m_seriesIa->setName("Ia"); m_seriesIa->setColor(QColor(100,180,255));  // 浅蓝
    m_seriesIb = new QLineSeries(); m_seriesIb->setName("Ib"); m_seriesIb->setColor(QColor(100,255,180));  // 浅绿
    m_seriesIc = new QLineSeries(); m_seriesIc->setName("Ic"); m_seriesIc->setColor(QColor(180,100,255));  // 紫色

    // 三相电压
    m_seriesUa = new QLineSeries(); m_seriesUa->setName("Ua"); m_seriesUa->setColor(QColor(255,200,100));  // 橙黄
    m_seriesUb = new QLineSeries(); m_seriesUb->setName("Ub"); m_seriesUb->setColor(QColor(255,120,120));  // 红
    m_seriesUc = new QLineSeries(); m_seriesUc->setName("Uc"); m_seriesUc->setColor(QColor(120,255,255));  // 青

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
    _btn_dcsc = createToolButton(":/icon/icon/chart_dc.svg", "对称输出");
    _btn_fdq= createToolButton(":/icon/icon/chart_fdq.svg", "放大器");
    _btn_bg_x = createToolButton(":/icon/icon/chart_x.svg", "背景X");
    _btn_bg_o = createToolButton(":/icon/icon/chart_o.svg", "背景圆");
    _btn_xfl_1 = createToolButton(":/icon/icon/chart_xiangfl.svg", "相分量");
    _btn_xdy = createToolButton(":/icon/icon/chart_xdy.svg", "线电压");
    _btn_xfl_2 = createToolButton(":/icon/icon/chart_xufl.svg", "序分量");

    ui->btn_widget_layout->addWidget(_btn_dcsc);
    ui->btn_widget_layout->addWidget(_btn_fdq);
    ui->btn_widget_layout->addWidget(_btn_bg_x);
    ui->btn_widget_layout->addWidget(_btn_bg_o);
    ui->btn_widget_layout->addWidget(_btn_xfl_1);
    ui->btn_widget_layout->addWidget(_btn_xdy);
    ui->btn_widget_layout->addWidget(_btn_xfl_2);
}
