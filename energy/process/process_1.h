#ifndef PROCESS_1_H
#define PROCESS_1_H

#include "process.h"

// 三相交流电流、电压实验

enum class t1_test_type{
    action,
    action_and_return
};

enum class t1_logic_type{
    logic_and,
    logic_or
};

enum class t1_test_auto{
    test_hand,
    test_auto,
    test_h_auto
};

enum class t1_test_auto_tpye{
    t_a_up,
    t_a_down
};

class process_1 : public process
{
public:
    explicit process_1(QObject *parent = nullptr);

public slots:
    void slot_start(QMap<QString, QList<QVariant>> map,
                    t1_test_type type, t1_logic_type logic, t1_test_auto t_auto, t1_test_auto_tpye t_a_t);
    void slot_stop();

private:
    int connectRetryCount = 0;
    static constexpr int MAX_CONNECT_RETRY = 3;
    QTimer *timeoutTimer = nullptr;
    QTimer *runtimeTimer = nullptr;
    quint64 startTimestamp = 0;

    QByteArray _frame;

    QString _test_type;

    void attemptConnect();

private slots:
    void slot_onSerialData(const QByteArray &data);
    void slot_onTimeout();
    void slot_updateRuntime();
};

#endif // PROCESS_1_H
