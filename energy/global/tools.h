#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>

class tools : public QObject
{
    Q_OBJECT
public:
    explicit tools(QObject *parent = nullptr);

signals:
};

#endif // TOOLS_H
