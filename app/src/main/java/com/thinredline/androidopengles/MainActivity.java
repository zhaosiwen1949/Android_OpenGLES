package com.thinredline.androidopengles;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.thinredline.androidopengles.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        WlSurfaceView wlSurfaceView = new WlSurfaceView(getApplicationContext());
        setContentView(wlSurfaceView);
    }
}