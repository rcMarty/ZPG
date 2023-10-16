//
// Created by rc_marty on 30.9.23.
//

#include "scene.h"
#include "../object/transform/transform.h"
#include "../object/transform/transform_node.h"
#include "../object/transform/translation.h"
#include "../object/transform/rotation.h"
#include "../object/transform/scale.h"
#include "../shader/lambert_shader.h"
#include "../shader/phong_shader.h"
#include "../shader/blinn_shader.h"


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

void Scene::set_inputs() {

    if (input_handler == nullptr) {
        fprintf(stderr, "[ERROR] Input handler not set\n");
        return;
    }

    if (camera == nullptr) {
        fprintf(stderr, "[ERROR] Camera not set\n");
        return;
    }


    //todo fix more keys events down simultaneously
    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_W)
            camera->go_forward(0.1f);
    });

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_A)
            camera->go_sideways(-0.1f);
    });

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_S)
            camera->go_forward(-0.1f);
    });

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_D)
            camera->go_sideways(0.1f);
    });

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_Q)
            camera->go_vertical(0.1f);
    });

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_E)
            camera->go_vertical(-0.1f);
    });


    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_UP)
            camera->look_up(1.f);
    });

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_DOWN)
            camera->look_up(-1.f);
    });

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_LEFT)
            camera->look_sideways(1.f);
    });

    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_RIGHT)
            camera->look_sideways(-1.f);
    });

    static double last_x, last_y;
    input_handler->subscribe([&](input::Cursor_event_data data) {
        if (glfwGetInputMode(this->window.get(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            camera->look_mouse(data.x - last_x, last_y - data.y);
            last_y = data.y;
            last_x = data.x;
        }
    });
}


void Scene::set_scene() {

    this->camera = std::make_shared<Camera>();
    std::shared_ptr<Light> light = std::make_shared<Light>();
    auto lightoperations = std::make_shared<Transforms::Transform_node>()->add({
                                                                                       std::make_shared<Transforms::Translation>(5, 0, 0),
                                                                                       std::make_shared<Transforms::Rotation>(0.0001, 0, 1, 0),
                                                                                       std::make_shared<Transforms::Translation>(-5, -0, 0),
                                                                               }
    );
    light->set_transform_operations(lightoperations);

    std::shared_ptr<Base_shader> shader = std::make_shared<Lambert_shader>(camera, light, "../shader/vertex_shader/lambert.vert", "../shader/fragment_shader/lambert.frag");
    std::shared_ptr<Observer> observer_shader = std::static_pointer_cast<Observer>(shader);
    camera->attach(observer_shader);
    camera->notify();
    set_inputs();

    std::shared_ptr<Base_shader> phong = std::make_shared<Phong_shader>(camera, light, "../shader/vertex_shader/phong.vert", "../shader/fragment_shader/phong.frag");
    std::shared_ptr<Observer> observer_phong = std::static_pointer_cast<Observer>(phong);
    camera->attach(observer_phong);
    camera->notify();

    std::shared_ptr<Base_shader> blinn = std::make_shared<Blinn_shader>(camera, light, "../shader/vertex_shader/blinn.vert", "../shader/fragment_shader/blinn.frag");
    std::shared_ptr<Observer> observer_blinn = std::static_pointer_cast<Observer>(blinn);
    camera->attach(observer_blinn);
    camera->notify();


    Renderable_object sphere = Renderable_object(Mesh("../resources/models/sphere.obj"), shader).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(1, 1, 0)
            ), false);
    add_object(sphere);

    Renderable_object sphere2 = Renderable_object(Mesh("../resources/models/sphere.obj"), phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(1, -1, 0)
            ), false);
    add_object(sphere2);

    Renderable_object sphere3 = Renderable_object(Mesh("../resources/models/sphere.obj"), blinn).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(-1, 1, 0)
            ), false);
    add_object(sphere3);

    Renderable_object sphere4 = Renderable_object(Mesh("../resources/models/sphere.obj"), shader).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(-1, -1, 0)
            ), false);
    sphere4.set_transform_operations(lightoperations, true);
    add_object(sphere4);



    //Renderable_object suzie4k = Renderable_object(Mesh("../resources/models/suzi.obj"), ).set_name("opice4k");
    Renderable_object suzie4k = Renderable_object(Mesh("../resources/models/suzi.obj"), shader).set_name("opice4k");

    suzie4k.set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Translation>(0, 0, 0),
                                                                        std::make_shared<Transforms::Rotation>(0, 0, 1, 0),
                                                                }), false);

    suzie4k.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add({
                                                                                                 std::make_shared<Transforms::Translation>(2, 0, 0),
                                                                                                 std::make_shared<Transforms::Rotation>(5, 0, 1, 0),
                                                                                                 std::make_shared<Transforms::Translation>(-2, 0, 0),
                                                                                         }), true);
    add_object(suzie4k);//todo remake api from add_object so i dont have to call add_object

    Renderable_object grid_down = Renderable_object(Mesh("../resources/models/grid.obj"), shader).set_name("grid_down");
    grid_down.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add({
                                                                                                   std::make_shared<Transforms::Translation>(0, -2, 0),
                                                                                                   std::make_shared<Transforms::Scale>(1.5),
                                                                                           }), false);
    add_object(grid_down);


    Renderable_object grid_up = Renderable_object(Mesh("../resources/models/grid.obj"), shader).set_name("grid_up");
    grid_up.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add({
                                                                                                 std::make_shared<Transforms::Translation>(0, 2, 0),
                                                                                                 std::make_shared<Transforms::Scale>(1.5),
                                                                                         }), false);
    add_object(grid_up);

    Renderable_object rat = Renderable_object(Mesh("../resources/models/rat.obj"), shader).set_name("rat");
    rat.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
            std::make_shared<Transforms::Scale>(0.7)
    ), false);
    rat.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
            std::make_shared<Transforms::Rotation>(2, 0, 1, 0)
    ), true);
    add_object(rat);

}

