//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMCURSORCONTROL_H
#define CODE_MRMCURSORCONTROL_H


#include <list>
#include "mrmCursor.h"
#include "mrmOSCursor.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class mrmCursorControl {
public:
    mrmCursorControl(list <mrmCursor> localcursors, list <mrmCursor> remotecursors, int amountlc,
                     int amountrc);

    /**
     * starts all the Thread of the known mice
     */
    void start(mrmOSCursor *);

    list <mrmCursor> getlist();

    /**
     * receives an event to work with. The event will be processed and given to the correct object
     * @param work_event
     * @return
     */
    int work_event(json work_event);

    list <mrmCursor> cursors;
    int amount;
    mrmOSCursor *oscursor;
    unsigned long amountlocal;
};


#endif //CODE_MRMCURSORCONTROL_H
