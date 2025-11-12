#include "ac_chart.h"
#include <complex>

ac_chart::ac_chart(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(320, 320);
    setStyleSheet("background-color: black;");
    initUI();
}

void ac_chart::paintEvent(QPaintEvent *event)
{
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

void ac_chart::slot_onModeChanged(int Id)
{
    switch (Id) {
    case 0: initPhasors_Phase();     break;
    case 1: initPhasors_Line();      break;
    case 2: initPhasors_Sequence();  break;
    }
    updatePhasorDisplay();
}

void ac_chart::slot_updatePhasorDisplay(const QMap<QString, QPair<double, double> > &data)
{
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        const QString& name = it.key();
        double mag = it.value().first;
        double pha = it.value().second;

        if (_phasors.contains(name)) {
            _phasors[name].magnitude = mag;
            _phasors[name].phase = pha;
        }
    }
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

void ac_chart::initUI()
{
    initPhasors_Phase();
}

void ac_chart::initPhasors_Phase()
{
    _phasors.clear();
    _phasors["UA"] = {100.0,   30.0, QColor(222, 116, 63),     "UA"};
    _phasors["UB"] = {100.0,   150.0, QColor(0, 180, 0), "UB"};
    _phasors["UC"] = {100.0,   270.0, Qt::magenta,    "UC"};
    _phasors["IA"] = {10.0,    60.0, Qt::red,       "IA"};
    _phasors["IB"] = {10.0,    180.0, Qt::blue,      "IB"};
    _phasors["IC"] = {10.0,    300.0, Qt::yellow,    "IC"};
}

void ac_chart::initPhasors_Line()
{
    auto get = [&](const QString& k) {
        auto p = _phasors[k];
        return std::polar(p.magnitude, p.phase * M_PI / 180.0);
    };
    auto to = [&](std::complex<double> c, QString l, QColor col) {
        return Phasor{std::abs(c), std::arg(c)*180/M_PI, col, l};
    };

    auto Ua = get("UA"), Ub = get("UB"), Uc = get("UC");

    _phasors.clear();
    _phasors["UAB"] = to(Ua - Ub, "UAB", QColor(222, 116, 63));
    _phasors["UBC"] = to(Ub - Uc, "UBC", QColor(0,180,0));
    _phasors["UCA"] = to(Uc - Ua, "UCA", Qt::magenta);
    _phasors["IA"] = _phasors.value("IA");
    _phasors["IB"] = _phasors.value("IB");
    _phasors["IC"] = _phasors.value("IC");
}

void ac_chart::initPhasors_Sequence()
{
    auto get = [&](const QString& k) {
        auto p = _phasors[k];
        return std::polar(p.magnitude, p.phase * M_PI / 180.0);
    };
    auto to = [&](std::complex<double> c, QString l, QColor col) {
        return Phasor{std::abs(c), std::arg(c)*180/M_PI, col, l};
    };

    auto Ua = get("UA"), Ub = get("UB"), Uc = get("UC");
    auto Ia = get("IA"), Ib = get("IB"), Ic = get("IC");
    std::complex<double> a = std::polar(1.0, 120 * M_PI / 180);
    std::complex<double> a2 = a * a;

    auto Upos = (Ua + a*Ub + a2*Uc)/3.0;
    auto Uneg = (Ua + a2*Ub + a*Uc)/3.0;
    auto Uzero = (Ua + Ub + Uc)/3.0;
    auto Ipos = (Ia + a*Ib + a2*Ic)/3.0;
    auto Ineg = (Ia + a2*Ib + a*Ic)/3.0;
    auto Izero = (Ia + Ib + Ic)/3.0;

    _phasors.clear();
    _phasors["U+"] = to(Upos,  "U+",  Qt::cyan);
    _phasors["U-"] = to(Uneg,  "U-",  Qt::red);
    _phasors["U0"] = to(Uzero, "U0",  Qt::gray);
    _phasors["I+"] = to(Ipos,  "I+",  Qt::yellow);
    _phasors["I-"] = to(Ineg,  "I-",  Qt::magenta);
    _phasors["I0"] = to(Izero, "I0",  Qt::darkGray);
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
