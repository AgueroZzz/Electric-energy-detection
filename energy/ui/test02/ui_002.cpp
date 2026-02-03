#include "ui_002.h"
#include "ui_ui_002.h"
#include "global/utils.h"

ui_002::ui_002(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_002)
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

    // 实现按钮互斥
    leftGroup = new QButtonGroup(this);
    leftGroup->addButton(ui->rb_hand, 0);   // 手动
    leftGroup->addButton(ui->rb_a_up, 1);   // 全自动
    leftGroup->addButton(ui->rb_a_down, 2);   // 半自动
    ui->rb_hand->setChecked(true);

    rightGroup = new QButtonGroup(this);
    rightGroup->addButton(ui->rb_action,   0);  // 动作
    rightGroup->addButton(ui->rb_return, 1);  // 返回
    ui->rb_action->setChecked(true);

    init_tb_sycs();
    GlobalUtils::get_table_values(*ui->tb_sycs, tb_sycs_values);
    calc_uab_bc_ca();
    QObject::connect(ui->tb_sycs, &QTableWidget::itemChanged, this, &ui_002::slot_on_tb_sycs_changed);

    qDebug() << tb_sycs_values;
}

ui_002::~ui_002()
{
    delete ui;
}

void ui_002::init_tb_sycs()
{
    int rows = ui->tb_sycs->rowCount();
    for (int row = 0; row < rows; ++row) {
        setupVarStep(row, 2, 3);
    }
}

void ui_002::setupVarStep(int row, int colVar, int colStep)
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

void ui_002::updateVarStepState(int row, int colVar, int colStep)
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

void ui_002::calc_uab_bc_ca()
{
    double ua = tb_sycs_values["UA"][0].toDouble();
    double ub = tb_sycs_values["UB"][0].toDouble();
    double uc = tb_sycs_values["UC"][0].toDouble();
    auto setItemText = [&](int row, int col, const QString &text) {
        QTableWidgetItem *item = ui->tb_down_1->item(row, col);
        if (!item) {
            item = new QTableWidgetItem();
            ui->tb_down_1->setItem(row, col, item);
        }
        item->setText(text);
    };
    setItemText(0, 1, QString::number(ua - ub, 'f', 3));
    setItemText(1, 1, QString::number(ub - uc, 'f', 3));
    setItemText(2, 1, QString::number(uc - ua, 'f', 3));
    return;
}

void ui_002::slot_on_tb_sycs_changed(QTableWidgetItem *item)
{
    if (!item)
        return;
    const int row = item->row();
    const int col = item->column();
    if (col != 1)
        return;
    QString originalText = item->text();
    QString formattedText = GlobalUtils::formatDoubleString(originalText, 3);

    if (formattedText == originalText)
        return;

    {
        QSignalBlocker blocker(ui->tb_sycs);
        item->setText(formattedText);
    }
    GlobalUtils::get_table_values(*ui->tb_sycs, tb_sycs_values);

    emit sig_charts_refresh(tb_sycs_values);

    // UAB / UBC / UCA 仅在 UA / UB / UC 变化时计算
    if (row == 0 || row == 1 || row == 2) {
        calc_uab_bc_ca();
    }
}
