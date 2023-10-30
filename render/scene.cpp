//
// Created by rc_marty on 30.9.23.
//

#include <random>
#include "scene.h"
#include "../object/transform/transform.h"
#include "../object/transform/transform_node.h"
#include "../object/transform/translation.h"
#include "../object/transform/rotation.h"
#include "../object/transform/scale.h"
#include "../object/light/light.h"
#include "../shader/shader_wrapper.h"
#include "../object/material.h"
#include "../resources/models/models_2023/Models/sphere.h"
#include "../resources/models/plain.h"

Scene Scene::add_object(const Renderable_object &object) {
    objects.push_back(object);
    return *this;
}

void Scene::init() {
    //set_scene();

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


    input_handler->subscribe([&](input::Cursor_event_data data) {

//        printf("[DEBUG] cursor position: %f, %f\n", data.x, data.y);
//        printf("[DEBUG] last position: %f, %f\n", last_x, last_y);
        if (glfwGetInputMode(this->window.get(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            camera->look_mouse(data.x, data.y);
            //printf("[DEBUG] camera -> lookmouse called\n");
        }
    });


}


void Scene::set_debug_scene() {

    std::shared_ptr<Material> default_material = std::make_shared<Material>();
    this->camera = std::make_shared<Camera>();
    input_handler->subscribe([&](input::Window_size_data data) {
        camera->set_aspect_ratio((float) data.width / (float) data.height);
        printf("[DEBUG] aspect ratio: %f\n", (float) data.width / (float) data.height);
    });
    // glm::vec4(1, 1, 0.5, 1), glm::vec3(0, -5, 0)
    std::shared_ptr<Light> light = std::make_shared<Light>(glm::vec4(1, 0, 0, 1), glm::vec3(0, -5, 0));

    set_inputs();

    std::shared_ptr<Base_shader> flat = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/constant.frag");
    std::shared_ptr<Observer> observer_flat = std::static_pointer_cast<Observer>(flat);
    camera->attach(observer_flat);
    camera->notify();

    std::shared_ptr<Base_shader> lambert = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/lambert.frag");
    std::shared_ptr<Observer> observer_lambert = std::static_pointer_cast<Observer>(lambert);
    camera->attach(observer_lambert);
    camera->notify();


    std::shared_ptr<Base_shader> phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/phong.frag");
    std::shared_ptr<Observer> observer_phong = std::static_pointer_cast<Observer>(phong);
    camera->attach(observer_phong);
    camera->notify();

    std::shared_ptr<Base_shader> blinn = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/blinn.frag");
    std::shared_ptr<Observer> observer_blinn = std::static_pointer_cast<Observer>(blinn);
    camera->attach(observer_blinn);
    camera->notify();




//#include "../resources/models/models_2023/Models/tree.h"
    auto sphere_mesh = Mesh(sphere_vec);
    Renderable_object sphere = Renderable_object(sphere_mesh, lambert).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Translation>(0, 2, 0),
                                                                        std::make_shared<Transforms::Scale>(0.1)}
            ), false).set_material(default_material);
    add_object(sphere);

    Renderable_object sphere2 = Renderable_object(sphere_mesh, phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(0.001, 0, 0)
            ), true).set_material(default_material);
    add_object(sphere2);

    Renderable_object sphere3 = Renderable_object(sphere_mesh, blinn).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(-2, 2, 0)
            ), false).set_material(default_material);
    add_object(sphere3);

    Renderable_object sphere4 = Renderable_object(sphere_mesh, flat).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(-2, -2, 0)
            ), false).set_material(default_material);
    add_object(sphere4);

    //random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angles(-50, 50);
    std::uniform_real_distribution<> position(-30, 30);

    auto suzi_mesh = Mesh("../resources/models/suzi.obj");


    //Renderable_object pyramid = Renderable_object(Mesh(sphere_vec), shader).set_name("koule");

    //Renderable_object suzie4k = Renderable_object(Mesh("../resources/models/suzi.obj"), ).set_name("opice4k");
    Renderable_object suzie4k = Renderable_object(suzi_mesh, lambert).set_name("opice4k").set_material(default_material);

    suzie4k.set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Translation>(0, 0, 0),
                                                                        std::make_shared<Transforms::Rotation>(0, 0, 1, 0),
                                                                }), false);
    auto rotate = std::make_shared<Transforms::Transform_node>()->add({
                                                                              std::make_shared<Transforms::Translation>(-2, 0, 0),
                                                                              std::make_shared<Transforms::Rotation>(5, 0, 1, 0),
                                                                              std::make_shared<Transforms::Translation>(2, 0, 0),
                                                                      });
    suzie4k.set_transform_operations(rotate, true);
    add_object(suzie4k);//todo remake api from add_object so i dont have to call add_object

    auto grid_mesh = Mesh("../resources/models/grid.obj");

    Renderable_object grid_down = Renderable_object(grid_mesh, lambert).set_name("grid_down").set_material(default_material);
    grid_down.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add({
                                                                                                   std::make_shared<Transforms::Translation>(0, -2, 0),
                                                                                                   std::make_shared<Transforms::Scale>(1.5),
                                                                                           }), false);
    add_object(grid_down);


    Renderable_object grid_up = Renderable_object(grid_mesh, lambert).set_name("grid_up").set_material(default_material);
    grid_up.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add({
                                                                                                 std::make_shared<Transforms::Translation>(0, 2, 0),
                                                                                                 std::make_shared<Transforms::Scale>(1.5),
                                                                                         }), false);
    add_object(grid_up);

    auto rat_mesh = Mesh("../resources/models/rat.obj");

    Renderable_object rat = Renderable_object(rat_mesh, lambert).set_name("rat").set_material(default_material);
    rat.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
            std::make_shared<Transforms::Scale>(1.5)
    ), false);


    rat.set_move([&](glm::mat4 m) {
        static float x = 0.0f;
        x = std::fmod(x, 360.0f);

        auto tranformation = std::make_shared<Transforms::Transform_node>()->add({
                                                                                         std::make_shared<Transforms::Rotation>(x, 0, 1, 0),
                                                                                         std::make_shared<Transforms::Translation>(4, 0, 0),

                                                                                 });
        x = x + 0.5f;
        return tranformation->get_matrix(m);

    });
    add_object(rat);


    Renderable_object rattatulie = Renderable_object(rat_mesh, phong).set_name("rattatulie").set_material(default_material);
    rattatulie.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
            std::make_shared<Transforms::Scale>(0.7)
    ), false);


    rattatulie.set_move([&](glm::mat4 m) {

        static float x = 0.0f;
        static float xx = 0.0f;
        x = std::fmod(x, 360.0f);
        xx = std::fmod(xx, 360.0f);


        auto tranformation = std::make_shared<Transforms::Transform_node>()->add(
                {
                        std::make_shared<Transforms::Rotation>(x, 0, 1, 0),
                        std::make_shared<Transforms::Translation>(4, 0, 0),

                });
        x = x + 0.5f;

        tranformation->add(
                {
                        std::make_shared<Transforms::Rotation>(xx, 0, 0, 1),
                        std::make_shared<Transforms::Translation>(0, 1, 0),

                });

        xx = xx + 10.f;

        return tranformation->get_matrix(m);

    });
    add_object(rattatulie);


    //HERE ARE TREES AND SO ON


    Renderable_object plain_obj = Renderable_object(Mesh(plain), lambert).set_name("plain").set_material(default_material).set_material(
                    std::make_shared<Material>(glm::vec4(0.2f, 0.8f, 0.08f, 1.0f), glm::vec4(0.2f, 0.2f, 0.05f, 1.0f), 0.75f, 30))
            .set_transform_operations(std::make_shared<Transforms::Transform_node>()->add({
                                                                                                  std::make_shared<Transforms::Translation>(0, -10, 0),
                                                                                                  std::make_shared<Transforms::Scale>(50),
                                                                                          }), false);
    add_object(plain_obj);

    printf("[DEBUG] TREEEEEEEEEEEEEEEEEEE\n");

    //trees
    auto tree_material = std::make_shared<Material>(glm::vec4(0.5f, 0.4f, 0.1f, 1.0f), glm::vec4(0.1f, 0.05f, 0.01f, 1.0f), 0.75f, 32);
    auto tree_mesh = Mesh("../resources/models/tree.obj");
    for (int i = 0; i < 100; ++i) {
        float angle_x = angles(gen);
        float angle_y = angles(gen);
        float angle_z = angles(gen);

        int position_x = position(gen);
        int position_z = position(gen);
        Renderable_object tree = Renderable_object(tree_mesh, lambert).set_name("tree" + std::to_string(i)).set_transform_operations(
                std::make_shared<Transforms::Transform_node>()->add({
                                                                            std::make_shared<Transforms::Translation>(position_x, -10, position_z),
                                                                            std::make_shared<Transforms::Rotation>(angle_x, 1, 0, 0),
                                                                            std::make_shared<Transforms::Rotation>(angle_y, 0, 1, 0),
                                                                            std::make_shared<Transforms::Rotation>(angle_z, 0, 0, 1),
                                                                    }), false).set_material(tree_material);
        add_object(tree);
    }
    //bushes
    auto bush_material = std::make_shared<Material>(glm::vec4(0.5f, 0.4f, 0.1f, 1.0f), glm::vec4(0.1f, 0.05f, 0.01f, 1.0f), 0.75f, 32);
    auto bush_mesh = Mesh("../resources/models/rat.obj");
    for (int i = 0; i < 100; ++i) {
        float angle_x = angles(gen);
        float angle_y = angles(gen);
        float angle_z = angles(gen);

        int position_x = position(gen);
        int position_z = position(gen);
        Renderable_object bush = Renderable_object(bush_mesh, lambert).set_name("bush" + std::to_string(i)).set_transform_operations(
                        std::make_shared<Transforms::Transform_node>()->add(
                                std::make_shared<Transforms::Translation>(position_x, -10, position_z)
                        ), false)
                .set_material(bush_material);

        add_object(bush);
    }


}

void Scene::set_phong_scene() {
    std::shared_ptr<Material> default_material = std::make_shared<Material>();

    this->camera = std::make_shared<Camera>();
    input_handler->subscribe([&](input::Window_size_data data) {
        camera->set_aspect_ratio((float) data.width / (float) data.height);
        printf("[DEBUG] aspect ratio: %f\n", (float) data.width / (float) data.height);
    });
    std::shared_ptr<Light> light = std::make_shared<Light>();

    set_inputs();

    std::shared_ptr<Base_shader> phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/phong.frag");
    std::shared_ptr<Observer> observer_phong = std::static_pointer_cast<Observer>(phong);
    camera->attach(observer_phong);
    camera->notify();


    Renderable_object sphere = Renderable_object(Mesh(sphere_vec), phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(2, 2, 0)
            ), false).set_material(default_material);
    add_object(sphere);

    Renderable_object sphere2 = Renderable_object(Mesh(sphere_vec), phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(2, -2, 0)
            ), false).set_material(default_material);
    add_object(sphere2);

    Renderable_object sphere3 = Renderable_object(Mesh(sphere_vec), phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(-2, 2, 0)
            ), false).set_material(default_material);
    add_object(sphere3);

    Renderable_object sphere4 = Renderable_object(Mesh(sphere_vec), phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(-2, -2, 0)
            ), false).set_material(default_material);
    add_object(sphere4);


}

void Scene::set_rotation_scene() {

    this->camera = std::make_shared<Camera>();
    input_handler->subscribe([&](input::Window_size_data data) {
        camera->set_aspect_ratio((float) data.width / (float) data.height);
        printf("[DEBUG] aspect ratio: %f\n", (float) data.width / (float) data.height);
    });
    std::shared_ptr<Light> light = std::make_shared<Light>(glm::vec4(1, 1, 0.5, 1), glm::vec3(0, 3, 0));

    set_inputs();

    std::shared_ptr<Base_shader> phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/phong.frag");
    std::shared_ptr<Observer> observer_phong = std::static_pointer_cast<Observer>(phong);
    camera->attach(observer_phong);
    camera->notify();

    //glm::vec4 color, glm::vec4 ambient, float specularStrength, int specularPower              yellow = rgb(255,255,204)
    Renderable_object sun = Renderable_object(Mesh(sphere_vec), phong).set_name("sun").set_material(
            std::make_shared<Material>(glm::vec4(0.7f, 0.1f, 0.8f, 1.0f), glm::vec4(0.2f, 0.2f, 0.05f, 1.0f), 0.9f, 256));
    add_object(sun);

    Renderable_object earth = Renderable_object(Mesh(sphere_vec), phong).set_name("earth").set_material(
            std::make_shared<Material>(glm::vec4(0.1f, 0.1f, 0.8f, 1.0f), glm::vec4(0.1f, 0.1f, 0.15f, 1.0f), 0.6f, 32));

    auto earth_move = [](glm::mat4 m) {
        static float x = 0.0f;
        x = std::fmod(x, 360.0f);
        auto transf = std::make_shared<Transforms::Transform_node>()->add(
                {
                        std::make_shared<Transforms::Rotation>(30, 0, 0, 1),
                        std::make_shared<Transforms::Rotation>(x, 0, 1, 0),
                        std::make_shared<Transforms::Translation>(3, 0, 0),

                        std::make_shared<Transforms::Scale>(0.5),

                });
        x++;
        return transf->get_matrix(m);
    };
    earth.set_move(earth_move);
    add_object(earth);

    Renderable_object moon1 = Renderable_object(Mesh(sphere_vec), phong).set_name("moon")
            .set_material(std::make_shared<Material>(glm::vec4(0.8f, 0.7f, 0.8f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), 0.75f, 64));

    auto moon1_move = [&](glm::mat4 m) {
        static float x = 0.0f;
        x = std::fmod(x, 360.0f);
        auto transf = std::make_shared<Transforms::Transform_node>()->add(
                {
                        std::make_shared<Transforms::Rotation>(30, 0, 0, 1),
                        std::make_shared<Transforms::Rotation>(x, 0, 1, 0),
                        std::make_shared<Transforms::Translation>(3, 0, 0),
                        std::make_shared<Transforms::Scale>(0.5),


                });
        x++;

        static float y = 0.0f;
        y = std::fmod(y, 360.0f);
        transf->add(std::make_shared<Transforms::Transform_node>()->add(
                {
                        std::make_shared<Transforms::Rotation>(89, 0, 0, 1),
                        std::make_shared<Transforms::Rotation>(y, 0, 1, 0),
                        std::make_shared<Transforms::Translation>(1.5, 0, 0),
                        std::make_shared<Transforms::Scale>(0.1),
                }));
        y += 3.5;
        return transf->get_matrix(m);
    };
    moon1.set_move(moon1_move);
    add_object(moon1);


}

void Scene::set_check_phong_scene() {
//    Test na ořezání světla, které nemůže dopadnou na plochu (úhel mezi normálou a vektorem ke světlu je mimo rozsah <-90,90>).
//    Scéna obsahuje jednu kulovou plochu, která je na přímce mezi světlem a kamerou.
//            Použijeme postupně dvě varianty Phongova shaderu, které mají mocninu u zrcadlové složky nastavenou na h=1. U jednoho bude kontrola na úhel mezi světlem a normálou a u druhého nebude (V jednom případě by mělo k přesahu dojít a ve druhém nikoli.).

    //Material(glm::vec4 color, glm::vec4 ambient, float specularStrength, int specularPower);
    std::shared_ptr<Material> default_material = std::make_shared<Material>();
    default_material->set_specular_power(1);

    this->camera = std::make_shared<Camera>();
    input_handler->subscribe([&](input::Window_size_data data) {
        camera->set_aspect_ratio((float) data.width / (float) data.height);
        printf("[DEBUG] aspect ratio: %f\n", (float) data.width / (float) data.height);
    });
    std::shared_ptr<Light> light = std::make_shared<Light>();

    set_inputs();


    std::shared_ptr<Base_shader> phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/phong.frag");
    std::shared_ptr<Observer> observer_phong = std::static_pointer_cast<Observer>(phong);
    camera->attach(observer_phong);
    camera->notify();

    std::shared_ptr<Base_shader> bad_phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/bad_phong.frag");
    std::shared_ptr<Observer> observer_bad_phong = std::static_pointer_cast<Observer>(bad_phong);
    camera->attach(observer_bad_phong);
    camera->notify();

    Renderable_object sphere = Renderable_object(Mesh(sphere_vec), phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(0, 2, 0)
            ), false).set_material(default_material);
    add_object(sphere);

    Renderable_object sphere2 = Renderable_object(Mesh(sphere_vec), bad_phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    std::make_shared<Transforms::Translation>(0, -2, 0)
            ), false).set_material(default_material);
    add_object(sphere2);

}