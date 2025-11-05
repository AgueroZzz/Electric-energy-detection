#ifndef UI__11_H
#define UI__11_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class ui_011;
}

class ui_011 : public QWidget
{
    Q_OBJECT

public:
    explicit ui_011(QWidget *parent = nullptr);
    ~ui_011();

private:
    Ui::ui_011 *ui;
};

#endif // UI__11_H
