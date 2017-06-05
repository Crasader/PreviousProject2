# -*- coding: utf-8 -*-
'''
@attention: 合并打包信息
'''
import json
import copy
from configData import configData
class gameConfig:
    _dicts={}       #key表示优先级，即子字典同时出现某个key时，取优先级高的子字典
          
    def getReqConfInfo(self,**dicts):
        '''
        @return: 合并后的配置信息
        ''' 
        result={}
        pop_list=[]
        self.__class__._dicts=copy.deepcopy(dicts)
        n=len(self.__class__._dicts)
        for key in self.__class__._dicts['0']:
            if self.__class__._dicts['0'][key] == 'NA' or self.__class__._dicts['0'][key] == 0:
                pop_list.append(key)
        for key in pop_list:
            self.__class__._dicts['0'].pop(key)
        for i in range(len(self.__class__._dicts)):
            result=dict(result.items()+self.__class__._dicts[str(n-i-1)].items())
        if result.has_key('px_ad') is False or result['px_ad'] == 'NA':
            if result.has_key('all_ad') and result['all_ad'] != 'NA':
                result['px_ad']=result['all_ad']
                result['yt_ad']=result['all_ad']
                result['ox_ad']=result['all_ad']
            else:
                result['px_ad']="false"
                result['yt_ad']="false"
                result['ox_ad']="false"
        if result.has_key('plugin_lists') is False or (result.has_key('plugin_lists') and result['plugin_lists']=='NA'):
            result['plugin_lists']=result.get('DEFAULT_PAY_LISTS')
        else:
            #根据excle填的值来修正不同运营商的默认配置
            if result.has_key('plugin_lists_phone') is False or (result.has_key('plugin_lists_phone') and result['plugin_lists_phone']=='NA'):
                result['plugin_lists_phone']  = result['plugin_lists']
                result['PAY_SEQ_CU'] = result['plugin_lists']
                result['PAY_SEQ_CT'] = result['plugin_lists']
                result['PAY_SEQ_CM'] = result['plugin_lists']
                result['PAY_SEQ_DEFAULT'] = result['plugin_lists']    
            else:
                result['PAY_SEQ_CU'] = result['plugin_lists_phone']
                result['PAY_SEQ_CT'] = result['plugin_lists_phone']
                result['PAY_SEQ_CM'] = result['plugin_lists_phone']
                result['PAY_SEQ_DEFAULT'] = result['plugin_lists_phone']           
        log_path=open('log.txt','a')
        log_path.write('\nthe final information:')
        for key,value in result.items():
            if key != 'special_data':
                log_path.write('\n\t')
                log_path.write(key)
                log_path.write(' is ')
                if key == 'plugin_lists':
                    if value == 'NA':
                        log_path.write(value)
                    else:
                        log_path.write(value)
                else:
                    try:
                        log_path.write(value)
                    except:
                        log_path.write(str(value))
        log_path.close()
        config_data=configData()
        config_data.set_by_dict(**result)
        #待上传数据
#         channel_ids=''
#         count=0
#         for i in range(len(dicts['0']['special_data'])):
#             count += 1
#             channel_ids+=dicts['0']['special_data'][0].get_channel_id()
#             if i<len(dicts['0']['special_data'])-1:
#                 channel_ids+=','
#         dicts['0']['channel_ids']=channel_ids
#         dicts['0']['counts']=count
#         dicts['0']['client_order_id']=dicts['2']['client_order_id']
#         dicts['0'].pop('special_data')
        
        return config_data



























