package com.t.p.view;

import java.io.IOException;
import java.io.InputStream;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.tbu.androidtools.util.ReadJsonUtil;

public class PLayoutUtil {
	private static int pUiLayoutResId = 0;

	public static int getPUiLayoutResId() {
		return pUiLayoutResId;
	}

	public static void setPUiLayoutResId(int pUiLayoutResId) {
		PLayoutUtil.pUiLayoutResId = pUiLayoutResId;
	}
	
	

}
