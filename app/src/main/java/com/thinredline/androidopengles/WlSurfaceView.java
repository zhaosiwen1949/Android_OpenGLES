package com.thinredline.androidopengles;

import android.content.Context;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

public class WlSurfaceView extends SurfaceView implements SurfaceHolder.Callback {
    private final NativeOpenGL nativeOpenGL = new NativeOpenGL();

    WlSurfaceView(Context context) {
        super(context);
        getHolder().addCallback(this);
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder surfaceHolder) {
        nativeOpenGL.surfaceCreate(surfaceHolder.getSurface());
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder surfaceHolder, int format, int width, int height) {
        nativeOpenGL.surfaceChange(width, height);
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder surfaceHolder) {

    }
}
