#include "Model.h"

#include <fstream>
#include <sstream>

#include "math/maths.h"

aModel::aModel()
    : vertices{}, triangles{}, transform{}
{
}

void aModel::update(float dt)
{
}

aModel load_from_file(const std::string& file_path)
{
    aModel model{};
    std::ifstream ifs{file_path};

    for (std::string line; std::getline(ifs, line);)
    {
        if (line[0] == '#')
            continue;

        if (line.substr(0, 2) == "v ")
        {
            std::istringstream iss{line.substr(2)};
            float x, y, z;
            iss >> x >> y >> z;
            model.vertices.push_back({x, y, z});
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::istringstream iss{line.substr(2)};
            int i{};
            std::size_t first{};
            for (std::string vertex{}; std::getline(iss, vertex, ' '); ++i)
            {
                if (i == 0)
                {
                    model.triangles.emplace_back();
                    model.triangles.back().col.r = random(0, 255);
                    model.triangles.back().col.g = random(0, 255);
                    model.triangles.back().col.b = random(0, 255);
                    model.triangles.back().col.a = 255;

                    first = std::distance(model.triangles.begin(), model.triangles.end() - 1);
                }
                std::istringstream v_iss{vertex};
                std::size_t v;
                v_iss >> v;
                --v;
                if (i >= 3)
                {
                    auto prev = std::prev(model.triangles.end());
                    model.triangles.emplace_back();
                    model.triangles.back().col.r = random(0, 255);
                    model.triangles.back().col.g = random(0, 255);
                    model.triangles.back().col.b = random(0, 255);
                    model.triangles.back().col.a = 255;

                    model.triangles.back().v.at(0) = model.triangles.at(first).v.at(0);
                    model.triangles.back().v.at(1) = prev->v.at(2);
                    model.triangles.back().v.at(2) = v;
                }
                else
                    model.triangles.back().v.at(i) = v;
            }
        }
    }

    return model;
}
