#include "ac_chart.h"
#include <complex>

ac_chart::ac_chart(const QMap<QString, QList<QVariant>>& initialMap, QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(320, 320);
    setStyleSheet("background-color: black;");

    // 初始化所有相量（基本 + 派生）为默认值
    initAllPhasors();

    // 如果传入初始 map，解析更新基本相量
    if (!initialMap.isEmpty()) {
        parseBasicPhasorsFromMap(initialMap);
    }

    // 计算派生相量
    calculateDerivedPhasors();

    // 根据默认模式（相分量）设置可见性
    updateVisiblePhasors();

    // 初始刷新显示
    updatePhasorDisplay();
}

void ac_chart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    painter.fillRect(rect(), Qt::black);                  // 黑色背景

    // 留出边距，避免贴边
    QRect drawRect = rect().marginsRemoved(QMargins(50, 50, 30, 50));
    QPointF center = drawRect.center();                  // 圆心
    double radius = qMin(drawRect.width(), drawRect.height()) / 2.0 - 10;

    drawGrid(painter, drawRect); // 绘制网格

    // 绘制每个可见的相量
    for (auto it = _phasors.constBegin(); it != _phasors.constEnd(); ++it) {
        if (it.value().visible) {
            drawPhasor(painter, drawRect, it.value(), center);
        }
    }
}

void ac_chart::setPhasors(const QMap<QString, Phasor> &phasors)
{
    _phasors = phasors;
    update();
}

void ac_chart::slot_setShowGridCircles(bool show)
{
    _showGridCircles = show;
    update();
}

void ac_chart::slot_setShowAxes(bool show)
{
    _showAxes = show;
    update();
}

void ac_chart::slot_onModeChanged(int id)
{
    _mode = id;

    // 更新可见性
    updateVisiblePhasors();

    // 刷新显示
    updatePhasorDisplay();
}

void ac_chart::slot_charts_refresh(const QMap<QString, QList<QVariant> > &map)
{
    qDebug() << map;
    // 解析更新基本相量
    parseBasicPhasorsFromMap(map);

    // 重新计算派生相量
    calculateDerivedPhasors();

    // 更新可见性（根据当前模式）
    updateVisiblePhasors();

    // 刷新显示
    updatePhasorDisplay();
}

void ac_chart::drawGrid(QPainter &painter, const QRect &rect)
{
    QPointF center = rect.center();
    double radius = qMin(rect.width(), rect.height()) / 2.0 - 10;

    // === 1. 绘制同心圆（可选）===
    if (_showGridCircles) {
        QPen circlePen(QColor(50, 50, 50)); // 深灰色圆
        circlePen.setWidth(1);
        painter.setPen(circlePen);
        painter.setFont(QFont("Arial", 7));

        int steps = 5; // 5个同心圆
        double stepVal = _maxMagnitude / steps;
        for (int i = 1; i <= steps; ++i) {
            double r = radius * i / steps;
            painter.drawEllipse(center, r, r);

            // 在右侧标注刻度值
            QString txt = QString::number(stepVal * i, 'f', 0);
            painter.drawText(QPointF(center.x() + r + 3, center.y() + 4), txt);
        }
    }

    // === 2. 绘制辐射线（每30°）===
    QPen radPen(QColor(64, 64, 64)); // 辐射线颜色
    radPen.setWidth(1);
    painter.setPen(radPen);
    for (int deg = 0; deg < 360; deg += 30) {
        double rad = deg * M_PI / 180.0;
        double x = center.x() + radius * cos(rad);
        double y = center.y() - radius * sin(rad); // 注意：Y轴向下
        painter.drawLine(center, QPointF(x, y));

        // 每90°标注一次角度
        if (deg % 90 == 0) {
            QString angle = QString::number(deg) + "°";
            double tx = center.x() + (radius + 18) * cos(rad);
            double ty = center.y() - (radius + 18) * sin(rad);
            painter.drawText(QPointF(tx - 15, ty + 6), angle);
        }
    }

    // === 3. 绘制X/Y坐标轴===
    if (_showAxes) {
        QPen axisPen(Qt::white);
        axisPen.setWidth(1);
        painter.setPen(axisPen);
        // X轴
        painter.drawLine(QPointF(center.x() - radius - 25, center.y()),
                         QPointF(center.x() + radius + 25, center.y()));
        // Y轴
        painter.drawLine(QPointF(center.x(), center.y() - radius - 25),
                         QPointF(center.x(), center.y() + radius + 25));
    }
}

void ac_chart::drawPhasor(QPainter &painter, const QRect &rect, const Phasor &p, const QPointF &center)
{
    double radius = qMin(rect.width(), rect.height()) / 2.0 - 10;
    double scale = radius / _maxMagnitude; // 像素/单位值
    double len = p.magnitude * scale;       // 矢量长度（像素）
    double rad = p.phase * M_PI / 180.0;    // 角度转弧度

    // 终点坐标
    double x2 = center.x() + len * cos(rad);
    double y2 = center.y() - len * sin(rad);

    // === 绘制主线 ===
    QPen pen(p.color);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(center, QPointF(x2, y2));

    // === 绘制箭头（等边三角形）===
    double arrowSize = 10;
    double angle = atan2(y2 - center.y(), x2 - center.x()); // 矢量方向角
    QPointF p1(x2 - arrowSize * cos(angle - M_PI / 6),
               y2 - arrowSize * sin(angle - M_PI / 6));
    QPointF p2(x2 - arrowSize * cos(angle + M_PI / 6),
               y2 - arrowSize * sin(angle + M_PI / 6));

    painter.setBrush(p.color); // 箭头填充
    painter.drawPolygon(QPolygonF() << QPointF(x2, y2) << p1 << p2);

    // === 绘制标签 ===
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 9, QFont::Bold));
    painter.drawText(QPointF(x2 + 8, y2 + 5), p.label);
}

void ac_chart::initAllPhasors()
{
    // 基本相量
    _phasors["UA"] = {0.0, 0.0, QColor(222, 116, 63),  "UA",  false};
    _phasors["UB"] = {0.0, 0.0, QColor(0, 180, 0),     "UB",  false};
    _phasors["UC"] = {0.0, 0.0, Qt::magenta,           "UC",  false};
    _phasors["IA"] = {0.0, 0.0, Qt::red,               "IA",  false};
    _phasors["IB"] = {0.0, 0.0, Qt::blue,              "IB",  false};
    _phasors["IC"] = {0.0, 0.0, Qt::yellow,            "IC",  false};

    // 线电压
    _phasors["UAB"] = {0.0, 0.0, QColor(222, 116, 63), "UAB", false};
    _phasors["UBC"] = {0.0, 0.0, QColor(0, 180, 0),    "UBC", false};
    _phasors["UCA"] = {0.0, 0.0, Qt::magenta,          "UCA", false};

    // 序分量
    _phasors["U0"]  = {0.0, 0.0, Qt::gray,             "U0",  false};
    _phasors["U+"]  = {0.0, 0.0, Qt::cyan,             "U+",  false};
    _phasors["U-"]  = {0.0, 0.0, Qt::red,              "U-",  false};
    _phasors["I0"]  = {0.0, 0.0, Qt::darkGray,         "I0",  false};
    _phasors["I+"]  = {0.0, 0.0, Qt::yellow,           "I+",  false};
    _phasors["I-"]  = {0.0, 0.0, Qt::magenta,          "I-",  false};
}

void ac_chart::parseBasicPhasorsFromMap(const QMap<QString, QList<QVariant> > &map)
{
    QStringList basicKeys = {"UA", "UB", "UC", "IA", "IB", "IC"};
    for (const QString& key : basicKeys) {
        _phasors[key].magnitude = 0.0;
        _phasors[key].phase = 0.0;
        _phasors[key].visible = false;
    }

    // 然后解析更新存在的
    constexpr int COL_MAG = 0;
    constexpr int COL_PHA = 4;

    for (const QString& key : basicKeys) {
        if (map.contains(key)) {
            const auto& values = map[key];
            if (values.size() > qMax(COL_MAG, COL_PHA)) {
                bool okMag = false, okPha = false;
                double mag = values[COL_MAG].toDouble(&okMag);
                double pha = values[COL_PHA].toDouble(&okPha);
                if (okMag && okPha) {
                    _phasors[key].magnitude = mag;
                    _phasors[key].phase = pha;
                    _phasors[key].visible = true;
                }
            }
        }
    }
}

void ac_chart::calculateDerivedPhasors()
{
    auto toComplex = [](const Phasor& p) {
        return std::polar(p.magnitude, p.phase * M_PI / 180.0);
    };

    auto updatePhasor = [](Phasor& p, const std::complex<double>& c) {
        p.magnitude = std::abs(c);
        p.phase = std::arg(c) * 180.0 / M_PI;
    };

    // 检查电压/电流是否完整
    bool hasAllVoltages = _phasors["UA"].visible && _phasors["UB"].visible && _phasors["UC"].visible;
    bool hasAllCurrents = _phasors["IA"].visible && _phasors["IB"].visible && _phasors["IC"].visible;

    std::complex<double> Ua, Ub, Uc, Ia, Ib, Ic;

    if (_phasors["UA"].visible) Ua = toComplex(_phasors["UA"]);
    if (_phasors["UB"].visible) Ub = toComplex(_phasors["UB"]);
    if (_phasors["UC"].visible) Uc = toComplex(_phasors["UC"]);

    if (_phasors["IA"].visible) Ia = toComplex(_phasors["IA"]);
    if (_phasors["IB"].visible) Ib = toComplex(_phasors["IB"]);
    if (_phasors["IC"].visible) Ic = toComplex(_phasors["IC"]);

    // 线电压 —— 只有当两个相电压都存在时才计算
    if (_phasors["UA"].visible && _phasors["UB"].visible)
        updatePhasor(_phasors["UAB"], Ua - Ub);
    else
        _phasors["UAB"].magnitude = 0;

    if (_phasors["UB"].visible && _phasors["UC"].visible)
        updatePhasor(_phasors["UBC"], Ub - Uc);
    else
        _phasors["UBC"].magnitude = 0;

    if (_phasors["UC"].visible && _phasors["UA"].visible)
        updatePhasor(_phasors["UCA"], Uc - Ua);
    else
        _phasors["UCA"].magnitude = 0;

    // 序分量 —— 需要三相都存在才计算，否则设为0
    if (hasAllVoltages) {
        std::complex<double> a  = std::polar(1.0, 120.0 * M_PI / 180.0);
        std::complex<double> a2 = a * a;

        std::complex<double> Uzero = (Ua + Ub + Uc) / 3.0;
        std::complex<double> Upos  = (Ua + a * Ub  + a2 * Uc) / 3.0;
        std::complex<double> Uneg  = (Ua + a2 * Ub + a * Uc)  / 3.0;

        updatePhasor(_phasors["U0"], Uzero);
        updatePhasor(_phasors["U+"], Upos);
        updatePhasor(_phasors["U-"], Uneg);
    } else {
        _phasors["U0"].magnitude = 0;
        _phasors["U+"].magnitude = 0;
        _phasors["U-"].magnitude = 0;
    }

    if (hasAllCurrents) {
        std::complex<double> a  = std::polar(1.0, 120.0 * M_PI / 180.0);
        std::complex<double> a2 = a * a;

        std::complex<double> Izero = (Ia + Ib + Ic) / 3.0;
        std::complex<double> Ipos  = (Ia + a * Ib  + a2 * Ic) / 3.0;
        std::complex<double> Ineg  = (Ia + a2 * Ib + a * Ic)  / 3.0;

        updatePhasor(_phasors["I0"], Izero);
        updatePhasor(_phasors["I+"], Ipos);
        updatePhasor(_phasors["I-"], Ineg);
    } else {
        _phasors["I0"].magnitude = 0;
        _phasors["I+"].magnitude = 0;
        _phasors["I-"].magnitude = 0;
    }
}

void ac_chart::updateVisiblePhasors()
{
    // 先全部隐藏
    for (auto& p : _phasors) {
        p.visible = false;
    }

    switch (_mode) {
    case 0: // 相分量 → 只显示实际传入的（依赖 parse 设置的 visible 和 magnitude>0）
        if (_phasors["UA"].magnitude > 1e-6) _phasors["UA"].visible = true;
        if (_phasors["UB"].magnitude > 1e-6) _phasors["UB"].visible = true;
        if (_phasors["UC"].magnitude > 1e-6) _phasors["UC"].visible = true;
        if (_phasors["IA"].magnitude > 1e-6) _phasors["IA"].visible = true;
        if (_phasors["IB"].magnitude > 1e-6) _phasors["IB"].visible = true;
        if (_phasors["IC"].magnitude > 1e-6) _phasors["IC"].visible = true;
        break;

    case 1: // 线电压 → 显示存在的线电压 + 存在的相电流
        if (_phasors["UAB"].magnitude > 1e-6) _phasors["UAB"].visible = true;
        if (_phasors["UBC"].magnitude > 1e-6) _phasors["UBC"].visible = true;
        if (_phasors["UCA"].magnitude > 1e-6) _phasors["UCA"].visible = true;

        if (_phasors["IA"].magnitude > 1e-6) _phasors["IA"].visible = true;
        if (_phasors["IB"].magnitude > 1e-6) _phasors["IB"].visible = true;
        if (_phasors["IC"].magnitude > 1e-6) _phasors["IC"].visible = true;
        break;

    case 2: // 序分量 → 只显示非零的（已用 >1e-6）
        if (_phasors["U0"].magnitude > 1e-6) _phasors["U0"].visible = true;
        if (_phasors["U+"].magnitude > 1e-6) _phasors["U+"].visible = true;
        if (_phasors["U-"].magnitude > 1e-6) _phasors["U-"].visible = true;
        if (_phasors["I0"].magnitude > 1e-6) _phasors["I0"].visible = true;
        if (_phasors["I+"].magnitude > 1e-6) _phasors["I+"].visible = true;
        if (_phasors["I-"].magnitude > 1e-6) _phasors["I-"].visible = true;
        break;
    }
}

void ac_chart::slot_onZoomOut()
{
    // 找到当前量程在序列中的位置
    int currentIndex = _scaleLevels.indexOf(_currentScale);
    if (currentIndex == -1) {
        _currentScale = _baseScale;  // 异常恢复
    } else {
        // 切换到下一个更小的量程
        int nextIndex = (currentIndex + 1) % _scaleLevels.size();
        _currentScale = _scaleLevels[nextIndex];
    }

    // 更新最大刻度（m_maxMagnitude 控制网格）
    _maxMagnitude = _currentScale;

    update();  // 触发重绘
}

void ac_chart::updatePhasorDisplay()
{
    double maxMag = 0;
    for (const auto& p : _phasors) {
        maxMag = qMax(maxMag, p.magnitude);
    }

    // 只在矢量超出当前量程时才自动放大
    if (maxMag > _currentScale * 0.9) {
        _maxMagnitude = maxMag * 1.2;
    } else {
        _maxMagnitude = _currentScale;  // 保持用户设置的量程
    }

    update();  // 重绘
}
