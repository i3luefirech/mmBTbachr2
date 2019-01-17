//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMCFGPARSER_H
#define CODE_MRMCFGPARSER_H

#include <string>
#include <list>
#include "mrmMouse.h"
#include "mrmCursor.h"
#include "mrmScreen.h"
#include <nlohmann/json.hpp>

using namespace std;

using json = nlohmann::json;

class mrmCfgParser {

public:
    /**
     * creates a cfg parser. Add the text to be parsed as a parameter
     * @param jsonstring
     */
    mrmCfgParser(string jsonstring);

    /**
     * parse the received string to an json object
     * @return
     */
    json parse();

    /**
     * creates a list of all the configured local mice
     * @param count
     * @return list of the mice objects
     */
    list<mrmMouse> createLocalMice(int *count);

    /**
     * creates a list of all the configured local cursors
     * @param count
     * @return list of the cursor objects
     */
    list<mrmCursor> createLocalCursors(int *count);

    /**
     * creates a list of all the configured remote cursors
     * @param count
     * @return list of the cursor objects
     */
    list<mrmCursor> createRemoteCursors(int *count);

    /**
     * creates a list of all the configured remote screens
     * @param count
     * @return list of the screen objects
     */
    list<mrmScreen> createScreens(int *count);

    /**
     * return the configured UDP port
     * @return
     */
    int getUDPPort();

    /**
     * return the configured host ip as a string
     * @return
     */
    string getHostIP();

    string jsonstr;
    json jsonobj;
};


#endif //CODE_MRMCFGPARSER_H
