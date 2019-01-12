//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMUDPCLIENT_H
#define CODE_MRMUDPCLIENT_H

#include <netinet/in.h>
#include "configparser.h"


class mrmUDPClient {

private:
    int s;
    struct sockaddr_in addrout;
public:
    mrmUDPClient();
    mrmUDPClient(int port);

    void sendtest();

    void sendevent(json sendevent);

    void sendscreenchange(int direction);
};


#endif //CODE_MRMUDPCLIENT_H
