//
// Created by rc_marty on 2.11.23.
//

#pragma once

#include "point_light.h"
#include <memory>
#include <vector>

class Light_wrapper {
private:
    int max_lights = 10;
    std::vector<std::shared_ptr<Light>> lights;
public:

    Light_wrapper add(std::vector<std::shared_ptr<Point_light>> lights);

    void render(double delta_time);

    void set_variables(Base_shader &shader);


};