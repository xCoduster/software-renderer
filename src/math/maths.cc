#include "maths.h"

#include <cstdlib>

inline Vector2 perpendicular(const Vector2& v)
{
    return {v.y, -v.x};
}

inline float signed_triangle_area(const Vector2& a, const Vector2& b, const Vector2& c)
{
    // Vector2 ac = c - a;
    // Vector2 abPerp = perpendicular(b - a);
    // return Vector2DotProduct(ac, abPerp) / 2.f;
    Vector2 ac{c.x - a.x, c.y - a.y};
    Vector2 abPerp{b.y - a.y, a.x - b.x};
    return (ac.x * abPerp.x + ac.y * abPerp.y) / 2.f;
}

bool point_in_triangle(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& p)
{
    float areaABP = signed_triangle_area(a, b, p);
    float areaBCP = signed_triangle_area(b, c, p);
    float areaCAP = signed_triangle_area(c, a, p);
    return areaABP >= 0 && areaBCP >= 0 && areaCAP >= 0 && (areaABP + areaBCP + areaCAP) > 0;
}

Vector3 weights(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& p)
{
    float areaABP = signed_triangle_area(a, b, p);
    float areaBCP = signed_triangle_area(b, c, p);
    float areaCAP = signed_triangle_area(c, a, p);
    Vector3 weights{areaABP, areaBCP, areaCAP};

    return weights / (areaABP + areaBCP + areaCAP);
}

bool point_in_triangle_b(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& p)
{
    auto v0 = b - a;
    auto v1 = c - a;
    auto v2 = p - a;
    auto d00 = Vector3DotProduct(v0, v0);
    auto d01 = Vector3DotProduct(v0, v1);
    auto d11 = Vector3DotProduct(v1, v1);
    auto d20 = Vector3DotProduct(v2, v0);
    auto d21 = Vector3DotProduct(v2, v1);
    auto det = (d00 * d11 - d01 * d01);
    auto v = (d11 * d20 - d01 * d21) / det;
    auto w = (d00 * d21 - d01 * d20) / det;
    auto u = 1.0f - v - w;
    return u >= 0 && v >= 0 && w >= 0 && u + v + w == 1.0f;
}

inline Vector3 operator/(float lhs, const Vector3& rhs)
{
    return {lhs / rhs.x, lhs / rhs.y, lhs / rhs.z};
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

int random(int min, int max)
{
    int range{max - min + 1};

    if (range == 0)
        return 0;

    return min + std::rand() % range;
}
