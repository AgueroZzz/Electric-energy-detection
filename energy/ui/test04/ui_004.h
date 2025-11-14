#ifndef UI___4_H
#define UI___4_H

#include <QWidget>
#include <QTreeWidget>
#include <QTableWidget>

namespace Ui {
class ui_004;
}

using harmonicRowData = QPair<qreal, qreal>;           // <幅值, 相位>
using harmonicMap = QMap<QString, harmonicRowData>;    // "基波" -> <10.0, 0.0>

class ui_004 : public QWidget
{
    Q_OBJECT

    friend class test_04;

public:
    explicit ui_004(QWidget *parent = nullptr);
    ~ui_004();

private slots:
    void slot_itemClicked(QTreeWidgetItem *item, int column);
    void slot_setHarmonicData(const QString &channel, const harmonicMap &data);
    harmonicMap slot_getHarmonicData(const QString &channel) const;
    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

private:
    Ui::ui_004 *ui;

    QString _currentChannel;
    QMap<QString, harmonicMap> _allData;
    // 全局统一 key 列表
    QStringList _harmonicKeys = {"直流", "基波", "2次", "3次", "4次", "5次", "6次", "7次", "8次", "9次", "10次",
                                 "11次", "12次", "13次", "14次", "15次", "16次", "17次", "18次", "19次", "20次"};

    void initUI();
    void init_table();
    void initDefaultHarmonicData();
    void updateTableFromMap(const QString &channel);
    void syncTableToData();
};

#endif // UI___4_H
