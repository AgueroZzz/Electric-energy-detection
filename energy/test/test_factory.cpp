#include "test_factory.h"

QMap<quint16, TestCreator>& TestFactory::instance()
{
    static QMap<quint16, TestCreator> factory;
    return factory;
}
