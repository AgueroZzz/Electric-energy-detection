#ifndef UI_CHARTS_H
#define UI_CHARTS_H

#include <QWidget>
#include <QtCharts/QPolarChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QToolButton>

namespace Ui{
class ui_charts;
}

class ui_charts : public QWidget
{
    Q_OBJECT
public:
    explicit ui_charts(QWidget *parent = nullptr);
    ~ui_charts();

    // 更新电流与电压
    void updateData(qreal Ia, qreal angleIa, qreal Ib, qreal angleIb, qreal Ic, qreal angleIc, qreal Ua, qreal angleUa, qreal Ub, qreal angleUb, qreal Uc, qreal angleUc);

    // 工具函数：创建一个带图标和文字的按钮
    inline QToolButton* createToolButton(const QString &iconPath, const QString &text, QWidget *parent = nullptr) {
        QToolButton* btn = new QToolButton(parent);
        btn->setIcon(QIcon(iconPath));
        btn->setText(text);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setIconSize(QSize(24, 24));
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 自动拉伸
        return btn;
    }

private:
    Ui::ui_charts *ui;
    void initUI();
    void initRadar();       // 初始化雷达图
    void initSeries();      // 初始化 6 个相量
    void initBtn();         // 初始化按钮

    QPolarChart *m_chart;
    QValueAxis *m_radialAxis;
    QValueAxis *m_angularAxis;
    // 三相电流
    QLineSeries *m_seriesIa; QLineSeries *m_seriesIb; QLineSeries *m_seriesIc;
    // 三相电压
    QLineSeries *m_seriesUa; QLineSeries *m_seriesUb; QLineSeries *m_seriesUc;

    QToolButton* _btn_dcsc;
    QToolButton* _btn_fdq;
    QToolButton* _btn_bg_x;
    QToolButton* _btn_bg_o;
    QToolButton* _btn_xfl_1;
    QToolButton* _btn_xdy;
    QToolButton* _btn_xfl_2;

};

#endif // UI_CHARTS_H
