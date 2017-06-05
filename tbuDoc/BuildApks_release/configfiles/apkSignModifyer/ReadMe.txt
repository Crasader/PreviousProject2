
这是一个对APK进行签名的批量处理工具，支持以下模式：
 — 随机签名：对不同APK包 采用不同的签名，签名文件自动生成。签名文件存储在temp目录下面。
 — 固定签名：对渠道包采用指定的同一个签名文件
 - 自动签名：对不同渠道包采用不同的签名，同一个渠道包下次自动签名模式下采用同一个签名，这样可以支持升级。签名文件存在工具目录下面

 渠道包的定义：包名+渠道ID 两者一致认为是同一个渠道包。


使用说明：

    1. 配置环境：将zipalign，jarsigner的路径加入PATH中
    2. 在命令行下调用
    
         随机签名
            ./apkResModifyerCMD --smode random -i 输入目录  -o 输出目录
   
   
         固定签名
            ./apkResModifyerCMD --smode fix --skeystore 签名的密钥文件 --spassword 签名的密码  --salias 签名的别名 -i 输入目录  -o 输出目录
     

         自动签名(一个包名+渠道号使用一个签名)
            修改config.xml
               启用config段（去掉注释）
                  custom.channelid.get 用于获取渠道号
                  第一种配置从文本中获取第一行数据
                  第二种配置从manifest文件中获取指定的节点
            ./apkResModifyerCMD -m modify-sign-auto --smode auto -i 输入目录  -o 输出目录      
        
    

     





    
