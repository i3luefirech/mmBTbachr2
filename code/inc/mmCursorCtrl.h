//
// Created by bluefire on 11/12/18.
//

#ifndef CODE_MMCURSORCTRL_H
#define CODE_MMCURSORCTRL_H

#include <list>
#include <unistd.h>
#include "../inc/mmCursor.h"

class mmCursorCtrl {
private:
    std::list<mmCursor*> cursorptr;
    int cursorAmount;
public:
    mmCursorCtrl();

    void addCursor(mmCursor * newcursor);

    void rmCursor(mmCursor * newcursor);

    int start();
};

#endif //CODE_MMCURSORCTRL_H
