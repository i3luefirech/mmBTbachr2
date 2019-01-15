//
// Created by root on 1/11/19.
//

#include <nlohmann/json.hpp>
#include <iostream>
#include <list>
#include "../inc/mrmCfgParser.h"

mrmCfgParser::mrmCfgParser(string jsonstring) {
    this->jsonstr = jsonstring;
}

json mrmCfgParser::parse() {
    this->jsonobj = json::parse(this->jsonstr);
    return this->jsonobj;
}

list<mrmCursor> mrmCfgParser::createRemoteCursors(int *count) {
    list<mrmCursor> retcursor;
    auto tempjson = this->jsonobj["remotemice"];
    (*count) = 0;
    cout << "remotecursor" << endl;
    for(json::iterator it1 = tempjson.begin(); it1 != tempjson.end(); ++it1){
        cout << "entry: " << it1.value() << endl;
        json entries = it1.value();
        int array[] = {0,0,0,0,0};
        retcursor.push_back(mrmCursor(entries["id"], entries["color_r"], entries["color_g"], entries["color_b"], entries["show"], entries["click"], entries["datatf"], false, array));
        (*count)++;
    }
    return retcursor;
}

int mrmCfgParser::getUDPPort() {
    auto tempjson = this->jsonobj["port"];
    int count = 0;
    json::iterator it1 = tempjson.begin();
    cout << "port " << it1.value() << endl;
    return it1.value();
}

string mrmCfgParser::getHostIP() {
    auto tempjson = this->jsonobj["hostip"];
    json::iterator it1 = tempjson.begin();
    cout << "host: " << it1.value() << endl;
    return it1.value();
}

list<mrmMouse> mrmCfgParser::createLocalMice(int * count) {
    list<mrmMouse> retmice;
    auto tempjson = this->jsonobj["localmice"];
    (*count) = 0;
    cout << "localmice" << endl;
    for(json::iterator it1 = tempjson.begin(); it1 != tempjson.end(); ++it1){
        cout << "entry: " << it1.value() << endl;
        json entries = it1.value();
        retmice.push_back(mrmMouse(entries["id"], entries["eventfile"]));
        (*count)++;
    }

    return retmice;
}

list<mrmCursor> mrmCfgParser::createLocalCursors(int *count) {
    list<mrmCursor> retcursors;
    auto tempjson = this->jsonobj["localmice"];
    (*count) = 0;
    cout << "localcursor" << endl;
    for(json::iterator it1 = tempjson.begin(); it1 != tempjson.end(); ++it1){
        cout << "entry: " << it1.value() << endl;
        json entries = it1.value();
        json::iterator devicenumberarray = entries["devicenumbers"].begin();
        int array[] = {devicenumberarray++.value(),devicenumberarray++.value(),devicenumberarray++.value(),devicenumberarray++.value(),devicenumberarray.value()};
        retcursors.push_back(mrmCursor(entries["id"], entries["color_r"], entries["color_g"], entries["color_b"], 1, 1, 1, true, array));
        (*count)++;
    }
    return retcursors;
}

list<mrmScreen> mrmCfgParser::createScreens(int * count) {
    list<mrmScreen> retscreens;
    auto tempjson = this->jsonobj["screens"];
    *count = 0;
    cout << "remotescreen" << endl;
    for(json::iterator it1 = tempjson.begin(); it1 != tempjson.end(); ++it1){
        cout << "entry: " << it1.value() << endl;
        json entries = it1.value();
        retscreens.push_back(mrmScreen(entries["ip"], entries["pos"]));
        (*count)++;
    }
    return retscreens;
}
