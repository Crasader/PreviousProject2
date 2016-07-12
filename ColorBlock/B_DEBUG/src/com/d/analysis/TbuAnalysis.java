package com.d.analysis;

import android.content.Context;

import com.t.h.domain.gamemark.HttpManage;
import com.tbu.androidtools.TbuAndroidTools;

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
