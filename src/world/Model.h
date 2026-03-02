#ifndef MODEL_H_
#define MODEL_H_

#include <raylib.h>

#include <array>
#include <string>
#include <vector>

#include "Transform.h"

struct Triangle
{
    std::array<std::size_t, 3> v;
    std::array<std::size_t, 3> vt;
    std::array<std::size_t, 3> vn;
    Color col;
};

struct aModel
{
    aModel();

    void update(float dt);

    std::vector<Vector3> vertices;
    std::vector<Vector2> texCoords;
    std::vector<Vector3> normals;
    std::vector<Triangle> triangles;

    aTransform transform;
};

aModel load_from_file(const std::string& file_path);

#endif // MODEL_H_
