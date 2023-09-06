//
// Created by DELL on 2023-09-06.
//

#ifndef ANDROID_OPENGLES_WLEGLTHREAD_H
#define ANDROID_OPENGLES_WLEGLTHREAD_H

#include <EGL/egl.h>
#include "pthread.h"
#include "android/native_window.h"

#include "WlEglHelper.h"

class WlEglThread {

public:
    pthread_t eglThread = -1;
    ANativeWindow *nativeWindow = NULL;
    WlEglHelper *wlEglHelper = NULL;

    bool isCreate = false;
    bool isChange = false;
    bool isExit = false;
    bool isStart = false;

    int surfaceWidth = 0;
    int surfaceHeight = 0;

public:
    WlEglThread();
    ~WlEglThread();

    void onSurfaceCreated(EGLNativeWindowType window);
    void onSurfaceChanged(int width, int height);
    void draw();
};


#endif //ANDROID_OPENGLES_WLEGLTHREAD_H
