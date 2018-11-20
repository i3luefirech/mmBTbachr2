//
// Created by bluefire on 11/12/18.
//

#include "../inc/mmCursorCtrl.h"

mmCursorCtrl::mmCursorCtrl() {
    mmCursor localmouse;
    this->cursorptr.push_back(&localmouse);
};

void mmCursorCtrl::addCursor(mmCursor * newcursor) {
    this->cursorptr.push_back(newcursor);
}

void mmCursorCtrl::rmCursor(mmCursor * rmcursor) {
    this->cursorptr.remove(rmcursor);
}

int mmCursorCtrl::start() {
    return 0;
}