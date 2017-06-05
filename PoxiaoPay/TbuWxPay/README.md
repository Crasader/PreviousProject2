破晓微信支付插件

===========
发布时间：2016-03-22

配置说明
    1.jar包括：tbu_wx.jar和libammsdk.jar
    2.AndroidManifest.xml配置 
        <activity
            android:name=".wxapi.WXPayEntryActivity"
            android:exported="true"
            android:launchMode="singleTop" />

        <receiver
            android:name=".AppRegister"
            android:permission="com.tencent.mm.plugin.permission.SEND" >
            <intent-filter>
                <action android:name="com.tencent.mm.plugin.openapi.Intent.ACTION_REFRESH_WXAPP" />
            </intent-filter>
        </receiver>
    3json文件。需要配置商户ID和APPID。wexininfo.json的内容{"appId":"wx884476f603eeb8be","partnerId":"1318535301"}配置好后需要加密。并且放到主工程的assets/json/wx

调用说明
    1.初始化:在第一个Activity调用TbuWxPay.getInstance().initOnFirstActivity(Activity activity)
    2.启动支付TbuWxPay.getInstance().Pay(final String orderId, final String tbuId,final String productId, final String productName, final String price)
    3.支付回调。在主工程下新建一个包。包名必须是xxx.xxx.xxx.wxapi。xxx.xxx.xxx是在微信申请的包名。将TbuWxPay工程下的wxactivity目录下的WXPayEntryActivity.java拷贝到该包下。
      在WXPayEntryActivity类的onResp方法中处理支付回调结果。
    4.关闭订单：TbuWxPay.getInstance().closeWxOrder(final String orderId),一般情况下可以不调用。如需要,如果订单在5分钟后还未完成，可以调用
    5.支付结果查询：queryOrder(final String orderId, final QueryCallBack callBack)。一般情况下可以不调用。若需要调用者需要查询到的订单成功后才方法道具给用户。

测试说明
    1.需要打包签名后才可以进行支付测试。签名需要和申请的时候一致。