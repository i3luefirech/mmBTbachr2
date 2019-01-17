//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMMULTIREMOTEMOUSE_H
#define CODE_MRMMULTIREMOTEMOUSE_H


#include <list>
#include "mrmUDPClient.h"
#include "mrmMouse.h"
#include "mrmCursor.h"
#include "mrmScreen.h"
#include "mrmUDPServer.h"
#include "mrmMiceControl.h"
#include "mrmCursorControl.h"
#include "mrmOSCursor.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class mrmMultiRemoteMouse {
private:
    mrmUDPClient *client;
    mrmUDPServer *server;
public:
    mrmMultiRemoteMouse(list<mrmMouse> localmice, int amountlm, list<mrmCursor> localcursors, int amountlc,
                        list<mrmCursor> remotecursors, int amountrc,
                        list<mrmScreen> remotescreens, int amountrs, mrmUDPClient *udpclient, mrmUDPServer *udpserver);

    list<mrmScreen> screens;
    mrmMiceControl *micectrl;
    mrmCursorControl *cursorctrl;
    mrmOSCursor *oscursor;

    void start();

    int amountscreen;
    int tempcount;

    void recvMouseEvent(json mouseEvent);

    void sendscreenchange(json scevent);

    void sendmouseevent(json mevent);

    string hostip;

    string getscreen(int i);

    string gethostip();
};


#endif //CODE_MRMMULTIREMOTEMOUSE_H
