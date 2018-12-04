//
// Created by root on 11/16/18.
//

#ifndef CODE_MMCURSOR_H
#define CODE_MMCURSOR_H

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

class mmCursor {
public:

    mmCursor();

private:

    Display *Xdisplay;
    int Xscreen;
    Window Xroot;
    GLXFBConfig *fbconfigs;
    GLXFBConfig fbconfig;
    int numfbconfigs;
    XVisualInfo *visual;
    XRenderPictFormat *pict_format;
    Colormap cmap;
    int width;
    int height;
    Window window_handle;
    Window glX_window_handle;
    Atom del_atom;
    static int VisData[];

    void describe_fbconfig(GLXFBConfig fbconfig);
    static int WaitForMapNotify(Display *d, XEvent *e, char *arg);
    void allow_input_passthrough (Window w);
};

#endif //CODE_MMCURSOR_H
