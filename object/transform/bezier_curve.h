//
// Created by rc_marty on 3.12.23.
//

#ifndef ZPG_BEZIER_CURVE_H
#define ZPG_BEZIER_CURVE_H
#pragma once

#include "transform.h"
#include <vector>
#include "bezier.h"

namespace Transforms {
    class Bezier_curve : public Transform {
    private:
        Bezier bezier;
        float t = 0;
        float speed = 0.01;

    public:
        Bezier_curve(Bezier bezier, float speed) : bezier(bezier), speed(speed) {
            t = 0;
        }


        virtual void tick(float delta_time) override {
            t += delta_time * speed;
            if (t >= bezier.get_curves_size()) {
                t = 0;
            }
        }

        virtual glm::mat4x4 get_matrix(glm::mat4x4 input_matrix) override {
            printf("[DEBUG] Bezier curve get matrix %f\n", t);
            return glm::translate(input_matrix, bezier.get_point(t));
        }

    };


}
#endif //ZPG_BEZIER_CURVE_H
