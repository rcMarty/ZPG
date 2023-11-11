//
// Created by rc_marty on 10.11.23.
//

#ifndef ZPG_SKY_BOX_H
#define ZPG_SKY_BOX_H

#pragma once

#include "../model/mesh.h"
#include "../camera/camera.h"
#include "../../shader/shader_wrapper.h"


class Sky_box : public Observer {
private:
    std::shared_ptr<Texture> textures;

protected:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader_wrapper> shader;
    std::shared_ptr<Camera> camera;


public:

    Sky_box() = default;

    Sky_box(files path, std::shared_ptr<Shader_wrapper> shader, std::shared_ptr<Camera> camera);

    virtual void render();

    //update for camera
    virtual void update() override;
};


#endif //ZPG_SKY_BOX_H
