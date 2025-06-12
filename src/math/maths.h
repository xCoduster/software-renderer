#ifndef MATHS_H_
#define MATHS_H_

#include <raylib.h>
#include <raymath.h>

#include <ostream>

inline Vector2 perpendicular(const Vector2& v);

inline float signed_triangle_area(const Vector2& a, const Vector2& b, const Vector2& c);
bool point_in_triangle(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& p);
Vector3 weights(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& p);

bool point_in_triangle_b(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& p);

inline Vector3 operator/(float lhs, const Vector3& rhs);

std::ostream& operator<<(std::ostream& os, const Vector2& vec);
std::ostream& operator<<(std::ostream& os, const Vector3& vec);

int random(int min, int max);

#endif // MATHS_H_
