#include "dc_chart.h"

const QMap<QString, QColor> dc_chart::CHANNEL_COLOR = {
    {"UA", Qt::yellow},
    {"UB", QColor(0x00,0xFF,0x00)},   // 绿色
    {"UC", Qt::red},
    {"IA", Qt::yellow},
    {"IB", QColor(0x00,0xFF,0x00)},
    {"IC", Qt::red}
};

dc_chart::dc_chart(QWidget *parent)
    : QWidget{parent}
{
    setMinimumSize(320, 320);
    setStyleSheet("background-color: black;");
    initUI();
}

void dc_chart::setValue(const QMap<QString, double> &values)
{
    for (auto it = values.constBegin(); it != values.constEnd(); ++it) {
        const QString &ch = it.key();
        if (CHANNEL_COLOR.contains(ch) && !qFuzzyCompare(_values[ch], it.value())) {
            _values[ch] = it.value();
        }
    }
    update();
}

void dc_chart::slot_set_scale()
{
    _scaleIndex = (_scaleIndex + 1) % _scale_list.size();
    _scale = _scale_list[_scaleIndex];
    update();
}

void dc_chart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 1. 背景色
    p.fillRect(rect(), QColor(30, 30, 30));   // #1E1E1E

    const int margin = 25;
    const int labelHeight = 25;  // 增加一点高度，确保文字完整
    QRect drawArea = rect().adjusted(margin, margin, -margin, -margin - labelHeight);

    // 2. 计算最大绝对值
    double maxAbs = 1.0;
    for (double v : _values) maxAbs = std::max(maxAbs, std::abs(v));
    maxAbs *= _scale;

    const int barCount = CHANNEL_COLOR.size();
    const int totalWidth = drawArea.width();
    const int barWidth = totalWidth / (barCount * 2 - 1);
    const int gap = barWidth;

    // 3. 垂直网格线
    p.setPen(QPen(QColor(80, 80, 80), 1));
    int x = drawArea.left();
    for (int i = 0; i <= barCount; ++i) {
        p.drawLine(x, drawArea.top(), x, drawArea.bottom());
        x += barWidth + gap;
    }

    // 4. 绘制柱子 + 标签
    x = drawArea.left() + gap / 2;
    for (auto it = CHANNEL_COLOR.constBegin(); it != CHANNEL_COLOR.constEnd(); ++it) {
        const QString &ch = it.key();
        double val = _values.value(ch, 0.0);

        // 柱子区域
        QRect barRect(x, drawArea.top(), barWidth, drawArea.height());
        drawBar(p, barRect, val, maxAbs, it.value());

        // 标签区域（在 drawArea 下方，完整在 widget 内）
        QRect labelRect(x, drawArea.bottom() + 2, barWidth, labelHeight);

        p.setPen(Qt::white);
        p.setFont(QFont("Microsoft YaHei", 10, QFont::Bold));
        p.drawText(labelRect, Qt::AlignCenter, ch);  // 自动居中

        x += barWidth + gap;
    }

    // 5. 零轴线
    p.setPen(QPen(Qt::white, 1, Qt::DashLine));
    int zeroY = drawArea.top() + drawArea.height() / 2;
    p.drawLine(drawArea.left(), zeroY, drawArea.right(), zeroY);
}

void dc_chart::drawBar(QPainter &p, const QRect &rect, double value, double maxAbs, const QColor &color)
{
    if (maxAbs <= 0) return;

    const int midY = rect.top() + rect.height() / 2;
    const double ratio = value / maxAbs;

    QRect fillRect;
    if (ratio >= 0) {
        int h = static_cast<int>(rect.height() * 0.5 * ratio);
        fillRect = QRect(rect.left(), midY - h, rect.width(), h);
    } else {
        int h = static_cast<int>(rect.height() * 0.5 * -ratio);
        fillRect = QRect(rect.left(), midY, rect.width(), h);
    }

    p.fillRect(fillRect, color);
    p.setPen(QPen(Qt::black, 1));  // 黑色细边框
    p.drawRect(fillRect);
}

void dc_chart::initUI()
{
    // 1. 设置默认比例
    _scale = _scale_list[0];
    _scaleIndex = 0;

    // 2. 初始化通道值（与原始界面一致）
    QMap<QString, double> defaultValues{
        {"UA", -8.0}, {"UB", -8.0}, {"UC", 1.0},
        {"IA",  1.0}, {"IB",  1.0}, {"IC", 1.0}
    };
    setValue(defaultValues);

    // 3. 强制首次绘制（确保窗口显示前就有图像）
    update();
}
