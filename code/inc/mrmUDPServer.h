//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMUDPSERVER_H
#define CODE_MRMUDPSERVER_H

#include <netinet/in.h>


class mrmUDPServer {

public:
    mrmUDPServer(int port);

    void start();
    void run();

    int s;
    struct sockaddr_in addrin;
};


#endif //CODE_MRMUDPSERVER_H
