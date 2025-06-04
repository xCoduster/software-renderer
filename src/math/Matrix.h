#ifndef MATRIX_H_
#define MATRIX_H_

#include "maths.h"

class Matrix33
{
public:
    float m0, m3, m6;
    float m1, m4, m7;
    float m2, m5, m8;

    Matrix33 operator*(const Matrix33& rhs) const;
    Vector3 operator*(const Vector3& rhs) const;

    Matrix33 transpose() const;

    Vector3 c1() const
    {
        return {m0, m1, m2};
    }

    Vector3 c2() const
    {
        return {m3, m4, m5};
    }

    Vector3 c3() const
    {
        return {m6, m7, m8};
    }

    static Matrix33 identity();
};

#endif // MATRIX_H_
