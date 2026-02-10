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

private slots:
    void slot_on_tb_sycs_changed(QTableWidgetItem *item);

private:
    void init_cl_table();
    void setupVarStep(int row, int colVar, int colStep);
    void updateVarStepState(int row, int colVar, int colStep);
};

#endif // UI__24_H
