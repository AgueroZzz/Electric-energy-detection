#ifndef UTILS_H
#define UTILS_H

#include <QTableWidget>
#include <QMap>
#include <QVariant>
#include <QList>
#include <QCheckBox>
#include <QWidget>
#include <QDebug>

namespace GlobalUtils {
    // 工具函数：获取表格中的所有列的数据：数据格式(QMap<QString, QStringList>)
    void get_table_values(const QTableWidget& table, QMap<QString, QList<QVariant>>& map){
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
}

#endif // UTILS_H
