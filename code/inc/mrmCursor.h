//
// Created by root on 1/11/19.
//

#ifndef CODE_MRMCURSOR_H
#define CODE_MRMCURSOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xutil.h>
#include <string>


using namespace std;


class mrmCursor {
private:
    static int VisData[];
    int Xscreen;
    Atom del_atom;
    Colormap cmap;
    Display *Xdisplay;
    XVisualInfo *visual;
    XRenderPictFormat *pict_format;
    GLXFBConfig *fbconfigs, fbconfig;
    int numfbconfigs;
    GLXContext render_context;
    Window Xroot, window_handle;
    GLXWindow glX_window_handle;
    int width, height;
    int posx, posy;
    bool active;
public:
    /**
     * get position
     * @return
     */
    int getPosx() const;

    /**
     * set position
     * @return
     */
    void setPosx(int posx);

    /**
     * get position
     * @return
     */
    int getPosy() const;

    /**
     * set position
     * @return
     */
    void setPosy(int posy);

    /**
     * get max position
     * @return
     */
    int getXMax();

    /**
     * get max position
     * @return
     */
    int getYMax();

    int clickrunning;

    Display *getDisplay();

    /**
     * create the current cursor with al the needed configuration values
     * @param id
     * @param color_r
     * @param color_g
     * @param color_b
     * @param show
     * @param click
     * @param datatf
     * @param active
     * @param devicenumbers
     */
    mrmCursor(string id, int color_r, int color_g, int color_b, int show, int click, int datatf, bool active,
              int devicenumbers[]);

    /**
     * get the id of this cursor as string
     * @return
     */
    string getid();

    void run(mrmCursor *cursor);

    /**
     * starts the Thread which is running the cursor. The run function wil be called in the thread.
     */
    void start();

    /**
     * Check the MEssage queue of the windowserver. Act if needed
     * @return
     */
    int updateTheMessageQueue();

    /**
     * create the window needed to draw in it
     */
    void createTheWindow();

    /**
     * creating the needed render content to be able to draw the window and the cursor
     */
    void createTheRenderContext();

    /**
     * redraw the window which holds our cursor. Redraw the cursor into this window.
     */
    void redrawTheWindow();

    /**
     * set/describe the current used fbconfig
     * @return
     */
    void describe_fbconfig(GLXFBConfig fbconfig);

    /**
     * set the last absolut value
     * @param lastabs
     */
    void setlastabsx(int lastabs);

    /**
     * set the last absolut value
     * @param lastabs
     */
    void setlastabsy(int lastabs);

    /**
     * calculate the relative value from the last two absolut values
     * @return rel value
     */
    int getrelxfromabs();

    /**
     * calculate the relative value from the last two absolut values
     * @return rel value
     */
    int getrelyfromabs();

    string id;
    int color_r;
    int color_g;
    int color_b;
    int show;
    int click;
    int datatf;
    int lastabsx;
    int lastabsy;
    int relx;
    int rely;

    /**
     * returns the current activ state
     * @return
     */
    bool isactive();

    /**
     * activate or deactivate the cursor. The parameter defines if deactivated or activated
     * @param activate
     */
    void activate(bool activate);
};


#endif //CODE_MRMCURSOR_H
