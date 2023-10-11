//
// Created by rc_marty on 10.10.23.
//

#include "camera.h"
#include "../shader/shader.h"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4 Camera::getCamera() {
    //return glm::lookAt(eye, eye+target, up);
    return glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
    //mat4 projection=glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}