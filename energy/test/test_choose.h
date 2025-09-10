#ifndef TEST_CHOOSE_H
#define TEST_CHOOSE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QScrollArea>
#include <QDialog>
#include <QLabel>
#include <QStyleFactory>
#include <QObject>

namespace Ui {
class test_choose;
}

class test_choose : public QWidget
{
    Q_OBJECT

public:
    explicit test_choose(QWidget *parent = nullptr);
    QString getSelectedFunction() const;
    ~test_choose();

signals:
    void sig_test_pro_choose(quint16);

private:
    Ui::test_choose *ui;

    void setupUI();
    void applyIndustrialStyle();

    quint16 current_test_index;

    QListWidget *listWidget;
};

#endif // TEST_CHOOSE_H
