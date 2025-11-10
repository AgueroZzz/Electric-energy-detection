#ifndef TEST_FACTORY_H
#define TEST_FACTORY_H

#include <QMap>
#include <functional>
#include <QDebug>

#include "test/test.h"

using TestCreator = std::function<test*(quint16)>;

/**
 * @brief 全局测试工厂（单例）
 * @return QMap<quint16, TestCreator>&
 */
inline QMap<quint16, TestCreator>& globalTestFactory()
{
    static QMap<quint16, TestCreator> factory;
    return factory;
}

/**
 * @brief 注册宏：自动将 test_XX 类加入全局工厂
 * @param TestClass  类名（如 test_23）
 * @param ID         对应的 test_id（如 22）
 *
 * 使用方式：
 *   在 test_23.cpp 底部：
 *   REGISTER_TEST(test_23, 22);
 */
#define REGISTER_TEST(TestClass, ID) \
namespace { \
    struct TestClass##_AutoRegistrar { \
        TestClass##_AutoRegistrar() { \
            auto creator = [](quint16 id) -> test* { \
                return new TestClass(id); \
        }; \
            if (globalTestFactory().contains(ID)) { \
                qWarning() << "Test ID" << ID << "already registered! Overwriting."; \
        } \
            globalTestFactory().insert(ID, creator); \
            qDebug() << "Registered test:" << #TestClass << "-> ID" << ID; \
    } \
}; \
    static TestClass##_AutoRegistrar g_##TestClass##_registrar; \
}

#endif // TEST_FACTORY_H
