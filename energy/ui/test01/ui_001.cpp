#include "ui_001.h"
#include "ui_ui_001.h"

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

    init_cl_table();
}

ui_001::~ui_001()
{
    delete ui;
}

void ui_001::init_cl_table()
{
    int rows = ui->tb_cl->rowCount();

    for (int row = 0; row < rows; ++row) {

        // ===== 第一组 变 → 步长 =====
        setupVarStep(row, COL_VAR1, COL_STEP1);

        // ===== 第二组 变 → 步长 =====
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
