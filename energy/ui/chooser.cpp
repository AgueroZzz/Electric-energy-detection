#include "chooser.h"
#include "ui_chooser.h"

chooser::chooser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chooser)
{
    ui->setupUi(this);

    _items = {
        {"交流试验",        ":/choose_bg/pic/STEP_0.BMP"},
        {"直流试验",        ":/choose_bg/pic/ZLSY_0.bmp"},
        {"交直流试验",      ":/choose_bg/pic/JZLSY_0.bmp"},
        {"差动定值",        ":/choose_bg/pic/DIFF_0.BMP"},
        {"差动保护",        ":/choose_bg/pic/DIFF_0.BMP"},
        {"差动谐波",        ":/choose_bg/pic/CDXZ_0.bmp"},
        {"差动继电",        ":/choose_bg/pic/CDJDQ_0.bmp"},
        {"时间特性",        ":/choose_bg/pic/TOOT_0.BMP"},
        {"谐波",            ":/choose_bg/pic/GZZX_0.bmp"},
        {"距离零序保护",    ":/choose_bg/pic/JLLXBH_0.bmp"},
        {"状态序列Ⅰ",        ":/choose_bg/pic/STATE_0.BMP"},
        {"状态序列Ⅱ",       ":/choose_bg/pic/state6i_0.bmp"},
        {"同期装置",       ":/choose_bg/pic/PDSYN_0.BMP"},
        {"阻抗特性",        ":/choose_bg/pic/ZKTX_0.bmp"},
        {"功率方向阻抗",        ":/choose_bg/pic/GLFXZK_0.bmp"},
        {"频率/高低周",    ":/choose_bg/pic/PLGDZ_0.bmp"},
        {"功率振荡",     ":/choose_bg/pic/OSC_0.BMP"},
        {"6-35kV综合保护",        ":/choose_bg/pic/6-35k_0.bmp"},
        {"备自投",             ":/choose_bg/pic/BZT_0.bmp"},
        {"整组试验Ⅰ",          ":/choose_bg/pic/SHOT_0.BMP"},
        {"整组试验Ⅱ",       ":/choose_bg/pic/SHOT_0.BMP"},
        {"保护定值校验",       ":/choose_bg/pic/TZK_0.BMP"},
        {"快切",    ":/choose_bg/pic/KQ_0.bmp"},
        {"交流试验6I",            ":/choose_bg/pic/STEP6I_0.BMP"},
        {"交流试验6U",      ":/choose_bg/pic/STEP6U_0.bmp"},
        {"交流试验6UI",      ":/choose_bg/pic/STEP6U_0.bmp"},
        {"交流试验3-按序分量输出",     ":/choose_bg/pic/transplay_0.bmp"}
    };

    init_UI();
    setWindowTitle(tr("继电保护测试系统 Ver 2.0"));

    resize(1200, 800);
}

chooser::~chooser()
{
    delete ui;
}

void chooser::slot_onItemClicked(int idx)
{
    emit sig_test_pro_choose(idx);
    hide();
}

void chooser::init_UI()
{
    QGridLayout* grid = new QGridLayout(ui->btn_widget);
    const int COLS = 9;
    for(int i = 0; i < _items.size(); ++i){
        QToolButton* btn = new QToolButton();
        btn->setFixedSize(90, 90);
        btn->setIconSize(QSize(55, 55));
        btn->setCheckable(true);

        QIcon ico(_items[i].iconRes);
        btn->setIcon(ico);

        btn->setText(_items[i].title);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setAttribute(Qt::WA_TranslucentBackground, true);  // 允许透明
        btn->setStyleSheet("background: transparent; border: none;");

        QObject::connect(btn, &QPushButton::clicked, this, [this, i]() {
            slot_onItemClicked(i);
        });
        _btns.append(btn);

        int row = i / COLS;
        int col = i % COLS;
        grid->addWidget(btn, row, col, Qt::AlignCenter);
    }
}

void chooser::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap bg(":/choose_bg/pic/bg_3x.bmp");
    QPixmap scaled = bg.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaled);
}
