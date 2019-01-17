//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMUDPSERVER_H
#define CODE_MRMUDPSERVER_H

#include <netinet/in.h>
#include <nlohmann/json.hpp>

using namespace std;

using json = nlohmann::json;


class mrmUDPServer {

public:
    mrmUDPServer(int port, string hostip);

    void start();

    void run();

    int s;
    struct sockaddr_in addrin;
    string hostip;
};


#endif //CODE_MRMUDPSERVER_H
