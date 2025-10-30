#ifndef UI_TABLE___2_H
#define UI_TABLE___2_H

#include <QWidget>

namespace Ui {
class ui_table_002;
}

class ui_table_002 : public QWidget
{
    Q_OBJECT

public:
    explicit ui_table_002(QWidget *parent = nullptr);
    ~ui_table_002();

private:
    Ui::ui_table_002 *ui;
};

#endif // UI_TABLE___2_H
