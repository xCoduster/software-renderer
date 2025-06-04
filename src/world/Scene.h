#ifndef SCENE_H_
#define SCENE_H_

#include "Camera.h"
#include "Model.h"
#include "render/RenderTarget.h"

#include <vector>

class Scene
{
public:
    Scene();

    void update(float dt);

    std::vector<aModel> models;
    aCamera camera;
};

#endif // SCENE_H_
