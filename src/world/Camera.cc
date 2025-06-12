#include "Camera.h"

#include "math/maths.h"

#include <algorithm>
#include <iostream>

aCamera::aCamera()
    : fov{45.f}, transform{}
{
    transform.scale = {1.f, 1.f, 1.f};
}

void aCamera::update(float dt)
{
    if (IsCursorHidden())
    {
        Vector2 mouseDelta{GetMouseDelta() * 0.05f * dt};
        transform.set_pitch(std::clamp(transform.get_pitch() + mouseDelta.y, DEG2RAD * -85.f, DEG2RAD * 85.f));
        transform.set_yaw(transform.get_yaw() - mouseDelta.x);

        const float speed{2.f};
        Matrix33 m{transform.get_basis_vectors()};
        Vector3 moveDelta{Vector3Zero()};

        if (IsKeyDown(KeyboardKey::KEY_W))
            moveDelta += m.c3();
        if (IsKeyDown(KeyboardKey::KEY_S))
            moveDelta -= m.c3();
        if (IsKeyDown(KeyboardKey::KEY_A))
            moveDelta -= m.c1();
        if (IsKeyDown(KeyboardKey::KEY_D))
            moveDelta += m.c1();

        moveDelta = Vector3Normalize(moveDelta) * speed * dt;
        transform.position.x += moveDelta.x;
        transform.position.z += moveDelta.z;
        transform.position.y += GetMouseWheelMoveV().y / 5.f;
    }
}
