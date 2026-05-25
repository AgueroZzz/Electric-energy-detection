#ifndef UI___3_H
#define UI___3_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QCheckBox>

namespace Ui {
class ui_003;
}

class ui_003 : public QWidget
{
    Q_OBJECT

    friend class test_03;

public:
    explicit ui_003(QWidget *parent = nullptr);
    ~ui_003();

signals:
    void sig_charts_refresh();

private:
    Ui::ui_003 *ui;
    QMap<QString, QList<QVariant>> tb_cl_values;        // UI界面的参量表格数据
    QList<QString> ac_list, dc_list;                    // AC/DC list
    QMap<QString, QList<QVariant>> ac_map;
    QMap<QString, QList<QVariant>> dc_map;

private:
    void init_table();
    void init_first_table();
    void setupVarStep(int row, int colVar, int colStep);
    void updateVarStepState(int row, int colVar, int colStep);
    void updateHzRowVisibility();        // 判断是否全部 DC，并决定是否显示/启用 Hz 行
    void split_ac_dc_map();

private slots:
    void slot_onCellClicked(int row, int col);
    void slot_on_tb_fz_changed(QTableWidgetItem* item);
};

#endif // UI___3_H
