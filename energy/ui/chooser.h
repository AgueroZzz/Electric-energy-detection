#ifndef CHOOSER_H
#define CHOOSER_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QGridLayout>
#include <QToolButton>

namespace Ui {
class chooser;
}

struct TestItem {
    QString title;
    QString iconRes;
    bool selected = false;
};

class chooser : public QWidget
{
    Q_OBJECT

public:
    explicit chooser(QWidget *parent = nullptr);
    ~chooser();

private slots:
    void slot_onItemClicked(int idx);
    // void onExit();
    // void onShutdown();

signals:
    void sig_test_pro_choose(quint16 index);

private:
    Ui::chooser *ui;

    void init_UI();
    void paintEvent(QPaintEvent* event);

    QVector<TestItem> _items;
    QVector<QToolButton*> _btns;
};

#endif // CHOOSER_H
