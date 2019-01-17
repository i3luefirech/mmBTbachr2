//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMUDPCLIENT_H
#define CODE_MRMUDPCLIENT_H

#include <netinet/in.h>
#include "../inc/mrmCfgParser.h"


class mrmUDPClient {

private:
    int s;
    struct sockaddr_in addrout;
public:
    /**
     * create the UDP client on the parameter port
     *
     * @param port
     */
    mrmUDPClient(int port);

    /**
     * send a event over the network. The event must be given as a json object
     * @param sendevent
     */
    void sendevent(json sendevent);
};


#endif //CODE_MRMUDPCLIENT_H
