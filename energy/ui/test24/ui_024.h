#ifndef UI__24_H
#define UI__24_H

#include <QWidget>
#include <QCheckBox>
#include <QTableWidgetItem>
#include <QButtonGroup>

namespace Ui {
class ui_024;
}

class ui_024 : public QWidget
{
    Q_OBJECT

    friend class test_24;

public:
    explicit ui_024(QWidget *parent = nullptr);
    ~ui_024();

signals:
    void sig_charts_refresh(const QMap<QString ,QList<QVariant>>& map);

private:
    Ui::ui_024 *ui;
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
    QMap<QString, QPair<QString,QString>> calcSixPhaseCurrent();      // 计算IO等
};

#endif // UI__24_H
