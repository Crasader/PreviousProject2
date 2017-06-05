TBU融合打包系统Server相关协议整理
=======
打包的大部分配置信息从Server端获取。整理数据信息列表如下。  

1 获取基本的打包信息
====
接口：http://183.131.152.31:1395/gameinfo/:tbuid  
示例：http://183.131.152.31:1395/gameinfo/201501  
返回数据格式(JSON)：[{"id":入库序号,"tbu_id":tbuid,"package_name_push":带push包名,"package_name_no_push":不带push包名,"game_version":游戏版本号，数字,"game_show_version":游戏显示版本号,"show_app_name":游戏显示名称,"output_name":输出包名显示缩写}]  
返回数据示例(JSON)：[{"id":1,"tbu_id":201501,"package_name_push":"com.dgg.yes","package_name_no_push":"com.kxllk.no","game_version":16,"game_show_version":"1.7.0","show_app_name":"开心连连看","output_name":"kxllk"}]  

2 获取特殊渠道头列表
====
接口：http://183.131.152.31:1395/gameinfo/spec/channelconfiglist  
示例：http://183.131.152.31:1395/gameinfo/spec/channelconfiglist  
返回数据格式(JSON)：[{"id":入库序号,"head":头字符串,"desc":渠道描述}]  
返回数据示例(JSON)：[{"id":1,"head":"youmi","desc":"有米"},{"id":2,"head":"cb","desc":"创变"},{"id":3,"head":"DOB_OC_37_","desc":"欧昕"},{"id":4,"head":"aliyun","desc":"阿里云"},{"id":5,"head":"gs","desc":"广升"}]  

3 获取特殊渠道头的特殊包名
====
接口：http://183.131.152.31:1395/gameinfo/channelconfig/:tbu_id/:channel_id  
示例：http://183.131.152.31:1395/gameinfo/channelconfig/201501/youmi  
返回数据格式(JSON)：[{"id":1,"tbu_id":游戏ID,"channel_id":渠道号,"package_name":包名}]  
返回数据示例(JSON)：[{"id":1,"tbu_id":201501,"channel_id":"youmi","package_name":"com.kxlianlk.ym"}]  

4 获取支付信息-指盟
====
接口：http://183.131.152.31:1395/gameinfo/payconfig/zhimeng/:tbuid  
示例：http://183.131.152.31:1395/gameinfo/payconfig/zhimeng/201501  
返回数据格式(JSON)：[{"id":入库序号,"tbu_id":tbuid,"app_id":指盟分配的单一app唯一标示}]  
返回数据示例(JSON)：[{"id":1,"tbu_id":201501,"app_id":7002646}]  

5 获取支付信息-乐途
====
接口：http://183.131.152.31:1395/gameinfo/payconfig/letu/:tbu_id  
示例：http://183.131.152.31:1395/gameinfo/payconfig/letu/201501  
返回数据格式(JSON)：[{"id":入库序号,"tbu_id":tbuid,"app_id":乐途分配的唯一app标示,"show_ui_key":一个包名对应一个uikey,"package_name":包名}]  
返回数据示例(JSON)：[{"id":1,"tbu_id":201501,"app_id":3030019,"show_ui_key":"f65e13b852a1874f49837bd58f02d873","package_name":"com.dgg.yes"},{"id":2,"tbu_id":201501,"app_id":3030019,"show_ui_key":"9bc32ddc0ecc742b15b9fc9913ff6a36","package_name":"com.kxllk.no"}] 

6 获取支付信息-破晓
====
接口：http://183.131.152.31:1395/gameinfo/payconfig/poxiao/:tbuid  
示例：http://183.131.152.31:1395/gameinfo/payconfig/poxiao/201501  
返回数据格式(JSON)：[{"id":入库序号,"tbu_id":tbuid,"game_id":破晓定义的单一游戏唯一标示}]  
返回数据示例(JSON)：[{"id":1,"tbu_id":201501,"game_id":9961}] 


7 获取支付信息-掌支付
====
接口：http://183.131.152.31:1395/gameinfo/payconfig/zhang/:tbuid  
示例：http://183.131.152.31:1395/gameinfo/payconfig/zhang/201501  
返回数据格式(JSON)：[{"id":入库序号,"tbu_id":tbuid,"game_id":破晓定义的单一游戏唯一标示}]  
返回数据示例(JSON)：[{"id":1,"tbu_id":201501,"app_id":1735,"key":"15E5F6DB56994D358E1909D3AD67FA9B"}]   

7 获取支付信息-悠悠村
====
接口：http://183.131.152.31:1395/gameinfo/payconfig/uucpay/:tbuid  
示例：http://183.131.152.31:1395/gameinfo/payconfig/uucpay/201501  
返回数据格式(JSON)：[{"id":入库序号,"tbu_id":tbuid,"app_id":悠悠村定义的单一游戏唯一标示}]  
返回数据示例(JSON)：[{"id":1,"tbu_id":201501,"app_id":1735] 


8 获取支付插件的商户信息
====
接口：http://183.131.152.31:1395/gameinfo/payconfig/merchantinfo  
示例：http://183.131.152.31:1395/gameinfo/payconfig/merchantinfo  
返回数据格式(JSON)：[{"id":入库序号,"sp_plugin":插件名称,"key":信息key值,"value":信息value}]  
返回数据示例(JSON)：[{"id":1,"sp_plugin":"letu","key":"merchantid","value":"HZPXPAY1001"},{"id":2,"sp_plugin":"letu","key":"merchant_key","value":"H@P6*1$Z#nkL9*X&"},{"id":3,"sp_plugin":"zhimeng","key":"merchant_id","value":"10642"},{"id":4,"sp_plugin":"zhimeng","key":"merchant_passwd","value":"hyu^&5(&122"}]  

9 查询默认支付插件列表
====
接口：http://183.131.152.31:1395/gameinfo/payconfig/defaultpluginlist  
示例：http://183.131.152.31:1395/gameinfo/payconfig/defaultpluginlist  
返回数据格式(JSON)：[{"id":入库序号,"pay_plugin_list":默认支付插件列表，用英文逗号分隔}]  
返回数据示例(JSON)：[{"id":0,"pay_plugin_list":"2,3,8"}] 

10 入库记录
====
接口：http://183.131.152.31:1395/gameinfo/process  
示例：http://183.131.152.31:1395/gameinfo/process  
HTTP类型 : POST  
参数说明：  
* client_order_id 客户端生成的订单号
* tbu_id 游戏id
* counts 本次出包数量
* channel_ids 渠道列表
* error_code 错误码
* desc 描述  
  
如果入库成功，返回{"result":0, errormsg : "success"}  
如果入库失败，result为非0  
入库错误信息如下：  
* 1 tbu_id字段错误
* 2 package_name字段错误
* 3 error_code字段错误
* 4 error_code + package_name 字段错误
* 100 数据库插入错误
  
[TODO]上传参数列表整理如下：  


11 返回目前入库的应用信息列表
====
接口：http://183.131.152.31:1395/gamelists  
示例：http://183.131.152.31:1395/gamelists  
返回数据格式(JSON)：  
返回数据示例(JSON)：[{"id":1,"tbu_id":201501,"package_name_push":"com.dgg.yes","package_name_no_push":"com.kxllk.no","game_version":16,"game_show_version":"1.7.0","show_app_name":"开心连连看","output_name":"kxllk"}]   

12 本地上传参数列表
====
client_order_id':"NA",
tbu_id':0,
counts':0,
channel_ids':"NA",
show_app_name':"NA",
package_name':"NA",
px_ad':"NA",
ox_ad':"NA",
yt_ad':"NA",
all_ad':"NA",
plugin_lists':"NA"
channel_ids :"NA"



附录A 参考信息
====
tbuid定义见：https://github.com/moloxiao/TbuDoc/wiki/Tbu%E6%B8%B8%E6%88%8F%E5%88%97%E8%A1%A8%E5%92%8CID%E4%BF%A1%E6%81%AF  
