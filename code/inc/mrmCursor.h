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
    int getPosx() const;

    void setPosx(int posx);

    int getPosy() const;

    void setPosy(int posy);

    int getXMax();

    int getYMax();

    int clickrunning;

    Display *getDisplay();


private:

    static int VisData[];
public:
    mrmCursor(string id, int color_r, int color_g, int color_b, int show, int click, int datatf, bool active,
              int devicenumbers[]);

    string getid();

    void run(mrmCursor *cursor);

    void start();

    int updateTheMessageQueue();

    void createTheWindow();

    void createTheRenderContext();

    void redrawTheWindow();

    void describe_fbconfig(GLXFBConfig fbconfig);

    void setlastabsx(int lastabs);

    void setlastabsy(int lastabs);

    int getrelxfromabs();

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

    bool isactive();

    void activate(bool activate);
};


#endif //CODE_MRMCURSOR_H
