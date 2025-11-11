#ifndef VOLTAGE_CHART_H
#define VOLTAGE_CHART_H

#include <QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QBarCategoryAxis>
#include <QVector>

class voltage_chart : public QChartView
{
    Q_OBJECT
public:
    explicit voltage_chart(QWidget *parent = nullptr);

signals:
};

#endif // VOLTAGE_CHART_H
