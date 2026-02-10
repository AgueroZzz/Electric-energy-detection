#include "ac_six_chart.h"

ac_six_chart::ac_six_chart(const QMap<QString, QList<QVariant> > &initialMap, QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(320, 320);
    setStyleSheet("background-color: black;");

    initAllPhasors();

    if (!initialMap.isEmpty()) {
        parsePhasorsFromMap(initialMap);
        calculateDerivedPhasors();
        updateVisiblePhasors();
        updateDisplay();
    }
}

void ac_six_chart::setPhasors(const QMap<QString, Phasor> &phasors)
{
    _phasors = phasors;
    update();
}

void ac_six_chart::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), Qt::black);

    QRect drawRect = rect().marginsRemoved(QMargins(50, 50, 40, 60));
    QPointF center = drawRect.center();
    double radius = qMin(drawRect.width(), drawRect.height()) / 2.0 - 10;

    drawGrid(painter, drawRect);

    for (const auto& p : _phasors)
    {
        if (p.visible && p.magnitude > 1e-6)
        {
            drawPhasor(painter, drawRect, p, center);
        }
    }
}

void ac_six_chart::slot_charts_refresh(const QMap<QString, QList<QVariant> > &map)
{
    parsePhasorsFromMap(map);
    calculateDerivedPhasors();
    updateVisiblePhasors();
    updateDisplay();
}

void ac_six_chart::slot_setShowGridCircles(bool show)
{
    _showGridCircles = show;
    update();
}

void ac_six_chart::slot_setShowAxes(bool show)
{
    _showAxes = show;
    update();
}

void ac_six_chart::slot_onModeChanged(int mode)
{
    if (mode < 0 || mode > 2) return;
    _mode = mode;
    updateVisiblePhasors();
    updateDisplay();
}

void ac_six_chart::slot_onZoomOut()
{
    int idx = _scaleLevels.indexOf(_currentScale);
    if (idx == -1) {
        _currentScale = 20.0;
    } else {
        idx = (idx + 1) % _scaleLevels.size();
        _currentScale = _scaleLevels[idx];
    }
    updateDisplay();
}

void ac_six_chart::initAllPhasors()
{
    // 相电流（大写）
    _phasors["IA"] = {0, 0, Qt::red,     "IA", false};
    _phasors["IB"] = {0, 0, Qt::blue,    "IB", false};
    _phasors["IC"] = {0, 0, Qt::yellow,  "IC", false};

    // 线电流（小写）
    _phasors["Ia"] = {0, 0, Qt::red,     "Ia", false};
    _phasors["Ib"] = {0, 0, Qt::blue,    "Ib", false};
    _phasors["Ic"] = {0, 0, Qt::yellow,  "Ic", false};

    // 序分量（常用写法）
    _phasors["I0"]  = {0, 0, Qt::gray,      "I₀",  false};
    _phasors["I+"]  = {0, 0, Qt::cyan,      "I⁺",  false};
    _phasors["I-"]  = {0, 0, Qt::magenta,   "I⁻",  false};

    // 兼容写法（小写 o / + / -）
    _phasors["Io"]  = {0, 0, Qt::gray,      "Io",  false};
    _phasors["i+"]  = {0, 0, Qt::cyan,      "i+",  false};
    _phasors["i-"]  = {0, 0, Qt::magenta,   "i-",  false};
}

void ac_six_chart::parsePhasorsFromMap(const QMap<QString, QList<QVariant> > &map)
{
    // 先全部清零隐藏
    for (auto& p : _phasors) {
        p.magnitude = 0;
        p.phase = 0;
        p.visible = false;
    }

    constexpr int COL_MAG = 0;
    constexpr int COL_PHASE = 4;   // 根据你之前的习惯，第4列是相位

    for (auto it = map.constBegin(); it != map.constEnd(); ++it)
    {
        QString key = normalizeKey(it.key());
        if (!_phasors.contains(key)) continue;

        const auto& vals = it.value();
        if (vals.size() <= qMax(COL_MAG, COL_PHASE)) continue;

        bool okMag = false, okPha = false;
        double mag = vals[COL_MAG].toDouble(&okMag);
        double pha = vals[COL_PHASE].toDouble(&okPha);

        if (okMag && okPha)
        {
            _phasors[key].magnitude = mag;
            _phasors[key].phase = pha;
            _phasors[key].visible = (mag > 1e-6);
        }
    }
}

void ac_six_chart::calculateDerivedPhasors()
{

}

void ac_six_chart::updateVisiblePhasors()
{
    // 先全部隐藏
    for (auto& p : _phasors) {
        p.visible = false;
    }

    switch (_mode)
    {
    case 0: // 相电流
        _phasors["IA"].visible = _phasors["IA"].magnitude > 1e-6;
        _phasors["IB"].visible = _phasors["IB"].magnitude > 1e-6;
        _phasors["IC"].visible = _phasors["IC"].magnitude > 1e-6;
        break;

    case 1: // 线电流
        _phasors["Ia"].visible = _phasors["Ia"].magnitude > 1e-6;
        _phasors["Ib"].visible = _phasors["Ib"].magnitude > 1e-6;
        _phasors["Ic"].visible = _phasors["Ic"].magnitude > 1e-6;
        break;

    case 2: // 序分量
        _phasors["I0"].visible = _phasors["I0"].magnitude > 1e-6;
        _phasors["I+"].visible = _phasors["I+"].magnitude > 1e-6;
        _phasors["I-"].visible = _phasors["I-"].magnitude > 1e-6;
        // 兼容写法也显示
        _phasors["Io"].visible = _phasors["I0"].magnitude > 1e-6;
        _phasors["i+"].visible = _phasors["I+"].magnitude > 1e-6;
        _phasors["i-"].visible = _phasors["I-"].magnitude > 1e-6;
        break;
    }
}

void ac_six_chart::updateDisplay()
{
    double maxMag = 0;
    for (const auto& p : _phasors) {
        if (p.visible) {
            maxMag = std::max(maxMag, p.magnitude);
        }
    }

    // 自动适应（只放大，不缩小）
    if (maxMag > _currentScale * 0.9) {
        _maxMagnitude = maxMag * 1.25;
    } else {
        _maxMagnitude = _currentScale;
    }

    update();
}

void ac_six_chart::drawGrid(QPainter &painter, const QRect &drawRect)
{
    QPointF center = rect().center();
    double radius = qMin(rect().width(), rect().height()) / 2.0 - 10;

    // 同心圆
    if (_showGridCircles)
    {
        QPen pen(QColor(50,50,50));
        pen.setWidth(1);
        painter.setPen(pen);
        painter.setFont(QFont("Arial", 7));

        int steps = 5;
        double stepVal = _maxMagnitude / steps;
        for (int i = 1; i <= steps; ++i)
        {
            double r = radius * i / steps;
            painter.drawEllipse(center, r, r);

            QString txt = QString::number(stepVal * i, 'f', 1);
            painter.setPen(Qt::darkGray);
            painter.drawText(QPointF(center.x() + r + 4, center.y() + 4), txt);
        }
    }

    // 辐射线 每30°
    QPen radPen(QColor(60,60,60));
    radPen.setWidth(1);
    painter.setPen(radPen);
    for (int deg = 0; deg < 360; deg += 30)
    {
        double rad = deg * M_PI / 180.0;
        double x = center.x() + radius * cos(rad);
        double y = center.y() - radius * sin(rad);
        painter.drawLine(center, QPointF(x, y));
    }

    // 坐标轴
    if (_showAxes)
    {
        QPen axisPen(Qt::white);
        axisPen.setWidth(1);
        painter.setPen(axisPen);
        painter.drawLine(center.x() - radius - 20, center.y(),
                         center.x() + radius + 20, center.y());
        painter.drawLine(center.x(), center.y() - radius - 20,
                         center.x(), center.y() + radius + 20);
    }
}

void ac_six_chart::drawPhasor(QPainter &painter, const QRect &drawRect, const Phasor &p, const QPointF &center)
{
    double radius = qMin(rect().width(), rect().height()) / 2.0 - 10;
    double scale = radius / _maxMagnitude;
    double len = p.magnitude * scale;
    double rad = p.phase * M_PI / 180.0;

    double x2 = center.x() + len * cos(rad);
    double y2 = center.y() - len * sin(rad);

    // 主线
    QPen pen(p.color);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(center, QPointF(x2, y2));

    // 箭头
    double arrowSize = 10;
    double angle = std::atan2(y2 - center.y(), x2 - center.x());
    QPointF p1(x2 - arrowSize * cos(angle - M_PI/6),
               y2 - arrowSize * sin(angle - M_PI/6));
    QPointF p2(x2 - arrowSize * cos(angle + M_PI/6),
               y2 - arrowSize * sin(angle + M_PI/6));

    painter.setBrush(p.color);
    painter.drawPolygon(QPolygonF() << QPointF(x2,y2) << p1 << p2);

    // 标签
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(QPointF(x2 + 10, y2 + 6), p.label);
}

QString ac_six_chart::normalizeKey(const QString &key) const
{
    QString k = key.trimmed().toUpper();
    if (k == "IO" || k == "I0")  return "I0";
    if (k == "I+" || k == "IP" || k == "I_POS") return "I+";
    if (k == "I-" || k == "IN" || k == "I_NEG") return "I-";
    if (k == "IA") return "IA";
    if (k == "IB") return "IB";
    if (k == "IC") return "IC";
    if (k == "IA" || k == "IA") return "Ia";  // 小写兼容
    if (k == "IB" || k == "IB") return "Ib";
    if (k == "IC" || k == "IC") return "Ic";
    return key; // 其他保持原样
}
