#ifndef WORLD_CAMERA_H_
#define WORLD_CAMERA_H_

#include "Transform.h"

class aCamera
{
public:
    aCamera();

    void update(float dt);

    float fov;
    aTransform transform;
};

#endif // WORLD_CAMERA_H_