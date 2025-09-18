#include "ui_charts.h"
#include "ui_ui_charts.h"

ui_charts::ui_charts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_charts)
{
    ui->setupUi(this);
}

ui_charts::~ui_charts()
{
    delete ui;
}

void ui_charts::initRadar()
{
    // 1. 创建极坐标图
    m_chart = new QPolarChart();
    m_chart->setTitle("三相电压/电流雷达图");

    // 2. 半径轴（数值大小：电压/电流幅值）
    m_radialAxis = new QValueAxis();
    m_radialAxis->setRange(0, 250);     // 例如 0~250
    m_radialAxis->setTickCount(6);
    m_chart->addAxis(m_radialAxis, QPolarChart::PolarOrientationRadial);

    // 3. 角度轴（相角）
    m_angularAxis = new QValueAxis();
    m_angularAxis->setRange(0, 360);
    m_angularAxis->setTickCount(13);   // 每 30°
    m_chart->addAxis(m_angularAxis, QPolarChart::PolarOrientationAngular);

    // 4. 初始化 6 个相量
    initSeries();

    // 5. ChartView
    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}
