#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QCheckBox>
#include <QFile>
#include <QLineEdit>
#include <QtCharts/QPolarChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QToolButton>
#include <QHeaderView>
#include <QTableWidget>
#include <QMouseEvent>
#include <QSet>
#include <QPainter>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QButtonGroup>
#include <QMessageBox>
#include <QTimer>
#include <QSharedPointer>

#include "serial/serial_port.h"
#include "serial/serial_ui.h"
#include "global/led.h"

namespace Ui {
class test;
}

enum class TestState{
    Idle,       // 空闲
    Running,    // 运行
    Sttopped,   // 停止
    Error       // 错误
};

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(quint16 test_id, QWidget *parent = nullptr);
    ~test();

    void set_qss();

    // 工具函数：创建一个带图标和文字的按钮
    inline QToolButton* createToolButton(const QString &iconPath, const QString &text, QWidget *parent = nullptr) {
        QToolButton* btn = new QToolButton(parent);
        btn->setIcon(QIcon(iconPath));
        btn->setText(text);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setIconSize(QSize(24, 24));
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 自动拉伸
        btn->setMinimumHeight(55);
        btn->setMaximumHeight(55);
        return btn;
    }

    // 工具函数：创建一个带复选框和文字的widget
    inline QWidget* create_cell_widget(const QString& cell_name, QWidget* parent = nullptr){
        QWidget* cell_widget = new QWidget(parent);
        QHBoxLayout* cell_layout= new QHBoxLayout();
        QCheckBox* check = new QCheckBox();
        QLabel* label = new QLabel(cell_name);
        cell_layout->addWidget(check);
        cell_layout->addWidget(label);
        cell_widget->setLayout(cell_layout);

        cell_widget->setStyleSheet("QWidget{background-color : #cccccc}");

        return cell_widget;
    }

signals:
    void sig_test_start();
    void sig_test_stop();

protected:
    // get/set方法
    TestState getState(){return _state;};
    void setState(TestState state);

private:
    quint16 _test_id;

    TestState _state = TestState::Idle;  // 默认空闲
};

#endif // TEST_H
