//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMSCREEN_H
#define CODE_MRMSCREEN_H

#include <string>

using namespace std;


class mrmScreen {
private:
public:
    /**
     * creates the screen with all needed information, like position and IP
     * @param ip
     * @param pos
     */
    mrmScreen(string ip, int pos);

    /**
     * getter function to receive the Direction of the screen
     * @return the direction as integer -1 and 1
     */
    int getDirection();

    /**
     * getter function to receive the IP of the screen
     * @return returns the IP as string value
     */
    string getipaddr();

    string ip;
    int pos;
};


#endif //CODE_MRMSCREEN_H
