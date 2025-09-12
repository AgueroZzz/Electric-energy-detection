#ifndef SQL_H
#define SQL_H

#include <QObject>

class sql : public QObject
{
    Q_OBJECT
public:
    explicit sql(QObject *parent = nullptr);

signals:
};

#endif // SQL_H
