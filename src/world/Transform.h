#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <raylib.h>

#include "math/Matrix.h"

class aTransform
{
public:
    aTransform();

    Vector3 to_world_point(const Vector3& p) const;
    Vector3 to_local_point(const Vector3& p) const;

    Matrix33 get_basis_vectors() const;

    void set_rotation(float pitch, float yaw, float roll);
    void set_pitch(float pitch);
    void set_yaw(float yaw);
    void set_roll(float roll);

    float get_pitch() const;
    float get_yaw() const;
    float get_roll() const;

    Vector3 position;
    Vector3 scale;

private:
    float pitch; // Rotation around x-axis
    float yaw;   // Rotation around y-axis
    float roll;  // Rotation around z-axis

    Matrix33 rotation_m;
};

#endif // TRANSFORM_H_
