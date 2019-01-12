//
// Created by root on 1/11/19.
//

#include "../inc/mrmMultiRemoteMouse.h"
#include "../inc/mrmMiceControl.h"
#include "../inc/mrmCursorControl.h"
#include "../inc/mrmOSCursor.h"

mrmMultiRemoteMouse::mrmMultiRemoteMouse(list<mrmMouse> localmice, int amountlm, list<mrmCursor> localcursors, int amountlc, list<mrmCursor> remotecursors, int amountrc,
        list<mrmScreen> remotescreens, int amountrs, mrmUDPClient *udpclient, mrmUDPServer *udpserver) {
    this->client = udpclient;
    this->server = udpserver;
    this->screens = remotescreens;
    this->amountscreen = amountrs;
    this->micectrl = new mrmMiceControl(localmice, amountlm);
    this->cursorctrl = new mrmCursorControl(localcursors, remotecursors, amountlc, amountrc);
    this->oscursor = new mrmOSCursor();
    this->tempcount = 0;
}

void mrmMultiRemoteMouse::start() {
    this->server->start();
    this->micectrl->start();
    this->cursorctrl->start(this->oscursor);
}

void mrmMultiRemoteMouse::recvMouseEvent(json mouseevent) {
    switch(this->cursorctrl->work_event(mouseevent)) {
        case 1:
            // send via client
            this->client->sendevent(mouseevent);
            break;
        case 2:
            // send screenchange left
            this->client->sendscreenchange(0);
            // send via client
            this->client->sendevent(mouseevent);
            break;
        case 3:
            // send screenchange right
            this->client->sendscreenchange(1);
            // send via client
            this->client->sendevent(mouseevent);
            break;
    }
}
