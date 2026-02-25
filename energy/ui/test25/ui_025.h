#ifndef UI__25_H
#define UI__25_H

#include <QWidget>
#include <QButtonGroup>
#include <QVariant>
#include <QTableWidgetItem>

namespace Ui {
class ui_025;
}

class ui_025 : public QWidget
{
    Q_OBJECT

    friend class test_25;

public:
    explicit ui_025(QWidget *parent = nullptr);
    ~ui_025();

signals:
    void sig_charts_refresh(const QMap<QString ,QList<QVariant>>& map);

private:
    Ui::ui_025 *ui;
    QMap<QString, QList<QVariant>> tb_cl_values;        // UI界面的参量表格数据
    QButtonGroup *leftGroup;   // 接点动作/返回
    QButtonGroup *rightGroup;  // 手动/自动加/自动减

private slots:
    void slot_on_tb_sycs_changed(QTableWidgetItem *item);

private:
    void init_cl_table();
    void calc_down_1();
    void setupVarStep(int row, int colVar, int colStep);
    void updateVarStepState(int row, int colVar, int colStep);
    QMap<QString, QPair<QString,QString>> calcSymmetricalComponents();      // 计算UO等
};

#endif // UI__25_H
