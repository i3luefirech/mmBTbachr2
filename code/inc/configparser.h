//
// Created by root on 12/25/18.
//

#ifndef CODE_CONFIGPARSER_H
#define CODE_CONFIGPARSER_H

#include <string>
#include <nlohmann/json.hpp>
#include "RealMouse.h"
#include "mmCursor.h"

// for convenience
using json = nlohmann::json;

class configparser{
public:
    configparser(std::string jsonstr);
    json parse();
    int createLocalMice(RealMouse * localmices);
    int createLocalCursor(mmCursor * localcursor);
    int createRemoteCursor(mmCursor * remotecursor);
    std::string jsonstr;
    json jsonobj;
};

#endif //CODE_CONFIGPARSER_H
