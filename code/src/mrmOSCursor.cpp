//
// Created by root on 1/11/19.
//
using namespace std;

#include <cstring>
#include <iostream>
#include "../inc/mrmOSCursor.h"

void mrmOSCursor::setCursor(int posx, int posy) {
    this->dpy = XOpenDisplay(NULL);
    this->posx = posx;
    this->posy = posy;

    XWarpPointer(this->dpy, None, RootWindow(this->dpy, DefaultScreen(this->dpy)), 0, 0, 0, 0, this->posx, this->posy);
    XFlush(dpy);

    XCloseDisplay(this->dpy);
}

void mrmOSCursor::releaseMutex() {
    pthread_mutex_unlock(&this->mutex);
}

void mrmOSCursor::getMutex() {
    pthread_mutex_lock(&this->mutex);
}

void mrmOSCursor::clickPress(int key) {
    this->dpy = XOpenDisplay(NULL);

    XEvent event;

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = key;
    event.xbutton.same_screen = True;

    XQueryPointer(this->dpy, RootWindow(this->dpy, DefaultScreen(this->dpy)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(this->dpy, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(this->dpy, PointerWindow, True, 0xfff, &event) <= 0){cout << "event send error" << endl;};

    XFlush(this->dpy);

    XCloseDisplay(this->dpy);
}

void mrmOSCursor::clickRelease(int key) {

    this->dpy = XOpenDisplay(NULL);

    XEvent event;

    memset(&event, 0x00, sizeof(event));

    event.xbutton.button = key;
    event.xbutton.same_screen = True;
    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    XQueryPointer(this->dpy, RootWindow(this->dpy, DefaultScreen(this->dpy)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(this->dpy, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(this->dpy, PointerWindow, True, 0xfff, &event) <= 0){cout << "event send error" << endl;};

    XFlush(this->dpy);

    XCloseDisplay(this->dpy);
}

mrmOSCursor::mrmOSCursor() {
    pthread_mutex_init(&this->mutex, NULL);

    this->dpy = XOpenDisplay(0);

    Window root = DefaultRootWindow(this->dpy);

    XFlush(this->dpy);

    XCloseDisplay(this->dpy);
}

void mrmOSCursor::sendMotionNotify(int key) {

    this->dpy = XOpenDisplay(NULL);

    XEvent event;

    memset(&event, 0x00, sizeof(event));

    event.xbutton.button = key;
    event.xbutton.same_screen = True;
    event.type = MotionNotify | ButtonPress;

    XQueryPointer(this->dpy, RootWindow(this->dpy, DefaultScreen(this->dpy)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(this->dpy, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(this->dpy, PointerWindow, True, 0xfff, &event) <= 0){cout << "event send error" << endl;};

    XFlush(this->dpy);

    XCloseDisplay(this->dpy);
}