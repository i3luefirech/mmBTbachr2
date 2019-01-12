//
// Created by bluefire on 11/12/18.
//

#include <pthread.h>
#include "../inc/mmCursorCtrl.h"

extern mmCursorCtrl * cc;

void *ThreadCC0(void *pVoid) {

    cc->localmouse->run();

    pthread_exit(nullptr);
}

mmCursorCtrl::mmCursorCtrl() {
    this->localmouse = new mmCursor();
    this->cursorptr.push_back(this->localmouse);
};

void mmCursorCtrl::addCursor(mmCursor * newcursor) {
    this->cursorptr.push_back(newcursor);
}

void mmCursorCtrl::rmCursor(mmCursor * rmcursor) {
    this->cursorptr.remove(rmcursor);
}

int mmCursorCtrl::start() {
    pthread_t threadCC0;
    // start Client
    pthread_create( &threadCC0, nullptr, ThreadCC0, (void *)nullptr );
    return 0;
}

mmCursorCtrl::mmCursorCtrl(mmCursor *localcursors, mmCursor *remotecursors) {

}
