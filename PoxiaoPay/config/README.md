游戏配置说明
=======

配置流程
====

配置GameConfig.xlsx

* 确认对应的AppConfig工程路劲在脚本中正确配置
* 其中PayPoint.xlsx会转换为其中的计费点信息
* 更新AppConfig工程中的内容（TODO 执行某个脚本文件，参看AppConfig工程说明）
* 从AppConfig导出gameconfig.jar文件

PayPointUi.xlsx

* 转换为paypointui.json

UiToPay.xlsx

* 转换为uitopay.json

拷贝文件对应目录

* payui -> assets/payui
* paypointui.json -> assets/payui/paypointui.json
* uitopay.json -> assets/payui/uitopay.json
* gameinfo.px -> assets/gameinfo.px
* gamepayplgin.px -> assets/gamepayplgin.px
* skymobi_a -> assets/skymobi_a
* ZM_ChannelID -> assets/ZM_ChannelID
* ZYF_ChannelID -> assets/ZYF_ChannelID
* 斯凯定制界面文件 -> assets/zmfiles/斯凯定制界面文件
* icon文件替换res目录下的各个文件

以上转换和拷贝执行同一个脚本文件(TODO 说明脚本文件)。

FAQ
=======


