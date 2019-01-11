//
// Created by bluefire on 11/12/18.
//

#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include "../inc/mmServer.h"

// functions

mmServer::mmServer() {
    this->s = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    std::cout << "mmServer: socket = " << this->s << std::endl;
    this->addrin.sin_family = AF_INET;
    this->addrin.sin_port = htons(60606);
    this->addrin.sin_addr.s_addr = htonl(INADDR_ANY);
};

void mmServer::run() {
    int ret = 0;
    int trueflag = 1;
    if ( this->s == -1 ) {
        std::cout << "mmServer: socketinit error" << std::endl;
        return;
    }

    if( (ret = bind( this->s, (struct sockaddr *)&this->addrin, sizeof(this->addrin))) == -1 ){
        std::cout << "mmServer: bind error " << ret << std::endl;
        return;
    }

    if ( (ret=setsockopt(this->s, SOL_SOCKET, SO_REUSEADDR, &trueflag, sizeof(trueflag))) < 0) {
        std::cout << "mmServer: setsockopt " << ret << std::endl;
    }
    char dgram[512];
    for (;;) {
        ssize_t ret = recv(s, dgram, sizeof dgram, 0);
        if (ret < 0) {
            std::cout << "mmServer: recv error" << std::endl;
            break;
        } else {
            std::cout << "mmServer: " << dgram << std::endl;
        }
    }
}
