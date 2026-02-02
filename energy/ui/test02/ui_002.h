#ifndef UI___2_H
#define UI___2_H

#include <QWidget>
#include <QCheckBox>
#include <QVariant>
#include <QButtonGroup>
#include <QTableWidgetItem>

namespace Ui {
class ui_002;
}

class ui_002 : public QWidget
{
    Q_OBJECT

    friend class test_02;

public:
    explicit ui_002(QWidget *parent = nullptr);
    ~ui_002();

signals:
    void sig_charts_refresh(const QMap<QString ,QList<QVariant>>& map);

private:
    Ui::ui_002 *ui;
    QMap<QString, QList<QVariant>> tb_sycs_values;        // UI界面的参量表格数据

    QButtonGroup *leftGroup;   // 手动 / 全自动 / 半自动
    QButtonGroup *rightGroup;  // 递增 / 递减

private:
    void init_tb_sycs();
    void setupVarStep(int row, int colVar, int colStep);
    void updateVarStepState(int row, int colVar, int colStep);
    void calc_uab_bc_ca();

private slots:
    void slot_on_tb_sycs_changed(QTableWidgetItem* item);
};

#endif // UI___2_H
