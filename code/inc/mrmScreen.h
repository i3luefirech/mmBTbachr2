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
    mrmScreen(string ip, int pos);

    int getDirection();

    string getipaddr();

    string ip;
    int pos;
};


#endif //CODE_MRMSCREEN_H
