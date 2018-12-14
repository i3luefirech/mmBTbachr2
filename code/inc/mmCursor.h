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
    void run();
    mmCursor();
};

#endif //CODE_MMCURSOR_H
