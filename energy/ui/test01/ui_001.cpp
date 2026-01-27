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
    QObject::connect(ui->tb_cl, &QTableWidget::itemChanged, this, &ui_001::slot_on_tb_cl_changed);
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

    // 可选：当禁用时，把右边两个都清空选中状态
    // if (!enableRight) {
    //     rightGroup->setExclusive(false);           // 临时关闭互斥
    //     ui->rb_up->setChecked(false);
    //     ui->rb_down->setChecked(false);
    //     rightGroup->setExclusive(true);            // 恢复互斥
    // }
}

void ui_001::slot_on_tb_cl_changed(QTableWidgetItem *item)
{
    {
        if(!item)
            return;
        // int row = item->row();
        int col = item->column();
        GlobalUtils::get_table_values(*ui->tb_cl, tb_cl_values);
        // 有效值改变和相位改变都会触发雷达图重新绘制
        if(col == 1 || col == 5){
            qDebug() << "有效值或相位改变";
            emit sig_charts_refresh(tb_cl_values);
        }
    }
}

void ui_001::init_cl_table()
{
    int rows = ui->tb_cl->rowCount();

    for (int row = 0; row < rows; ++row) {

        // ===== 第一组 变 → 步长 =====
        setupVarStep(row, COL_VAR1, COL_STEP1);

        // ===== 第二组 变 → 步长 =====
        if(row == 7){
            return;
        }
        setupVarStep(row, COL_VAR2, COL_STEP2);
    }
}

void ui_001::setupVarStep(int row, int colVar, int colStep)
{
    // ---- CheckBox ----
    QCheckBox *cb = new QCheckBox();

    QWidget *w = new QWidget();
    QHBoxLayout *l = new QHBoxLayout(w);
    l->addWidget(cb);
    l->setAlignment(Qt::AlignCenter);
    l->setContentsMargins(0,0,0,0);

    ui->tb_cl->setCellWidget(row, colVar, w);

    // ---- 步长 item ----
    QTableWidgetItem *stepItem = ui->tb_cl->item(row, colStep);
    if (!stepItem) {
        stepItem = new QTableWidgetItem();
        ui->tb_cl->setItem(row, colStep, stepItem);
    }

    // 初始状态
    updateVarStepState(row, colVar, colStep);

    // ---- CheckBox 联动 ----
    connect(cb, &QCheckBox::stateChanged, this,
            [=](int){
                updateVarStepState(row, colVar, colStep);
            });
}

void ui_001::setItemState(QTableWidgetItem *item, bool editable, bool green)
{
    if (!item) return;

    if (editable) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setBackground(Qt::white);
    } else {
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);

        if (green) {
            item->setBackground(
                QBrush(QColor("#c2edc3"), Qt::Dense4Pattern)
                );
        } else {
            item->setBackground(Qt::white);
        }
    }
}

void ui_001::updateVarStepState(int row, int colVar, int colStep)
{
    QTableWidgetItem *stepItem = ui->tb_cl->item(row, colStep);

    QWidget *w = ui->tb_cl->cellWidget(row, colVar);
    QCheckBox *cb = w ? w->findChild<QCheckBox *>() : nullptr;
    bool checked = cb && cb->isChecked();

    if (row == ROW_UX && ui->cb_ux->currentIndex() != 0) {
        // 强制锁死
        setItemState(stepItem, false, true);
        return;
    }

    if (checked) {
        setItemState(stepItem, true, false);
    } else {
        setItemState(stepItem, false, true);
    }
}
