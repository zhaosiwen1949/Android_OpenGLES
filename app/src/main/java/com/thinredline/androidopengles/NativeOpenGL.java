package com.thinredline.androidopengles;

import android.view.Surface;

public class NativeOpenGL {
    // Used to load the 'androidopengles' library on application startup.
    static {
        System.loadLibrary("androidopengles");
    }

    native void surfaceCreate(Surface surface);

    native void surfaceChange(int width, int height);
}
