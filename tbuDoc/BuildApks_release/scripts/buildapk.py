# -*- coding: utf-8 -*-

from gameServerConfig import gameServerConfig
from gameRequestConfig import gameRequestConfig
from gameNativeInfo import gameNativeInfo
from gameConfig import gameConfig
from workspaceConfig import workspaceConfig
from channelOut import channelOut
import sys
reload(sys)
sys.setdefaultencoding("utf-8")

class buildapk:

    def build(self):
        # step 1 输入gameConfig.xlsx路径
        gameConfig_path = "C:\\Users\\Administrator\\Desktop\\gameConfig.xlsx"
        # gameConfig_path=raw_input()
        # step 2 获取本地配置信息,gameConfig信息占有绝对统治地位。
        dict_local = gameRequestConfig().getReqConfInfo(gameConfig_path)
        # step 3 获取本地环境
        dict_path = gameNativeInfo().getReqConfInfo(**dict_local)
        # step 4 获取服务端配置信息
        dict_server, dict_local = gameServerConfig().getReqConfInfo(**dict_local)
        # step 5 合并打包信息
        dict_unite = {'0': dict_local, '1': dict_server, "2": dict_path}
        config_data = gameConfig().getReqConfInfo(**dict_unite)
        # step 6 在输出缓存目录配置工程
        workspaceConfig(config_data, **dict_local)
        # step 7 分渠道出包
        channelOut(config_data, **dict_local)
   

