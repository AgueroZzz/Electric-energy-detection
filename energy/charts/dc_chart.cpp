#include "dc_chart.h"

dc_chart::dc_chart(const QMap<QString, QList<QVariant>>& initialMap,
                   QWidget *parent)
    : QWidget{parent}, _sycs(initialMap), _zoomFactor(1.0)
{
    setMinimumSize(320, 320);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void dc_chart::updateValues(const QMap<QString, QList<QVariant> > &data)
{
    _sycs = data;
    update();  // 触发重绘
}

void dc_chart::slot_set_scale()
{
    qDebug() << "当前比例尺为" << _zoomFactor;
    _zoomFactor *= _zoomStep;
    if (_zoomFactor > _maxZoom) {
        _zoomFactor = 1.0;             // 放大到最大比例后缩小到初始比例尺
    }
    update();
}

void dc_chart::slot_charts_refresh(const QMap<QString, QList<QVariant> > &map)
{
    updateValues(map);
}

void dc_chart::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);

    //  动态计算所有布局参数
    const int w = width();
    const int h = height();

    // 字体大小随控件高度自适应
    int fontSize = qBound(9, h / 28, 14);
    QFont font = p.font();
    font.setPointSize(fontSize);
    p.setFont(font);
    QFontMetrics fm(font);

    // 计算标签区宽度（取最宽的通道名 + 余量）
    double maxLabelWidth = 0;
    for (const auto &ch : _channelOrder) {
        maxLabelWidth = std::max(maxLabelWidth, double(fm.horizontalAdvance(ch)));
    }
    _channelLabelWidth = maxLabelWidth + 24;  // 左右余量

    // 内容区域
    double contentLeft   = _channelLabelWidth + 12;
    double contentRight  = w - 24;
    double contentWidth  = contentRight - contentLeft;
    double contentHeight = h - 60;

    _zeroX = contentLeft + contentWidth * 0.5;

    // 柱子最大长度（左右各 ~42%）
    _maxBarLength = contentWidth * 0.42;

    // 柱子高度与间距（6条通道）
    int channelCount = _channelOrder.size();
    double totalBarsSpace = contentHeight * 0.88;  // 留 12% 上下边距
    _barHeight  = totalBarsSpace / (channelCount * 1.55);   // 高度:间距 ≈ 1:0.55
    _barSpacing = _barHeight * 0.55;

    // 起始 Y（顶部居中偏上）
    _yStart = 35 + (contentHeight - totalBarsSpace) / 2.0;

    //  2. 开始绘制
    drawBackground(p);
    drawZeroLine(p);
    drawBarsAndValues(p);
}

void dc_chart::drawBackground(QPainter &p)
{
    p.fillRect(rect(), Qt::black);

    // 细网格线
    p.setPen(QPen(QColor(38, 38, 45), 1));
    int w = width();
    for (int i = 1; i < 10; ++i) {
        double x = _channelLabelWidth + 12 + (w - _channelLabelWidth - 36) * i / 10.0;
        p.drawLine(QPointF(x, 20), QPointF(x, height() - 30));
    }
}

void dc_chart::drawZeroLine(QPainter &p)
{
    QPen dashPen(QColor(90, 90, 110), 1.2, Qt::DashLine);
    dashPen.setDashPattern({6, 6});
    p.setPen(dashPen);
    p.drawLine(QPointF(_zeroX, _yStart - 15),
               QPointF(_zeroX, _yStart + (_barHeight + _barSpacing) * 6 + 15));
}

void dc_chart::drawBarsAndValues(QPainter &p)
{
    QFont font = p.font();
    QFontMetrics fm(font);

    double y = _yStart;

    for (const QString &channel : _channelOrder)
    {
        if (!_sycs.contains(channel) || _sycs[channel].isEmpty()) continue;

        QString valueStr = _sycs[channel].first().toString().trimmed();
        bool ok = false;
        double value = valueStr.toDouble(&ok);
        if (!ok) value = 0.0;

        bool isVoltage  = channel.startsWith("U", Qt::CaseInsensitive);
        bool isNegative = value < 0;
        double absValue = std::abs(value);

        double fullScale = isVoltage ? 300.0 : 10.0;
        double ratio = std::min(absValue / fullScale, 1.6);

        // 关键：zoomFactor 越大柱子越长
        double effectiveMaxLength = _maxBarLength * _zoomFactor;
        int barLength = qRound(effectiveMaxLength * ratio);

        QColor barColor = isVoltage ? colorVoltage :
                              isNegative ? colorCurrentNeg : colorCurrentPos;

        double barX = isNegative ? (_zeroX - barLength) : _zeroX;

        QRectF barRect(barX, y, barLength, _barHeight);
        p.fillRect(barRect, barColor);
        p.setPen(barColor.lighter(145));
        p.drawRect(barRect.adjusted(0.5, 0.5, -0.5, -0.5));

        // 通道名
        p.setPen(Qt::white);
        p.drawText(qRound(_channelLabelWidth - 12 - fm.horizontalAdvance(channel)),
                   qRound(y + _barHeight/2 + fm.ascent()/2 - 1),
                   channel);

        // 数值
        QString displayText = QString("%1").arg(value, 0, 'f', 3);
        if (value >= 0) displayText = "+" + displayText;

        double textX = isNegative ?
                           (_zeroX - barLength - fm.horizontalAdvance(displayText) - 10) :
                           (_zeroX + barLength + 10);

        QColor textColor = isVoltage ? colorVoltage.lighter(115) :
                               isNegative ? colorCurrentNeg.lighter(125) :
                               colorCurrentPos.lighter(125);

        p.setPen(textColor);
        p.drawText(qRound(textX),
                   qRound(y + _barHeight/2 + fm.ascent()/2 - 1),
                   displayText);

        y += _barHeight + _barSpacing;
    }

    // 右上角显示当前放大倍数
    if (_zoomFactor > 1.01) {
        p.setPen(QColor(140, 140, 160));
        QFont smallFont = font;
        smallFont.setPointSize(font.pointSize() - 2);
        p.setFont(smallFont);

        QString zoomText = QString("zoom: ×%1").arg(QString::number(_zoomFactor, 'f', 1));
        p.drawText(width() - 20 - p.fontMetrics().horizontalAdvance(zoomText),
                   24, zoomText);
    }
}
