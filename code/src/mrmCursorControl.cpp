//
// Created by root on 1/11/19.
//

#include <iostream>
#include <linux/input-event-codes.h>
#include <zconf.h>
#include "../inc/mrmOSCursor.h"
#include "../inc/mrmCursorControl.h"

mrmCursorControl::mrmCursorControl(list <mrmCursor> localcursors, list <mrmCursor> remotecursors, int amountlc,
                                   int amountrc) {
    this->cursors = localcursors;
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
    for(auto it = this->cursors.begin(); it != this->cursors.end(); it++){
        if(it->id.compare(work_event["id"])==0){
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
                    case BTN_SIDE:
                        if ((int)work_event["value"]==1) {
                            this->oscursor->getMutex();
                            it->clickrunning = Button4;
                            this->oscursor->setCursor(it->getPosx(), it->getPosy());
                            this->oscursor->clickPress(Button4);
                        } else {
                            this->oscursor->setCursor(it->getPosx(), it->getPosy());
                            this->oscursor->clickRelease(Button4);
                            it->clickrunning = 0;
                            this->oscursor->releaseMutex();
                        }
                        break;
                    case BTN_EXTRA:
                        if ((int)work_event["value"]==1) {
                            this->oscursor->getMutex();
                            it->clickrunning = Button5;
                            this->oscursor->setCursor(it->getPosx(), it->getPosy());
                            this->oscursor->clickPress(Button5);
                        } else {
                            this->oscursor->setCursor(it->getPosx(), it->getPosy());
                            this->oscursor->clickRelease(Button5);
                            it->clickrunning = 0;
                            this->oscursor->releaseMutex();
                        }
                        break;
                }
            } else if(EV_REL==(int)work_event["type"]){
                if(REL_X==(int)work_event["code"]){
                    int newpos = it->getPosx()+(int)work_event["value"];
                    if(newpos<0){
                        newpos=0;
                    }
                    if(newpos>it->getXMax()-1){
                        newpos=it->getXMax()-1;
                    }
                    it->setPosx(newpos);
                } else if(REL_Y==(int)work_event["code"]){
                    int newpos = it->getPosy()+(int)work_event["value"];
                    if(newpos<0){
                        newpos=0;
                    }
                    if(newpos>it->getYMax()-1){
                        newpos=it->getYMax()-1;
                    }
                    it->setPosy(newpos);
                } else if(REL_WHEEL==(int)work_event["code"]){
                    cout << "v: " << work_event["value"] << endl;
                }
                if(it->clickrunning==Button1 || it->clickrunning==Button2 || it->clickrunning==Button3 || it->clickrunning==Button4 || it->clickrunning==Button5){
                    this->oscursor->setCursor(it->getPosx(), it->getPosy());
                }
            } else if(EV_ABS==(int)work_event["type"]) {
                if(ABS_X==(int)work_event["code"]){
                    it->setlastabsx((int)work_event["value"]);
                    int relval = it->getrelxfromabs();
                    if(relval<-100){
                        relval= -100;
                    } else if(relval>100){
                        relval = 100;
                    }
                    int newpos = it->getPosx()-relval;
                    if(newpos<0){
                        newpos=0;
                    }
                    if(newpos>it->getXMax()-1){
                        newpos=it->getXMax()-1;
                    }
                    it->setPosx(newpos);
                } else if(ABS_Y==(int)work_event["code"]){
                    it->setlastabsy((int)work_event["value"]);
                    int relval = it->getrelyfromabs();
                    if(relval<-70){
                        relval= -70;
                    } else if(relval>70){
                        relval = 70;
                    }
                    int newpos = it->getPosy()-relval;
                    if(newpos<0){
                        newpos=0;
                    }
                    if(newpos>it->getYMax()-1){
                        newpos=it->getYMax()-1;
                    }
                    it->setPosy(newpos);
                }
                if(it->clickrunning==Button1 || it->clickrunning==Button2 || it->clickrunning==Button3 || it->clickrunning==Button4 || it->clickrunning==Button5){
                    this->oscursor->setCursor(it->getPosx(), it->getPosy());
                }
            }
        }
    }
    return 0;
}
