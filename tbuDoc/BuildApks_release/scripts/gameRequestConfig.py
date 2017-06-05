# -*- coding: utf-8 -*-
'''
@attention: 获取本地配置信息
@param gameConfigXlsx_path: 本地配置表格的位置
@return: 本地配置信息字典
'''
import xlrd
import sys
import os
import codecs
import time
import json
import datetime
from specialData import specialData
from tools.pyutils import pyutils
reload(sys)
sys.setdefaultencoding( "utf-8" )

class gameRequestConfig:
    dict={'client_order_id':"NA",'tbu_id':0,'counts':0,'channel_ids':"NA",'zhang_qds':"NA",\
          'uuc_own_channel':"NA",'show_app_name':"NA",'package_name':"NA",'px_ad':"NA",'ox_ad':"NA",\
          'yt_ad':"NA",'all_ad':"NA",'plugin_lists':"NA",'plugin_lists_phone':"NA"}
    
    def getClientOrderID(self):
        try:
            pathconfigJson_path = codecs.open("./pathconfig.json", "r", "utf-8")
            paths = json.load(pathconfigJson_path)
            client_number=paths['Client_Number']
            self.dict['save_path']=paths['save_path']
            self.dict['client_order_id']=client_number+"_"+time.strftime('%Y%m%d%H%M', time.localtime())
        except:
            print 'check your pathconfig.json please'
            pyutils().record(self.dict,'13', '本地的pathconfig.json填写有误')
            exit(1)
   
    def getReqConfInfo(self,gameConfigXlsx_path):
        self.getClientOrderID()
        ad_num=0        
        log_path=open('log.txt','w')
        log_path.truncate()
        log_path.write('the information from your gameConfig.xlsx:')
        
        if not os.path.exists(gameConfigXlsx_path):
            print "gameConfig.xlsx does not exist."
            pyutils().record(self.dict,'20', '输入的gameConfig.xlsx路径有误')
            exit(1)
        data = xlrd.open_workbook(gameConfigXlsx_path)
        table = data.sheet_by_index(0)
        for r in range(1, table.nrows):
            key = str(table.cell_value(r, 0)).strip()
            val = str(table.cell_value(r, 1)).strip()
            if key == 'game_id':
                if len(val) != 6:
                    print "game_id is not correct."
                    pyutils().record(self.dict,'1', 'gameConfig.xlsx没有提供有效的game_id')
                    exit(1)
                else:
                    self.dict['tbu_id']=val
                    log_path.write('\n\ttbu_id is '+val)
            elif key == 'show_app_name':
                if val.find(" ") != -1:
                    print "show_app_name is not correct."
                    pyutils().record(self.dict,'2', 'gameConfig.xlsx没有提供有效的show_app_name')
                    exit(1)
                elif val != "":
                    self.dict[key]=val.strip()
                    log_path.write('\n\tshow_app_name is '+val)
            elif key == 'package_name':
                if val.find(" ") != -1 or val.lower() != val:
                    print "package_name is not correct."
                    pyutils().record(self.dict,'3', 'gameConfig.xlsx没有提供有效的package_name')
                    exit(1)
                elif val != "":
                    self.dict['package_name']=val.strip()
                    log_path.write('\n\tpackage_name is '+val)
            elif key == 'px_ad':
                if val != "false" and val != "true":
                    print "px_ad is not correct."
                    pyutils().record(self.dict,'4', 'gameConfig.xlsx没有提供有效的px_ad')
                    exit(1)
                else:
                    ad_num+=1
                    self.dict['px_ad']=val
                    log_path.write('\n\tpx_ad is '+val)
            elif key == 'yt_ad':
                if val != "false" and val != "true":
                    print "yt_ad is not correct."
                    pyutils().record(self.dict,'5', 'gameConfig.xlsx没有提供有效的yt_ad')
                    exit(1)
                else:
                    ad_num+=1
                    self.dict['yt_ad']=val
                    log_path.write('\n\tyt_ad is '+val)
            elif key == 'ox_ad':
                if val != "false" and val != "true":
                    print "ox_ad is not correct."
                    pyutils().record(self.dict,'6', 'gameConfig.xlsx没有提供有效的ox_ad')
                    exit(1)
                else:
                    ad_num+=1
                    self.dict['ox_ad']=val
                    log_path.write('\n\tox_ad is '+val)
            elif key == 'all_ad':
                if val != "false" and val != "true":
                    print "all_ad is not correct."
                    pyutils().record(self.dict,'7', 'gameConfig.xlsx没有提供有效的all_ad')
                    exit(1)
                elif val != "":
                    self.dict['all_ad']=val
                    log_path.write('\n\tall_ad is '+val)
            elif key == 'plugin_lists':
                if self.__plugin_list_is_correct(val) is False:
                    print "plugin_lists is not correct."
                    pyutils().record(self.dict,'8', 'gameConfig.xlsx没有提供有效的plugin_lists')
                    exit(1)
                elif val != "":
                    # TODO  需要将旧的1,2,3,4,5转化成新的1010,1020,1030,1040,1050
                    self.dict['plugin_lists']=val
                    log_path.write('\n\tplugin_lists is '+val)
            elif key == 'plugin_lists_phone':
                if self.__plugin_list_is_correct(val) is False:
                    print "plugin_lists is not correct."
                    pyutils().record(self.dict,'8', 'gameConfig.xlsx没有提供有效的plugin_lists_phone')
                    exit(1)
                elif val != "":
                    # TODO  需要将旧的1,2,3,4,5转化成新的1010,1020,1030,1040,1050
                    self.dict['plugin_lists_phone']=val
                    log_path.write('\n\tplugin_lists_phone is '+val)
                    
        if self.dict['tbu_id'] == 'NA':
            print "game_id does not exist."
            pyutils().record(self.dict,'1', 'gameConfig.xlsx没有提供有效的game_id')
            exit(1)
        if ad_num != 3 and ad_num != 0:
            print "cheack ad please.fill in px_ad,yt_ad and ox_ad.Or,fill in all_ad."
            pyutils().record(self.dict,'9', 'gameConfig.xlsx中广告开关提供有误')
            exit(1)
        #取渠道号
        table = data.sheet_by_index(1)    
        ids = []
        log_path.write('\n\tchannel_id = ')
        for r in range(1, table.nrows):
            try:
                val = str(int(table.cell_value(r, 0)))
                val2 = str(int(table.cell_value(r, 1)))
                val3 = str(int(table.cell_value(r, 2)))
            except:
                val = str(table.cell_value(r, 0)).strip()
                val2 = str(table.cell_value(r, 1)).strip()
                val3 = str(table.cell_value(r, 2)).strip()
                log_path.write(val+";")
                log_path.write(val2+" ")
                log_path.write(val3+" ")
            spe_data=specialData()
            spe_data.set_channel_id(val)
            if(val2==''):
                val2 ='NA'
            spe_data.set_zhang_qd(val2)
            if(val3==''):
                val3 ='NA'
            spe_data.set_uuc_own_channel(val3)
            ids.append(spe_data)  
        log_path.close()
        if len(ids) < 1:
            print "channel id dose not exist."       
            pyutils().record(self.dict,'10', 'gameConfig.xlsx中没有填写渠道号')  
            exit(1)    
        self.dict['special_data']=ids
        channel_ids=''
        zhang_qds=''
        uuc_own_channel=''
        count=0
        for i in range(len(self.dict['special_data'])):
            count += 1
            channel_ids+=self.dict['special_data'][i].get_channel_id()
            zhang_qds+=self.dict['special_data'][i].get_zhang_qd()
            uuc_own_channel+=self.dict['special_data'][i].get_uuc_own_channel()

            if i<len(self.dict['special_data'])-1:
                channel_ids+=','
                zhang_qds+=','
                uuc_own_channel+=','
        self.dict['channel_ids']=channel_ids
        self.dict['counts']=count
        return self.dict

    def __changePluginId(self,val):
        plugins = val.split(',')
        print ('plugins = '+plugins)

    def __plugin_list_is_correct(self,val):
        if val == "":
            return True
        plugins=val.split(',')
        print val
        if '1000' in plugins or '1010' in plugins or '1020' in plugins or '1030' in plugins or '1040' in plugins or '1050' in plugins or '1060' in plugins  or '1070' in plugins or '1080' in plugins or val == '':
            return True
        else:
            return False
