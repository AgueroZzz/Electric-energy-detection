#ifndef UI___4_H
#define UI___4_H

#include <QWidget>
#include <QTreeWidget>
#include <QTableWidget>

namespace Ui {
class ui_004;
}

class ui_004 : public QWidget
{
    Q_OBJECT

    friend class test_04;

public:
    explicit ui_004(QWidget *parent = nullptr);
    ~ui_004();

private:
    Ui::ui_004 *ui;

private:
    // 初始化UI界面
    void InitUI();
};

#endif // UI___4_H
