#include "voltage_chart.h"

voltage_chart::voltage_chart(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(320, 320);
    setStyleSheet("background-color: black;");
}

void voltage_chart::paintEvent(QPaintEvent *event)
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

void voltage_chart::slot_setPhasors(const QMap<QString, Phasor> &phasors)
{
    _phasors = phasors;
    update();
}

void voltage_chart::slot_setMaxScale(double maxValue)
{
    _maxMagnitude = qMax(1.0, maxValue); // 防止为0
    update();
}

void voltage_chart::slot_setShowGridCircles(bool show)
{
    _showGridCircles = show;
    update();
}

void voltage_chart::slot_setShowAxes(bool show)
{
    _showAxes = show;
    update();
}

void voltage_chart::slot_multiplyAllMagnitudes(double factor)
{
    // 遍历所有相量，统一缩放幅值
    for (auto it = _phasors.begin(); it != _phasors.end(); ++it) {
        it->magnitude *= factor;
    }
    update();
}

void voltage_chart::drawGrid(QPainter &painter, const QRect &rect)
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
        axisPen.setWidth(2);
        painter.setPen(axisPen);
        // X轴
        painter.drawLine(QPointF(center.x() - radius - 25, center.y()),
                         QPointF(center.x() + radius + 25, center.y()));
        // Y轴
        painter.drawLine(QPointF(center.x(), center.y() - radius - 25),
                         QPointF(center.x(), center.y() + radius + 25));
    }
}

void voltage_chart::drawPhasor(QPainter &painter, const QRect &rect, const Phasor &p, const QPointF &center)
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
