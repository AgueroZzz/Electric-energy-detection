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

namespace Ui {
class test;
}

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
        return btn;
    }

private:
    quint16 _test_id;
};

#endif // TEST_H
