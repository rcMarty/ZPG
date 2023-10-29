//
// Created by rc_marty on 20.10.23.
//

#ifndef ZPG_OBSERVER_H
#define ZPG_OBSERVER_H


class Observer {
public:
    virtual ~Observer() = default;

    virtual void update() = 0;

};


#endif //ZPG_OBSERVER_H
