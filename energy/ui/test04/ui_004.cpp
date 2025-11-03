#include "ui_004.h"
#include "ui_ui_004.h"

ui_004::ui_004(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_004)
{
    ui->setupUi(this);

    init_table();
}

ui_004::~ui_004()
{
    delete ui;
}

void ui_004::init_table()
{
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

    QStringList xbhl_name;
    xbhl_name << "直流" << "基波" << "2次" << "3次" << "4次" << "5次" << "6次" << "7次" << "8次" << "9次"
              << "10次" << "11次" << "12次" << "13次" << "14次" << "15次" << "16次" << "17次" << "18次" << "19次" << "20次";
    for(int i = 0; i < ui->tb_xbhl->rowCount(); ++i){
        QTableWidgetItem* item = new QTableWidgetItem(xbhl_name[i]);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        item->setFont(font);
        item->setTextAlignment(Qt::AlignCenter);
        item->setBackground(QBrush(QColor(0xc2edc3)));
        item->setBackground(QBrush(QColor(0xc2edc3), Qt::Dense4Pattern));

        ui->tb_xbhl->setItem(i, 0, item);
    }
}
