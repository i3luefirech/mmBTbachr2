//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMMOUSE_H
#define CODE_MRMMOUSE_H

#include <string>

using namespace std;

#include <unistd.h>
#include <iostream>
#ifdef __linux__
#include <linux/input.h>
#else
#include "../inc/osinput.h"
#endif
#include <fcntl.h>

class mrmMouse {
private:
public:
    struct input_event * ieMouse;
    mrmMouse(string id, string evenfile);
    int mousefile;
    const char * id;
    const char * eventfile;

    void start();
    void run(mrmMouse * mouse);
};


#endif //CODE_MRMMOUSE_H
