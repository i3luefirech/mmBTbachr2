//
// Created by bluefire on 11/12/18.
//

#ifndef CODE_MMCLIENT_H
#define CODE_MMCLIENT_H

#include<arpa/inet.h>

class mmClient {
private:
    int s;
    struct sockaddr_in addrout;
public:
    mmClient();
    int start();
    void run();
};

#endif //CODE_MMCLIENT_H
