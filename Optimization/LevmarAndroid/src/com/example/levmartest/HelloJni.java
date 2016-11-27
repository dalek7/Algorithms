package com.example.levmartest;
import android.util.Log;
// Seung-Chan Kim
// Written at Starbucks Mangpo
// November 27, 2016
//
// Android implementation : see https://github.com/3deggi/levmar-ndk
// http://users.ics.forth.gr/~lourakis/levmar/
// Test environment 
//  - OS X Mavericks
//  - Android 5.0.1
//  - NDK : android-ndk-r10e

//
// javah -classpath . -jni com.example.levmartest.HelloJni


public class HelloJni {

	private static final String  TAG  = "NDK_TEST";
	 
	private static final String LIB_NAME = "levmarjni";
	public native void test(int nSample);
	
	static{
		
		System.loadLibrary( LIB_NAME );
		Log.i(TAG, "NDK loaded successfully");

	}

}
