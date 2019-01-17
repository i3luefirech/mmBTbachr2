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
    struct input_event *ieMouse;

    /**
     * create the mouse object. It will know which Devicefile to read with the eventfile string parameter.
     * @param id
     * @param evenfile
     */
    mrmMouse(string id, string evenfile);

    int mousefile;
    const char *id;
    const char *eventfile;

    /**
     * starts the Thread which is running the mousobject. The run function wil be called in the thread.
     */
    void start();

    /**
     * the run function. This function will bi called from the mouse thread. The run function receives Mousevent packages and send them to our controller
     * @param mouse
     */
    void run(mrmMouse *mouse);
};


#endif //CODE_MRMMOUSE_H
