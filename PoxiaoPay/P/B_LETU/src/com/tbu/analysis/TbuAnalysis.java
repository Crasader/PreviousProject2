package com.tbu.analysis;

import android.content.Context;

import com.tbu.androidtools.TbuAndroidTools;
import com.tbu.http.domain.gamemark.HttpManage;

public class TbuAnalysis {
	public static void uploadAnalysis(final Context context,
			final String event, final String eventExtend,
			final String sessionTime, String markVersion) {
		HttpManage.uploadData(
				String.valueOf(TbuAndroidTools.getEventPointVersion(context))
						+ String.valueOf(TbuAndroidTools
								.getPPointVersion(context)), event,
				eventExtend, sessionTime, markVersion);

	}
}
