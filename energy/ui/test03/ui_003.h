#ifndef UI___3_H
#define UI___3_H

#include <QWidget>
#include "ui/test01/ui_charts.h"
#include "ui/test02/ui_charts_002.h"

namespace Ui {
class ui_003;
}

class ui_003 : public QWidget
{
    Q_OBJECT

public:
    explicit ui_003(QWidget *parent = nullptr);
    ~ui_003();

private:
    Ui::ui_003 *ui;

    ui_charts* _chart_001;
    ui_charts_002* _chart_002;
};

#endif // UI___3_H
