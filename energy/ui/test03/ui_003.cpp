#include "ui_003.h"
#include "ui_ui_003.h"
#include "global/utils.h"

ui_003::ui_003(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_003)
{
    ui->setupUi(this);
    init_table();
}

ui_003::~ui_003()
{
    delete ui;
}

void ui_003::init_table()
{
    ui->tb_fz_xw->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_fz_xw->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tb_kgl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kgl->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_kgl->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tb_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_result->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tb_result->setEditTriggers(QAbstractItemView::NoEditTriggers);

    init_first_table();

    GlobalUtils::get_table_values(*ui->tb_fz_xw, tb_cl_values, 1);
    split_ac_dc_map();

    ac_list << "UA" << "UB" << "UC" << "IA" << "IB" << "IC";
    dc_list << "UX";
}

void ui_003::init_first_table()
{
    int rows = ui->tb_fz_xw->rowCount();
    for (int row = 0; row < rows; ++row) {
        setupVarStep(row, 3, 4);
    }
    for (int row = 0; row < rows -2 ; ++ row){
        setupVarStep(row, 7, 8);
    }

    for (int row = 0; row < rows - 2; ++row){
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText("AC");
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->tb_fz_xw->setItem(row, 0, item);
    }

    QTableWidgetItem* item = new QTableWidgetItem("DC");
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->tb_fz_xw->setItem(6, 0, item);

    item = new QTableWidgetItem("");
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->tb_fz_xw->setItem(7, 0, item);

    QObject::connect(ui->tb_fz_xw, &QTableWidget::cellClicked, this, &ui_003::slot_onCellClicked);
    QObject::connect(ui->tb_fz_xw, &QTableWidget::itemChanged, this, &ui_003::slot_on_tb_fz_changed);
}

void ui_003::setupVarStep(int row, int colVar, int colStep)
{
    QCheckBox *cb = new QCheckBox();

    QWidget *w = new QWidget();
    QHBoxLayout *l = new QHBoxLayout(w);
    l->addWidget(cb);
    l->setAlignment(Qt::AlignCenter);
    l->setContentsMargins(0,0,0,0);
    ui->tb_fz_xw->setCellWidget(row, colVar, w);
    QTableWidgetItem *stepItem = ui->tb_fz_xw->item(row, colStep);
    if (!stepItem) {
        stepItem = new QTableWidgetItem();
        ui->tb_fz_xw->setItem(row, colStep, stepItem);
    }

    // 初始状态
    updateVarStepState(row, colVar, colStep);

    connect(cb, &QCheckBox::stateChanged, this, [=](int){
        updateVarStepState(row, colVar, colStep);
    });
}

void ui_003::updateVarStepState(int row, int colVar, int colStep)
{
    QTableWidgetItem *stepItem = ui->tb_fz_xw->item(row, colStep);

    QWidget *w = ui->tb_fz_xw->cellWidget(row, colVar);
    QCheckBox *cb = w ? w->findChild<QCheckBox *>() : nullptr;
    bool checked = cb && cb->isChecked();
    if (checked) {
        GlobalUtils::setItemState(stepItem, true, false);
    } else {
        GlobalUtils::setItemState(stepItem, false, true);
    }
}

void ui_003::updateHzRowVisibility()
{
    const bool allDC = (dc_list.size() == 7);
    for (int i = 0; i < 6; ++i) {
        QTableWidgetItem *item = ui->tb_fz_xw->item(7, i);
        if (!item) break;

        GlobalUtils::setItemState(item, !allDC, allDC);

        if (i == 3 && allDC) {
            QWidget *cell = ui->tb_fz_xw->cellWidget(7, 3);
            if (cell) {
                QCheckBox *cb = qobject_cast<QCheckBox*>(cell->layout()->itemAt(0)->widget());
                if (cb) cb->setCheckable(false);
            }
        }
    }

    if (!allDC) {
        setupVarStep(7, 3, 4);
        GlobalUtils::setItemState(ui->tb_fz_xw->item(7, 5), true, false);
    }
}

void ui_003::split_ac_dc_map()
{
    ac_map.clear();
    dc_map.clear();
    for (auto it = tb_cl_values.constBegin(); it != tb_cl_values.constEnd(); ++it) {
        const QString& key = it.key();
        if (key == "UX") break;

        const QList<QVariant>& values = it.value();
        if (values.isEmpty()) continue;

        const QString type = values.first().toString();

        if (type == "AC" && values.size() >= 2) {
            ac_map.insert(key, values.mid(1));
        } else if (type == "DC" && values.size() > 4) {
            dc_map.insert(key, values.mid(1, values.size() - 4));
        }
    }
}

void ui_003::slot_onCellClicked(int row, int col)
{
    if (col != 0 || row == 6 || row == 7) return;

    QTableWidgetItem *item = ui->tb_fz_xw->item(row, col);
    if (!item) return;

    ui->tb_fz_xw->blockSignals(true);

    QString current = item->text().trimmed();
    QString param = ui->tb_fz_xw->item(row, 1)->text();

    if (current == "DC") {
        item->setText("AC");
        dc_list.removeAll(param);
        ac_list.append(param);
        setupVarStep(row, 7, 8);
        ui->tb_fz_xw->item(row, 6)->setText("0.0");
        GlobalUtils::setItemState(ui->tb_fz_xw->item(row, 6), true, false);
        ui->tb_fz_xw->item(row, 8)->setText("1.0");
    } else {
        item->setText("DC");
        ac_list.removeAll(param);
        dc_list.append(param);
        for (int i = 6; i < 9; ++i) {
            if (i == 7) {
                QWidget *cell = ui->tb_fz_xw->cellWidget(row, 7);
                if (cell) {
                    QCheckBox *cb = qobject_cast<QCheckBox*>(cell->layout()->itemAt(0)->widget());
                    if (cb) cb->setCheckable(false);
                    continue;
                }
            }
            QTableWidgetItem *newItem = new QTableWidgetItem("");
            newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
            ui->tb_fz_xw->setItem(row, i, newItem);
        }
    }

    updateHzRowVisibility();
    GlobalUtils::get_table_values(*ui->tb_fz_xw, tb_cl_values, 1);
    split_ac_dc_map();
    emit sig_charts_refresh();

    ui->tb_fz_xw->blockSignals(false);
}

void ui_003::slot_on_tb_fz_changed(QTableWidgetItem *item)
{
    if (!item || item->column() == 0) return;

    const int col = item->column();
    const bool is3DecimalCol = (col == 2 || col == 4 || col == 5);
    const bool is1DecimalCol = (col == 6 || col == 8);

    if (!is3DecimalCol && !is1DecimalCol) return;

    const int decimals = is3DecimalCol ? 3 : 1;
    QString originalText = item->text();
    QString formattedText = GlobalUtils::formatDoubleString(originalText, decimals);

    if (formattedText != originalText) {
        QSignalBlocker blocker(ui->tb_fz_xw);
        item->setText(formattedText);
    }

    GlobalUtils::get_table_values(*ui->tb_fz_xw, tb_cl_values, 1);
    split_ac_dc_map();
    emit sig_charts_refresh();
}
