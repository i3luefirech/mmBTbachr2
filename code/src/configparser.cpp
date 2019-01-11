//
// Created by root on 12/25/18.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "../inc/configparser.h"
#include "../inc/RealMouse.h"

//json j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

configparser::configparser(std::string jsonstr) {
    this->jsonstr = jsonstr;
}

json configparser::parse(){
    this->jsonobj = json::parse(this->jsonstr);
    return this->jsonobj;
}

int configparser::createLocalMice(RealMouse * localmices) {
    RealMouse *ptrlocalmices = localmices;
    auto tempjson = this->jsonobj["localmice"];
    int count = 0;
    std::cout << "localmice" << std::endl;
    for(json::iterator it1 = tempjson.begin(); it1 != tempjson.end(); ++it1){
        ptrlocalmices = new RealMouse();
        ptrlocalmices++;
        std::cout << it1.value() << std::endl;
        count++;
    }
    return count;
}

int configparser::createLocalCursor(mmCursor * localcursor) {
    mmCursor *ptrlocalcursor = localcursor;
    auto tempjson = this->jsonobj["localmice"];
    int count = 0;
    std::cout << "localcursor" << std::endl;
    for(json::iterator it1 = tempjson.begin(); it1 != tempjson.end(); ++it1){
        ptrlocalcursor = new mmCursor(20*count,0);
        ptrlocalcursor++;
        std::cout << it1.value() << std::endl;
        count++;
    }
    return count;
}

int configparser::createRemoteCursor(mmCursor * remotecursor) {
    mmCursor *ptrremotecursor = remotecursor;
    auto tempjson = this->jsonobj["remotemice"];
    int count = 0;
    std::cout << "remotemice/cursors" << std::endl;
    for(json::iterator it1 = tempjson.begin(); it1 != tempjson.end(); ++it1){
        ptrremotecursor = new mmCursor();
        ptrremotecursor++;
        std::cout << it1.value() << std::endl;
        count++;
    }
    return count;
}