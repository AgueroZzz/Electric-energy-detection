#ifndef TEST_FACTORY_H
#define TEST_FACTORY_H

// test_factory.h
#pragma once

#include <QMap>
#include <functional>
#include <QDebug>

#include "test/test.h"

using TestCreator = std::function<test*(quint16)>;

// 声明
class TestFactory
{
public:
    static QMap<quint16, TestCreator>& instance();
};

// 宏：必须在 TestFactory 声明之后
#define REGISTER_TEST(TestClass, ID) \
namespace { \
    struct TestClass##_Registrar { \
        TestClass##_Registrar() { \
            auto creator = [](quint16 id) -> test* { \
                return new TestClass(id); \
        }; \
            if (TestFactory::instance().contains(ID)) { \
                qWarning() << "Test ID" << ID << "already registered!"; \
        } \
            TestFactory::instance().insert(ID, creator); \
            qDebug() << "Registered test:" << #TestClass << "-> ID" << ID; \
    } \
}; \
    [[maybe_unused]] static TestClass##_Registrar g_registrar_##TestClass; \
}

#endif // TEST_FACTORY_H
