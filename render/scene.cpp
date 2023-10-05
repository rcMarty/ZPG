//
// Created by rc_marty on 30.9.23.
//

#include "scene.h"
#include "../resources/models/suzi_flat.h"


Scene Scene::add_object(Renderable_object object) {
    objects.push_back(object);
    return *this;
}

void Scene::init() {
    set_scene();
    for (auto &object : objects) {
        object.init();
    }
}

void Scene::render() {
    for (auto &object : objects) {
        object.render();
    }
}

Renderable_object Scene::find_object(std::string name) {
    for (auto &object : objects) {
        if (object.name == name) {
            return object;
        }
    }
    return Renderable_object();
}

void Scene::set_scene() {
    Shader shader = Shader("../shader/vertex_shader/flat_v3.vert", "../shader/fragment_shader/flat_v3.frag");

#include "../resources/models/sphere.h"

    //Renderable_object pyramid = Renderable_object(Mesh(sphere,17280), shader).set_name("jehlan");
    //add_object(pyramid);


    Renderable_object suzie4k = Renderable_object(Mesh("../resources/models/suzi.obj"), shader).set_name("opice4k");
    add_object(suzie4k);

}
