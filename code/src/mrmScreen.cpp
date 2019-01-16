//
// Created by root on 1/11/19.
//

#include "../inc/mrmScreen.h"

mrmScreen::mrmScreen(string ip, int pos) {
    this->ip = ip;
    this->pos = pos;
}

int mrmScreen::getDirection() {
    return this->pos;
}

string mrmScreen::getipaddr() {
    return this->ip;
}
