//
// Created by root on 1/11/19.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <X11/Xatom.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xrender.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#include <iostream>
#include <sstream>

#include "../inc/mrmCursor.h"


static Bool WaitForMapNotify(Display *d, XEvent *e, char *arg)
{
    return d && e && arg && (e->type == MapNotify) && (e->xmap.window == *(Window*)arg);
}

static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
{
    fputs("Error at context creation", stderr);
    return 0;
}

void mrmCursor::describe_fbconfig(GLXFBConfig fbconfig)
{
    int doublebuffer;
    int red_bits, green_bits, blue_bits, alpha_bits, depth_bits;

    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_DOUBLEBUFFER, &doublebuffer);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_RED_SIZE, &red_bits);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_GREEN_SIZE, &green_bits);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_BLUE_SIZE, &blue_bits);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_ALPHA_SIZE, &alpha_bits);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_DEPTH_SIZE, &depth_bits);

    fprintf(stderr, "FBConfig selected:\n"
                    "Doublebuffer: %s\n"
                    "Red Bits: %d, Green Bits: %d, Blue Bits: %d, Alpha Bits: %d, Depth Bits: %d\n",
            doublebuffer == True ? "Yes" : "No",
            red_bits, green_bits, blue_bits, alpha_bits, depth_bits);
}

int mrmCursor::VisData[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_DOUBLEBUFFER, True,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 16,
        None
};

mrmCursor::mrmCursor(string id, int color_r, int color_g, int color_b, int show, int click, int datatf, int devicenumbers[]) {
    this->id = id;
    this->color_r = color_r;
    this->color_g = color_g;
    this->color_b = color_b;
    this->show = show;
    this->click = click;
    this->datatf = datatf;
    this->posx = 0;
    this->posy = 0;
    this->lastabsx = 0;
    this->lastabsy = 0;
    this->relx = 0;
    this->rely = 0;
    this->clickrunning = 0;

    for(int i = 0; i < 5; i++){
        if(devicenumbers[i]!=0){
            stringstream command;
            command << "xinput disable " << devicenumbers[i];
            system(command.str().c_str());
        }
    }
}
void *ThreadCursor(void *pVoid) {

    mrmCursor* cursor = static_cast<mrmCursor*>(pVoid);
    cursor->run(cursor);

    pthread_exit(nullptr);
}

void mrmCursor::start(){
    cout << "mrmCursor: start " << this->id << endl;
    pthread_t thread;
    // start Client
    pthread_create( &thread, nullptr, ThreadCursor, static_cast<void*>(this));
}

void mrmCursor::run(mrmCursor * cursor) {
    cursor->createTheWindow();
    cursor->createTheRenderContext();
    while (cursor->updateTheMessageQueue()) {
        cursor->redrawTheWindow();
    }
}

void mrmCursor::createTheWindow()
{
    XEvent event;
    int x,y, attr_mask;
    XSizeHints hints;
    XWMHints *startup_state;
    XTextProperty textprop;
    XSetWindowAttributes attr = {0,};
    static char *title = "FTB's little OpenGL example - ARGB extension by WXD";

    this->Xdisplay = XOpenDisplay(NULL);
    if (!this->Xdisplay) {
        printf("Couldn't connect to X server\n");
    }
    this->Xscreen = DefaultScreen(this->Xdisplay);
    this->Xroot = RootWindow(this->Xdisplay, this->Xscreen);

    this->fbconfigs = glXChooseFBConfig(this->Xdisplay, this->Xscreen, this->VisData, &this->numfbconfigs);
    this->fbconfig = 0;
    for(int i = 0; i<this->numfbconfigs; i++) {
        this->visual = (XVisualInfo*) glXGetVisualFromFBConfig(this->Xdisplay, this->fbconfigs[i]);
        if(!this->visual)
            continue;

        this->pict_format = XRenderFindVisualFormat(this->Xdisplay, this->visual->visual);
        if(!this->pict_format)
            continue;

        this->fbconfig = this->fbconfigs[i];
        if(this->pict_format->direct.alphaMask > 0) {
            break;
        }
    }

    if(!this->fbconfig) {
        printf("No matching FB config found");
    }

    describe_fbconfig(this->fbconfig);

    /* Create a colormap - only needed on some X clients, eg. IRIX */
    this->cmap = XCreateColormap(this->Xdisplay, this->Xroot, this->visual->visual, AllocNone);

    attr.colormap = this->cmap;
    attr.background_pixmap = None;
    attr.border_pixmap = None;
    attr.border_pixel = 0;
    attr.event_mask =
            StructureNotifyMask;
            EnterWindowMask |
            LeaveWindowMask |
            ExposureMask |
            ButtonPressMask |
            ButtonReleaseMask |
            OwnerGrabButtonMask |
            KeyPressMask |
            KeyReleaseMask;

    attr_mask =
            CWBackPixmap|
            CWColormap|
            CWBorderPixel|
            CWOverrideRedirect |
            CWEventMask;

    attr.override_redirect = true;

    this->width = 20;//DisplayWidth(Xdisplay, DefaultScreen(Xdisplay));
    this->height = 20;//DisplayHeight(Xdisplay, DefaultScreen(Xdisplay));
    x=0, y=0;

    //this->window_handle = XCompositeGetOverlayWindow(Xdisplay,Xroot);
    this->window_handle = XCreateWindow(  this->Xdisplay,
                                          this->Xroot,
                                    x, y, this->width, this->height,
                                    0,
                                          this->visual->depth,
                                    InputOutput,
                                          this->visual->visual,
                                    attr_mask, &attr);

    XserverRegion region = XFixesCreateRegion (this->Xdisplay, NULL, 0);

    XFixesSetWindowShapeRegion (this->Xdisplay, this->window_handle, ShapeBounding, 0, 0, 0);
    XFixesSetWindowShapeRegion (this->Xdisplay, this->window_handle, ShapeInput, 0, 0, region);

    XFixesDestroyRegion (this->Xdisplay, region);

    if( !window_handle ) {
        printf("Couldn't create the window\n");
    }

    this->glX_window_handle = this->window_handle;

    textprop.value = (unsigned char*)title;
    textprop.encoding = XA_STRING;
    textprop.format = 8;
    textprop.nitems = strlen(title);

    hints.x = x;
    hints.y = y;
    hints.width = this->width;
    hints.height = this->height;
    hints.flags = USPosition|USSize;

    startup_state = XAllocWMHints();
    startup_state->initial_state = NormalState;
    startup_state->flags = StateHint;

    XSetWMProperties(this->Xdisplay, this->window_handle,&textprop, &textprop,
                     NULL, 0,
                     &hints,
                     startup_state,
                     NULL);


    XFree(startup_state);

    XMapWindow(this->Xdisplay, this->window_handle);
    XIfEvent(this->Xdisplay, &event, WaitForMapNotify, (char*)&this->window_handle);

    if ((this->del_atom = XInternAtom(this->Xdisplay, "WM_DELETE_WINDOW", 0)) != None) {
        XSetWMProtocols(this->Xdisplay, this->window_handle, &this->del_atom, 1);
    }
    Atom del_atom1;
    if ((del_atom1 = XInternAtom(this->Xdisplay, "NET_WM_STATE_ABOVE", 0)) != None) {
        XSetWMProtocols(this->Xdisplay, this->window_handle, &del_atom1, 1);
    }
}
void mrmCursor::createTheRenderContext()
{
#if 1
    int dummy;
    if (!glXQueryExtension(this->Xdisplay, &dummy, &dummy)) {
        printf("OpenGL not supported by X server\n");
    }

    {
        this->render_context = glXCreateNewContext(this->Xdisplay, this->fbconfig, GLX_RGBA_TYPE, 0, True);
        if (!this->render_context) {
            printf("Failed to create a GL context\n");
        }
    }

    if (!glXMakeContextCurrent(this->Xdisplay, this->glX_window_handle, this->glX_window_handle, this->render_context)) {
        printf("glXMakeCurrent failed for window\n");
    }
#else
    glewExperimental=true; // Needed in core profile
    if (int ret = glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW %s\n",glewGetErrorString(ret));
        return;
    }
#endif

}

int mrmCursor::updateTheMessageQueue()
{
    XEvent event;
    XConfigureEvent *xc;

    while (XPending(this->Xdisplay))
    {
        XNextEvent(this->Xdisplay, &event);
        switch (event.type)
        {
            case ClientMessage:
                if (event.xclient.data.l[0] == this->del_atom)
                {
                    return 0;
                }
                break;

            case ConfigureNotify:
                xc = &(event.xconfigure);
                this->width = xc->width;
                this->height = xc->height;
                break;
        }
    }
    return 1;
};

void mrmCursor::redrawTheWindow() {
    //
    XWindowAttributes winattr;

    XGetWindowAttributes(this->Xdisplay, this->glX_window_handle, &winattr);
    glViewport(0, 0, winattr.width, winattr.height);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f((1.0f/255)*this->color_r, (1.0f/255)*this->color_g, (1.0f/255)*this->color_b);

    glBegin(GL_TRIANGLES);

    glVertex3f(-1.0f,-1.0f,0.0f);
    glVertex3f(1.0f,1.0f,0.0f);
    glVertex3f(-1.0f,1.0f,0.0f);

    glEnd();

    glXSwapBuffers(this->Xdisplay, this->glX_window_handle);

    XMoveWindow(this->Xdisplay, this->glX_window_handle, this->posx, this->posy);
}

int mrmCursor::getPosx() const {
    return posx;
}

void mrmCursor::setPosx(int posx) {
    mrmCursor::posx = posx;
}

int mrmCursor::getPosy() const {
    return posy;
}

void mrmCursor::setPosy(int posy) {
    mrmCursor::posy = posy;
}

int mrmCursor::getXMax() {
    return DisplayWidth(this->Xdisplay, DefaultScreen(this->Xdisplay));
}

int mrmCursor::getYMax() {
    return DisplayHeight(this->Xdisplay, DefaultScreen(this->Xdisplay));
}

void mrmCursor::setlastabsx(int newabs){
    int tempabs = this->lastabsx;
    if(tempabs==0){
        tempabs = this->lastabsx-1;
    }
    this->relx = tempabs - newabs;
    this->lastabsx = newabs;
}

void mrmCursor::setlastabsy(int newabs){
    int tempabs = this->lastabsy;
    if(tempabs==0){
        tempabs = this->lastabsy-1;
    }
    this->rely = tempabs - newabs;
    this->lastabsy = newabs;
}

int mrmCursor::getrelxfromabs() {
    return this->relx;
}

int mrmCursor::getrelyfromabs() {
    return this->rely;
}

Display *mrmCursor::getDisplay() {
    return this->Xdisplay;
}