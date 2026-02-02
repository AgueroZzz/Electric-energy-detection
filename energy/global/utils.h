#ifndef UTILS_H
#define UTILS_H

#include <QTableWidget>
#include <QMap>
#include <QVariant>
#include <QList>
#include <QCheckBox>
#include <QWidget>
#include <QDebug>
#include <complex.h>
#include <math.h>
#include <QPair>

struct VoltagePhasor
{
    double rms;       // 有效值
    double phase_deg; // 相位（角度）
};

static constexpr double DEG2RAD = M_PI / 180.0;
static constexpr double RAD2DEG = 180.0 / M_PI;

namespace GlobalUtils {
// 工具函数：获取表格中的所有列的数据：数据格式(QMap<QString, QStringList>)
inline void get_table_values(const QTableWidget& table, QMap<QString, QList<QVariant>>& map){
    map.clear();
    constexpr int COL_PARAM = 0;        // 第一列为KEY
    for(int r = 0; r <table.rowCount(); ++r){
        auto* param = table.item(r, COL_PARAM);
        if(!param || param->text().trimmed().isEmpty())
            continue;
        QString key = param->text().trimmed();
        QList<QVariant> row;

        for(int c = 1; c < table.columnCount(); ++c){
            if(QWidget* cell = table.cellWidget(r, c)){
                if(QCheckBox* cb = cell->findChild<QCheckBox*>()){
                    row << cb->isChecked();
                    continue;
                }
            }

            auto* item = table.item(r, c);
            row << (item ? item->text().trimmed() : QString());
        }

        map.insert(key ,row);
    }
}

// Ux计算方式
inline std::complex<double> calcUx(const VoltagePhasor& UA, const VoltagePhasor& UB, const VoltagePhasor& UC, double k){
    auto toComplex = [](const VoltagePhasor& U) {
        double rad = U.phase_deg * M_PI / 180.0;
        return std::polar(U.rms, rad);
    };

    std::complex<double> Ux =
        k * (toComplex(UA) + toComplex(UB) + toComplex(UC));

    // 工程级零值处理
    constexpr double EPS = 1e-9;

    if (std::abs(Ux) < EPS) {
        Ux = std::complex<double>(0.0, 0.0);
    }

    return Ux;
}

// 计算UAB/UBC/UCA
inline QMap<QString, QPair<QString, QString>> calcLineVoltageMap(
    double Ua_rms, double Ua_deg,
    double Ub_rms, double Ub_deg,
    double Uc_rms, double Uc_deg
    )
{
    QMap<QString, QPair<QString, QString>> result;

    // 1. 相电压 → 复数相量
    auto makePhasor = [](double rms, double deg) {
        return std::polar(rms, deg * DEG2RAD);
    };

    std::complex<double> UA = makePhasor(Ua_rms, Ua_deg);
    std::complex<double> UB = makePhasor(Ub_rms, Ub_deg);
    std::complex<double> UC = makePhasor(Uc_rms, Uc_deg);

    // 2. 线电压
    QMap<QString, std::complex<double>> lineMap;
    lineMap["UAB"] = UA - UB;
    lineMap["UBC"] = UB - UC;
    lineMap["UCA"] = UC - UA;

    // 3. 转字符串（格式化）
    for (auto it = lineMap.begin(); it != lineMap.end(); ++it) {
        const std::complex<double>& z = it.value();

        double rms   = std::abs(z);
        double phase = std::arg(z) * RAD2DEG;

        // 相位归一到 [-180, 180)
        if (phase >= 180.0) phase -= 360.0;
        if (phase < -180.0) phase += 360.0;

        QString rmsStr   = QString("%1").arg(rms,   0, 'f', 3, QLatin1Char('+'));
        QString phaseStr = QString("%1").arg(phase, 0, 'f', 1, QLatin1Char('+'));

        result[it.key()] = qMakePair(rmsStr, phaseStr);
    }
    return result;
}

// 计算U0/U+/U-
inline QMap<QString, QPair<QString, QString>> calcSymmetricalVoltageMap(
    double Ua_rms, double Ua_deg,
    double Ub_rms, double Ub_deg,
    double Uc_rms, double Uc_deg
    )
{
    QMap<QString, QPair<QString, QString>> result;

    // 1. 相电压 → 复数相量
    auto makePhasor = [](double rms, double deg) {
        return std::polar(rms, deg * DEG2RAD);
    };

    std::complex<double> UA = makePhasor(Ua_rms, Ua_deg);
    std::complex<double> UB = makePhasor(Ub_rms, Ub_deg);
    std::complex<double> UC = makePhasor(Uc_rms, Uc_deg);

    // 2. 旋转算子 a = e^(j120°)
    std::complex<double> a  = std::polar(1.0, 120.0 * DEG2RAD);
    std::complex<double> a2 = a * a;

    // 3. 对称分量
    std::complex<double> U0 = (UA + UB + UC) / 3.0;
    std::complex<double> Up = (UA + a * UB + a2 * UC) / 3.0;
    std::complex<double> Um = (UA + a2 * UB + a * UC) / 3.0;

    QMap<QString, std::complex<double>> seqMap;
    seqMap["U0"] = U0;
    seqMap["U+"] = Up;
    seqMap["U-"] = Um;

    // 4. 格式化输出
    for (auto it = seqMap.begin(); it != seqMap.end(); ++it) {
        const std::complex<double>& z = it.value();

        double rms   = std::abs(z);
        double phase = std::arg(z) * RAD2DEG;

        // 相位归一到 [-180, 180)
        if (phase >= 180.0) phase -= 360.0;
        if (phase < -180.0) phase += 360.0;

        QString rmsStr   = QString("%1").arg(rms,   0, 'f', 3, QLatin1Char('+'));
        QString phaseStr = QString("%1").arg(phase, 0, 'f', 1, QLatin1Char('+'));

        result[it.key()] = qMakePair(rmsStr, phaseStr);
    }

    return result;
}

// 计算IO/I+/I-
inline QMap<QString, QPair<QString, QString>> calcSymmetricalCurrentMap(
    double Ia_rms, double Ia_deg,
    double Ib_rms, double Ib_deg,
    double Ic_rms, double Ic_deg
    )
{
    QMap<QString, QPair<QString, QString>> result;
    auto makePhasor = [](double rms, double deg) {
        return std::polar(rms, deg * DEG2RAD);
    };

    std::complex<double> IA = makePhasor(Ia_rms, Ia_deg);
    std::complex<double> IB = makePhasor(Ib_rms, Ib_deg);
    std::complex<double> IC = makePhasor(Ic_rms, Ic_deg);

    std::complex<double> a  = std::polar(1.0, 120.0 * DEG2RAD);
    std::complex<double> a2 = a * a;

    std::complex<double> I0 = (IA + IB + IC) / 3.0;
    std::complex<double> Ip = (IA + a * IB + a2 * IC) / 3.0;
    std::complex<double> Im = (IA + a2 * IB + a * IC) / 3.0;

    QMap<QString, std::complex<double>> seqMap;
    seqMap["I0"] = I0;
    seqMap["I+"] = Ip;
    seqMap["I-"] = Im;

    for (auto it = seqMap.begin(); it != seqMap.end(); ++it) {
        const std::complex<double>& z = it.value();

        double rms   = std::abs(z);
        double phase = std::arg(z) * RAD2DEG;

        // 相位归一到 [-180, 180)
        if (phase >= 180.0) phase -= 360.0;
        if (phase < -180.0) phase += 360.0;

        // 幅值接近 0 时，工程上相位清零
        if (rms < 1e-6) {
            phase = 0.0;
        }

        QString rmsStr   = QString("%1").arg(rms,   0, 'f', 3, QLatin1Char('+'));
        QString phaseStr = QString("%1").arg(phase, 0, 'f', 1, QLatin1Char('+'));

        result[it.key()] = qMakePair(rmsStr, phaseStr);
    }

    return result;
}

// 设置QTableWidget单元格状态
inline void setItemState(QTableWidgetItem *item, bool editable, bool green)
{
    if (!item) return;

    if (editable) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setBackground(Qt::white);
    } else {
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);

        if (green) {
            item->setBackground(
                QBrush(QColor("#c2edc3"), Qt::Dense4Pattern)
                );
        } else {
            item->setBackground(Qt::white);
        }
    }
}

// 表格数据检查:验证并格式化输入为指定小数位数的double字符串
inline QString formatDoubleString(const QString& text, int decimals = 3, bool* ok = nullptr)
{
    QString trimmedText = text.trimmed();

    if (ok) *ok = false;

    // 处理空字符串
    if (trimmedText.isEmpty()) {
        if (ok) *ok = true; // 空字符串视为有效，使用默认值
        return QString::number(0.0, 'f', decimals);
    }

    // 尝试转换为double
    bool conversionOk = false;
    double value = trimmedText.toDouble(&conversionOk);

    if (!conversionOk) {
        return QString::number(0.0, 'f', decimals);
    }

    // 检查是否为有效数值
    if (!std::isfinite(value)) {
        return QString::number(0.0, 'f', decimals);
    }

    if (ok) *ok = true;
    return QString::number(value, 'f', decimals);
}
}

#endif // UTILS_H
