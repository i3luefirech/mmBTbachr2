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

class multimouse {
private:
    mmClient *client;
    mmServer *server;
    mmRealMouseCtrl *rmCtrl;
    mmVirtualMouseCtrl *vmCtrl;
    mmCursorCtrl * cCtrl;
public:
    multimouse();
};

#endif //CODE_MULTIMOUSE_H

