#include "ui_004.h"
#include "ui_ui_004.h"
#include <QTreeWidgetItem>
#include <QRegularExpression>

ui_004::ui_004(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_004)
{
    ui->setupUi(this);

    initUI();
    init_table();
    initDefaultHarmonicData();

    // 默认显示 UA
    _currentChannel = "UA";
    updateTableFromMap("UA");

    // 表格编辑 → 同步数据
    connect(ui->tb_xbhl, &QTableWidget::itemChanged, this, &ui_004::syncTableToData);
}

ui_004::~ui_004()
{
    delete ui;
}

// ========================================
// 1. 初始化 UI（树：UA→UB→UC→IA→IB→IC）
// ========================================
void ui_004::initUI()
{
    ui->treeWidget->setHeaderHidden(true);

    // 电压组
    QTreeWidgetItem *voltGroup = new QTreeWidgetItem(ui->treeWidget);
    voltGroup->setText(0, tr("电压"));
    voltGroup->setFlags(Qt::ItemIsEnabled);

    // 电流组
    QTreeWidgetItem *currGroup = new QTreeWidgetItem(ui->treeWidget);
    currGroup->setText(0, tr("电流"));
    currGroup->setFlags(Qt::ItemIsEnabled);

    // lambda 创建通道
    auto addChannel = [=](QTreeWidgetItem *parent, const QString &text, const QString &channel) {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setText(0, text);
        item->setData(0, Qt::UserRole, channel);
        item->setCheckState(0, Qt::Unchecked);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        return item;
    };

    // 顺序：UA → UB → UC → IA → IB → IC
    QTreeWidgetItem *ua = addChannel(voltGroup, "UA", "UA");
    QTreeWidgetItem *ub = addChannel(voltGroup, "UB", "UB");
    QTreeWidgetItem *uc = addChannel(voltGroup, "UC", "UC");

    QTreeWidgetItem *ia = addChannel(currGroup, "IA", "IA");
    QTreeWidgetItem *ib = addChannel(currGroup, "IB", "IB");
    QTreeWidgetItem *ic = addChannel(currGroup, "IC", "IC");

    ui->treeWidget->expandAll();

    // 连接信号（避免 lambda 重载）
    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &ui_004::slot_itemClicked);
    connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &ui_004::on_treeWidget_itemChanged);

    // 默认选中 UA
    ua->setCheckState(0, Qt::Checked);
}

// ========================================
// 2. 初始化表格（固定谐波名 + 不可编辑）
// ========================================
void ui_004::init_table()
{
    ui->tb_xbhl->setRowCount(20);
    ui->tb_xbhl->setColumnCount(3);

    for (int row = 0; row < 20; ++row) {
        // 第 0 列：谐波名（不可编辑）
        QTableWidgetItem *nameItem = new QTableWidgetItem(_harmonicKeys[row]);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        ui->tb_xbhl->setItem(row, 0, nameItem);

        // 第 1 列：幅值
        ui->tb_xbhl->setItem(row, 1, new QTableWidgetItem("0.000"));

        // 第 2 列：相位
        ui->tb_xbhl->setItem(row, 2, new QTableWidgetItem("0.0"));
    }

    ui->tb_xbhl->setHorizontalHeaderLabels({tr("谐波"), tr("幅值"), tr("相位")});
    ui->tb_xbhl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_xbhl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 其他表格拉伸
    auto stretch = [](QTableWidget *tbl) {
        tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tbl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    };
    stretch(ui->tb_bhfw);
    stretch(ui->tb_blxz);
    stretch(ui->tb_kglsz);
    stretch(ui->tb_result);
}

// ========================================
// 3. 初始化默认数据（每个通道相位一致）
// ========================================
void ui_004::initDefaultHarmonicData()
{
    auto setChannel = [&](const QString& ch, qreal baseAmp, qreal phase) {
        harmonicMap map;
        for (const QString &k : _harmonicKeys) {
            if(k == "直流"){
                map[k] = {0.000, 0.0};
            }else if(k == "基波"){
                map[k] = {};
            }else{

            }
            qreal amp = (k == _harmonicKeys[0]) ? 0.000 : (k == _harmonicKeys[1] ? baseAmp : 0.000);
            map[k] = {amp, phase};
        }
        _allData[ch] = map;
    };

    setChannel("UA", 10.000,   0.0);
    setChannel("UB", 10.000, -120.0);
    setChannel("UC", 10.000,  120.0);
    setChannel("IA",  1.000,   0.0);
    setChannel("IB",  1.000, -120.0);
    setChannel("IC",  1.000,  120.0);
}

// ========================================
// 4. 数据 → 表格（强制按 m_harmonicKeys 顺序）
// ========================================
void ui_004::updateTableFromMap(const QString &channel)
{
    if (!_allData.contains(channel)) return;

    const harmonicMap &data = _allData[channel];
    bool isVoltage = channel.startsWith('U');

    for (int row = 0; row < 20; ++row) {
        const QString &key = _harmonicKeys[row];
        auto it = data.constFind(key);
        if (it == data.constEnd()) continue;

        qreal amp = it->first;
        qreal phase = it->second;

        ui->tb_xbhl->item(row, 1)->setText(QString("%1 %2")
                                               .arg(amp, 0, 'f', 3));
        ui->tb_xbhl->item(row, 2)->setText(QString("%1°").arg(phase, 0, 'f', 1));
    }

    _currentChannel = channel;
}

// 表格 → 数据
void ui_004::syncTableToData()
{
    if (_currentChannel.isEmpty()) return;

    harmonicMap &data = _allData[_currentChannel];

    for (int row = 0; row < 20; ++row) {
        QTableWidgetItem *nameItem  = ui->tb_xbhl->item(row, 0);
        QTableWidgetItem *ampItem   = ui->tb_xbhl->item(row, 1);
        QTableWidgetItem *phaseItem = ui->tb_xbhl->item(row, 2);

        if (!nameItem || !ampItem || !phaseItem) continue;

        QString key = nameItem->text().trimmed();
        if (key.isEmpty()) continue;

        // 幅值
        QString ampText = ampItem->text();
        bool ok;
        qreal amp = ampText.toDouble(&ok);
        if (!ok) amp = 0.0;

        // 相位
        QString phaseText = phaseItem->text();
        qreal phase = phaseText.toDouble(&ok);
        if (!ok) phase = 0.0;

        data[key] = {amp, phase};
    }
}

void ui_004::slot_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if (item->childCount() > 0) return;

    QString channel = item->data(0, Qt::UserRole).toString();
    if (channel.isEmpty()) return;

    item->setCheckState(0, Qt::Checked);
    _currentChannel = channel;
}

void ui_004::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    if (column != 0 || item->childCount() > 0 || item->checkState(0) != Qt::Checked)
        return;

    auto *root = ui->treeWidget->invisibleRootItem();
    for (int i = 0; i < root->childCount(); ++i) {
        auto *group = root->child(i);
        for (int j = 0; j < group->childCount(); ++j) {
            auto *leaf = group->child(j);
            if (leaf != item) {
                leaf->setCheckState(0, Qt::Unchecked);
            }
        }
    }

    QString ch = item->data(0, Qt::UserRole).toString();
    if (!ch.isEmpty()) {
        _currentChannel = ch;
        updateTableFromMap(ch);
    }
}

void ui_004::slot_setHarmonicData(const QString &channel, const harmonicMap &data)
{
    if (channel.isEmpty() || data.size() != 20) return;
    _allData[channel] = data;
    if (_currentChannel == channel) {
        updateTableFromMap(channel);
    }
}

harmonicMap ui_004::slot_getHarmonicData(const QString &channel) const
{
    return _allData.value(channel);
}
