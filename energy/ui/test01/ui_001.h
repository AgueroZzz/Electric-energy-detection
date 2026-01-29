#ifndef UI___1_H
#define UI___1_H

#include <QWidget>
#include <QCheckBox>
#include <QTableWidgetItem>
#include <QButtonGroup>

namespace Ui {
class ui_001;
}

class ui_001 : public QWidget
{
    Q_OBJECT

    friend class test_01;

public:
    explicit ui_001(QWidget *parent = nullptr);
    ~ui_001();

signals:
    void sig_charts_refresh(const QMap<QString ,QList<QVariant>>& map);

private slots:
    void slot_onLeftMode_changed(int id, bool checked);
    void slot_on_tb_cl_changed(QTableWidgetItem* item);
    void slot_ux_mode_changed(int index);

private:
    Ui::ui_001 *ui;

    void init_cl_table();
    void setupVarStep(int row, int colVar, int colStep);
    void setItemState(QTableWidgetItem *item,
                      bool editable,
                      bool green);
    void updateVarStepState(int row, int colVar, int colStep);
    void set_ux_value(QString value, QString phase);
    QPair<QString, QString> calc_ux_value(int index);
    //计算函数
    void calc_uab_value();
    void calc_uo_value();
    void calc_io_value();



    QMap<QString, QList<QVariant>> tb_cl_values;        // UI界面的参量表格数据

    QButtonGroup *leftGroup;   // 手动 / 全自动 / 半自动
    QButtonGroup *rightGroup;  // 递增 / 递减
    QButtonGroup *testTypeGroup;    // 接点动作 / 动作和返回
    QButtonGroup *logicGroup;    // 逻辑与 / 逻辑或
};

#endif // UI___1_H
