#include "ui_025.h"
#include "ui_ui_025.h"
#include "global/utils.h"

ui_025::ui_025(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_025)
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
    QObject::connect(ui->tb_sycs, &QTableWidget::itemChanged, this, &ui_025::slot_on_tb_sycs_changed);
    calc_down_1();
}

ui_025::~ui_025()
{
    delete ui;
}

void ui_025::slot_on_tb_sycs_changed(QTableWidgetItem *item)
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
        calc_down_1();
        emit sig_charts_refresh(tb_cl_values);
    }
}

void ui_025::init_cl_table()
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

void ui_025::calc_down_1()
{
    auto result = calcSymmetricalComponents();
    auto setItemText = [&](int row, int col, const QString &text) {
        QTableWidgetItem *item = ui->tb_down_1->item(row, col);
        if (!item) {
            item = new QTableWidgetItem();
            ui->tb_down_1->setItem(row, col, item);
        }
        item->setText(text);
    };
    QStringList c_key = {"Uo", "U+", "U-", "uo", "u+", "u-"};
    for(int row = 0; row < ui->tb_down_1->rowCount(); ++row){
        setItemText(row, 1, result[c_key[row]].first);
        setItemText(row, 2, result[c_key[row]].second);
    }
    qDebug() << result;
}

void ui_025::setupVarStep(int row, int colVar, int colStep)
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

void ui_025::updateVarStepState(int row, int colVar, int colStep)
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

QMap<QString, QPair<QString, QString> > ui_025::calcSymmetricalComponents()
{
    qDebug() << tb_cl_values;  // 保留调试输出

    QMap<QString, QPair<QString, QString>> result;

    // 辅助函数：从 tb_cl_values 取幅度和相位，转成复数
    auto toComplex = [&](const QString& key) -> std::complex<double>
    {
        double mag = 0.0;
        double phase = 0.0;

        if (tb_cl_values.contains(key) && tb_cl_values.value(key).size() > 5)
        {
            mag   = tb_cl_values[key][0].toString().toDouble();
            phase = tb_cl_values[key][4].toString().toDouble();
        }

        return std::polar(mag, qDegreesToRadians(phase));
    };

    auto toPair = [&](const std::complex<double>& c) -> QPair<QString, QString>
    {
        double mag = std::abs(c);
        double phase = qRadiansToDegrees(std::arg(c));

        // if (phase < 0)
        //     phase += 360.0;

        // 幅度很小视为0（避免 -0.000 或科学计数法）
        if (qFuzzyCompare(mag, 0.0) || mag < 1e-6)
            mag = 0.0;

        // 相位很接近0/360/180等可以规范化，但这里保持原样
        return {
            QString("%1").arg(mag,   0, 'f', 3),
            QString("%1").arg(phase, 0, 'f', 1)
        };
    };

    // 计算一组三相的对称分量
    auto calcGroup = [&](const QString& A, const QString& B, const QString& C,
                         const QString& k0, const QString& k1, const QString& k2)
    {
        std::complex<double> Ua = toComplex(A);
        std::complex<double> Ub = toComplex(B);
        std::complex<double> Uc = toComplex(C);

        // 旋转算子 a = e^(j120°), a² = e^(j240°)
        std::complex<double> a  = std::polar(1.0, 2.0 * M_PI / 3.0);
        std::complex<double> a2 = std::polar(1.0, 4.0 * M_PI / 3.0);

        std::complex<double> I0 = (Ua + Ub + Uc)             / 3.0;
        std::complex<double> I1 = (Ua + a  * Ub + a2 * Uc)   / 3.0;
        std::complex<double> I2 = (Ua + a2 * Ub + a  * Uc)   / 3.0;

        result[k0] = toPair(I0);
        result[k1] = toPair(I1);
        result[k2] = toPair(I2);
    };

    calcGroup("UA", "UB", "UC", "Uo",  "U+",  "U-");
    calcGroup("Ua", "Ub", "Uc", "uo",  "u+",  "u-");

    return result;
}
