//
// Created by root on 1/11/19.
//
#include <unistd.h>
#include <iostream>
#include <linux/input.h>
#include <fcntl.h>
#include <cstring>
#include "../inc/mrmMouse.h"
#include "../inc/mrmMultiRemoteMouse.h"

mrmMouse::mrmMouse(string id, string eventfile) {
    this->id = (char *)malloc(sizeof(char)*(strlen(id.c_str())+1));
    this->eventfile = (char *)malloc(sizeof(char)*(strlen(eventfile.c_str())+1));
    strcpy((char *)this->id, (char *)id.c_str());
    strcpy((char *)this->eventfile, (char *)eventfile.c_str());
    cout << "mrmMouse: " << this->id << ": open file" << this->eventfile << endl;
    if((this->mousefile = open(this->eventfile, O_RDONLY)) == -1) {
        cout << "opening device MOUSEFILE failed" << endl;
        this->mousefile = -1;
    }
}

void *ThreadMouse(void *pVoid) {

    mrmMouse* mouse = static_cast<mrmMouse*>(pVoid);
    mouse->run(mouse);

    pthread_exit(nullptr);
}

void mrmMouse::start() {
    cout << "mrmMouse: start " << this->eventfile << endl;
    pthread_t thread;
    // start Client
    pthread_create( &thread, nullptr, ThreadMouse, static_cast<void*>(this));
}

extern mrmMultiRemoteMouse * mrm;

void mrmMouse::run(mrmMouse* mouse) {
    cout << "mrmMouse: run " << mouse->eventfile << endl;
    struct input_event mouseevent;
    int ret = 0;
    while (ret = read(mouse->mousefile, &mouseevent, sizeof(struct input_event))) {
        if(ret > 0 && !(mouseevent.type == 0 && mouseevent.code == 0 && mouseevent.value == 0)) {
            json eventobj;
            eventobj["id"] = mouse->id;
            eventobj["type"] = mouseevent.type;
            eventobj["code"] = mouseevent.code;
            eventobj["value"] = mouseevent.value;
            eventobj["time_s"] = mouseevent.time.tv_sec;
            eventobj["time_us"] = mouseevent.time.tv_usec;
            mrm->recvMouseEvent(eventobj);
        } else {
            usleep(500);
        }
    }
    cout << "error" << endl;
}