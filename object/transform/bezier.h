//
// Created by rc_marty on 3.12.23.
//

#ifndef ZPG_BEZIER_H
#define ZPG_BEZIER_H
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <stdexcept>

class Bezier {
private:
    std::vector<glm::vec3> points;

    float factorial(int n) {
        // calculate factorial
        return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
    }

public:
    Bezier() = default;

    Bezier(std::vector<glm::vec3> points) {
        if (points.size() < 4) {
            throw std::invalid_argument("Bezier curve needs at least 4 points");
        }
        this->points = points;
    }

    void add_point(glm::vec3 point) {
        points.push_back(point);
    }

    void add_points(std::vector<glm::vec3> points) {
        this->points.insert(this->points.end(), points.begin(), points.end());
    }

    int get_curves_size() {
        return floor(points.size() / 4) + 1;
    }


    glm::vec3 get_point(float t) {

        int index = floor(t);
        t = t - index;
        index *= 3;

        if (t >= points.size())
            throw std::invalid_argument("Bezier out of index");


//        if (t + 3 >= points.size())
//            index = points.size() - 4;

        glm::vec3 B;

//        for (int i = 0; i < 4; i++) {
//            B += points[index + i] * bernstein_polynomial(i, t);
//        }

        B.x = (1 - t) * (1 - t) * (1 - t) * points[index].x + 3 * (1 - t) * (1 - t) * t * points[index + 1].x + 3 * (1 - t) * t * t * points[index + 2].x + t * t * t * points[index + 3].x;
        B.y = (1 - t) * (1 - t) * (1 - t) * points[index].y + 3 * (1 - t) * (1 - t) * t * points[index + 1].y + 3 * (1 - t) * t * t * points[index + 2].y + t * t * t * points[index + 3].y;
        B.z = (1 - t) * (1 - t) * (1 - t) * points[index].z + 3 * (1 - t) * (1 - t) * t * points[index + 1].z + 3 * (1 - t) * t * t * points[index + 2].z + t * t * t * points[index + 3].z;

        return B;

    }
};


#endif //ZPG_BEZIER_H
