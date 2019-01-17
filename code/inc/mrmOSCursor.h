//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMOSCURSOR_H
#define CODE_MRMOSCURSOR_H

#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>
#include <X11/extensions/XTest.h>
#include <X11/Xutil.h>

class mrmOSCursor {
private:
public:
    /**
     * create the OS cursor object
     */
    mrmOSCursor();

    /**
     * get the mutex. This function will make a blocking wait until you have acces to the mutex
     */
    void getMutex();

    /**
     * release the mutex. This function frees the mutex if it is in your control
     */
    void releaseMutex();

    /**
     * sets the cursor position to the parameter values for posx and y.
     * @param posx
     * @param posy
     */
    void setCursor(int posx, int posy);

    /**
     * simulates a button click press on the os cursor. The param gives the used key for the click
     * @param key
     */
    void clickPress(int key);

    /**
     * simulates a button click release on the os cursor. The param gives the used key for the click
     * @param key
     */
    void clickRelease(int key);

    int posx;
    int posy;
    Display *dpy;
    pthread_mutex_t mutex;
};


#endif //CODE_MRMOSCURSOR_H
