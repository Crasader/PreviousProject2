package com.tbu.register;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.Button;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

public class TestActivity extends Activity {
	private Activity activity;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_test);
		activity=this;
		Button btnInsert = (Button) this.findViewById(R.id.Button01);
	    btnInsert.setOnClickListener(listener);
	    DeviceInfo.init(this);
	   
	    //dealRegisterQXT(activity.getApplicationContext());
	    Debug.e("Test UA="+getUA(activity.getApplicationContext()));
	}
	public static String getUA(Context context){
		WebView webview;
		webview = new WebView(context);
		webview.layout(0, 0, 0, 0);
		WebSettings settings = webview.getSettings();
		String ua = settings.getUserAgentString();
		return ua;
	}
	
	private String user_phone="";
	private String user_prov_id="";
	private void dealRegisterQXT(final Context context){
		//在注册请求中会判断是否需要去注册［有没有的问题，是否满足申请条件的问题］
		//疑问：传递的插件参数的作用是？？
		RegisterManager.getInstance().reqRigster(context, DeviceInfo.getsi(),
				RegisterAgreement.REGISTER_QXT_CODE, "imsi="+DeviceInfo.getsi()+"&pay_plugin=poxiao"
						,5, 1,new RegisterCallback(){
					@Override
					public void result(int code, String result) {
						if(code==RegisterAgreement.REGISTER_GET_USER_INFO_SUCCESS){
							//成功获取到用户注册信息
							if(result!=""){
								Log.i("TBU_DEBUG", "企信通成功获取到用户注册信息:"+result);
								String[] infos=result.toString().split(";");
								user_phone=infos[0];
								user_prov_id=infos[1];
							}else{
								Log.e("TBU_DEBUG", "企信通成功获取到用户注册信息:"+result);
								user_phone="";
							}
							
						}else if(code==RegisterAgreement.REGISTER_USER_REGISTERED){
							//用户已经注册过了
							//info :返回的注册信息 phone;provice;savetime								
							if(result!=""){
								Log.i("TBU_DEBUG", "企信通用户已经注册过了:"+result);
								String[] infos=result.toString().split(";");
								user_phone=infos[0];
								user_prov_id=infos[1];
							}else{
								Log.e("TBU_DEBUG", "企信通用户已经注册过了:"+result);
								user_phone="";
							}
							
						}else if(code==RegisterAgreement.GET_REGISTER_INFO_FAIL_1_AFTER_SMS){
							RegisterManager.getInstance().getUserRegisterInfo(context ,RegisterAgreement.REGISTER_QXT_CODE,
									DeviceInfo.getsi(),
									1*60,3,new RegisterCallback(){

										@Override
										public void result(int code, String result) {
											// TODO Auto-generated method stub
											if(code==RegisterAgreement.REGISTER_GET_USER_INFO_SUCCESS){
												//成功获取到用户注册信息
												if(result!=""){
													Log.i("TBU_DEBUG", "企信通成功获取到用户注册信息:"+result);
													String[] infos=result.toString().split(";");
													user_phone=infos[0];
													user_prov_id=infos[1];
												}else{
													Log.e("TBU_DEBUG", "企信通成功获取到用户注册信息:"+result);
													user_phone="";
												}
												
											}else if(code==RegisterAgreement.REGISTER_USER_REGISTERED){
												//用户已经注册过了
												//info :返回的注册信息 phone;provice;savetime								
												if(result!=""){
													Log.i("TBU_DEBUG", "企信通用户已经注册过了:"+result);
													String[] infos=result.toString().split(";");
													user_phone=infos[0];
													user_prov_id=infos[1];
												}else{
													Log.e("TBU_DEBUG", "企信通用户已经注册过了:"+result);
													user_phone="";
												}
												
											}else{
												Log.e("TBU_DEBUG", "企信通获取注册信息error code:"+code+",result="+result);
											}
										}
								
							});
						}
						
						else{
							Log.e("TBU_DEBUG", "qxt error code:"+code+",result="+result);
						}
				}
		});
	}
	
    View.OnClickListener listener = new View.OnClickListener() {
		@Override
		public void onClick(View v) {
			Debug.i("start onclick!");
			//dealRegisterQXT(activity.getApplicationContext());
			Debug.e("Test UA="+getUA(activity.getApplicationContext()));
		}
	};
	
	
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.test, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

}
