//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMOSCURSOR_H
#define CODE_MRMOSCURSOR_H

#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xutil.h>

class mrmOSCursor {
private:
public:
    mrmOSCursor();
    void getMutex();
    void releaseMutex();
    void setCursor(int posx, int posy);
    void clickPress(int key);
    void clickRelease(int key);
    void sendMotionNotify(int key);

    int posx;
    int posy;
    Display *dpy;
    pthread_mutex_t mutex;
};


#endif //CODE_MRMOSCURSOR_H
