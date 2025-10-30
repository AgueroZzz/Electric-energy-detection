#ifndef UI_CHARTS___2_H
#define UI_CHARTS___2_H

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QBarCategoryAxis>
#include <QVector>

class ui_charts_002 : public QChartView
{
    Q_OBJECT
public:
    explicit ui_charts_002(QWidget *parent = nullptr);
    ~ui_charts_002() override = default;

public slots:
    void slot_update_chart(const QVector<double> &values);

private:
    void init_chart();

    QBarSeries* m_series = nullptr;
    QBarSet* m_setU   = nullptr;   // UA、UB、UC
    QBarSet* m_setI   = nullptr;   // IA、IB、IC

    QValueAxis* m_axisY = nullptr;
};

#endif // UI_CHARTS___2_H
