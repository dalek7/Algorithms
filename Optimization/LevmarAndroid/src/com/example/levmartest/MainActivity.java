package com.example.levmartest;

//Seung-Chan Kim
//Written at Starbucks Mangpo
//November 27, 2016
//
// Android implementation : see https://github.com/3deggi/levmar-ndk
// http://users.ics.forth.gr/~lourakis/levmar/
// Test environment 
//  - OS X Mavericks
//  - Android 5.0.1
//  - NDK : android-ndk-r10e


import com.example.levmartest.R;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends ActionBarActivity {
	private static final String TAG = "NDK_STARBUCKS";
	private Button m_btn_1;
	HelloJni levmar1;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
               
        levmar1 = new HelloJni();
        m_btn_1 = (Button) findViewById(R.id.button1);
        m_btn_1.setOnClickListener(new OnClickListener() {
    		@Override
    		public void onClick(View v) {
    			Button b = (Button) v;
    			Log.i(TAG, "clicked");
    			//ProcUDP.sendUDPMessage("143.248.51.42", 12345, "m_btn_update");
    			levmar1.test(40);
    		}
    		});
        
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
