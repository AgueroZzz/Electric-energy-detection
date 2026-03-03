#include "ui_026.h"
#include "ui_ui_026.h"
#include "global/utils.h"

ui_026::ui_026(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_026)
{
    ui->setupUi(this);

    ui->tb_sycs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_sycs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_down_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_1->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tb_down_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    leftGroup = new QButtonGroup(this);
    leftGroup->addButton(ui->rb_action, 0);   // 动作
    leftGroup->addButton(ui->rb_return, 1);   // 返回
    ui->rb_action->setChecked(true);

    rightGroup = new QButtonGroup(this);
    rightGroup->addButton(ui->rb_hand,   0);  // 手动
    rightGroup->addButton(ui->rb_a_up, 1);  // 自动加
    rightGroup->addButton(ui->rb_a_down, 2);  // 自动减
    ui->rb_hand->setChecked(true);

    init_cl_table();
    GlobalUtils::get_table_values(*ui->tb_sycs, tb_cl_values, 0);
    QObject::connect(ui->tb_sycs, &QTableWidget::itemChanged, this, &ui_026::slot_on_tb_sycs_changed);
}

ui_026::~ui_026()
{
    delete ui;
}

void ui_026::slot_on_tb_sycs_changed(QTableWidgetItem *item)
{
    if (!item)
        return;

    // const int row = item->row();
    const int col = item->column();

    const bool isValueCol  = (col == 1 || col == 3);
    const bool isPhaseCol  = (col == 5 || col == 7);
    const bool isIntCol   = (col == 4);
    const bool needFormat = isValueCol || isPhaseCol || isIntCol;

    if (!needFormat)
        return;

    int decimals = 0;
    if (isIntCol) {
        decimals = 0;
    } else if (isValueCol) {
        decimals = 3;
    } else if (isPhaseCol) {
        decimals = 1;
    }
    QString originalText = item->text();
    QString formattedText = GlobalUtils::formatDoubleString(originalText, decimals);

    // 文本没变化，直接退出
    if (formattedText == originalText)
        return;

    {
        QSignalBlocker blocker(ui->tb_sycs);
        item->setText(formattedText);
    }
    GlobalUtils::get_table_values(*ui->tb_sycs, tb_cl_values, 0);

    // 有效值列（1）或 相位列（5）改变才刷新
    if (col == 1 || col == 5) {
        emit sig_charts_refresh(tb_cl_values);
    }
}

void ui_026::init_cl_table()
{
    int rows = ui->tb_sycs->rowCount();
    for (int row = 0; row < rows; ++row) {
        setupVarStep(row, 2, 3);
        setupVarStep(row, 6, 7);
    }
}

void ui_026::setupVarStep(int row, int colVar, int colStep)
{
    QCheckBox *cb = new QCheckBox();

    QWidget *w = new QWidget();
    QHBoxLayout *l = new QHBoxLayout(w);
    l->addWidget(cb);
    l->setAlignment(Qt::AlignCenter);
    l->setContentsMargins(0,0,0,0);
    ui->tb_sycs->setCellWidget(row, colVar, w);
    QTableWidgetItem *stepItem = ui->tb_sycs->item(row, colStep);
    if (!stepItem) {
        stepItem = new QTableWidgetItem();
        ui->tb_sycs->setItem(row, colStep, stepItem);
    }

    // 初始状态
    updateVarStepState(row, colVar, colStep);

    connect(cb, &QCheckBox::stateChanged, this, [=](int){
        updateVarStepState(row, colVar, colStep);
    });
}

void ui_026::updateVarStepState(int row, int colVar, int colStep)
{
    QTableWidgetItem *stepItem = ui->tb_sycs->item(row, colStep);

    QWidget *w = ui->tb_sycs->cellWidget(row, colVar);
    QCheckBox *cb = w ? w->findChild<QCheckBox *>() : nullptr;
    bool checked = cb && cb->isChecked();
    if (checked) {
        GlobalUtils::setItemState(stepItem, true, false);
    } else {
        GlobalUtils::setItemState(stepItem, false, true);
    }
}
