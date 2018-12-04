//
// Created by root on 11/16/18.
//

#include <X11/Xlib.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>
#include "../inc/mmCursor.h"

int mmCursor::VisData[] = {
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

void mmCursor::allow_input_passthrough (Window w)
{
    XserverRegion region = XFixesCreateRegion (this->Xdisplay, NULL, 0);

    XFixesSetWindowShapeRegion (this->Xdisplay, w, ShapeBounding, 0, 0, 0);
    XFixesSetWindowShapeRegion (this->Xdisplay, w, ShapeInput, 0, 0, region);

    XFixesDestroyRegion (this->Xdisplay, region);
}

mmCursor::mmCursor() {

    // create the window

    XEvent event;
    int x, y, attr_mask;
    XSizeHints hints;
    XWMHints *startup_state;
    XTextProperty textprop;
    XSetWindowAttributes attr = {0,};

    this->Xdisplay = XOpenDisplay(NULL);
    if (!this->Xdisplay) {
        printf("Couldn't connect to X server\r\n");
        return;
    }
    this->Xscreen = DefaultScreen(this->Xdisplay);
    this->Xroot = RootWindow(this->Xdisplay, this->Xscreen);

    this->fbconfigs = glXChooseFBConfig(this->Xdisplay, this->Xscreen, this->VisData, &this->numfbconfigs);
    this->fbconfig = 0;
    for (int i = 0; i < this->numfbconfigs; i++) {
        this->visual = glXGetVisualFromFBConfig(this->Xdisplay, this->fbconfigs[i]);
        if (!this->visual)
            continue;

        this->pict_format = XRenderFindVisualFormat(this->Xdisplay, this->visual->visual);
        if (!this->pict_format)
            continue;

        this->fbconfig = this->fbconfigs[i];
        if (this->pict_format->direct.alphaMask > 0) {
            break;
        }
    }

    if (!fbconfig) {
        printf("No matching FB config found\r\n");
        return;
    }

    this->describe_fbconfig(fbconfig);

    /* Create a colormap - only needed on some X clients, eg. IRIX */
    this->cmap = XCreateColormap(this->Xdisplay, this->Xroot, visual->visual, AllocNone);

    attr.colormap = cmap;
    attr.background_pixmap = None;
    attr.border_pixmap = None;
    attr.border_pixel = 1;
    attr.event_mask = StructureNotifyMask |
            EnterWindowMask |
            LeaveWindowMask |
            ExposureMask |
            ButtonPressMask |
            ButtonReleaseMask |
            OwnerGrabButtonMask |
            KeyPressMask |
            KeyReleaseMask;

    attr_mask =
            //	CWBackPixmap|
            CWOverrideRedirect |
            CWColormap |
            CWBorderPixel |
            CWEventMask;
    attr.override_redirect = True;

    this->width = DisplayWidth(this->Xdisplay, DefaultScreen(this->Xdisplay)) / 2;
    this->height = DisplayHeight(this->Xdisplay, DefaultScreen(this->Xdisplay)) / 2;
    x = this->width / 2, y = this->height / 2;

    this->window_handle = XCreateWindow(Xdisplay,
                                        Xroot,
                                        x, y, this->width, this->height,
                                        0,
                                        visual->depth,
                                        InputOutput,
                                        visual->visual,
                                        attr_mask, &attr);

    this->allow_input_passthrough (this->window_handle);

    if (!this->window_handle) {
        printf("Couldn't create the window\r\n");
        return;
    }

#if USE_GLX_CREATE_WINDOW
    fputs("glXCreateWindow ", stderr);
    int glXattr[] = { None };
    glX_window_handle = glXCreateWindow(Xdisplay, fbconfig, window_handle, glXattr);
    if( !glX_window_handle ) {
        fatalError("Couldn't create the GLX window\n");
    }
#else
    this->glX_window_handle = this->window_handle;
#endif

    textprop.value = (unsigned char *) "title";
    textprop.encoding = XA_STRING;
    textprop.format = 8;
    textprop.nitems = strlen("title");

    hints.x = x;
    hints.y = y;
    hints.width = width;
    hints.height = height;
    hints.flags = USPosition | USSize;

    startup_state = XAllocWMHints();
    startup_state->initial_state = NormalState;
    startup_state->flags = StateHint;

    XSetWMProperties(this->Xdisplay, this->window_handle, &textprop, &textprop,
                     NULL, 0,
                     &hints,
                     startup_state,
                     NULL);

    XFree(startup_state);

    XMapWindow(this->Xdisplay, this->window_handle);
    XIfEvent(this->Xdisplay, &event, this->WaitForMapNotify, (char *) &this->window_handle);

    if ((this->del_atom = XInternAtom(this->Xdisplay, "WM_DELETE_WINDOW", 0)) != None) {
        XSetWMProtocols(this->Xdisplay, this->window_handle, &this->del_atom, 1);
    }

    // create the render object

    int dummy;
    if (!glXQueryExtension(Xdisplay, &dummy, &dummy)) {
        printf("OpenGL not supported by X server\r\n");
        return;
    }
/*
#if USE_GLX_CREATE_CONTEXT_ATTRIB
        #define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
	#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
	render_context = NULL;
	if( isExtensionSupported( glXQueryExtensionsString(Xdisplay, DefaultScreen(Xdisplay)), "GLX_ARB_create_context" ) ) {
		typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
		if( glXCreateContextAttribsARB ) {
			int context_attribs[] =
			{
				GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
				GLX_CONTEXT_MINOR_VERSION_ARB, 0,
				//GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				None
			};

			int (*oldHandler)(Display*, XErrorEvent*) = XSetErrorHandler(&ctxErrorHandler);

			render_context = glXCreateContextAttribsARB( Xdisplay, fbconfig, 0, True, context_attribs );

			XSync( Xdisplay, False );
			XSetErrorHandler( oldHandler );

			fputs("glXCreateContextAttribsARB failed", stderr);
		} else {
			fputs("glXCreateContextAttribsARB could not be retrieved", stderr);
		}
	} else {
			fputs("glXCreateContextAttribsARB not supported", stderr);
	}

#else
    if(!render_context)
    {
        {
#endif
            render_context = glXCreateNewContext(Xdisplay, fbconfig, GLX_RGBA_TYPE, 0, True);
            if (!render_context) {
                fatalError("Failed to create a GL context\n");
            }
        }

        if (!glXMakeContextCurrent(Xdisplay, glX_window_handle, glX_window_handle, render_context)) {
            fatalError("glXMakeCurrent failed for window\n");
        }
    }*/
};

Bool mmCursor::WaitForMapNotify(Display *d, XEvent *e, char *arg)
{
    return d && e && arg && (e->type == MapNotify) && (e->xmap.window == *(Window*)arg);
}

void mmCursor::describe_fbconfig(GLXFBConfig fbconfig)
{
    int doublebuffer;
    int red_bits, green_bits, blue_bits, alpha_bits, depth_bits;

    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_DOUBLEBUFFER, &doublebuffer);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_RED_SIZE, &red_bits);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_GREEN_SIZE, &green_bits);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_BLUE_SIZE, &blue_bits);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_ALPHA_SIZE, &alpha_bits);
    glXGetFBConfigAttrib(this->Xdisplay, fbconfig, GLX_DEPTH_SIZE, &depth_bits);

    printf("FBConfig selected:\r\nDoublebuffer: %s\r\n"
                    "Red Bits: %d, Green Bits: %d, Blue Bits: %d, Alpha Bits: %d, Depth Bits: %d\n",
            doublebuffer == True ? "Yes" : "No",
            red_bits, green_bits, blue_bits, alpha_bits, depth_bits);
}