#pragma once
#include <QtTest/QtTest>

#include "Matrix.h"

namespace core
{
namespace test
{
class Matrix : public QObject
{
    Q_OBJECT
 public:
    Matrix();
 private slots:
    void basics();
    void operations();
};
}  // namespace test
}  // namespace core
