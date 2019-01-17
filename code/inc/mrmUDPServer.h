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
    /**
     * creating the USP server and will be opened with the parameter port. The hostip is needed to chekc which messages are import for our server
     * @param port
     * @param hostip
     */
    mrmUDPServer(int port, string hostip);

    /**
     * starts the Thread which is running the server. The run function wil be called in the thread.
     */
    void start();

    /**
     * the run function. This function will bi called from the server thread. The run function receives UDP packages and send them to our controller
     */
    void run();

    int s;
    struct sockaddr_in addrin;
    string hostip;
};


#endif //CODE_MRMUDPSERVER_H
