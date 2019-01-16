//
// Created by root on 1/11/19.
//

#include <iostream>
#include <arpa/inet.h>
#include "../inc/mrmUDPServer.h"
#include "../inc/mrmMultiRemoteMouse.h"

using namespace std;

extern mrmMultiRemoteMouse * mrm;

mrmUDPServer::mrmUDPServer(int port, string hostip) {
    this->s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    cout << "mrmUDPServer: socket = " << this->s << endl;
    this->addrin.sin_family = AF_INET;
    this->addrin.sin_port = htons(port);
    this->addrin.sin_addr.s_addr = htonl(INADDR_ANY);
    this->hostip = hostip;
    int ret = 0;
    int trueflag = 1;
    if ( this->s == -1 ) {
        cout << "mrmUDPServer: socketinit error" << endl;
    }

    /*if( (ret = */bind( this->s, (struct sockaddr *)&this->addrin, sizeof(this->addrin));/*) == -1 ){
        cout << "mrmUDPServer: bind error " << ret << endl;
    }*/

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
    char dgram[1024];
    for (;;) {
        struct sockaddr_in srcaddr;
        socklen_t addrlen = sizeof(srcaddr);
        ssize_t ret = recvfrom(this->s, dgram, sizeof(dgram), 0, (struct sockaddr *)&srcaddr, &addrlen);
        if (ret < 0) {
            cout << "mrmUDPServer: recv error" << endl;
            break;
        } else {
            if(this->hostip.compare(inet_ntoa(srcaddr.sin_addr))!=0) {
                json temp = json::parse(dgram);
                mrm->recvMouseEvent(temp);
                cout << "received from: " << inet_ntoa(srcaddr.sin_addr) << endl;
            }
        }
    }
}