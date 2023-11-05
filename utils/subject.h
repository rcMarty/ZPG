//
// Created by rc_marty on 5.11.23.
//

#ifndef ZPG_SUBJECT_H
#define ZPG_SUBJECT_H

#pragma once

#include <memory>

class Observer;

class Subject {
public:

    virtual ~Subject() = default;

    virtual void attach(std::shared_ptr<Observer> observer) = 0;

    virtual void detach(std::shared_ptr<Observer> observer) = 0;

    virtual void notify() = 0;
};


#endif //ZPG_SUBJECT_H
