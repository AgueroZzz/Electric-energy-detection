#include "ui_004.h"
#include "ui_ui_004.h"
#include "global/utils.h"
#include <QTreeWidgetItem>
#include <QRegularExpression>

ui_004::ui_004(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ui_004)
{
    ui->setupUi(this);
    InitUI();
}

ui_004::~ui_004()
{
    delete ui;
}

void ui_004::InitUI()
{
    // 初始化按钮
    BtnUtils::createToolButton(ui->btn_open_para, ":/icon/icon/open_file.svg", "导入参数");
    BtnUtils::createToolButton(ui->btn_save_para, ":/icon/icon/save_file.svg", "保存参数");
    BtnUtils::createToolButton(ui->btn_open_test, ":/icon/icon/open_file.svg", "打开报告");
    BtnUtils::createToolButton(ui->btn_start_test, ":/icon/icon/open_file.svg", "开始实验");
    BtnUtils::createToolButton(ui->btn_stop_test, ":/icon/icon/stop.svg", "停止实验");
    BtnUtils::createToolButton(ui->btn_reset_para, ":/icon/icon/recover.svg", "参数复位");
    BtnUtils::createToolButton(ui->btn_up_para, ":/icon/icon/up.svg", "单步增加");
    BtnUtils::createToolButton(ui->btn_down_test, ":/icon/icon/down.svg", "单步减少");

}
