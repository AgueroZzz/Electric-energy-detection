#ifndef UI___1_H
#define UI___1_H

#include <QWidget>
#include <QCheckBox>
#include <QTableWidgetItem>

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

private:
    Ui::ui_001 *ui;

    void init_cl_table();
    void setupVarStep(int row, int colVar, int colStep);
    void setItemState(QTableWidgetItem *item,
                      bool editable,
                      bool green);
    void updateVarStepState(int row, int colVar, int colStep);
};

#endif // UI___1_H
