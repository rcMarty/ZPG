//
// Created by rc_marty on 3.12.23.
//

#ifndef ZPG_BEZIER_H
#define ZPG_BEZIER_H
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <stdexcept>
#include <mutex>

class Bezier {
private:

public:
    std::vector<glm::vec3> points;

    Bezier() = default;

    explicit Bezier(std::vector<glm::vec3> points) {
        if (points.size() < 4) {
            throw std::invalid_argument("Bezier curve needs at least 4 points");
        }
        this->points = points;
    }

    void add_point(glm::vec3 point) {
        this->points.push_back(point);
    }

    void add_points(std::vector<glm::vec3> points) {
        this->points.insert(this->points.end(), points.begin(), points.end());
    }

    int get_curves_size() {
        int n = points.size() - 1;
        return n / (4 - 1);

    }


    glm::vec3 get_point(float t) {

        int index = floor(t);
        t = t - index;
        index *= 3;

        if (t >= points.size())
            throw std::invalid_argument("Bezier out of index");

        glm::vec3 B;

        B.x = pow((1 - t), 3) * points[index].x + 3 * pow((1 - t), 2) * t * points[index + 1].x + 3 * (1 - t) * pow(t, 2) * points[index + 2].x + pow(t, 3) * points[index + 3].x;
        B.y = pow((1 - t), 3) * points[index].y + 3 * pow((1 - t), 2) * t * points[index + 1].y + 3 * (1 - t) * pow(t, 2) * points[index + 2].y + pow(t, 3) * points[index + 3].y;
        B.z = pow((1 - t), 3) * points[index].z + 3 * pow((1 - t), 2) * t * points[index + 1].z + 3 * (1 - t) * pow(t, 2) * points[index + 2].z + pow(t, 3) * points[index + 3].z;

        return B;
    }
};


#endif //ZPG_BEZIER_H
