//
// Created by rc_marty on 30.9.23.
//

#include "scene.h"
#include "../object/transform/transform.h"
#include "../object/transform/transform_node.h"
#include "../object/transform/translation.h"
#include "../object/transform/rotation.h"
#include "../object/transform/scale.h"

Scene Scene::add_object(const Renderable_object &object) {
    objects.push_back(object);
    return *this;
}

void Scene::init() {
    set_scene();
    for (auto &object: objects) {
        object.init();
    }
}

void Scene::render() {


    for (auto &object: objects) {
        //todo no allocation in render loop
        object.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(std::make_shared<Transforms::Rotation>(2, 0, 1, 0)));
        object.render();
    }
}

Renderable_object Scene::find_object(const std::string &name) {
    for (auto &object: objects) {
        if (object.name == name) {
            return object;
        }
    }
    //printf("[ERROR] Object with name %s not found\n", name.c_str());
    fprintf(stderr, "[ERROR] Object with name %s not found\n", name.c_str());
    return {};
}

void Scene::set_scene() {

    this->camera = std::make_shared<Camera>();
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(camera, "../shader/vertex_shader/flat_v3.vert", "../shader/fragment_shader/flat_v3.frag");
    camera->attach_shader(shader);
    camera->notify_shaders();

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_W) {
            camera->go_forward(0.1f);
        }
        if (data.key == GLFW_KEY_S) {
            camera->go_forward(-0.1f);
        }
        if (data.key == GLFW_KEY_A) {
            camera->go_sideways(0.1f);
        }
        if (data.key == GLFW_KEY_D) {
            camera->go_sideways(-0.1f);
        }
        printf("[DEBUG] key: %d, scancode: %d, action: %d, mods: %d\n", data.key, data.scancode, data.action, data.mods);
        camera->notify_shaders();
    });


#include "../resources/models/sphere.h"

//    Renderable_object pyramid = Renderable_object(Mesh(sphere, 17280), shader).set_name("jehlan");
//    add_object(pyramid);


    Renderable_object suzie4k = Renderable_object(Mesh("../resources/models/suzi.obj"), shader).set_name("opice4k");

    suzie4k.set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Rotation>(180, 0, 1, 0),
                                                                        std::make_shared<Transforms::Scale>(0.3),
                                                                        std::make_shared<Transforms::Transform_node>()->add(
                                                                                {
                                                                                        std::make_shared<Transforms::Translation>(2, 0, 0),
                                                                                        std::make_shared<Transforms::Translation>(0, 1, 0),
                                                                                        std::make_shared<Transforms::Transform_node>()->add(
                                                                                                std::make_shared<Transforms::Rotation>(-20, 1, 0, 0)
                                                                                        ),
                                                                                        std::make_shared<Transforms::Transform_node>()->add(
                                                                                                {
                                                                                                        std::make_shared<Transforms::Translation>(-3, 0, 0),
                                                                                                        std::make_shared<Transforms::Translation>(0, -2, 0),
                                                                                                        std::make_shared<Transforms::Transform_node>()->add(
                                                                                                                std::make_shared<Transforms::Rotation>(-15, 0, 0, 1)
                                                                                                        )

                                                                                                }
                                                                                        )
                                                                                }
                                                                        )
                                                                }));
    add_object(suzie4k);

    Renderable_object rat = Renderable_object(Mesh("../resources/models/rat.obj"), shader).set_name("rat");
    rat.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
            std::make_shared<Transforms::Scale>(0.7)
    ));
    add_object(rat);

}

