#ifndef UI___4_H
#define UI___4_H

#include <QWidget>

namespace Ui {
class ui_004;
}

class ui_004 : public QWidget
{
    Q_OBJECT

public:
    explicit ui_004(QWidget *parent = nullptr);
    ~ui_004();

private:
    Ui::ui_004 *ui;

    void init_table();
};

#endif // UI___4_H
