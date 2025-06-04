#ifndef RENDERER_H_
#define RENDERER_H_

#include "RenderTarget.h"
#include "world/Camera.h"
#include "world/Scene.h"
#include "world/Transform.h"

class Renderer
{
public:
    Renderer();

    void Render(RenderTarget& target, const Scene& scene);
};

Vector3 vertex_to_screen(const Vector3& vertex, const aTransform& transform, const aCamera& cam,
                         const Vector2& screen_size);

#endif // RENDERER_H_
