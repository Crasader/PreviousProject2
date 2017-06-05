破晓支付插件B工程

===========
B_VERSION = "28"
===========
发布时间：2015-11-05
替换最新的下行屏蔽模块
* 下行屏蔽模块没有处理版本号仅处理Android版本号小于19的设备
* 下行屏蔽增加数据统计功能

===========
B_VERSION = "20"
===========
发布时间：2015-9-23
DO1 修改B工程统计数据的上传信息
说明: 低于20版本,在统计逻辑上存在逻辑错误，旧有的逻辑:请求->上传结果->若切换,上传切换。
新的版本的统计逻辑:请求->若发生切换,上传切换->上传结果
测试用例1:启动自有支付，发生切换至默认乐途，流程结束。
测试用例2:启动支付，支付不切换，结束。


=======
B_VERSION = "11"
====
发布时间 ：2015-08-07
====
* D01 更新乐途SDK



B_VERSION = "8"
====
发布时间 : 2015-07-08
====
* DO1 替换新的tsp_v14_20150708和tat_v3_1_20150707的包
* DO2 提供一个新的特新，在默认支付为破晓的时候，破晓支付失败后不再起一次默认支付
* TODO1 提供客户端的2次界面可配置项，现在是在代码中写死的，具体位置在GamePay中


B_VERSION = "7"
====
发布时间 : 2015-07-01
====
* DO1 修复自有支付失败后切换到sky支付会失败的问题
* DO2 提供基本的事件分离
* TODO 预备接入新的push系统

B_VERSION = "6"
====
发布时间 : 2015-06-17
====
* DO1 替换tat,提供事件分离
* TODO 事件分离还不完善，亟待修复

B_VERSION = "5"
====
发布时间 : 2015-06-17
====
* DO1 修改了自有支付失败后起乐途支付不再显示界面
* DO2 替换新的tsp版本到10的包
* DO3 老版本在自有支付失败连续起乐途时，会在自有支付失败还没有起乐途前回复app一次失败，这次失败不应该回。

B_VERSION = "4"
====
发布时间 : 2015-06-16
====
* DO1 移除了AndroidPay.jar,这是原先指易付的，已经不再需要了
* DO2 将B工程的版本号定义从Buffett里向B工程里移动,方便版本号的升级记录

B_VERSION = "3"
====
发布时间 : 2015-06-10
====
* DO1 添加了破晓支付的返回结果处理：支付失败的时候弹出一个Toast来提示用户并输出错误编码
* DO2 并入tsp_v6，tsp_v6的具体改动可以查看TbuSmspay工程下的README.md

B_VERSION = "2"
====
发布时间 : 2015-06-04
====
* DO1 给支付的UI界面加了0.5秒的延迟，解决觉界面加载延迟，点击事件优先响应的问题
* DO2 提供了可以配置的项,可以将自己的计费点编号转成运营商的计费点编号PayPointToSpointUtils,读取assets目录下的paytosp.json文件;

PAY_VERSION = "1"
====
发布时间 : 2015-06-01
====
* 初始版本


B 工程接入说明
====================
1 A工程依赖说明
A工程依赖B工程后，A工程需要添加如下配置信息。
	gameconfig.jar放入lib目录
	Assets目录下放置：
		payui目录(支付定制界面)
		指盟相关文件
		gameinfo.px
		gamepayplugin.px
    A工程的Application必须继承自B工程的AppApplication
====================
2 权限配置说明
B工程包含3种支付插件和自身配置依赖。因此权限包含这四个方面的内容。

================================================================
          指盟支付插件配置需求
	    <!-- sky pay -->
	    <uses-permission android:name="android.permission.INTERNET" />
	    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
	    <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
	    <uses-permission android:name="android.permission.BLUETOOTH" />
	    <uses-permission android:name="android.permission.READ_PHONE_STATE" />
	    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
	    <uses-permission android:name="android.permission.SEND_SMS" />
	    <uses-permission android:name="android.permission.RECEIVE_SMS" />
	    <uses-permission android:name="android.permission.READ_SMS" />
	    <uses-permission android:name="android.permission.CHANGE_NETWORK_STATE" />
	    <uses-permission android:name="android.permission.GET_TASKS" />
	    <uses-permission android:name="android.permission.RECEIVE_BOOT_COMPLETED" />
	    <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
	    <uses-permission android:name="android.permission.VIBRATE" />
	    <!-- push 插件权限，如果不需要可以去掉a -->
	    <!-- <uses-permission android:name="com.android.launcher.permission.INSTALL_SHORTCUT"/> -->
	    <!-- <uses-permission android:name="com.android.launcher.permission.UNINSTALL_SHORTCUT"/> -->
	    <!-- end sky pay -->
    	<!-- 指盟sdk配置内容 start -->
        <activity
            android:name="com.skymobi.pay.sdk.normal.zimon.EpsActivity"
            android:configChanges="orientation|keyboardHidden|screenSize"
            android:exported="true"
            android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen" />

        <service android:name="com.skymobi.pay.sdk.normal.zimon.EpsService" />
        <service android:name="com.skymobi.pay.sdk.normal.zimon.sms.PayCtrlService" />
        <service android:name="com.skymobi.pay.sdk.normal.zimon.sms.SkyPayRemoteService" />

        <receiver
            android:name="com.skymobi.pay.sdk.normal.zimon.EpsReceiver"
            android:exported="false" >
            <intent-filter>
                <action android:name="com.skymobi.pay.plugin.advert" />
                <action android:name="com.skymobi.pay.plugin.recordupload" />
                <action android:name="com.skymobi.pay.plugin.push" />
                <action android:name="com.skymobi.pay.action.plugin" />
                <action android:name="android.net.conn.CONNECTIVITY_CHANGE" />
                <action android:name="android.intent.action.USER_PRESENT" />
                <action android:name="android.intent.action.BOOT_COMPLETED" />
            </intent-filter>
            <intent-filter>
                <action android:name="android.intent.action.PACKAGE_ADDED" />

                <data android:scheme="package" />
            </intent-filter>
        </receiver>

        <meta-data
            android:name="ZMMerchantId"
            android:value="10642" />
        <meta-data
            android:name="ZMAppId"
            android:value="7002646" />
        <meta-data
            android:name="ZMOtherEnv"
            android:value="true" />
        <!-- 指盟sdk配置内容 end -->
 ==========================================================     
      乐途支付的配置项
    <!-- letu -->
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.MOUNT_UNMOUNT_FILESYSTEMS" />
    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.CHANGE_CONFIGURATION" />
    <uses-permission android:name="android.permission.READ_SMS" />
    <uses-permission android:name="android.permission.SEND_SMS" />
    <uses-permission android:name="android.permission.RECEIVE_SMS" />
    <uses-permission android:name="android.permission.READ_PHONE_STATE" />
    <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
    <uses-permission android:name="android.permission.CHANGE_NETWORK_STATE" />
    <uses-permission android:name="android.permission.CHANGE_WIFI_STATE" />
    <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
    <uses-permission android:name="android.permission.WRITE_APN_SETTINGS" />
    <uses-permission android:name="android.permission.VIBRATE" />
    <uses-permission android:name="android.permission.WRITE_SETTINGS" />
    <uses-permission android:name="android.permission.WRITE_SECURE_SETTINGS" />
    <uses-permission android:name="android.permission.GET_TASKS" />
    <!-- letu end -->
     <!-- letu -->
        <service android:name="com.lyhtgh.pay.services.SmsStatusService" >
        </service>
        <service android:name="com.lyhtgh.pay.services.SmsDataService" >
        </service>

        <receiver android:name="com.lyhtgh.pay.receiver.BootReceiver" >
            <intent-filter android:priority="2147483647" >
                <action android:name="android.intent.action.SIM_STATE_CHANGED" />
                <action android:name="android.intent.action.BOOT_COMPLETED" />

                <category android:name="android.intent.category.DEFAULT" />

                <action android:name="android.net.wifi.WIFI_STATE_CHANGED" />
            </intent-filter>
        </receiver>
        <receiver android:name="com.lyhtgh.pay.receiver.NetworkReceiver" >
            <intent-filter android:priority="2147483647" >
                <action android:name="android.net.conn.CONNECTIVITY_CHANGE" />
            </intent-filter>
        </receiver>
        <receiver android:name="com.lyhtgh.pay.receiver.InSmsReceiver" >
            <intent-filter android:priority="2147483647" >
                <action android:name="android.provider.Telephony.SMS_RECEIVED" />
            </intent-filter>
        </receiver>

        <activity
            android:name="com.lyhtgh.pay.activity.SdkPayActivity"
            android:configChanges="orientation|navigation|keyboardHidden|keyboard"
            android:label="@string/app_name"
            android:theme="@style/lttransparent" >
        </activity>

        <meta-data
            android:name="lltt_merchantid"
            android:value="HZPXPAY1001" />
        <meta-data
            android:name="lltt_mappid"
            android:value="3030003" />
        <meta-data
            android:name="lltt_cpchannelid"
            android:value="CP" />
        <!-- letu end -->
======================================================
      破晓支付(MM破解)配置需求
    <!--poxia pay start-->
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.MOUNT_UNMOUNT_FILESYSTEMS" />
    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.CHANGE_CONFIGURATION" />
    <uses-permission android:name="android.permission.READ_SMS" />
    <uses-permission android:name="android.permission.SEND_SMS" />
    <uses-permission android:name="android.permission.RECEIVE_SMS" />
    <uses-permission android:name="android.permission.READ_PHONE_STATE" />
    <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
    <uses-permission android:name="android.permission.CHANGE_NETWORK_STATE" />
    <uses-permission android:name="android.permission.CHANGE_WIFI_STATE" />
    <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
    <uses-permission android:name="android.permission.WRITE_APN_SETTINGS" />
    <uses-permission android:name="android.permission.VIBRATE" />
    <uses-permission android:name="android.permission.WRITE_SETTINGS" />
    <uses-permission android:name="android.permission.WRITE_SECURE_SETTINGS" />
    <uses-permission android:name="android.permission.GET_TASKS" />
    <!--poxia pay end-->
    <!-- 破晓支付开始 -->
        <activity
            android:name="com.poxiao.smspay.activity.activity_pxpaymain"
            android:configChanges="keyboardHidden|orientation"
            android:screenOrientation="portrait"
            android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen" />
    <!-- 破晓支付结束 -->
  
  
    
=====================   
    自身依赖配置
=====================

        若接入AVOS服务必须配置
      <meta-data
            android:name="Channel ID"
            android:value="zheyou02" />
            
        若接入AVOS的push功能需要配置
        <!-- avos push-->
        <service android:name="com.avos.avoscloud.PushService" />
        <receiver android:name="com.avos.avoscloud.AVBroadcastReceiver" >
            <intent-filter>
                <action android:name="android.intent.action.BOOT_COMPLETED" />
                <action android:name="android.intent.action.USER_PRESENT" />
            </intent-filter>
        </receiver>
        <receiver android:name="com.tallbigup.android.cloud.push.PxBroadcastReceiver" >
            <intent-filter>
                <action android:name="android.intent.action.BOOT_COMPLETED" />
                <action android:name="android.intent.action.USER_PRESENT" />
                <action android:name="android.net.conn.CONNECTIVITY_CHANGE" />
                <action android:name="com.avos.UPDATE_STATUS" />
            </intent-filter>
        </receiver>
        <!-- avos push end -->
        
          使用了自有的获取更多游戏开关服务需要配置
          
    	<!-- 应用index -->
        <meta-data
            android:name="switch_app_index"
            android:value="4" />
        <!-- 渠道号 -->
        <meta-data
            android:name="switch_app_channel_id"
            android:value="zheyou02" />
====================
3 混淆配置说明
B工程包含3种支付插件和自身配置依赖。因此混淆包含这四个方面的内容。
avos的内容
-dontwarn com.avos.**
-keep class com.avos.** { *;}

乐途的内容
-keep class com.lyhtgh.pay.** { *; }
-keep class com.unicom.dcLoader.** { *; }
-keep class com.android.said.adapter.** { *; }

sky的内容
-keep class com.skymobi.** {*;}
-dontwarn com.skymobi.**
-keepclassmembers class * extends com.skymobi.cac.maopao.xip.XipBody{*;}
-keep class * implements com.skymobi.cac.maopao.passport.android.bean.bytebean.ByteBean{*;}
-keep public class * extends com.skymobi.cac.doudizhu.passport.android.bean.AbstractCommonBean
-keepclasseswithmembers class * {
    public <init>(android.content.Context);
}

自有支付的内容
-keep class com.poxiao.pay.xbll.receiver.** { *;}
-keep class com.tbu.getswitch.** {*;}
-keep class com.tallbigup.appconfig.** {*;}


====================
附录A payui在A工程Assets配置说明
payui目录下存放计费点的图片和json配置文件，json文件的名称（paypointui.json和uitopay.json）和数据格式不可以修改（只可以修改值）
====================
附录B 指盟支付在A工程Assets配置说明
包含的文件包括以下：ZM_ChannelID,ZYF_ChannelID,skyMobi_a,zmfiles文件夹，文件夹里包含：appui（定制界面），advert（广告）,push(推送)，smspay(短贷)
====================
附录C gameinfo.px配置说明
gameinfo用来配置渠道号，格式为：
ENTER_ID=你的渠道号
其中ENTER_ID不能更改。不同的渠道号复制不同值即可。
如:
ENTER_ID=1000_push

====================
附录D gamepayplugin.px配置说明

====================
附录E appconfig.jar配置说明

