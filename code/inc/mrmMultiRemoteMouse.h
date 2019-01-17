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
    /**
     * creates the multimouse controller. The multimouse controller needs to know all the objects.
     * All known objects are given with the constructor
     * @param localmice
     * @param amountlm
     * @param localcursors
     * @param amountlc
     * @param remotecursors
     * @param amountrc
     * @param remotescreens
     * @param amountrs
     * @param udpclient
     * @param udpserver
     */
    mrmMultiRemoteMouse(list<mrmMouse> localmice, int amountlm, list<mrmCursor> localcursors, int amountlc,
                        list<mrmCursor> remotecursors, int amountrc,
                        list<mrmScreen> remotescreens, int amountrs, mrmUDPClient *udpclient, mrmUDPServer *udpserver);

    list<mrmScreen> screens;
    mrmMiceControl *micectrl;
    mrmCursorControl *cursorctrl;
    mrmOSCursor *oscursor;

    /**
     * starting all threads of the integreated objects
     */
    void start();

    int amountscreen;
    int tempcount;

    /**
     * If a mouse or a server receives a mouseevent, it will call this function.
     * This function will send the event to the correct controler and work the event.
     * @param mouseEvent
     */
    void recvMouseEvent(json mouseEvent);

    /**
     * if a cursor needs to send a screenchange it will call this function.
     * The controller knows the client and will forward the request.
     * The request is given with the parameter json object
     * @param scevent
     */
    void sendscreenchange(json scevent);

    /**
     * if a cursor needs to send a mouseevent it will call this function.
     * The controller knows the client and will forward the request.
     * The request is given with the parameter json object
     * @param mevent
     */
    void sendmouseevent(json mevent);

    string hostip;

    /**
     * Sometimes the cursor needs to get the next screen in a specific direction.
     * The cursor will call this function. The controller knows the screen objects and will answer with an IP as a string
     * @param i
     * @return screen IP as string value
     */
    string getscreen(int i);

    /**
     * this function returns the host IP as string value
     * @return
     */
    string gethostip();
};


#endif //CODE_MRMMULTIREMOTEMOUSE_H
