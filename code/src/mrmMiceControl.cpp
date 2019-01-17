#include <utility>

//
// Created by root on 1/11/19.
//

using namespace std;

#include "../inc/mrmMiceControl.h"

mrmMiceControl::mrmMiceControl(list<mrmMouse> localmice, int amount) {
    this->mice = std::move(localmice);
    this->amount = amount;
}

void mrmMiceControl::start() {
    cout << "mrmMiceControl: start " << this->mice.size() << " , " << amount << endl;
    for (auto it = this->mice.begin(); it != this->mice.end(); it++) {
        it->start();
    }
}