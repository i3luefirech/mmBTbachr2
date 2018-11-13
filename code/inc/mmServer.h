//
// Created by bluefire on 11/12/18.
//

#ifndef CODE_MMSERVER_H
#define CODE_MMSERVER_H

#include<arpa/inet.h>

class mmServer {
private:
    int s;
    struct sockaddr_in addrin;
public:
    mmServer();
    int start();
    void run();
};

#endif //CODE_MMSERVER_H
