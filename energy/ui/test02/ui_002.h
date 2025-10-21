#ifndef UI___2_H
#define UI___2_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QCheckBox>
#include "serial/serial_opera.h"

namespace Ui {
class ui_002;
}

class ui_002 : public QWidget
{
    Q_OBJECT

public:
    explicit ui_002(QWidget *parent = nullptr);
    ~ui_002();

    void init_UI();
    void init_table();

    // 工具函数：创建一个带复选框和文字的widget
    inline QWidget* create_cell_widget(const QString& cell_name, QWidget* parent = nullptr){
        QWidget* cell_widget = new QWidget(parent);
        QHBoxLayout* cell_layout= new QHBoxLayout();
        QLabel* label = new QLabel(cell_name);
        cell_layout->addWidget(label);
        cell_widget->setLayout(cell_layout);

        cell_widget->setStyleSheet("QWidget{background-color : #cccccc}");

        return cell_widget;
    }

private:
    Ui::ui_002 *ui;

    serial_opera* _opera;

    QTableWidget* _chart_table_widget;
};

#endif // UI___2_H
