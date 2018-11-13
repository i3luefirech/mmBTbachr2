//
// Created by bluefire on 11/12/18.
//

#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <cstring>
#include "../inc/mmClient.h"

mmClient::mmClient() {
    this->s = socket(AF_INET,SOCK_DGRAM,0);
    this->addrout.sin_family = AF_INET;
    this->addrout.sin_port = htons(12322);
    this->addrout.sin_addr.s_addr = htonl(INADDR_BROADCAST);
};

int mmClient::start() {
    int ret = 0;
    int trueflag = 1;
    if ( this->s == -1 ) {
        std::cout << "mmClient: socketinit error" << std::endl;
        return -1;
    }

    if ((ret = setsockopt( this->s, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof(trueflag))) < 0) {
        std::cout << "mmClient: setsockopt " << ret << std::endl;
    }

    this->run();
    return ret;
}

void mmClient::run() {
    char dgram[512];
    int cnt = 0;
    for (;;) {
        sprintf(dgram,"%i\r\n",cnt++);
        ssize_t ret = sendto(this->s, dgram, strlen(dgram)+1, 0, (struct sockaddr*) &this->addrout, sizeof(this->addrout));
        if (ret < 0) {
            std::cout << "mmClient: send error" << std::endl;
            break;
        } else {
            std::cout << "mmClient: " << dgram << std::endl;
        }
        sleep(1);
    }
}
