#include "ui_004.h"
#include "ui_ui_004.h"

ui_004::ui_004(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_004)
{
    ui->setupUi(this);

    initUI();

    init_table();
}

ui_004::~ui_004()
{
    delete ui;
}

void ui_004::slot_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    // 只响应叶子节点（UA/UB...）
    if (item->childCount() > 0) return;

    QString channel = item->data(0, Qt::UserRole).toString();
    if (!channel.isEmpty()) {
        // updateTable(channel);
    }
}

void ui_004::slot_setHarmonicData(const QString &channel, const harmonicMap &data)
{
    if (channel.isEmpty() || data.size() != 20) return;

    m_allData[channel] = data;

    // 如果当前显示的就是这个通道，立即刷新表格
    if (_currentChannel == channel) {
        updateTableFromMap(channel);
    }
}

harmonicMap ui_004::slot_getHarmonicData(const QString &channel) const
{

}

void ui_004::initUI()
{
    ui->treeWidget->setHeaderHidden(true);

    // 电压组
    QTreeWidgetItem *voltGroup = new QTreeWidgetItem(ui->treeWidget);
    voltGroup->setText(0, tr("电压"));
    // voltGroup->setIcon(0, QIcon(":/icons/voltage.png")); // 可选图标

    QTreeWidgetItem *ua = new QTreeWidgetItem(voltGroup);
    ua->setText(0, "UA");
    ua->setData(0, Qt::UserRole, "UA");
    // ua->setIcon(0, QIcon(":/icons/yellow.png"));

    QTreeWidgetItem *ub = new QTreeWidgetItem(voltGroup);
    ub->setText(0, "UB");
    ub->setData(0, Qt::UserRole, "UB");
    // ub->setIcon(0, QIcon(":/icons/green.png"));

    QTreeWidgetItem *uc = new QTreeWidgetItem(voltGroup);
    uc->setText(0, "UC");
    uc->setData(0, Qt::UserRole, "UC");
    // uc->setIcon(0, QIcon(":/icons/red.png"));

    // 电流组
    QTreeWidgetItem *currGroup = new QTreeWidgetItem(ui->treeWidget);
    currGroup->setText(0, tr("电流"));
    // currGroup->setIcon(0, QIcon(":/icons/current.png"));

    QTreeWidgetItem *ia = new QTreeWidgetItem(currGroup);
    ia->setText(0, "IA");
    ia->setData(0, Qt::UserRole, "IA");
    // ia->setIcon(0, QIcon(":/icons/yellow.png"));

    QTreeWidgetItem *ib = new QTreeWidgetItem(currGroup);
    ib->setText(0, "IB");
    ib->setData(0, Qt::UserRole, "IB");
    // ib->setIcon(0, QIcon(":/icons/green.png"));

    QTreeWidgetItem *ic = new QTreeWidgetItem(currGroup);
    ic->setText(0, "IC");
    ic->setData(0, Qt::UserRole, "IC");
    // ic->setIcon(0, QIcon(":/icons/red.png"));

    ui->treeWidget->expandAll();

    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &ui_004::slot_itemClicked);
}

void ui_004::init_table()
{
    for (int i = 0; i < 20; ++i) {
        ui->tb_xbhl->setItem(i, 0, new QTableWidgetItem());
        ui->tb_xbhl->setItem(i, 1, new QTableWidgetItem("0.000 V"));
        ui->tb_xbhl->setItem(i, 2, new QTableWidgetItem("0.0°"));
    }

    ui->tb_xbhl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_xbhl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_bhfw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_bhfw->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_blxz->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_blxz->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_kglsz->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kglsz->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void ui_004::updateTableFromMap(const QString &channel)
{
    const harmonicMap &data = m_allData[channel];
    bool isVoltage = channel.startsWith('U');

    int row = 0;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        const QString &key = it.key();
        qreal amp = it.value().first;
        qreal phase = it.value().second;

        ui->tb_xbhl->item(row, 0)->setText(key);
        ui->tb_xbhl->item(row, 1)->setText(QString("%1 %2")
                                           .arg(amp, 0, 'f', 3)
                                           .arg(isVoltage ? "V" : "A"));
        ui->tb_xbhl->item(row, 2)->setText(QString("%1°").arg(phase, 0, 'f', 1));
        ++row;
    }
}
