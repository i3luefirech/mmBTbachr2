//
// Created by root on 1/11/19.
//

using namespace std;

#include <iostream>
#include <cstring>
#include "../inc/mrmUDPClient.h"

mrmUDPClient::mrmUDPClient(int port) {
    this->s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    cout << "mrmUDPClient: socket = " << this->s << endl;
    this->addrout.sin_family = AF_INET;
    this->addrout.sin_port = htons(port);
    this->addrout.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    int ret = 0;
    // activate rights for broadcasting on socket
    int trueflag = 1;
    if ( this->s == -1 ) {
        cout << "mrmUDPClient: socketinit error" << endl;
    }
    if ((ret = setsockopt( this->s, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof(trueflag))) < 0) {
        cout << "mrmUDPClient: setsockopt " << ret << endl;
    }
}

void mrmUDPClient::sendevent(json sendevent) {
    ssize_t ret = sendto(this->s, sendevent.dump(4).c_str(), sizeof(char) * (strlen(sendevent.dump(4).c_str())+1), 0, (struct sockaddr*) &this->addrout, sizeof(this->addrout));
}

