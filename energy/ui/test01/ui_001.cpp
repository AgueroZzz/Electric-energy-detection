#include "ui_001.h"
#include "ui_ui_001.h"
#include "global/utils.h"

constexpr int COL_VAR1  = 2;
constexpr int COL_STEP1 = 3;

constexpr int COL_VAR2  = 6;
constexpr int COL_STEP2 = 7;

constexpr int ROW_UX = 6;   // Ux 行

ui_001::ui_001(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_001)
{
    ui->setupUi(this);

    ui->tb_cl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_cl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_1->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tb_down_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tb_down_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 实现按钮互斥
    leftGroup = new QButtonGroup(this);
    leftGroup->addButton(ui->rb_hand, 0);   // 手动
    leftGroup->addButton(ui->rb_auto, 1);   // 全自动
    leftGroup->addButton(ui->rb_h_auto, 2);   // 半自动

    rightGroup = new QButtonGroup(this);
    rightGroup->addButton(ui->rb_up,   0);  // 递增
    rightGroup->addButton(ui->rb_down, 1);  // 递减

    connect(leftGroup, &QButtonGroup::idToggled, this, &ui_001::slot_onLeftMode_changed);

    ui->rb_hand->setChecked(true);
    slot_onLeftMode_changed(0, true);

    // 测试类型互斥按钮
    testTypeGroup = new QButtonGroup(this);
    testTypeGroup->addButton(ui->rb_action, 0);     // 测接点动作
    testTypeGroup->addButton(ui->rb_action_return, 1);      // 接点动作和返回
    ui->rb_action->setChecked(true);

    // 开入量逻辑
    logicGroup = new QButtonGroup(this);
    logicGroup->addButton(ui->rb_and, 0);       // 逻辑与
    logicGroup->addButton(ui->rb_or, 1);        // 逻辑或
    ui->rb_and->setChecked(true);

    ui->rb_up->setChecked(true);

    init_cl_table();
    GlobalUtils::get_table_values(*ui->tb_cl, tb_cl_values);
    calc_uab_value();
    calc_uo_value();
    calc_io_value();
    QObject::connect(ui->tb_cl, &QTableWidget::itemChanged, this, &ui_001::slot_on_tb_cl_changed);
    QObject::connect(ui->cb_ux, &QComboBox::currentIndexChanged, this, &ui_001::slot_ux_mode_changed);
}

ui_001::~ui_001()
{
    delete ui;
}

void ui_001::slot_onLeftMode_changed(int id, bool checked)
{
    // 只在被选中（checked == true）时处理
    if (!checked) return;

    bool enableRight = (id == 1 || id == 2);  // 全自动 或 半自动 才启用右边

    // 启用/禁用右边两个单选按钮
    ui->rb_up->setEnabled(enableRight);
    ui->rb_down->setEnabled(enableRight);
}

void ui_001::slot_on_tb_cl_changed(QTableWidgetItem *item)
{
    if (!item)
        return;

    const int row = item->row();
    const int col = item->column();

    const bool isValueCol  = (col == 1 || col == 3);
    const bool isPhaseCol  = (col == 5 || col == 7);
    const bool needFormat = isValueCol || isPhaseCol;

    if (!needFormat)
        return;

    const int decimals = isValueCol ? 3 : 1;
    QString originalText = item->text();
    QString formattedText = GlobalUtils::formatDoubleString(originalText, decimals);

    // 文本没变化，直接退出
    if (formattedText == originalText)
        return;

    {
        QSignalBlocker blocker(ui->tb_cl);
        item->setText(formattedText);
    }
    GlobalUtils::get_table_values(*ui->tb_cl, tb_cl_values);

    // 有效值列（1）或 相位列（5）改变才刷新
    if (col == 1 || col == 5) {
        emit sig_charts_refresh(tb_cl_values);

        // 电压
        if (row >= 0 && row <= 2) {
            auto value_pair = calc_ux_value(ui->cb_ux->currentIndex());
            set_ux_value(value_pair.first, value_pair.second);

            calc_uab_value();   // UAB / UBC / UCA
            calc_uo_value();    // Uo / U+ / U-
        }

        // 电流
        else if (row >= 3 && row <= 5) {
            calc_io_value();    // Io / I+ / I-
        }
    }
}

void ui_001::slot_ux_mode_changed(int index)
{
    int row = 6;            // Ux所在行
    if(index == 0){
        for (int col = 0; col < ui->tb_cl->columnCount(); ++col) {
            // 获取或创建item
            QTableWidgetItem *item = ui->tb_cl->item(row, col);
            if(col == 3 || col == 7){
                GlobalUtils::setItemState(item, false, true);
                continue;
            }
            GlobalUtils::setItemState(item, true, false);
        }
        for (int col = 0; col < ui->tb_cl->columnCount(); ++col) {
            // 获取或创建item
            QTableWidgetItem *item = ui->tb_cl->item(row, col);
            if(col == 1){item->setText("10.000");}
            else if(col == 4){item->setText("120");}
            else if(col == 5){item->setText("0.0");}
        }
        return;
    }else{
        for (int col = 0; col < ui->tb_cl->columnCount(); ++col) {
            // 获取或创建item
            QTableWidgetItem *item = ui->tb_cl->item(row, col);
            // 设置为不可编辑
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            // 设置背景色和填充模式
            item->setBackground(QBrush(QColor("#c2edc3"), Qt::Dense4Pattern));
        }
    }
    auto value_pair = calc_ux_value(index);
    set_ux_value(value_pair.first, value_pair.second);
    return;
}

void ui_001::init_cl_table()
{
    int rows = ui->tb_cl->rowCount();
    for (int row = 0; row < rows; ++row) {
        setupVarStep(row, COL_VAR1, COL_STEP1);
        if(row == 7){
            return;
        }
        setupVarStep(row, COL_VAR2, COL_STEP2);
    }
}

void ui_001::setupVarStep(int row, int colVar, int colStep)
{
    QCheckBox *cb = new QCheckBox();

    QWidget *w = new QWidget();
    QHBoxLayout *l = new QHBoxLayout(w);
    l->addWidget(cb);
    l->setAlignment(Qt::AlignCenter);
    l->setContentsMargins(0,0,0,0);
    ui->tb_cl->setCellWidget(row, colVar, w);
    QTableWidgetItem *stepItem = ui->tb_cl->item(row, colStep);
    if (!stepItem) {
        stepItem = new QTableWidgetItem();
        ui->tb_cl->setItem(row, colStep, stepItem);
    }

    // 初始状态
    updateVarStepState(row, colVar, colStep);

    connect(cb, &QCheckBox::stateChanged, this, [=](int){
        updateVarStepState(row, colVar, colStep);
    });
}

void ui_001::updateVarStepState(int row, int colVar, int colStep)
{
    QTableWidgetItem *stepItem = ui->tb_cl->item(row, colStep);

    QWidget *w = ui->tb_cl->cellWidget(row, colVar);
    QCheckBox *cb = w ? w->findChild<QCheckBox *>() : nullptr;
    bool checked = cb && cb->isChecked();
    if (row == ROW_UX && ui->cb_ux->currentIndex() != 0) {
        // 强制锁死
        GlobalUtils::setItemState(stepItem, false, true);
        return;
    }
    if (checked) {
        GlobalUtils::setItemState(stepItem, true, false);
    } else {
        GlobalUtils::setItemState(stepItem, false, true);
    }
}

void ui_001::set_ux_value(QString value, QString phase)
{
    QTableWidgetItem* item_1 = ui->tb_cl->item(6, 1);
    item_1->setText(value);
    QTableWidgetItem* item_2 = ui->tb_cl->item(6, 5);
    item_2->setText(phase);
    GlobalUtils::get_table_values(*ui->tb_cl, tb_cl_values);
}

QPair<QString, QString> ui_001::calc_ux_value(int index)
{
    static const QMap<int, double> multipliers {
                                               {1,  1.0},
                                               {2, -1.0},
                                               {3,  std::sqrt(3.0)},
                                               {4, -std::sqrt(3.0)},
                                               };

    if (index >= 5 && index <= 7) {
        static const QStringList phases = {"UA", "UB", "UC"};
        QString key = phases[index - 5];
        return { tb_cl_values[key][0].toString(),
                tb_cl_values[key][4].toString() };
    }

    if (!multipliers.contains(index)) {
        return {"--", "--"};
    }

    VoltagePhasor ua {tb_cl_values["UA"][0].toDouble(), tb_cl_values["UA"][4].toDouble()};
    VoltagePhasor ub {tb_cl_values["UB"][0].toDouble(), tb_cl_values["UB"][4].toDouble()};
    VoltagePhasor uc {tb_cl_values["UC"][0].toDouble(), tb_cl_values["UC"][4].toDouble()};

    auto ux = GlobalUtils::calcUx(ua, ub, uc, multipliers[index]);

    return {
        QString::number(std::abs(ux),  'f', 3),
        QString::number(std::arg(ux)*180/M_PI, 'f', 1)
    };
}

void ui_001::calc_uab_value()
{
    QMap<QString, QPair<QString, QString>> result =
        GlobalUtils::calcLineVoltageMap(tb_cl_values["UA"][0].toDouble(), tb_cl_values["UA"][4].toDouble(),
                                        tb_cl_values["UB"][0].toDouble(), tb_cl_values["UB"][4].toDouble(),
                                        tb_cl_values["UC"][0].toDouble(), tb_cl_values["UC"][4].toDouble()
                                        );
    auto setItemText = [&](int row, int col, const QString &text) {
        QTableWidgetItem *item = ui->tb_down_1->item(row, col);
        if (!item) {
            item = new QTableWidgetItem();
            ui->tb_down_1->setItem(row, col, item);
        }
        item->setText(text);
    };
    const QStringList keys = { "UAB", "UBC", "UCA" };

    for (int row = 0; row < keys.size(); ++row) {
        const auto &value = result[keys[row]];
        setItemText(row, 1, value.first);   // 有效值
        setItemText(row, 2, value.second);  // 相位
    }
}

void ui_001::calc_uo_value()
{
    QMap<QString, QPair<QString, QString>> result =
        GlobalUtils::calcSymmetricalVoltageMap(tb_cl_values["UA"][0].toDouble(), tb_cl_values["UA"][4].toDouble(),
                                               tb_cl_values["UB"][0].toDouble(), tb_cl_values["UB"][4].toDouble(),
                                               tb_cl_values["UC"][0].toDouble(), tb_cl_values["UC"][4].toDouble()
                                               );
    auto setItemText = [&](int row, int col, const QString &text) {
        QTableWidgetItem *item = ui->tb_down_1->item(row, col);
        if (!item) {
            item = new QTableWidgetItem();
            ui->tb_down_1->setItem(row, col, item);
        }
        item->setText(text);
    };
    const QStringList keys = { "U0", "U+", "U-" };
    const int startRow = 3;

    for (int i = 0; i < keys.size(); ++i) {
        const auto &value = result[keys[i]];
        setItemText(startRow + i, 1, value.first);   // 有效值
        setItemText(startRow + i, 2, value.second);  // 相位
    }
}

void ui_001::calc_io_value()
{
    QMap<QString, QPair<QString, QString>> result =
        GlobalUtils::calcSymmetricalCurrentMap(tb_cl_values["IA"][0].toDouble(), tb_cl_values["IA"][4].toDouble(),
                                               tb_cl_values["IB"][0].toDouble(), tb_cl_values["IB"][4].toDouble(),
                                               tb_cl_values["IC"][0].toDouble(), tb_cl_values["IC"][4].toDouble()
                                               );
    auto setItemText = [&](int row, int col, const QString &text) {
        QTableWidgetItem *item = ui->tb_down_1->item(row, col);
        if (!item) {
            item = new QTableWidgetItem();
            ui->tb_down_1->setItem(row, col, item);
        }
        item->setText(text);
    };
    const QStringList keys = { "I0", "I+", "I-" };
    const int startRow = 6;

    for (int i = 0; i < keys.size(); ++i) {
        const auto &value = result[keys[i]];
        setItemText(startRow + i, 1, value.first);   // 有效值
        setItemText(startRow + i, 2, value.second);  // 相位
    }
}
