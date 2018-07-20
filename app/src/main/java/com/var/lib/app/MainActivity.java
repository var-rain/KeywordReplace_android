package com.var.lib.app;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.var.lib.keywords.Keywords;

public class MainActivity extends AppCompatActivity {

    private EditText text;
    private TextView show;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        requestPermission();

        text = findViewById(R.id.match_input);
        Button start = findViewById(R.id.start_but);
        show = findViewById(R.id.target_text);

        start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String str = text.getText().toString();
                if (str.length() != 0) {
                    show.setText(Keywords.replaceKeywords(str, '*'));
                }
            }
        });
    }

    @SuppressLint("SdCardPath")
    private void requestPermission() {
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.JELLY_BEAN) {
            int selfPermission = ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE);
            if (selfPermission == PackageManager.PERMISSION_DENIED) {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 999);
            } else {
                Keywords.loadDict("/sdcard/dict.txt");
            }
        }
    }

    @SuppressLint("SdCardPath")
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == 999) {
            if (permissions[0].equals(Manifest.permission.READ_EXTERNAL_STORAGE)) {
                if (grantResults[0] == PackageManager.PERMISSION_DENIED) {
                    Toast.makeText(this, "权限不允许！", Toast.LENGTH_SHORT).show();
                } else {
                    Keywords.loadDict("/sdcard/dict.txt");
                }
            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Keywords.destroy();
    }
}
