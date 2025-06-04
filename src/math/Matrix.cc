#include "Matrix.h"

Matrix33 Matrix33::operator*(const Matrix33& rhs) const
{
    Matrix33 result{};
    result.m0 = m0 * rhs.m0 + m3 * rhs.m1 + m6 * rhs.m2;
    result.m1 = m1 * rhs.m0 + m4 * rhs.m1 + m7 * rhs.m2;
    result.m2 = m2 * rhs.m0 + m5 * rhs.m1 + m8 * rhs.m2;

    result.m3 = m0 * rhs.m3 + m3 * rhs.m4 + m6 * rhs.m5;
    result.m4 = m1 * rhs.m3 + m4 * rhs.m4 + m7 * rhs.m5;
    result.m5 = m2 * rhs.m3 + m5 * rhs.m4 + m8 * rhs.m5;

    result.m6 = m0 * rhs.m6 + m3 * rhs.m7 + m6 * rhs.m8;
    result.m7 = m1 * rhs.m6 + m4 * rhs.m7 + m7 * rhs.m8;
    result.m8 = m2 * rhs.m6 + m5 * rhs.m7 + m8 * rhs.m8;

    return result;
}

Vector3 Matrix33::operator*(const Vector3& rhs) const
{
    Vector3 result{};
    result.x = m0 * rhs.x + m3 * rhs.y + m6 * rhs.z;
    result.y = m1 * rhs.x + m4 * rhs.y + m7 * rhs.z;
    result.z = m2 * rhs.x + m5 * rhs.y + m8 * rhs.z;

    return result;
}

Matrix33 Matrix33::transpose() const
{
    Matrix33 result{};
    result.m0 = m0;
    result.m1 = m3;
    result.m2 = m6;

    result.m3 = m1;
    result.m4 = m4;
    result.m5 = m7;

    result.m6 = m2;
    result.m7 = m5;
    result.m8 = m8;

    return result;
}

Matrix33 Matrix33::identity()
{
    return Matrix33{1, 0, 0, 0, 1, 0, 0, 0, 1};
}
