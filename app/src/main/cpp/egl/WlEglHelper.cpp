//
// Created by DELL on 2023-09-05.
//

#include "WlAndroidLog.h"

#include "WlEglHelper.h"

static const char* TAG = "WlEglHelper";

WlEglHelper::WlEglHelper() {
    mEglDisplay = EGL_NO_DISPLAY;
    mEglConfig = NULL;
    mEglSurface = EGL_NO_SURFACE;
    mEglContext = EGL_NO_CONTEXT;
}

int WlEglHelper::initEgl(EGLNativeWindowType window) {
    // 1、获取 EGLDisplay
    mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(mEglDisplay == EGL_NO_DISPLAY)
    {
        LOGE(TAG, "EglDisplay getting failed!")
        return -1;
    }

    // 2、初始化 EGLDisplay
    EGLint version[2] = {0};
    if(!eglInitialize(mEglDisplay, &version[0], &version[1]))
    {
        LOGE(TAG, "EglDisplay initializing failed!")
        return -1;
    }
    LOGD(TAG, "EglDisplay initializing success! Major Version: %d, Minor Version: %d", version[0], version[1])

    // 3、获取 EGLConfig
    const EGLint displayAttribs[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLint num_config;
    if(!eglChooseConfig(mEglDisplay, displayAttribs, NULL, 0, &num_config))
    {
        LOGE(TAG, "egl choose config failed!")
        return -1;
    }
    LOGD(TAG, "Egl has %d config", num_config)

    if(!eglChooseConfig(mEglDisplay, displayAttribs, &mEglConfig, 1, NULL))
    {
        LOGE(TAG, "egl get config failed!")
        return -1;
    }

    // 4、创建 EGLContext
    const EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, contextAttribs);
    if(mEglContext == EGL_NO_CONTEXT)
    {
        LOGE(TAG, "EGLContext creating failed!")
        return -1;
    }

    // 5、创建 EGLSurface
    mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, window, NULL);
    if(mEglSurface == EGL_NO_SURFACE)
    {
        LOGE(TAG, "EGLSurface creating failed!")
        return -1;
    }

    // 6、绑定上下文
    if(!eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext))
    {
        LOGE(TAG, "egl make current context failed!")
        return -1;
    }

    LOGD(TAG, "egl initialization success!")

    return 0;
}

int WlEglHelper::swapBuffers() {
    if(mEglDisplay != EGL_NO_DISPLAY && mEglSurface != EGL_NO_SURFACE)
    {
        if(eglSwapBuffers(mEglDisplay, mEglSurface))
        {
            LOGD(TAG, "egl swapBuffers success!")
            return 0;
        }
    }
    LOGE(TAG, "egl swapBuffers failed!")
    return -1;
}

int WlEglHelper::destroyEgl() {
    if(mEglDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }

    if(mEglDisplay != EGL_NO_DISPLAY && mEglSurface != EGL_NO_SURFACE)
    {
        eglDestroySurface(mEglDisplay, mEglSurface);
        mEglSurface = EGL_NO_SURFACE
    }

    if(mEglDisplay != EGL_NO_DISPLAY && mEglContext != EGL_NO_CONTEXT)
    {
        eglDestroyContext(mEglDisplay, mEglContext);
        mEglContext = EGL_NO_CONTEXT;
    }

    if(mEglDisplay != EGL_NO_DISPLAY)
    {
        eglTerminate(mEglDisplay);
        mEglDisplay = EGL_NO_DISPLAY;
    }

    return 0;
}
