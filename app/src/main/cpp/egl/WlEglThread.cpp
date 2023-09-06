//
// Created by DELL on 2023-09-06.
//

#include "GLES2/gl2.h"
#include "WlAndroidLog.h"
#include "WlEglThread.h"

static const char* TAG = "WlEglThread";

WlEglThread::WlEglThread() {

}

WlEglThread::~WlEglThread() {

}

static void* _eglThreadImpl(void* context)
{
    WlEglThread* thread = (WlEglThread*)context;

    if(thread != nullptr)
    {
        thread->wlEglHelper->initEgl(thread->nativeWindow);
        thread->isExit = false;

        while(true)
        {
            if(thread->isCreate)
            {
                LOGD(TAG, "eglThread call surfaceCreated")
                thread->isCreate = false;
            }

            if(thread->isChange)
            {
                LOGD(TAG, "eglThread call surfaceChanged")
                thread->isChange = false;
                thread->isStart = true;
                glViewport(0, 0, thread->surfaceWidth, thread->surfaceHeight);
            }

            if(thread->isStart)
            {
                thread->draw();
            }

            if(thread->isExit)
            {
                LOGD(TAG, "eglThread call exit")
                thread->isExit = false;
                break;
            }
        }
    }

    return nullptr;
}

void WlEglThread::onSurfaceCreated(EGLNativeWindowType window) {
    if(eglThread == -1)
    {
        isCreate = true;
        nativeWindow = window;
        wlEglHelper = new WlEglHelper();

        pthread_create(&eglThread, nullptr, _eglThreadImpl,this);
    }
}

void WlEglThread::onSurfaceChanged(int width, int height) {
    isChange = true;
    surfaceWidth = width;
    surfaceHeight = height;
}

void WlEglThread::draw() {
//    LOGD(TAG, "eglThread call draw")

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    wlEglHelper->swapBuffers();
}
