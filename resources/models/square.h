//
// Created by rc_marty on 30.9.23.
//
#pragma once
// position and color
struct point {
    float pos[4];
    float color[4];
};

// points with struct point
// 4x4 per line
const point square_vertices[6] = {
        {{-.8f, -.8f, .5f, 1}, {1, 0, 0, 1}},
        {{-.8f, .8f,  .5f, 1}, {0, 1, 0, 1}},
        {{.8f,  .8f,  .5f, 1}, {0, 0, 1, 1}},
        {{.8f,  -.8f, .5f, 1}, {1, 1, 1, 1}},
        {{-.8f, .8f,  .5f, 1}, {0, 1, 0, 1}},
        {{.8f,  .8f,  .5f, 1}, {0, 0, 1, 1}},
};