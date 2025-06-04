#ifndef RENDERTARGET_H_
#define RENDERTARGET_H_

#include <raylib.h>

#include <vector>

struct RenderTarget
{
    RenderTarget(int width, int height)
        : size{static_cast<float>(width), static_cast<float>(height)}, colour_buffer{}, depth_buffer{}
    {
        colour_buffer.resize(width * height);
        depth_buffer.resize(width * height);
    }

    Vector2 size;
    std::vector<Color> colour_buffer;
    std::vector<float> depth_buffer;
};

#endif // RENDERTARGET_H_
