TBU融合打包本地配置规则
=======  
1.manifestAdd文件夹
  1.1 application文件夹
  包含各个插件需要在AndroidManifest.xml的application注册的内容,每个配置文件里都包含一段注释,脚本会根据这段配置来去重和插入。不可以随意修改。

  1.2 manifest文件夹
    包含各个插件的权限需求.每个配置文件里都包含一段注释,脚本会根据这段配置来去重和插入。不可以随意修改。

2.default文件夹
  2.1 Add_IapMM  新创需要的文件,放在主工程的assets目录下。
  2.2 Add_UU   优投广告的权限
  2.3 Add_Others B工程的反射配置以及新创MM的平台信息外部配置。
  2.4 游戏配置文件夹已tbuid命名。
      2.4.1 Add_Avos avos的appid和key
      2.4.2 Add_OX 殴昕广告的脚本
      2.4.3 Add_UU 优投广告的jar
      2.4.4 B_Single_Zimon sky支付的
      2.4.5 Add_uucpay 悠悠村支付的
      2.4.6 Add_Zhang 掌支付的
      2.4.7 Others游戏屏幕分辨率和适配机制
      2.4.8 event2pay时间点表
      2.4.9 PayPoint计费点表 
  2.5 Add_uucpay 悠悠村支付配置文件
      2.5.1 A 放在主工程asset下的文件
      2.5.2 B B工程需要的配置文件,资源等



