#include "Transform.h"

#include <cmath>

#include "math/maths.h"

aTransform::aTransform()
    : position{}, scale{1.f, 1.f, 1.f}, pitch{}, yaw{}, roll{}, rotation_m{}
{
    set_rotation(0.f, 0.f, 0.f);
}

Vector3 aTransform::to_world_point(const Vector3& p) const
{
    Vector3 point{p * scale};
    return rotation_m * point + position;
}

Vector3 aTransform::to_local_point(const Vector3& p) const
{
    return rotation_m.transpose() * (p - position);
}

Matrix33 aTransform::get_basis_vectors() const
{
    // clang-format off
    Matrix33 pitch_m{1,        0,               0,
                     0,  std::cos(pitch), std::sin(pitch),
                     0, -std::sin(pitch), std::cos(pitch)
                    };

    Matrix33 yaw_m  {std::cos(yaw), 0, -std::sin(yaw),
                           0,       1,        0,
                     std::sin(yaw), 0,  std::cos(yaw)
                    };
    
    Matrix33 roll_m {std::cos(roll), -std::sin(roll), 0,
                     std::sin(roll),  std::cos(roll), 0,
                           0,               0,        1
                    };
    // clang-format on

    return roll_m * yaw_m * pitch_m;
}

void aTransform::set_rotation(float pitch, float yaw, float roll)
{
    this->pitch = pitch;
    this->yaw = yaw;
    this->roll = roll;

    rotation_m = get_basis_vectors();
}

void aTransform::set_pitch(float pitch)
{
    set_rotation(pitch, yaw, roll);
}

void aTransform::set_yaw(float yaw)
{
    set_rotation(pitch, yaw, roll);
}

void aTransform::set_roll(float roll)
{
    set_rotation(pitch, yaw, roll);
}

float aTransform::get_pitch() const
{
    return pitch;
}

float aTransform::get_yaw() const
{
    return yaw;
}

float aTransform::get_roll() const
{
    return roll;
}
