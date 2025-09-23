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

class CheckBoxHeader : public QHeaderView {
    Q_OBJECT
public:
    explicit CheckBoxHeader(Qt::Orientation orientation, QWidget *parent = nullptr)
        : QHeaderView(orientation, parent) {
        setSectionsClickable(true);
        // 给行头留出空间，避免复选框被文字覆盖
        setDefaultSectionSize(25);
    }

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override {
        // 先画默认的表头背景
        QHeaderView::paintSection(painter, rect, logicalIndex);

        // --- 绘制复选框 ---
        QStyleOptionButton option;
        option.rect = QRect(rect.left() + 2, rect.center().y() - 8, 16, 16);
        option.state = QStyle::State_Enabled;

        if (checkedRows.contains(logicalIndex))
            option.state |= QStyle::State_On;
        else
            option.state |= QStyle::State_Off;

        style()->drawControl(QStyle::CE_CheckBox, &option, painter);

        // --- 绘制文字 ---
        QString text = model()->headerData(logicalIndex, orientation(), Qt::DisplayRole).toString();
        QRect textRect = rect.adjusted(20, 0, -2, 0);  // 给文字留出空间
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);
    }

    void mousePressEvent(QMouseEvent *event) override {
        int row = logicalIndexAt(event->pos());
        if (row >= 0) {
            int y = sectionViewportPosition(row);
            int h = sectionSize(row);
            QRect checkRect(2, y + h/2 - 8, 16, 16);

            if (checkRect.contains(event->pos())) {
                if (checkedRows.contains(row))
                    checkedRows.remove(row);
                else
                    checkedRows.insert(row);

                updateSection(row);
                return; // 阻止文字选择干扰
            }
        }
        QHeaderView::mousePressEvent(event);
    }

private:
    mutable QSet<int> checkedRows; // 记录已勾选行
};

#endif // TEST_H
