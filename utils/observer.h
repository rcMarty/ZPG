//
// Created by rc_marty on 20.10.23.
//
#pragma once

class Subject;

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update() = 0;

};
