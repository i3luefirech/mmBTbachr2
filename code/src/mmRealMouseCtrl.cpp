//
// Created by bluefire on 11/12/18.
//

#include <unistd.h>
#include<iostream>

#include <linux/input.h>
#include <fcntl.h>
#include <X11/Xlib.h>

#include "../inc/mmRealMouseCtrl.h"

// cat /proc/bus/input/devices
// evtest /dev/input/eventX
//#define MOUSEFILE "/dev/input/event6" for touchdevice virtual box
#define MOUSEFILE "/dev/input/event5" // for ps/2 mouse virtual box
#define MOUSEBUTTONFILE "/dev/input/event4" // both virtual box
//#define KEYBOARD "/dev/input/event2" // both virtual box

mmRealMouseCtrl::mmRealMouseCtrl() {
    this->mousefile = 0;
    this->buttonfile = 0;
    this->ieMouse = (struct input_event *)malloc(sizeof(struct input_event));
    this->ieButton = (struct input_event *)malloc(sizeof(struct input_event));
};

int mmRealMouseCtrl::start(void *pVoid) {
    if((this->mousefile = open(MOUSEFILE, O_RDONLY)) == -1) {
        std::cout << "opening device MOUSEFILE failed" << std::endl;
        return -1;
    }

    if((this->buttonfile = open(MOUSEBUTTONFILE, O_RDONLY)) == -1) {
        std::cout << "opening device MOUSEBUTTONFILE failed" << std::endl;
        return -2;
    }

    this->run(pVoid);
}

void mmRealMouseCtrl::run(void *pVoid) {
    int *task = (int *)pVoid;
    switch(*task){
        case 0:
            while(read(this->mousefile, this->ieMouse, sizeof(struct input_event))) {
                std::cout << "type: " << this->ieMouse->type << "code: " << this->ieMouse->code << "value: " << this->ieMouse->value << std::endl;
            }
            break;
        case 1:
            while(read(this->buttonfile, this->ieButton, sizeof(struct input_event))) {
                std::cout << "type: " << this->ieButton->type << "code: " << this->ieButton->code << "value: " << this->ieButton->value << std::endl;
            }
            break;
        default:
            std::cout << "unknown task " << *task << std::endl;
            break;
    }
}