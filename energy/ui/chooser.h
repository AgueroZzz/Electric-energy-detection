#ifndef CHOOSER_H
#define CHOOSER_H

#include <QWidget>

namespace Ui {
class chooser;
}

class chooser : public QWidget
{
    Q_OBJECT

public:
    explicit chooser(QWidget *parent = nullptr);
    ~chooser();

private:
    Ui::chooser *ui;
};

#endif // CHOOSER_H
