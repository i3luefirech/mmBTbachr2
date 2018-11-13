//
// Created by bluefire on 11/12/18.
//

#include <pthread.h>
#include "../inc/multimouse.h"

extern multimouse * mm;

void *Thread1(void *pVoid) {

    mm->startserver();

    pthread_exit(nullptr);
}

void *Thread0(void *pVoid) {

    mm->startclient();

    pthread_exit(nullptr);
}

multimouse::multimouse(){
    // create Client
    this->client = new mmClient();
    // create Server
    this->server = new mmServer();
    // create RealMouseCtrl
    this->rmCtrl = new mmRealMouseCtrl();
    // create VirtualMouseCtrl
    this->vmCtrl = new mmVirtualMouseCtrl();
    // create CursorCtrl
    this->cCtrl = new mmCursorCtrl();
}

void multimouse::start(){
    // threads
    pthread_t thread0;
    pthread_t thread1;
    // start Client
    pthread_create( &thread0, nullptr, Thread0, (void *)nullptr );
    // start Server
    pthread_create( &thread1, nullptr, Thread1, (void *)nullptr );
};

void multimouse::startserver() {
    mm->server->start();
};

void multimouse::startclient() {
    mm->client->start();
};