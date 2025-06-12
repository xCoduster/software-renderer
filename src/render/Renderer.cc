#include "Renderer.h"

#include "math/maths.h"

#include <algorithm>
#include <iostream>
#include <limits>

Renderer::Renderer()
{
}

void Renderer::Render(RenderTarget& target, const Scene& scene)
{
    std::fill(target.colour_buffer.begin(), target.colour_buffer.end(), BLACK);
    std::fill(target.depth_buffer.begin(), target.depth_buffer.end(), std::numeric_limits<float>::infinity());

    for (const aModel& model : scene.models)
    {
        for (auto it = model.triangles.begin(); it != model.triangles.end(); ++it)
        {
            Vector3 a = vertex_to_screen(model.vertices[it->v.at(0)], model.transform, scene.camera, target.size);
            Vector3 b = vertex_to_screen(model.vertices[it->v.at(1)], model.transform, scene.camera, target.size);
            Vector3 c = vertex_to_screen(model.vertices[it->v.at(2)], model.transform, scene.camera, target.size);

            if (a.z <= 0.f || b.z <= 0.f || c.z <= 0.f)
                continue;

            int minX = std::min(std::min(a.x, b.x), c.x);
            int minY = std::min(std::min(a.y, b.y), c.y);
            int maxX = std::ceil(std::max(std::max(a.x, b.x), c.x));
            int maxY = std::ceil(std::max(std::max(a.y, b.y), c.y));

            int blockStartX = std::clamp(minX, 0, static_cast<int>(target.size.x));
            int blockStartY = std::clamp(minY, 0, static_cast<int>(target.size.y));
            int blockEndX = std::clamp(maxX, 0, static_cast<int>(target.size.x));
            int blockEndY = std::clamp(maxY, 0, static_cast<int>(target.size.y));

            for (int y = blockStartY; y < blockEndY; ++y)
            {
                for (int x = blockStartX; x < blockEndX; ++x)
                {
                    Vector2 p{};
                    p.x = x;
                    p.y = y;
                    if (point_in_triangle({a.x, a.y}, {b.x, b.y}, {c.x, c.y}, p))
                    {
                        Vector3 weight{weights({a.x, a.y}, {b.x, b.y}, {c.x, c.y}, p)};
                        Vector3 depths{1 / a.z, 1 / b.z, 1 / c.z};
                        float depth = 1.f / Vector3DotProduct(depths, weight);
                        if (depth > target.depth_buffer[x + target.size.x * y])
                            continue;
                        target.colour_buffer[x + target.size.x * y] = it->col;
                        target.depth_buffer[x + target.size.x * y] = depth;
                    }
                }
            }
        }
    }
}

Vector3 vertex_to_screen(const Vector3& vertex, const aTransform& transform, const aCamera& cam,
                         const Vector2& screen_size)
{
    Vector3 v_world{transform.to_world_point(vertex)};
    Vector3 v_view{cam.transform.to_local_point(v_world)};

    float screenHeight_world = std::tan(cam.fov / 2.f) * 2.f;
    float pixels_per_world_unit = screen_size.y / screenHeight_world / v_view.z;
    Vector2 pixelOffset{v_view.x, v_view.y};
    pixelOffset *= pixels_per_world_unit;
    Vector2 v_screen{screen_size / 2.f + pixelOffset};

    return Vector3{v_screen.x, v_screen.y, v_view.z};
}
