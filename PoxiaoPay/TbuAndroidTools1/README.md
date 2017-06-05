TBU Android工具类
=======
VERSION = "16"
*DO1 支付开关的结果接口移动到获取开关工程中

VERSION = "14"
*DO1 imsi 添加电信的imsi判断

VERSION = "12"
*DO1 读取本地配置的默认插件的时候添加一个转化方法,以统一原先客户端和服务端分裂的协议
*DO2 融合工程的启动类加载配置项从tat移除，从新移到融合工程
*DO3 需要通过反射来完成加载的插件,这些插件的类名和方法的信息读取模块移动到插件切换模块
*DO4 事件点，计费点，SP编码的类名修改，获取方法统一到TbuAndroidTools中

===========================

VERSION = "10"
*DO1 修改了AppInfo,由原先的属性直接获取改为方法获取
*DO2 修改了Device,由原先的属性直接获取改为方法获取
*DO3 计费点信息获取从AppInfo中移除，直接从PayPiontUtil获取

===========================
VERSION = "8"

INFO:没有及时添加更新日志，时间久了，无法确定修改了。

*短信发送模块需要把带有业务信息的编码模块移出

VERSION = "3"
export = tat_v3_1_20150924.jar
==============
DO1：增加imsi异常判断
DO2:添加短信发送基础模块


VERSION = "3"
export = tat_v3_1_20150707.jar
==============
DO1:将PhoneINfoManager中的未取到imei、imsi、simserialnumber的默认值改为public。


VERSION = "3"
==============
export = tat_v3_20150624.jar
DO1:增加了查看常用安全软件是否安装的方法


VERSION = "2"
==============
DO1:添加事件分离json文件，包含3个信息，事件点编号，改事件点对应的计费点，事件点是否开启  getPaypointByEventpoint(Context context, int point)
DO2:提供了自有的计费点向运营商计费编号之间的转化  getSpointbyPoint(Context context, int point)

VERSION = "1"
==============
初始版本