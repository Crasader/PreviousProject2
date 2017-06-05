# -*- coding: utf-8 -*-
'''
@attention: 获取应用本地环境信息
@param 游戏ID:tbuid
@return: 本地配置信息字典
'''
import codecs
import json
import time
import os
import sys
import shutil
from tools.pyutils import pyutils
reload(sys)
sys.setdefaultencoding( "utf-8" )
 
class gameNativeInfo:
    _tbuid=''
    _dict_path={}
         
    def getReqConfInfo(self,**dict_local):
            self._tbuid=dict_local['tbu_id']
#         try:
            pathconfigJson_path = codecs.open("./pathconfig.json", "r", "utf-8")
#             pathconfigJson_path = file("./pathconfig.json")  
            paths = json.load(pathconfigJson_path)
            
            project_copy_path = paths['project_copy_path']
            self._dict_path['project_path']=paths['project_path'][self._tbuid]
            self._dict_path['b_up_path']=paths['b_up_path']
            self._dict_path['save_path']=paths['save_path']
            self._dict_path['config_files_path']=paths['configfiles_path']
            self._dict_path['other_libraries']=[]
            if paths['other_libraries'].has_key(self._tbuid):
                self._dict_path['other_libraries']=paths['other_libraries'][self._tbuid]
                print self._dict_path['other_libraries']
            if os.path.exists(project_copy_path) is False:
                os.mkdir(project_copy_path)
            
            if not os.path.exists(self._dict_path['project_path']):
                print "project_path is not correct or project does not exist."
                pyutils().record(dict_local,'11', '指定位置的主工程不存在')
                exit(1)
            if not os.path.exists(self._dict_path['b_up_path']+"\\B"):
                print "b_up_path is not correct or project b dose not exist."
                pyutils().record(dict_local,'12', '指定位置的B工程上级目录不存在')
                exit(1)
            file_name=self._tbuid+"_"+time.strftime('%Y%m%d%H%M', time.localtime())
            self._dict_path['dst_path']=project_copy_path+"\\"+file_name
            return self._dict_path
#         except:
#             print 'check your pathconfig.json please'
#             pyutils().record(dict_local,'13', '本地的pathconfig.json填写有误')
#             exit(1)

        

         
             
