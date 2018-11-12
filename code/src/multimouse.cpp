//
// Created by bluefire on 11/12/18.
//

#include "../inc/multimouse.h"

multimouse::multimouse(){

    // create Server
    this->server = new mmServer();
    // create Client
    this->client = new mmClient();
    // create RealMouseCtrl
    this->rmCtrl = new mmRealMouseCtrl();
    // create VirtualMouseCtrl
    this->vmCtrl = new mmVirtualMouseCtrl();
    // create CursorCtrl
    this->cCtrl = new mmCursorCtrl();

    // start Server
    this->server->start();
    // start Client
    this->client->start();

};