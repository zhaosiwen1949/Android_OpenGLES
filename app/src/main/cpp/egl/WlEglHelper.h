//
// Created by DELL on 2023-09-05.
//

#ifndef ANDROID_OPENGLES_WLEGLHELPER_H
#define ANDROID_OPENGLES_WLEGLHELPER_H

#include "EGL/egl.h"

class WlEglHelper {
private:
    EGLDisplay mEglDisplay;
    EGLConfig mEglConfig;
    EGLSurface mEglSurface;
    EGLContext mEglContext;


public:
    WlEglHelper();
    ~WlEglHelper();

    int initEgl(EGLNativeWindowType window);
    int swapBuffers();
    int destroyEgl();
};


#endif //ANDROID_OPENGLES_WLEGLHELPER_H
