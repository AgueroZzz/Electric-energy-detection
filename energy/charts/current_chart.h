#ifndef CURRENT_CHART_H
#define CURRENT_CHART_H

#include <QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QBarCategoryAxis>
#include <QVector>

class current_chart : public QChartView
{
    Q_OBJECT
public:
    explicit current_chart(QWidget *parent = nullptr);
    ~current_chart() override = default;

public slots:
    void slot_update_chart(const QVector<double> &values);

private:
    void init_chart();

    QBarSeries* m_series = nullptr;
    QBarSet* m_setU   = nullptr;   // UA、UB、UC
    QBarSet* m_setI   = nullptr;   // IA、IB、IC

    QValueAxis* m_axisY = nullptr;
};

#endif // CURRENT_CHART_H
