//
// Created by rc_marty on 11.11.23.
//

#ifndef ZPG_SKY_DOME_H
#define ZPG_SKY_DOME_H

#pragma once

#include "sky_box.h"


class Sky_dome : public Sky_box {
public:
    Sky_dome(const std::string &path, std::shared_ptr<Shader_wrapper> shader, std::shared_ptr<Camera> camera);

    virtual void render() override;

};


#endif //ZPG_SKY_DOME_H
