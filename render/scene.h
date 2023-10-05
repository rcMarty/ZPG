//
// Created by rc_marty on 30.9.23.
//

#pragma once


#include <vector>
#include "../object/renderable_object.h"

class Scene {
private:
    std::vector<Renderable_object> objects;

    void set_scene();

public:
    Scene() = default;

    Scene add_object(const Renderable_object &object);

    Renderable_object find_object(const std::string &name);

    void init();

    void render();


};

