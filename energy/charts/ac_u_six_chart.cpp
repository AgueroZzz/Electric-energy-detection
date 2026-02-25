#include "ac_u_six_chart.h"

ac_u_six_chart::ac_u_six_chart(const QMap<QString, QList<QVariant> > &initialMap, QWidget *parent)
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

void ac_u_six_chart::setPhasors(const QMap<QString, Phasor> &phasors)
{
    _phasors = phasors;
    update();
}

void ac_u_six_chart::paintEvent(QPaintEvent *event)
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

void ac_u_six_chart::slot_charts_refresh(const QMap<QString, QList<QVariant> > &map)
{
    parsePhasorsFromMap(map);
    calculateDerivedPhasors();
    updateVisiblePhasors();
    updateDisplay();
}

void ac_u_six_chart::slot_setShowGridCircles(bool show)
{
    _showGridCircles = show;
    update();
}

void ac_u_six_chart::slot_setShowAxes(bool show)
{
    _showAxes = show;
    update();
}

void ac_u_six_chart::slot_onModeChanged(int mode)
{
    if (mode < 0 || mode > 2) return;
    _mode = mode;
    updateVisiblePhasors();
    updateDisplay();
}

void ac_u_six_chart::slot_onZoomOut()
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

void ac_u_six_chart::initAllPhasors()
{
    // 相电压
    _phasors["UA"] = {0, 0, Qt::red,     "UA", false};
    _phasors["UB"] = {0, 0, Qt::blue,    "UB", false};
    _phasors["UC"] = {0, 0, Qt::yellow,  "UC", false};

    // 线电压
    _phasors["Ua"] = {0, 0, Qt::red,     "Ua", false};
    _phasors["Ub"] = {0, 0, Qt::blue,    "Ub", false};
    _phasors["Uc"] = {0, 0, Qt::yellow,  "Uc", false};

    // 序分量
    _phasors["Uo"]  = {0, 0, Qt::gray,      "Uo",  false};
    _phasors["U+"]  = {0, 0, Qt::cyan,      "U+",  false};
    _phasors["U-"]  = {0, 0, Qt::magenta,   "U-",  false};

    _phasors["uo"]  = {0, 0, Qt::gray,      "uo",  false};
    _phasors["u+"]  = {0, 0, Qt::cyan,      "u+",  false};
    _phasors["u-"]  = {0, 0, Qt::magenta,   "u-",  false};
}

void ac_u_six_chart::parsePhasorsFromMap(const QMap<QString, QList<QVariant> > &map)
{
    // 先全部清零隐藏
    for (auto& p : _phasors) {
        p.magnitude = 0;
        p.phase = 0;
        p.visible = false;
    }

    constexpr int COL_MAG = 0;
    constexpr int COL_PHASE = 4;

    for (auto it = map.constBegin(); it != map.constEnd(); ++it)
    {
        // QString key = normalizeKey(it.key());
        QString key = it.key();
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

void ac_u_six_chart::calculateDerivedPhasors()
{

}

void ac_u_six_chart::updateVisiblePhasors()
{
    // 先全部隐藏
    for (auto& p : _phasors) {
        p.visible = false;
    }

    switch (_mode)
    {
    case 0: // 相分量
        _phasors["UA"].visible = _phasors["UA"].magnitude > 1e-6;
        _phasors["UB"].visible = _phasors["UB"].magnitude > 1e-6;
        _phasors["UC"].visible = _phasors["UC"].magnitude > 1e-6;
        _phasors["Ua"].visible = _phasors["Ua"].magnitude > 1e-6;
        _phasors["Ub"].visible = _phasors["Ub"].magnitude > 1e-6;
        _phasors["Uc"].visible = _phasors["Uc"].magnitude > 1e-6;
        break;

    case 1: // 序分量
        _phasors["Uo"].visible  = _phasors["Uo"].magnitude > 1e-6;
        _phasors["U+"].visible  = _phasors["U+"].magnitude > 1e-6;
        _phasors["U-"].visible  = _phasors["U-"].magnitude > 1e-6;
        // 兼容写法
        _phasors["uo"].visible  = _phasors["uo"].magnitude > 1e-6;
        _phasors["u+"].visible  = _phasors["u+"].magnitude > 1e-6;
        _phasors["u-"].visible  = _phasors["u-"].magnitude > 1e-6;
        break;
    }

    update();
}

void ac_u_six_chart::updateDisplay()
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

void ac_u_six_chart::drawGrid(QPainter &painter, const QRect &drawRect)
{
    QPointF center = drawRect.center();   // ← 改成和相量一样
    double radius = qMin(drawRect.width(), drawRect.height()) / 2.0 - 10;

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

void ac_u_six_chart::drawPhasor(QPainter &painter, const QRect &drawRect, const Phasor &p, const QPointF &center)
{
    double radius = qMin(rect().width(), rect().height()) / 2.0 - 10;
    double scale = radius / _maxMagnitude;
    double len = p.magnitude * scale;
    double rad = p.phase * M_PI / 180.0;

    double x2 = center.x() + len * cos(rad);
    double y2 = center.y() - len * sin(rad);

    // 根据是相电流还是线电流设置不同线宽和样式
    QPen pen(p.color);
    if (p.label.startsWith("U") && p.label.length() == 2) {  // UA/UB/UC
        pen.setWidth(4);           // 相电流更粗
        pen.setStyle(Qt::SolidLine);
    } else if (p.label.startsWith("U") || (p.label.length() == 2 && p.label[0].isLower())) {  // Ua/Ub/Uc
        pen.setWidth(2);           // 线电流更细
        // pen.setStyle(Qt::DashLine);  // 可选：改成虚线，更容易区分
        pen.setStyle(Qt::SolidLine);
    }
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

QString ac_u_six_chart::normalizeKey(const QString &key) const
{
    QString k = key.trimmed().toUpper();
    if (k == "Uo" || k == "Uo")  return "Uo";
    if (k == "U+" || k == "UP" || k == "I_POS") return "U+";
    if (k == "U-" || k == "UN" || k == "I_NEG") return "U-";
    if (k == "UA") return "UA";
    if (k == "UB") return "UB";
    if (k == "UC") return "UC";
    if (k == "Ua" || k == "Ua") return "Ua";  // 小写兼容
    if (k == "Ub" || k == "Ub") return "Ub";
    if (k == "Uc" || k == "Uc") return "Uc";
    return key; // 其他保持原样
}
