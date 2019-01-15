//
// Created by root on 1/11/19.
//

#include <iostream>
#include <linux/input-event-codes.h>
#include <zconf.h>
#include "../inc/mrmOSCursor.h"
#include "../inc/mrmCursorControl.h"
#include "../inc/mrmMultiRemoteMouse.h"

extern mrmMultiRemoteMouse * mrm;

mrmCursorControl::mrmCursorControl(list <mrmCursor> localcursors, list <mrmCursor> remotecursors, int amountlc,
                                   int amountrc) {
    this->cursors = localcursors;
    this->amountlocal = localcursors.size();
    this->cursors.insert(this->cursors.end(), remotecursors.begin(), remotecursors.end());
    this->amount = amountlc+amountrc;
}

void mrmCursorControl::start(mrmOSCursor * oscursor) {
    this->oscursor = oscursor;
    cout << "mrmCursorControl: start " << this->cursors.size() << " , " << amount << endl;
    for(auto it = this->cursors.begin(); it != this->cursors.end(); it++){
        it->start();
    }
}

int mrmCursorControl::work_event(json work_event) {
    int cnt = 0;
    auto it = this->cursors.begin();
    for(; it != this->cursors.end(); it++, cnt++){
        if(it->id.compare(work_event["id"])==0){
            break;
        }
    }
    json type = work_event["type"];
    if(!type.is_number()){
        // screenchange event
        // TODO work event
        // TODO deactivate/activate cursor
    } else {
        // mouse event
        // check ob aktiv
        if(it->isactive()){
            // check ob bewegungsevent
            if((EV_REL==(int)work_event["type"] && REL_WHEEL!=(int)work_event["code"]) || (EV_ABS==(int)work_event["type"] && ABS_WHEEL!=(int)work_event["code"])){
                int newx = it->getPosx(), newy = it->getPosy();
                int relx, rely;
                int absx, absy;
                int limitreached = 0;
                // check ob relativ
                if(EV_REL==(int)work_event["type"]){
                    // relativ
                    if(REL_X==(int)work_event["code"]) {
                        newx = it->getPosx() + (int) work_event["value"];
                    } else if(REL_Y==(int)work_event["code"]){
                        newy = it->getPosy() + (int) work_event["value"];
                    }
                } else {
                    // absolut
                    if(ABS_X==(int)work_event["code"]) {
                        it->setlastabsx((int) work_event["value"]);
                        int relval = it->getrelxfromabs();
                        if (relval < -100) {
                            relval = -100;
                        } else if (relval > 100) {
                            relval = 100;
                        }
                        newx = it->getPosx() - relval;
                    } else if(ABS_Y==(int)work_event["code"]) {
                        it->setlastabsy((int) work_event["value"]);
                        int relval = it->getrelyfromabs();
                        if (relval < -70) {
                            relval = -70;
                        } else if (relval > 70) {
                            relval = 70;
                        }
                        newy = it->getPosy()-relval;
                    }
                }
                // check limits
                if(newx<0){
                    newx=0;
                    limitreached = -1;
                }
                if(newx>it->getXMax()-1){
                    newx=it->getXMax()-1;
                    limitreached = 1;
                }
                if(newy<0){
                    newy=0;
                }
                if(newy>it->getYMax()-1){
                    newy=it->getYMax()-1;
                }
                // wenn limit erreicht
                if(limitreached!=0){
                    // wenn remotescreen für seite
                        json scevent;
                        // send screen change
                        mrm->sendscreenchange(scevent);
                        if(this->amountlocal>cnt){
                            // ist lokaler event
                            // sendeevent
                            mrm->sendmouseevent(work_event);
                        }
                } else {
                    // steuere cursor
                    it->setPosx(newx);
                    it->setPosy(newy);
                }
            } else {
                if(EV_KEY==(int)work_event["type"]) {
                    switch ((int)work_event["code"]) {
                        case BTN_LEFT:
                            if ((int)work_event["value"]==1) {
                                this->oscursor->getMutex();
                                it->clickrunning = Button1;
                                this->oscursor->setCursor(it->getPosx(), it->getPosy());
                                this->oscursor->clickPress(Button1);
                            } else {
                                this->oscursor->setCursor(it->getPosx(), it->getPosy());
                                this->oscursor->clickRelease(Button1);
                                it->clickrunning = 0;
                                this->oscursor->releaseMutex();
                            }
                            break;
                        case BTN_RIGHT:
                            if ((int)work_event["value"]==1) {
                                this->oscursor->getMutex();
                                it->clickrunning = Button3;
                                this->oscursor->setCursor(it->getPosx(), it->getPosy());
                                this->oscursor->clickPress(Button3);
                            } else {
                                this->oscursor->setCursor(it->getPosx(), it->getPosy());
                                this->oscursor->clickRelease(Button3);
                                it->clickrunning = 0;
                                this->oscursor->releaseMutex();
                            }
                            break;
                        case BTN_MIDDLE:
                            if ((int)work_event["value"]==1) {
                                this->oscursor->getMutex();
                                it->clickrunning = Button2;
                                this->oscursor->setCursor(it->getPosx(), it->getPosy());
                                this->oscursor->clickPress(Button2);
                            } else {
                                this->oscursor->setCursor(it->getPosx(), it->getPosy());
                                this->oscursor->clickRelease(Button2);
                                it->clickrunning = 0;
                                this->oscursor->releaseMutex();
                            }
                            break;
                    }
                } else if(REL_WHEEL==(int)work_event["code"] || ABS_WHEEL==(int)work_event["code"]) {
                    if (1==(int)work_event["value"]) {
                        it->clickrunning = Button4;
                        this->oscursor->setCursor(it->getPosx(), it->getPosy());
                        this->oscursor->clickPress(Button4);
                        this->oscursor->clickRelease(Button4);
                        it->clickrunning = 0;
                    } else if(-1==(int)work_event["value"]) {
                            it->clickrunning = Button5;
                        this->oscursor->setCursor(it->getPosx(), it->getPosy());
                        this->oscursor->clickPress(Button5);
                        this->oscursor->clickRelease(Button5);
                            it->clickrunning = 0;
                    }
                }
            }
        } else {
            // wenn inaktiv
            if(this->amountlocal>cnt){
                // ist lokaler event
                // sendeevent
                mrm->sendmouseevent(work_event);
            }
        }
        if(it->clickrunning==Button1 || it->clickrunning==Button2 || it->clickrunning==Button3){
            this->oscursor->setCursor(it->getPosx(), it->getPosy());
        }
    }
    return 0;
}
