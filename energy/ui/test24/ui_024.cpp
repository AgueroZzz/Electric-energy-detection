#include "ui_024.h"
#include "ui_ui_024.h"
#include "global/utils.h"

ui_024::ui_024(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_024)
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

    ui->tb_down_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_down_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    init_cl_table();
    GlobalUtils::get_table_values(*ui->tb_sycs, tb_cl_values, 0);
    QObject::connect(ui->tb_sycs, &QTableWidget::itemChanged, this, &ui_024::slot_on_tb_sycs_changed);
}

ui_024::~ui_024()
{
    delete ui;
}

void ui_024::slot_on_tb_sycs_changed(QTableWidgetItem *item)
{
    if (!item)
        return;

    const int row = item->row();
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

void ui_024::init_cl_table()
{
    int rows = ui->tb_sycs->rowCount();
    for (int row = 0; row < rows; ++row) {
        setupVarStep(row, 2, 3);
        if(row == 6){
            return;
        }
        setupVarStep(row, 6, 7);
    }
}

void ui_024::setupVarStep(int row, int colVar, int colStep)
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

void ui_024::updateVarStepState(int row, int colVar, int colStep)
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
