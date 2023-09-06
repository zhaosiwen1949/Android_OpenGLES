#include <jni.h>
#include <string>
#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"

#include "log/WlAndroidLog.h"
#include "egl/WlEglThread.h"

static ANativeWindow *_nativeWindow = nullptr;
static WlEglThread *_eglThread = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_thinredline_androidopengles_NativeOpenGL_surfaceCreate(JNIEnv *env, jobject thiz, jobject surface) {
    _nativeWindow = ANativeWindow_fromSurface(env, surface);

    _eglThread = new WlEglThread();
    _eglThread->onSurfaceCreated(_nativeWindow);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_thinredline_androidopengles_NativeOpenGL_surfaceChange(JNIEnv *env, jobject thiz,
                                                                jint width, jint height) {
    if(_eglThread != nullptr)
    {
        _eglThread->onSurfaceChanged(width, height);
    }
}