//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMCFGPARSER_H
#define CODE_MRMCFGPARSER_H

#include <string>
#include "mrmMouse.h"
#include "mrmCursor.h"
#include "mrmScreen.h"
#include <nlohmann/json.hpp>

using namespace std;

using json = nlohmann::json;

class mrmCfgParser {

public:
    mrmCfgParser(string jsonstring);

    json parse();

    list<mrmMouse> createLocalMice(int *count);

    list<mrmCursor> createLocalCursors(int *count);

    list<mrmCursor> createRemoteCursors(int *count);

    list<mrmScreen> createScreens(int *count);

    int getUDPPort();
    string getHostIP();

    string jsonstr;
    json jsonobj;
};


#endif //CODE_MRMCFGPARSER_H
