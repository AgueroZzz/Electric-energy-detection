#ifndef UI___4_H
#define UI___4_H

#include <QWidget>
#include <QTreeWidget>
#include <QTableWidget>

namespace Ui {
class ui_004;
}

using harmonicRowData = QPair<qreal, qreal>;
using harmonicMap = QMap<QString, harmonicRowData>;

class ui_004 : public QWidget
{
    Q_OBJECT

    friend class test_04;

public:
    explicit ui_004(QWidget *parent = nullptr);
    ~ui_004();

private slots:
    void slot_itemClicked(QTreeWidgetItem *item, int column);
    // 设置指定通道的谐波数据
    void slot_setHarmonicData(const QString &channel, const harmonicMap &data);
    // 获取指定通道的谐波数据
    harmonicMap slot_getHarmonicData(const QString &channel) const;

private:
    Ui::ui_004 *ui;

    QString _currentChannel;            // 当前显示的通道
    QMap<QString, harmonicMap> m_allData;           // 所有通道数据

    // 存储所有数据：key="UA", value=20个<幅值,相位>
    QMap<QString, QVector<QPair<qreal, qreal>>> _harmonicData;

    void initUI();

    void init_table();

    void updateTableFromMap(const QString &channel);
};

#endif // UI___4_H
