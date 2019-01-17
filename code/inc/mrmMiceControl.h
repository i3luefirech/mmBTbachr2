//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMMICECONTROL_H
#define CODE_MRMMICECONTROL_H


#include <list>
#include "../inc/mrmMouse.h"

class mrmMiceControl {

public:
    mrmMiceControl(list <mrmMouse> localmice, int amount);

    void start();

    list <mrmMouse> mice;

    void run();

    int amount;
};


#endif //CODE_MRMMICECONTROL_H
