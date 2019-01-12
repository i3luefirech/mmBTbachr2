//
// Created by root on 1/11/19.
//

#include <iostream>
#include "../inc/mrmUDPServer.h"

using namespace std;

mrmUDPServer::mrmUDPServer(int port) {
    this->s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    cout << "mrmUDPServer: socket = " << this->s << endl;
    this->addrin.sin_family = AF_INET;
    this->addrin.sin_port = htons(port);
    this->addrin.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = 0;
    int trueflag = 1;
    if ( this->s == -1 ) {
        cout << "mrmUDPServer: socketinit error" << endl;
    }

    if( (ret = bind( this->s, (struct sockaddr *)&this->addrin, sizeof(this->addrin))) == -1 ){
        cout << "mrmUDPServer: bind error " << ret << endl;
    }

    if ( (ret=setsockopt(this->s, SOL_SOCKET, SO_REUSEADDR, &trueflag, sizeof(trueflag))) < 0) {
        cout << "mrmUDPServer: setsockopt " << ret << endl;
    }
}

void *ThreadUDPServer(void *pVoid) {

    mrmUDPServer* server = static_cast<mrmUDPServer*>(pVoid);
    server->run();

    pthread_exit(nullptr);
}

void mrmUDPServer::start() {
    cout << "mrmUDPServer: start" << endl;
    pthread_t thread;
    // start Client
    pthread_create( &thread, nullptr, ThreadUDPServer, static_cast<void*>(this));
}

void mrmUDPServer::run() {
    cout << "mrmUDPServer: run" << endl;
    char dgram[512];
    for (;;) {
        ssize_t ret = recv(this->s, dgram, sizeof dgram, 0);
        if (ret < 0) {
            cout << "mrmUDPServer: recv error" << endl;
            break;
        } else {
            cout << "mrmUDPServer: " << dgram << endl;
        }
    }
}