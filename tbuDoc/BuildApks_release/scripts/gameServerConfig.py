# -*- coding: utf-8 -*-
'''
@attention: 从服务端获取配置信息
@param 游戏ID:tbuid
@return: 本地配置信息字典
'''
import json
import os
import time
import sys
import codecs
import shutil
import re
import random
import string
from tools.pyutils import pyutils
reload(sys)
sys.setdefaultencoding("utf-8")

class gameServerConfig:
    _tbuid = ''
    _dict = {}
    _copy = {}
    _plugin_ids = []
    _default_ad = 'false'
    _is_timeout = True
    _url = 'http://183.131.152.31:1395/'
    _url_gameinfo = _url + 'gameinfo/'
    _url_zhimeng = _url + 'gameinfo/payconfig/zhimeng/'
    _url_letu = _url + 'gameinfo/payconfig/letu/'
    _url_poxiao = _url + 'gameinfo/payconfig/poxiao/'
    _url_zhang = _url+'gameinfo/payconfig/zhang/'
    _url_uucpay = _url+'gameinfo/payconfig/uucpay/'
    _url_wechat = _url+'gameinfo/payconfig/wechat/'
    _url_taiku = _url+'gameinfo/payconfig/taiku/'
    _url_defaultpluginlist = _url + 'gameinfo/payconfig/packpluginlist'
    _url_channelconfig = _url + 'gameinfo/channelconfig/'
    _url_channelconfiglist = _url + 'gameinfo/spec/channelconfiglist'
    _url_merchantinfo = _url + 'gameinfo/payconfig/merchantinfo'

    def getMerchantinfo(self):
        read_native_json = True
        resp_merchantinfo = []
        if self._is_timeout is True:
            resp_merchantinfo = pyutils().http_post(self._url_merchantinfo)
            if resp_merchantinfo is not None:
                if not os.path.exists("./buffers"):
                    os.mkdir("./buffers")
                f = codecs.open("merchantinfo.json", 'w', "utf-8")
                read_native_json = False
                f.write(u'{\n\t"' + 'merchantinfo":' +
                        self.list2str(resp_merchantinfo) + '\n}')
                f.close()
                shutil.copy("merchantinfo.json", "./buffers/merchantinfo.json")
                os.remove("merchantinfo.json")
            else:
                read_native_json = True
        if read_native_json is True:
            if os.path.exists('./buffers/merchantinfo.json'):
                f = file("./buffers/merchantinfo.json", 'r')
                resp = json.load(f)
                resp_merchantinfo = resp['merchantinfo']
            else:
                print "no buffers on your computer."
                pyutils().record(self._copy, "22", "连接网络失败且本地没有缓存配置文件")
                exit(1)

        return resp_merchantinfo

    def getSpePackageName(self, head):
        read_native_json = True
        if self._is_timeout is True:
            resp_channelconfig = pyutils().http_post(
                self._url_channelconfig + self._tbuid + '/' + head)
            if resp_channelconfig is not None:
                read_native_json = False
                if not os.path.exists("./buffers"):
                    os.mkdir("./buffers")
                f = codecs.open("channelconfig.json", 'w', "utf-8")
                f.write(u'{\n\t"' + 'channelconfig":' +
                        self.list2str(resp_channelconfig) + '\n}')
                f.close()
                shutil.copy("channelconfig.json",
                            "./buffers/channelconfig.json")
                os.remove("channelconfig.json")
            else:
                read_native_json = True
        if read_native_json is True:
            if os.path.exists("./buffers/channelconfig.json"):
                f = file("./buffers/channelconfig.json", 'r')
                resp = json.load(f)
                resp_channelconfig = resp['channelconfig']
            else:
                print "no buffers on your computer."
                pyutils().record(self._copy, "22", "连接网络失败且本地没有缓存配置文件")
                exit(1)

        for i in range(len(resp_channelconfig)):
            if str(resp_channelconfig[i]['tbu_id']) == self._tbuid and resp_channelconfig[i]['channel_id'] == head:
                return resp_channelconfig[i]['package_name']

        return ""

    def getDefaultpluginlist(self):
        read_native_json = True
        if self._is_timeout is True:
            resp_defaultpluginlist = pyutils().http_post(self._url_defaultpluginlist)
            if resp_defaultpluginlist is not None:
                read_native_json = False
                if not os.path.exists("./buffers"):
                    os.mkdir("./buffers")
                f = codecs.open("defaultpluginlist.json", 'w', "utf-8")
                f.write(u'{\n\t"' + 'defaultpluginlist":' +
                        self.list2str(resp_defaultpluginlist) + '\n}')
                f.close()
                shutil.copy("defaultpluginlist.json",
                            "./buffers/defaultpluginlist.json")
                os.remove("defaultpluginlist.json")
            else:
                read_native_json = True
        if read_native_json is True:
            if os.path.exists("./buffers/defaultpluginlist.json"):
                f = file("./buffers/defaultpluginlist.json", 'r')
                resp = json.load(f)
                resp_defaultpluginlist = resp['defaultpluginlist']
            else:
                print "no buffers on your computer."
                pyutils().record(self._copy, "22", "连接网络失败且本地没有缓存配置文件")
                exit(1)
        return resp_defaultpluginlist

    def getReqConfInfo(self, **dict):
        self._copy = dict
        self._tbuid = dict['tbu_id']

# if dict['plugin_lists'] == "NA" or dict.has_key('plugin_lists') is
# False:
        resp_defaultpluginlist = self.getDefaultpluginlist()
        for i in range(len(resp_defaultpluginlist)):
            for key, value in resp_defaultpluginlist[i].items():
                if key == 'key' and value == 'DEFAULT_PAY_LISTS':
                    self._dict['DEFAULT_PAY_LISTS'] = resp_defaultpluginlist[
                        i]['value'].encode('utf8')
                if key == 'key' and value == 'PAY_SEQ_CM':
                    self._dict['PAY_SEQ_CM'] = resp_defaultpluginlist[
                        i]['value']
                if key == 'key' and value == 'PAY_SEQ_CU':
                    self._dict['PAY_SEQ_CU'] = resp_defaultpluginlist[
                        i]['value']
                if key == 'key' and value == 'PAY_SEQ_CT':
                    self._dict['PAY_SEQ_CT'] = resp_defaultpluginlist[
                        i]['value']
                if key == 'key' and value == 'PAY_SEQ_DEFAULT':
                    self._dict['PAY_SEQ_DEFAULT'] = resp_defaultpluginlist[
                        i]['value'].encode('utf8')

# self._dict['plugin_lists'] =
# resp_defaultpluginlist[0]['DEFAULT_PAY_LISTS'].split(',')

        if dict.has_key('plugin_lists') and dict['plugin_lists'] != "NA":
            self._plugin_ids = dict['plugin_lists'].split(',')
        else:
            dict['plugin_lists'] = self._dict.get('DEFAULT_PAY_LISTS')
            self._plugin_ids = self._dict['DEFAULT_PAY_LISTS'].split(',')
        self._is_timeout = self.isTimeout()

        package_name = ''
        if dict['package_name'] != 'NA':
            package_name = dict['package_name']
        px_ad = ''
        if dict['px_ad'] != 'NA':
            px_ad = dict['px_ad']
        elif dict['all_ad'] != 'NA':
            px_ad = dict['all_ad']
        else:
            px_ad = self._default_ad
            dict['px_ad'] = self._default_ad
            dict['ox_ad'] = self._default_ad
            dict['yt_ad'] = self._default_ad

        resp_gameinfo = []
        resp_poxiao = []
        resp_zhimeng = []
        resp_letu = []
        resp_zhang =[]
        resp_uucpay =[]
        resp_wechat=[]
        resp_taiku=[]

        if self._is_timeout is False and os.path.exists("./buffers/gameinfo" + self._tbuid + ".json"):
            f = file("./buffers/gameinfo" + self._tbuid + ".json", 'r')
            resp = json.load(f)
            resp_gameinfo = resp['gameinfo']
            resp_poxiao = resp['poxiao']
            resp_zhimeng = resp['zhimeng']
            resp_letu = resp['letu']
            resp_zhang = resp['zhang']
            resp_uucpay= resp['uucpay']
            resp_wechat=resp['wechat']
            resp_taiku=['taiku']
        if len(resp_gameinfo) == 0:
            if not os.path.exists("./buffers"):
                os.mkdir("./buffers")
            f = codecs.open("gameinfo" + self._tbuid + ".json", 'w', "utf-8")

            self.__class__._url_gameinfo += self._tbuid
            resp_gameinfo = pyutils().http_post(self.__class__._url_gameinfo)

            if '1010' in self._plugin_ids and len(resp_poxiao) == 0 :
                self.__class__._url_poxiao += self._tbuid
                resp_poxiao = pyutils().http_post(self.__class__._url_poxiao)

            if '1020' in self._plugin_ids and len(resp_zhimeng) == 0:
                self.__class__._url_zhimeng += self._tbuid
                resp_zhimeng = pyutils().http_post(self.__class__._url_zhimeng)

            if '1030' in self._plugin_ids and len(resp_letu) == 0:
                self.__class__._url_letu += self._tbuid
                resp_letu = pyutils().http_post(self.__class__._url_letu)

            if '1050' in self._plugin_ids and len(resp_zhang) == 0:
                self.__class__._url_zhang += self._tbuid
                resp_zhang = pyutils().http_post(self.__class__._url_zhang)

            if '1060' in self._plugin_ids and len(resp_uucpay) == 0:
                self.__class__._url_uucpay += self._tbuid
                resp_uucpay = pyutils().http_post(self.__class__._url_uucpay)
            if '1070' in self._plugin_ids and len(resp_wechat) == 0:
                self.__class__._url_wechat += self._tbuid
                resp_wechat = pyutils().http_post(self.__class__._url_wechat)
            if '1080' in self._plugin_ids and len(resp_taiku) == 0:
                self.__class__._url_taiku += self._tbuid
                resp_taiku = pyutils().http_post(self.__class__._url_taiku)    

            if resp_gameinfo is None:
                if os.path.exists("./buffers/gameinfo" + self._tbuid + ".json"):
                    f1 = file("./buffers/gameinfo" +
                              self._tbuid + ".json", 'r')
                    resp = json.load(f1)
                    resp_gameinfo = resp['gameinfo']
                else:
                    pyutils().record(dict, "18", "连接网络失败")
            if resp_poxiao is None:
                if os.path.exists("./buffers/gameinfo" + self._tbuid + ".json"):
                    f1 = file("./buffers/gameinfo" +
                              self._tbuid + ".json", 'r')
                    resp = json.load(f1)
                    resp_poxiao = resp['poxiao']
                else:
                    pyutils().record(dict, "18", "连接网络失败")
            if resp_zhimeng is None:
                if os.path.exists("./buffers/gameinfo" + self._tbuid + ".json"):
                    f1 = file("./buffers/gameinfo" +
                              self._tbuid + ".json", 'r')
                    resp = json.load(f1)
                    resp_zhimeng = resp['zhimeng']
                else:
                    pyutils().record(dict, "18", "连接网络失败")
            if resp_letu is None:
                if os.path.exists("./buffers/gameinfo" + self._tbuid + ".json"):
                    f1 = file("./buffers/gameinfo" +
                              self._tbuid + ".json", 'r')
                    resp = json.load(f1)
                    resp_letu = resp['letu']
                else:
                    pyutils().record(dict, "18", "连接网络失败")
            if resp_zhang is None:
                if os.path.exists("./buffers/gameinfo" + self._tbuid + ".json"):
                    f1 = file("./buffers/gameinfo" +
                              self._tbuid + ".json", 'r')
                    resp = json.load(f1)
                    resp_zhang = resp['zhang']
                else:
                    pyutils().record(dict, "18", "连接网络失败")
            if resp_uucpay is None:
                if os.path.exists("./buffers/gameinfo" + self._tbuid + ".json"):
                    f1 = file("./buffers/gameinfo" +
                              self._tbuid + ".json", 'r')
                    resp = json.load(f1)
                    resp_uucpay = resp['uucpay']
                else:
                    pyutils().record(dict, "18", "连接网络失败")
            if resp_wechat is None:
                if os.path.exists("./buffers/gameinfo" + self._tbuid + ".json"):
                    f1 = file("./buffers/gameinfo" +
                              self._tbuid + ".json", 'r')
                    resp = json.load(f1)
                    resp_wechat = resp['wechat']
                else:
                    pyutils().record(dict, "18", "连接网络失败")

            f.write(u'{\n\t"' + 'gameinfo":' + self.list2str(resp_gameinfo) + ',\n\t"poxiao":' + self.list2str(resp_poxiao) +
                    ',\n\t"zhimeng":' + self.list2str(resp_zhimeng) + ',\n\t"letu":' + self.list2str(resp_letu)+ 
                    ',\n\t"zhang":' + self.list2str(resp_zhang) + ',\n\t"uucpay":' + self.list2str(resp_uucpay)+ '\n}')
            f.close()
            shutil.copy("gameinfo" + self._tbuid + ".json",
                        "./buffers/gameinfo" + self._tbuid + ".json")
            os.remove("gameinfo" + self._tbuid + ".json")

        self.__class__._dict['game_version'] = resp_gameinfo[0]['game_version']
        self.__class__._dict['game_show_version'] = resp_gameinfo[
            0]['game_show_version']
        self.__class__._dict['screen_orientation'] = resp_gameinfo[
            0]['screen_orientation']
        self.__class__._dict['show_app_name'] = resp_gameinfo[
            0]['show_app_name']
        if dict.has_key('show_app_name') and dict['show_app_name'] == 'NA':
            dict['show_app_name'] = resp_gameinfo[0]['show_app_name']
        self.__class__._dict['output_name'] = resp_gameinfo[0]['output_name']
        self.__class__._dict['avos_app_id'] = resp_gameinfo[0]['avos_app_id']
        self.__class__._dict['avos_app_key'] = resp_gameinfo[0]['avos_app_key']
        if '1010' in self._plugin_ids:
            self.__class__._dict['poxiao_game_id'] = resp_poxiao[0]['game_id']
        if '1020' in self._plugin_ids:
            self.__class__._dict['zhimeng_app_id'] = resp_zhimeng[0]['app_id']
        if '1030' in self._plugin_ids:
            self.__class__._dict['letu_app_id'] = resp_letu[0]['app_id']
        if '1050' in self._plugin_ids:
            self.__class__._dict['zhang_app_id'] = resp_zhang[0]['app_id']
            self.__class__._dict['zhang_key'] = resp_zhang[0]['key']
        if '1060' in self._plugin_ids:
            #TODO:uuc的appId是这么跟tbu_id对应的
            self.__class__._dict['uuc_app_id'] = resp_uucpay[0]['app_id']
        if '1070' in self._plugin_ids:
            self.__class__._dict['wechat_app_id'] = resp_wechat[0]['app_id']
            self.__class__._dict['wechat_merchant_id'] = resp_wechat[0]['merchant_id']
            self.__class__._dict['wechat_package_name'] = resp_wechat[0]['package_name']

            #包名不一致时不能打包
            print 'check your package_name please current is :'+package_name
            print 'check your package_name please config is :'+self.__class__._dict['wechat_package_name']

            #if  package_name!=self.__class__._dict['wechat_package_name']
                #TODO error信息
               # pyutils().record(self.dict,'101', '本地的微信包名配置有误')
                #exit(1)
            
        resp_merchantinfo = self.getMerchantinfo()

        #处理商户信息

        for i in resp_merchantinfo:
            if json.loads(json.dumps(i))['sp_plugin'] == 'zhimeng':
                if json.loads(json.dumps(i))['key'] == 'merchant_id':
                    self._dict['zhimeng_merchant_id'] = json.loads(json.dumps(i))[
                        'value']
                elif json.loads(json.dumps(i))['key'] == 'merchant_passwd':
                    self._dict['zhimeng_merchant_passwd'] = json.loads(json.dumps(i))[
                        'value']
            elif json.loads(json.dumps(i))['sp_plugin'] == 'letu':
                if json.loads(json.dumps(i))['key'] == 'merchant_id':
                    self._dict['letu_merchant_id'] = json.loads(json.dumps(i))[
                        'value']
                elif json.loads(json.dumps(i))['key'] == 'merchant_key':
                    self._dict['letu_merchant_key'] = json.loads(json.dumps(i))[
                        'value']
                elif json.loads(json.dumps(i))['key'] == 'sc_channel_lists':
                    self._dict['letu_sc_channel_lists'] = json.loads(json.dumps(i))[
                        'value']
            elif json.loads(json.dumps(i))['sp_plugin'] == 'zhang':
                if json.loads(json.dumps(i))['key'] == 'channel_id':
                    self._dict['zhang_channel_id'] = json.loads(json.dumps(i))[
                        'value']            
            elif json.loads(json.dumps(i))['sp_plugin'] == 'uucpay':
                if json.loads(json.dumps(i))['key'] == 'merchant_key':
                    self._dict['uuc_merchant_key'] = json.loads(json.dumps(i))[
                        'value']
                elif json.loads(json.dumps(i))['key'] == 'secret_key':
                    self._dict['uuc_secret_key'] = json.loads(json.dumps(i))[
                        'value']
        dict['package_name'] = ''
        for i in range(len(dict['special_data'])):
            exist_letu_key = False
            head = self.isSpecificChannelId(
                dict['special_data'][i].get_channel_id())
            if package_name != '':
                dict['special_data'][i].set_package_name(package_name)
                dict['package_name'] += package_name
            # elif head != "":
            #     pname = self.getSpePackageName(head)
            #     if pname == "":
            #         print "get specific channel package name fail.suggest filling in package_name in gameConfig.xlsx."
            #         pyutils().record(dict, '14', dict['special_data'][
            #             i].get_channel_id() + '为特殊渠道号，但无法通过网络获取包名')
            #         exit(1)
            #     dict['special_data'][i].set_package_name(pname)
            #     dict['package_name'] += pname
            # elif px_ad == 'true':
            #     dict['special_data'][i].set_package_name(
            #         resp_gameinfo[0]['package_name_push'])
            #     dict['package_name'] += resp_gameinfo[0]['package_name_push']
            else:
                dict['special_data'][i].set_package_name('com.'
                    +string.join(random.sample(['z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a'], 5)).replace(' ','')+
                    '.'+string.join(random.sample(['z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a'], 5)).replace(' ',''))
                dict['package_name'] += package_name
            if '1030' in self._plugin_ids:
                for r in range(len(resp_letu)):
                    if resp_letu[r]['package_name'] == dict['special_data'][i].get_package_name():
                        if(dict['special_data'][i].get_channel_id() == self._dict['letu_sc_channel_lists']):
                            dict['plugin_lists'] = '1030'
                            print 'letu 特殊渠道号,uikey为空,插件列表强制修改为1030'
                        else:
                            dict['special_data'][i].set_letu_key(
                                resp_letu[r]['show_ui_key'])
                        exist_letu_key = True
                # if exist_letu_key is False:
                #     print "no package name in the buffer or on the server."
                #     pyutils().record(dict, '21', dict['special_data'][
                #         i].get_package_name() + '无法获取到对应的乐途key')
                #     exit(1)
            if i < len(dict['special_data']) - 1 and package_name != '':
                dict['package_name'] += ','
        print dict
        return self.__class__._dict, dict

    def isSpecificChannelId(self, channel_id):
        read_native_json = True
        if self._is_timeout is True:
            channel_config_list = pyutils().http_post(self._url_channelconfiglist)
            if channel_config_list is None:
                read_native_json = True
            else:
                if not os.path.exists("./buffers"):
                    os.mkdir("./buffers")
                f = codecs.open("channelconfiglist.json", 'w', "utf-8")
                read_native_json = False
                f.write(u'{\n\t"' + 'channelconfiglist":' +
                        self.list2str(channel_config_list) + '\n}')
                f.close()
                shutil.copy("channelconfiglist.json",
                            "./buffers/channelconfiglist.json")
                os.remove("channelconfiglist.json")
        if read_native_json is True:
            f = file("./buffers/channelconfiglist.json", 'r')
            resp = json.load(f)
            channel_config_list = resp['channelconfiglist']

        for i in range(len(channel_config_list)):
            tt_match = re.search(channel_config_list[i]['head'], channel_id)
            if tt_match:
                return channel_config_list[i]['head']
        return ''

    def isTimeout(self):
        return True
#         if not os.path.exists("./buffers"):
#             os.mkdir("./buffers")
#             return True
#         else:
#             if not os.path.exists("./buffers/gameinfo"+self._tbuid+".json"):
#                 return True
#             elif time.time() - os.path.getmtime("./buffers/gameinfo"+self._tbuid+".json") > 4 * 24 * 60 * 60 * 1000:
#                 return True
#             else:
#                 return False

    def list2str(self, list):
        return json.dumps(list)
