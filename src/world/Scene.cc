#include "Scene.h"

#include "math/maths.h"

Scene::Scene()
    : models{}, camera{}
{
    models.push_back(load_from_file("res/cube.obj"));
    models.back().transform.position = {-1.f, 0.f, 3.f};
    models.back().transform.scale /= 2.f;
    models.push_back(load_from_file("res/monkey.obj"));
    models.back().transform.position = {1.f, 0.f, 3.f};
    models.back().transform.set_pitch(DEG2RAD * 180.f);
}

void Scene::update(float dt)
{
    for (aModel& model : models)
        model.update(dt);
    models.front().transform.set_roll(models.front().transform.get_roll() + dt);

    camera.update(dt);
}
