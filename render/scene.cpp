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
#include "../object/light/point_light.h"
#include "../object/material.h"
#include "../resources/models/plain.h"
#include "../object/light/spot_light.h"
#include "../resources/models/sphere.h"
#include "../object/light/directional_light.h"
#include "../object/skybox/sky_dome.h"

Scene Scene::add_object(std::shared_ptr<Renderable_object> object) {
    objects.push_back(object);
    return *this;
}

Scene Scene::add_object(std::shared_ptr<Light_wrapper> object) {
    lights.push_back(object);
    return *this;
}

Scene Scene::set_skybox(std::shared_ptr<Sky_box> object) {
    sky_box = object;
    return *this;
}

void Scene::init() {
    //set_scene();

    for (auto &object: objects) {
        object->init();
    }

    //get aspect ratio from window
    auto window = glfwGetVideoMode(glfwGetPrimaryMonitor());
    camera->set_aspect_ratio(window->width / window->height);
}

void Scene::render(double delta_time) {

    if (sky_box) {
        glStencilFunc(GL_ALWAYS, 0, 0xff);
        sky_box->render();
    }

    for (auto i = 0; i < objects.size(); i++) {
        glStencilFunc(GL_ALWAYS, i + 1, 0xff);
        objects[i]->render(delta_time);
    }
    //auto sz = objects.size();
    for (auto i = 0; i < lights.size(); i++) {
        //glStencilFunc(GL_ALWAYS, sz + i, 0xff);
        lights[i]->render(delta_time);
    }

}

std::shared_ptr<Renderable_object> Scene::find_object(const std::string &name) {
    for (auto &object: objects) {
        if (object->name == name) {
            return object;
        }
    }
    //printf("[ERROR] Object with name %s not found\n", name.c_str());
    fprintf(stderr, "[ERROR] Object with name %s not found\n", name.c_str());

}

void Scene::set_active() {
    this->is_active = true;
}

void Scene::set_inactive() {
    this->is_active = false;
}


std::shared_ptr<Renderable_object> Scene::get_object_at(int x, int y) {

    int index;
    glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    index--;

    printf("\t index: %d\n", index);

    if (index < 0)
        return nullptr;

    //if(index >= objects.size())
    //return lights[index-objects.size()] // todo set names to lights in lightwrapper

    std::string name;
    if (objects[index]->name.empty()) {
        name = "NaN";
    } else {
        name = objects[index]->name;
    }
    auto str = name + "index: " + std::to_string(index);
    printf("\t name: %s\n", str.c_str());
    return objects[index];
}

void Scene::clicked_pixel(std::function<void(std::shared_ptr<Renderable_object> obj)> callback) {

    if (!this->is_active)
        return;

    int width, height;
    glfwGetWindowSize(this->window.get(), &width, &height);
    double x, y;
    glfwGetCursorPos(this->window.get(), &x, &y);


    printf("[DEBUG] CLICKED ON\n");
    printf("\t x:%f, y:%f\n", x, y);
    unsigned char pixel[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    y = height - y;
    printf("\t color: (%d, %d, %d, %d)\n", pixel[0], pixel[1], pixel[2], pixel[3]);

    //get Z buffer
    float depth;
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    printf("\t depth: %f\n", depth);

    //get stencil buffer
    auto obj = this->get_object_at(x, y);
    if (obj)
        callback(obj);

    //unproject

    //Můžeme vypočíst pozici v globálním souřadném systému.
    glm::vec3 screenX = glm::vec3(x, y, depth);
    glm::vec4 viewPort = glm::vec4(0, 0, width, height);
    glm::vec3 pos = glm::unProject(screenX, camera->get_view_matrix(), camera->get_projection_matrix(), viewPort);

    printf("\t pos: (%f, %f, %f)\n", pos.x, pos.y, pos.z);

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
        if (glfwGetInputMode(this->window.get(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            camera->look_mouse(data.x, data.y);
            //printf("[DEBUG] camera -> lookmouse called\n");
        }
    });

    // get clicked pixel on screen and color ...
    input_handler->subscribe([&](input::Mouse_btn_event_data data) {
        if (data.action == GLFW_PRESS) {
            this->clicked_pixel([&](std::shared_ptr<Renderable_object> obj) {
                printf("[DEBUG] clicked on object %s with index \n", obj->name.c_str());
                obj->set_name(obj->name + " clicked");
                obj->set_material(std::make_shared<Material>(glm::vec4(1, 1, 1, 1), glm::vec4(0.1f, 0.0f, 0.0f, 1.0f), 1.f, 5));
            });
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

    set_inputs();
    auto pointlight = std::make_shared<Point_light>(Point_light(glm::vec4(1, 1, 1, 1), glm::vec3(1, -4, 1)));
    auto dirlight = std::make_shared<Directional_light>(Directional_light(glm::vec4(0.3, 0.3, 0.3, 1), glm::vec3(-1, -0.5, 0.75)));
    auto flashlight = std::make_shared<Spot_light>(Spot_light(glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0), 12.5f, 15.0f));
    std::shared_ptr<Light_wrapper> light = std::make_shared<Light_wrapper>(Light_wrapper().add(
            {
                    dirlight,
                    //                pointlight,
                    //              flashlight,
            }));

    add_object(light);


    auto flat = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/constant.frag");
    camera->attach(flat);
    camera->notify();
    this->shaders.push_back(flat);


    auto lambert = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/lambert.frag");
    camera->attach(lambert);
    camera->notify();
    this->shaders.push_back(lambert);


    auto phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/phong.frag");
    camera->attach(phong);
    camera->notify();
    this->shaders.push_back(phong);

    auto blinn = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/blinn.frag");
    camera->attach(blinn);
    camera->notify();
    this->shaders.push_back(blinn);


    auto skydome_shader = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/skyobject.vert", "../shader/fragment_shader/skyobject.frag");
    this->sky_box = std::make_shared<Sky_dome>("../resources/skybox/hq360/sky.obj", skydome_shader, camera);
    camera->attach(sky_box);
    camera->notify();


    auto sphere_mesh = std::make_shared<Mesh>(sphere_vec);

    pointlight->set_object(sphere_mesh, flat, std::make_shared<Material>(Material(glm::vec4(1, 1, 1, 1), glm::vec4(1.f, 1.0f, 1.0f, 1.0f), 1.f, 5)));
    camera->attach(flashlight);
    flashlight->set_camera(camera);
//#include "../resources/models/models_2023/Models/tree.h"
    Renderable_object sphere = Renderable_object(sphere_mesh, lambert).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Translation>(0, 10, 0),
                                                                }
            ), true).set_material(default_material);
    add_object(std::make_shared<Renderable_object>(sphere));

    Renderable_object sphere2 = Renderable_object(sphere_mesh, phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    {std::make_shared<Transforms::Translation>(-1, -2, 0)}
            ), true).set_material(default_material);
    add_object(std::make_shared<Renderable_object>(sphere2));

    auto one_mat = std::make_shared<Material>()->set_specular_power(1);

    Renderable_object sphere3 = Renderable_object(sphere_mesh, blinn).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    {std::make_shared<Transforms::Translation>(-2, 2, 0)}
            ), true).set_material(std::make_shared<Material>(one_mat));
    add_object(std::make_shared<Renderable_object>(sphere3));

    Renderable_object sphere4 = Renderable_object(sphere_mesh, flat).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    {std::make_shared<Transforms::Translation>(-2, -2, 0)}
            ), true).set_material(default_material);
    add_object(std::make_shared<Renderable_object>(sphere4));


    auto suzi_mesh = std::make_shared<Mesh>("../resources/models/suzi.obj");


    //Renderable_object pyramid = Renderable_object(Mesh(sphere_vec), shader).set_name("koule");

    //Renderable_object suzie4k = Renderable_object(Mesh("../resources/models/suzi.obj"), ).set_name("opice4k");
    Renderable_object suzie4k = Renderable_object(suzi_mesh, lambert).set_name("opice4k").set_material(default_material);

    suzie4k.set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    {
                            std::make_shared<Transforms::Translation>(0, 0, 0),
                            std::make_shared<Transforms::Rotation>(0, 0, 1, 0),
                    }
            ), true);
    auto rotate = std::make_shared<Transforms::Transform_node>()->add({
                                                                              std::make_shared<Transforms::Rotation>(0, 0, 1, 0)->set_dynamic_function([](float angle) {
                                                                                  return angle + 0.1f;
                                                                              }),
                                                                              std::make_shared<Transforms::Translation>(2, 0, 0),
                                                                              std::make_shared<Transforms::Rotation>(0, 0, 1, 0)->set_dynamic_function([](float angle) {
                                                                                  return angle + 0.05f;
                                                                              }),
                                                                              std::make_shared<Transforms::Scale>(0.1)->set_dynamic_function([](glm::vec3 scale) {
                                                                                  static float x = 0.0f;
                                                                                  x = std::fmod(x, 90.0f);
                                                                                  x = x + 0.01f;
                                                                                  return glm::vec3((sin(x) + 1) * 0.5);
                                                                              }),
                                                                      });
    suzie4k.set_transform_operations(rotate);
    add_object(std::make_shared<Renderable_object>(suzie4k));

    auto grid_mesh = std::make_shared<Mesh>("../resources/models/grid.obj");

    Renderable_object grid_down = Renderable_object(grid_mesh, lambert).set_name("grid_down").set_material(default_material);
    grid_down.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add({
                                                                                                   std::make_shared<Transforms::Translation>(0, -2, 0),
                                                                                                   std::make_shared<Transforms::Scale>(1.5),
                                                                                           }), true);
    add_object(std::make_shared<Renderable_object>(grid_down));


    auto rat_mesh = std::make_shared<Mesh>("../resources/models/rat.obj");

    Renderable_object rat = Renderable_object(rat_mesh, lambert).set_name("rat").set_material(default_material);
    rat.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
            {std::make_shared<Transforms::Scale>(1.5)}
    ), true);

    auto rat_move = std::make_shared<Transforms::Transform_node>()->add(
            {
                    std::make_shared<Transforms::Rotation>(0, 0, 1, 0)->set_dynamic_function([](float angle) {
                        return angle + 0.1f;
                    }),
                    std::make_shared<Transforms::Translation>(0, 2, 0),
            });

    add_object(std::make_shared<Renderable_object>(rat.set_transform_operations(rat_move)));


    Renderable_object rattatulie = Renderable_object(rat_mesh, phong).set_name("rattatulie").set_material(default_material);
    rattatulie.set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
            {std::make_shared<Transforms::Scale>(0.7)}
    ), true);

    auto rattatulie_move = std::make_shared<Transforms::Transform_node>()->add(
            {
                    rat_move,
                    std::make_shared<Transforms::Rotation>(90, 0, 0, 1)->set_dynamic_function([](float angle) {
                        return angle + 0.1f;
                    }),
                    std::make_shared<Transforms::Translation>(0, 0, 2),
            });

    add_object(std::make_shared<Renderable_object>(rattatulie.set_transform_operations(rattatulie_move)));


    //HERE ARE TREES AND SO ON
    //random number generator

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angles(-50, 50);
    std::uniform_real_distribution<> position(-30, 30);

    Renderable_object plain_obj = Renderable_object(std::make_shared<Mesh>(plain), phong).set_name("plain").set_material(
                    std::make_shared<Material>(glm::vec4(0.2f, 0.1f, 0.08f, 1.0f), glm::vec4(0.05f, 0.1f, 0.05f, 1.0f), 0.75f, 30))
            .set_transform_operations(std::make_shared<Transforms::Transform_node>()->add({
                                                                                                  std::make_shared<Transforms::Translation>(0, -10, 0),
                                                                                                  std::make_shared<Transforms::Scale>(50),
                                                                                          }));
    add_object(std::make_shared<Renderable_object>(plain_obj));

    printf("[DEBUG] TREEEEEEEEEEEEEEEEEEE\n");

    //trees
    auto tree_material = std::make_shared<Material>(glm::vec4(1.0f, 0.9f, 0.8f, 1.0f), glm::vec4(0.05f, 0.05f, 0.01f, 1.0f), 0.75f, 128);
    auto tree_mesh = std::make_shared<Mesh>("../resources/models/tree.obj");
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
                                                                    })).set_material(tree_material);
        add_object(std::make_shared<Renderable_object>(tree));
    }
    //bushes
    auto bush_material = std::make_shared<Material>(glm::vec4(0.5f, 1.f, 0.1f, 1.0f), glm::vec4(0.1f, 0.05f, 0.01f, 1.0f), 0.75f, 32);
    auto bush_mesh = std::make_shared<Mesh>("../resources/models/rat.obj");
    for (int i = 0; i < 100; ++i) {
        float angle_x = angles(gen);
        float angle_y = angles(gen);
        float angle_z = angles(gen);

        int position_x = position(gen);
        int position_z = position(gen);
        Renderable_object bush = Renderable_object(bush_mesh, lambert).set_name("bush" + std::to_string(i)).set_transform_operations(
                        std::make_shared<Transforms::Transform_node>()->add(
                                {std::make_shared<Transforms::Translation>(position_x, -10, position_z)}
                        ))
                .set_material(bush_material);

        add_object(std::make_shared<Renderable_object>(bush));
    }

}

void Scene::set_phong_scene() {

    printf("[DEBUG] Setting phong scene\n");

    std::shared_ptr<Material> default_material = std::make_shared<Material>();

    this->camera = std::make_shared<Camera>();
    input_handler->subscribe([&](input::Window_size_data data) {
        camera->set_aspect_ratio((float) data.width / (float) data.height);
        printf("[DEBUG] aspect ratio: %f\n", (float) data.width / (float) data.height);
    });

    set_inputs();

    auto sphere_mesh = std::make_shared<Mesh>(sphere_vec);

    auto redlight = std::make_shared<Point_light>(Point_light(glm::vec4(1, 0, 0, 1), glm::vec3(4, 0, 0))
                                                          .set_transform_operations(
                                                                  std::make_shared<Transforms::Transform_node>()->add(
                                                                          {
                                                                                  std::make_shared<Transforms::Rotation>(0, 0, 1, 0)->set_dynamic_function([](float angle) {
                                                                                      return angle + 0.01f;
                                                                                  }),
                                                                                  std::make_shared<Transforms::Translation>(4, 0, 0),
                                                                                  std::make_shared<Transforms::Scale>(0.1)
                                                                          }
                                                                  )));

    auto flashlight = std::make_shared<Spot_light>(Spot_light(glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0), 12.5f, 15.0f));

    std::shared_ptr<Light_wrapper> light = std::make_shared<Light_wrapper>(Light_wrapper().add(
            {
                    flashlight,
                    redlight,
//                    std::make_shared<Point_light>(Point_light(glm::vec4(0, 1, 0, 1), glm::vec3(4, 0, 0))
//                                                          .set_transform_operations(
//                                                                  std::make_shared<Transforms::Transform_node>()->add(
//                                                                          {
//                                                                                  std::make_shared<Transforms::Rotation>(0, 1, 0, 0)->set_dynamic_function([](float angle) {
//                                                                                      return angle + 0.1f;
//                                                                                  }),
//                                                                                  std::make_shared<Transforms::Translation>(0, 1, 0),
//                                                                          }
//                                                                  ))),
                    std::make_shared<Directional_light>(Directional_light(glm::vec4(0.3, 0.3, 0.3, 1), glm::vec3(1, -1, -2))),

            }));


    add_object(light);

    auto blinn = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/blinn.frag");
    camera->attach(blinn);

    auto phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/phong.frag");
    camera->attach(phong);
    camera->notify();
    camera->attach(flashlight);
    flashlight->set_camera(camera);
    redlight->set_object(sphere_mesh, phong, std::make_shared<Material>(Material(glm::vec4(1, 0, 0, 1), glm::vec4(1.f, 0.0f, 0.0f, 1.0f), 1.f, 5)));

    //make skybox and shader
    auto skybox_shader = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/skybox.vert", "../shader/fragment_shader/skybox.frag");
    auto files_path = files();
    files_path.path = "../resources/skybox/night_skyboxes/3";
    files_path.filename_extension = ".png";
    files_path.update_extension();
    this->sky_box = std::make_shared<Sky_box>(files_path, skybox_shader, camera);



    //skydome and his shader
//    auto skydome_shader = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/skyobject.vert", "../shader/fragment_shader/skyobject.frag");
//    this->sky_box = std::make_shared<Sky_dome>("../resources/skybox/sky/skydome.obj", skydome_shader, camera);


    camera->attach(sky_box);
    camera->notify();

//    add_object(std::make_shared<Renderable_object>(
//            Renderable_object(std::make_shared<Mesh>("../resources/skybox/sky/skydome.obj"), phong).set_name("dome").set_material(default_material).set_has_texture(true)));


    Renderable_object sphere = Renderable_object(sphere_mesh, blinn).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    {
                            std::make_shared<Transforms::Translation>(1, 1, 0)}
            ), true).set_material(default_material);
    add_object(std::make_shared<Renderable_object>(sphere));

    Renderable_object sphere2 = Renderable_object(sphere_mesh, blinn).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    {std::make_shared<Transforms::Translation>(1, -1, 0)}
            ), true).set_material(default_material);
    add_object(std::make_shared<Renderable_object>(sphere2));

    Renderable_object sphere3 = Renderable_object(sphere_mesh, phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    {std::make_shared<Transforms::Translation>(-1, 1, 0)}
            ), true).set_material(default_material);
    add_object(std::make_shared<Renderable_object>(sphere3));

    Renderable_object sphere4 = Renderable_object(sphere_mesh, phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add(
                    {std::make_shared<Transforms::Translation>(-1, -1, 0)}
            ), true).set_material(default_material);
    add_object(std::make_shared<Renderable_object>(sphere4));


    auto plane_mesh = std::make_shared<Mesh>(plain);
    Renderable_object grid_down = Renderable_object(plane_mesh, phong).set_name("grid_down").set_material(default_material).set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Translation>(0, -2, 0),
                                                                        std::make_shared<Transforms::Scale>(5),
                                                                }), true);
    add_object(std::make_shared<Renderable_object>(grid_down));


    auto backpack = std::make_shared<Mesh>("../resources/models/backpack/backpack.obj");
    Renderable_object backpack_obj = Renderable_object(backpack, phong).set_name("backpack").set_material(default_material).set_has_texture(true);
    add_object(std::make_shared<Renderable_object>(backpack_obj));

    auto pacman = std::make_shared<Mesh>("../resources/models/pacman/pacman.obj");
    Renderable_object pacman_obj = Renderable_object(pacman, phong).set_name("pacman").set_material(default_material).set_has_texture(true)
            .set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
                    {std::make_shared<Transforms::Translation>(0, -3, 0)}
            ), true);
    add_object(std::make_shared<Renderable_object>(pacman_obj));

}

void Scene::set_rotation_scene() {

    this->camera = std::make_shared<Camera>();
    input_handler->subscribe([&](input::Window_size_data data) {
        camera->set_aspect_ratio((float) data.width / (float) data.height);
        printf("[DEBUG] aspect ratio: %f\n", (float) data.width / (float) data.height);
    });

    set_inputs();

    std::shared_ptr<Light_wrapper> light = std::make_shared<Light_wrapper>(Light_wrapper().add(
            {std::make_shared<Point_light>(glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 0))
            }));


    std::shared_ptr<Base_shader> phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/phong.frag");
    std::shared_ptr<Observer> observer_phong = std::static_pointer_cast<Observer>(phong);
    camera->attach(observer_phong);
    camera->notify();

    auto sphere_mesh = std::make_shared<Mesh>(sphere_vec);

    //glm::vec4 color, glm::vec4 ambient, float specularStrength, int specularPower              yellow = rgb(255,255,204)
    Renderable_object sun = Renderable_object(sphere_mesh, phong).set_name("sun").set_material(
                    std::make_shared<Material>(glm::vec4(0.7f, 0.1f, 0.8f, 1.0f), glm::vec4(0.2f, 0.2f, 0.05f, 1.0f), 0.9f, 256))
            .set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
                    {
                            std::make_shared<Transforms::Scale>(1.8)
                    }
            ), true)
            .set_transform_operations(std::make_shared<Transforms::Transform_node>()->add(
                    {
                            std::make_shared<Transforms::Translation>(0, 0, 0)->set_dynamic_function([](glm::vec3 transfor) {
                                //make it moving up and down
                                static float x = 0.0f;
                                x = std::fmod(x, 360.0f);
                                x = x + 0.01f;
                                return glm::vec3(transfor.x, sin(transfor.y + x + 2) * 0.9f, transfor.z);
                            }),
                    }
            ));
    add_object(std::make_shared<Renderable_object>(sun));

    Renderable_object earth = Renderable_object(sphere_mesh, phong).set_name("earth").set_material(
            std::make_shared<Material>(glm::vec4(0.1f, 0.1f, 0.8f, 1.0f), glm::vec4(0.1f, 0.1f, 0.15f, 1.0f), 0.6f, 32));

    std::shared_ptr<Transforms::Transform_node> earth_move = std::make_shared<Transforms::Transform_node>()->add(
            {
                    std::make_shared<Transforms::Rotation>(0, 0, 1, 0)->set_dynamic_function([](float angle) {
                        return angle + 0.01f;
                    }),
                    std::make_shared<Transforms::Translation>(4, 0, 0),
                    std::make_shared<Transforms::Scale>(0.5),
            }
    );

    earth.set_transform_operations(earth_move);
    add_object(std::make_shared<Renderable_object>(earth));

    Renderable_object moon1 = Renderable_object(sphere_mesh, phong).set_name("moon")
            .set_material(std::make_shared<Material>(glm::vec4(0.8f, 0.7f, 0.8f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), 0.75f, 64));

    std::shared_ptr<Transforms::Transform_node> moon1_move = std::make_shared<Transforms::Transform_node>()->add(
            {
                    earth_move,
                    std::make_shared<Transforms::Rotation>(0.5, 0, 1, 0)->set_dynamic_function([](float angle) {
                        return angle + 0.1f;
                    }),
                    std::make_shared<Transforms::Translation>(3, 0, 0),
                    std::make_shared<Transforms::Scale>(0.1)
            }
    );
    moon1.set_transform_operations(moon1_move);
    add_object(std::make_shared<Renderable_object>(moon1));


    std::shared_ptr<Transforms::Transform_node> earth2_move = std::make_shared<Transforms::Transform_node>()->add(
            {
                    std::make_shared<Transforms::Rotation>(0, 0, 1, 0)->set_dynamic_function([](float angle) {
                        return angle + 0.01f;
                    }),
                    std::make_shared<Transforms::Translation>(4, 0, 0),
                    std::make_shared<Transforms::Scale>(0.5),
            }
    );
    Renderable_object earth2 = Renderable_object(sphere_mesh, phong)
            .set_name("earth")
            .set_material(std::make_shared<Material>(glm::vec4(0.1f, 0.1f, 0.8f, 1.0f), glm::vec4(0.1f, 0.1f, 0.15f, 1.0f), 0.6f, 32))
            .set_transform_operations(earth2_move);
    add_object(std::make_shared<Renderable_object>(earth2));

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
    set_inputs();


    std::shared_ptr<Light_wrapper> light = std::make_shared<Light_wrapper>(Light_wrapper().add(
            {std::make_shared<Point_light>(glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 0))
            }));

    std::shared_ptr<Base_shader> phong = std::make_shared<Shader_wrapper>(camera, light, "../shader/vertex_shader/model.vert", "../shader/fragment_shader/phong.frag");
    std::shared_ptr<Observer> observer_phong = std::static_pointer_cast<Observer>(phong);
    camera->attach(observer_phong);
    camera->notify();

    auto sphere_mesh = std::make_shared<Mesh>(sphere_vec);
    Renderable_object sphere = Renderable_object(sphere_mesh, phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Translation>(0, 2, 0)
                                                                }
            ), true).set_material(default_material);
    add_object(std::make_shared<Renderable_object>(sphere));


    Renderable_object sphere2 = Renderable_object(sphere_mesh, phong).set_name("sphere").set_transform_operations(
            std::make_shared<Transforms::Transform_node>()->add({
                                                                        std::make_shared<Transforms::Translation>(0, -2, 0)
                                                                }
            ), true).set_material(std::make_shared<Material>(Material().set_specular_power(1)));
    add_object(std::make_shared<Renderable_object>(sphere2));

}




