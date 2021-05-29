#include "TestMatrix.h"

core::test::Matrix::Matrix()
{
}


void core::test::Matrix::basics()
{
    auto m = core::Matrix({{1, 2, 3}, {4, 5, 6}});

    QCOMPARE(m[0][0], 1);
    QCOMPARE(m[0][1], 2);
    QCOMPARE(m[0][2], 3);
    QCOMPARE(m[1][0], 4);
    QCOMPARE(m[1][1], 5);
    QCOMPARE(m[1][2], 6);

    m[0][1] = 10;

    QCOMPARE(m[0][1], 10);

    auto m1 = core::Matrix({{1, 2}, {3, 4}});
    auto m2 = m1;

    QCOMPARE(m2, m1);

    m2[0][1] = 2;
    m1 = m2;

    QCOMPARE(m1, m2);

    const auto filled = core::Matrix<int, 2, 2>(0);
    QCOMPARE(filled[0][0], 0);
    QCOMPARE(filled[0][1], 0);
    QCOMPARE(filled[1][0], 0);
    QCOMPARE(filled[1][1], 0);
}


void core::test::Matrix::operations()
{
    const auto m1 = core::Matrix({{1, 2}, {3, 4}}) + core::Matrix({{4, 3}, {2, 1}});
    const auto m2 = core::Matrix<int, 2, 2>(5);
    QCOMPARE(m1, m2);

    const auto zeros = core::Matrix<int, 2, 2>(0);
    QCOMPARE(m1 - m1, zeros);

    const auto m3 =
        core::Matrix({{1, 2, 3}, {4, 5, 6}}) * core::Matrix({{10, 11}, {20, 21}, {30, 31}});
    const auto m4 = core::Matrix({{140, 146}, {320, 335}});
    QCOMPARE(m3, m4);

    qDebug().nospace() << '\n' << (0.5 * core::Matrix({{1, 2}, {3, 4}})).toStr().c_str();
}
