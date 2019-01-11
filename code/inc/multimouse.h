//
// Created by bluefire on 11/12/18.
//

#ifndef CODE_MULTIMOUSE_H
#define CODE_MULTIMOUSE_H

#include "mmClient.h"
#include "mmServer.h"
#include "mmRealMouseCtrl.h"
#include "mmVirtualMouseCtrl.h"
#include "mmCursorCtrl.h"
#include "RealMouse.h"

class multimouse {
private:
    mmClient * client;
    mmServer * server;
    mmRealMouseCtrl * rmCtrl;
    mmVirtualMouseCtrl * vmCtrl;
    mmCursorCtrl * cCtrl;
    pthread_t serverthread;
    pthread_t clientthread;
public:
    multimouse();
    void start();
    void startserver();
    void startclient();
    void startrealmouse(void *pVoid);

    multimouse(RealMouse *localmice, mmCursor *localcursors, mmCursor *remotecursors);
};

#endif //CODE_MULTIMOUSE_H

