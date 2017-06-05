# -*- coding: utf-8 -*-
import shutil
import os
import re
import codecs
import xlrd
from tools.pyutils import pyutils
import xml.etree.ElementTree as et
from xml.dom import minidom
from configData import configData
import glob

class workspaceConfig:
    _project_path = ''
    _dst_path = ''
    _B_path = '' #PoxiaoMoneyGame的路径
    _in_path = ''
    _tbuid = ''
    _dict = {}
    _config_data = configData()
    _plugin_ids = ''
    _debug_model = 'false'

    def __init__(self, config_data, **dict_local):
        self._dict = dict_local
        self._plugin_ids = config_data.get_plugin_lists().split(',')
        self._tbuid = config_data.get_tbu_id()
        self._config_data = config_data
        from_path = config_data.get_project_path()
        self._dst_path = config_data.get_dst_path()
        self._B_path = config_data.get_b_up_path()
        self._in_path = config_data.get_config_files_path()
        self._project_path = self._dst_path + "\\A"
        shutil.copytree(from_path, self._project_path)
        # 通过渠道号来判断是否是白包,白包使用B_DEBUG来打包
        shutil.copytree(self._B_path + "\\B", self._dst_path + '\\B')
        for i in range(len(self._config_data.get_other_libraries())):
            shutil.copytree(self._config_data.get_other_libraries()[
                            i], self._dst_path + '\\D' + str(i))
        for i in range(len(config_data.get_special_data())):
            self.addPlugin(config_data.get_special_data()[i])
        self.addAd()
        self.modifyFiles()
        self.replaceXml()
        self.modifyEncryptedJson()
        self.modifyDependence()

    # avospush相关的部分配置
    def addAd(self):
        print('start to push')
        manifestXml = open(self._project_path + "\\AndroidManifest.xml", 'r')
        content = manifestXml.read()
        manifestXml.close()
        pos = content.find("</application>")
        startNO_avos = content.find("<!-- avos push -->")
#         startNO_tbu = content.find("<!-- tbu push start -->")
        if self._config_data.get_px_ad() == "true":
            # self.moveJar('tps_', self._B_path + "\\B\\libs", self._B_path + "\\B\\push_lib")
            self.moveJar('avoscloud-push-', self._project_path +
                         "\\libs", self._dst_path + "\\B\\push_lib")
            if startNO_avos == -1:

                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO_avos, "<!-- avos end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\application\\avosPush.txt"), content, pos, "true")
                pos1 = content.find("</manifest>")
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO_avos, "<!-- avos push permission end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\avosPush.txt"), content, pos1, "true")
#             if startNO_tbu == -1:
#                 self.modifyManifest(self._in_path, startNO_tbu, "<!-- tbu push end -->", "tbuPush.txt", content, pos, "true")

        else:
            # self.deleteJar('tps_', self._B_path + "\\B\\libs")
            self.deleteJar('avoscloud-push', self._project_path + "\\libs")
            if startNO_avos != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                             startNO_avos, "<!-- avos end -->", "", content, pos, "false")
                pos1 = content.find("</manifest>")
                startNO_avosPermission = content.find(
                    "<!-- avos push permission start -->")
                if startNO_avosPermission != -1:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_avosPermission, "<!-- avos push permission end -->", "", content, pos1, "false")
#             if startNO_tbu == -1:
#                 self.modifyManifest(self._in_path, startNO_tbu, "<!-- tbu push end -->", "tbuPush.txt", content, pos, "false")
        print('push successfully.')

    # 支付插件先关的内容配置
    def addPlugin(self,spe_data):
        manifestXml = open(self._project_path + "\\AndroidManifest.xml", 'r')
        content = manifestXml.read()
        manifestXml.close()
        pos = content.find("</application>")

        # 乐途的依赖jar包中带有联通。b_letu,b_zimon,b_cu共用。若不带letu支付插件，而带有其他两种中的任何一种，都应该把Multimode_Unipay_base.jar加入到B工程中
        if '1030' not in self._plugin_ids and ('1020' in self._plugin_ids ) and not os.path.exists(self._B_path + 'B\\libs\\Multimode_Unipay_base.jar'):
            shutil.copyfile(self._in_path + '\\default\\Add_CU\\Multimode_Unipay_base.jar',
                            self._dst_path + '\\B\\libs\\Multimode_Unipay_base.jar')
        elif os.path.exists(self._dst_path + '\\B\\libs\\Multimode_Unipay_base.jar'):
            os.remove(self._dst_path + '\\B\\libs\\Multimode_Unipay_base.jar')

        #free
        startNO = content.find("<!-- free permission start -->")
        if '1000' in self._plugin_ids:
            pos1 = content.find("</manifest>")
            content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- free permission end -->",
                                                 pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\free.txt"), content, pos1, "true")
            self.moveJar('b_free_', self._dst_path + "\\B\\libs",self._in_path + '\\default\\Add_Free')
        else:
            self.deleteJar("b_free_", self._dst_path + "\\B\\libs")
            pos1 = content.find("</manifest>")
            startNO_poxiaoPermission = content.find(
                    "<!-- free permission start -->")
            if startNO_poxiaoPermission != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_poxiaoPermission, "<!-- px permission end -->", "", content, pos1, "false")
        # poxiao
        startNO = content.find("<!-- px p start -->")
        if '1010' in self._plugin_ids:
            if startNO == -1:
                if str(self._config_data.get_screen_orientation()) == '1':
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- px p end -->",
                                                 pyutils().getContent(self._in_path + "\\manifestAdd\\application\\poxiao_landscape.txt"), content, pos, "true")
                    pos1 = content.find("</manifest>")
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- px permission end -->",
                                                 pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\poxiao.txt"), content, pos1, "true")
                else:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- px p end -->",
                                                 pyutils().getContent(self._in_path + "\\manifestAdd\\application\\poxiao_portrait.txt"), content, pos, "true")
                    pos1 = content.find("</manifest>")
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- px permission end -->",
                                                 pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\poxiao.txt"), content, pos1, "true")
            self.moveJar('b_px_', self._dst_path + "\\B\\libs",
                         self._in_path + "\\jars")
        else:
            self.deleteJar("b_px_", self._dst_path + "\\B\\libs")
            if startNO != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                             startNO, "<!-- px p end -->", "", content, pos, "false")
                pos1 = content.find("</manifest>")
                startNO_poxiaoPermission = content.find(
                    "<!-- px p start -->")
                if startNO_poxiaoPermission != -1:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_poxiaoPermission, "<!-- px permission end -->", "", content, pos1, "false")

        # sky
        stringXml = open(self._project_path +
                         "\\res\\values\\strings.xml", 'r')
        contentString = stringXml.read()
        stringXml.close()
        pos2 = contentString.find("</resources>")
        startNO1 = contentString.find('<string name="g_class_name" />')
        startNO = content.find("<!-- zm config start -->")
        if '1020' in self._plugin_ids:
            self.moveJar('b_zm_', self._dst_path + "\\B\\libs",
                         self._in_path + "\\jars")
            if not os.path.exists(self._project_path + "\\assets\\zmfiles"):
                shutil.copytree(self._in_path + '\\default\\' + self._tbuid +
                                "\\B_Single_Zimon\\zmfiles", self._project_path + "\\assets\\zmfiles")
            if not os.path.exists(self._project_path + "\\assets\\skymobi_a"):
                shutil.copyfile(self._in_path + '\\default\\' + self._tbuid +
                                "\\B_Single_Zimon\\skymobi_a", self._project_path + "\\assets\\skymobi_a")
            if not os.path.exists(self._project_path + "\\assets\\ZM_ChannelID"):
                shutil.copyfile(self._in_path + '\\default\\' + self._tbuid +
                                "\\B_Single_Zimon\\ZM_ChannelID", self._project_path + "\\assets\\ZM_ChannelID")
            if not os.path.exists(self._project_path + "\\assets\\ZYF_ChannelID"):
                shutil.copyfile(self._in_path + '\\default\\' + self._tbuid +
                                "\\B_Single_Zimon\\ZYF_ChannelID", self._project_path + "\\assets\\ZYF_ChannelID")
#             if not os.path.exists(self._B_path + "\\B\\zimon"):
#                 shutil.copytree(self._B_path + "\\B_ZIMON\\zimon", self._B_path + "\\B\\zimon")
            if not os.path.exists(self._dst_path + "\\B\\libs\\zimon.jar"):
                shutil.copyfile(self._B_path + "\\B_ZIMON\\libs\\zimon.jar",
                                self._dst_path + "\\B\\libs\\zimon.jar")
            if not os.path.exists(self._B_path + "\\B\\libs\\AndroidPay_UniPay.jar"):
                shutil.copyfile(self._B_path + "\\B_ZIMON\\libs\\AndroidPay_UniPay.jar",
                                self._dst_path + "\\B\\libs\\AndroidPay_UniPay.jar")
            if not os.path.exists(self._B_path + "\\B\\libs\\newpay_sdk_maxture.jar"):
                shutil.copyfile(self._B_path + "\\B_ZIMON\\libs\\newpay_sdk_maxture.jar",
                                self._dst_path + "\\B\\libs\\newpay_sdk_maxture.jar")
            if not os.path.exists(self._B_path + "\\B\\libs\\armeabi\\libzimon.so"):
                shutil.copyfile(self._B_path + "\\B_ZIMON\\libs\\armeabi\\libzimon.so",
                                self._dst_path + "\\B\\libs\\armeabi\\libzimon.so")
            if startNO1 == -1:
                pyutils().modifyXML(self._project_path + "\\res\\values\\strings.xml", startNO1,
                                   'g_class_name" />', '<string name="g_class_name" />', contentString, pos2, "true")
            if startNO == -1:
                # 修改manifest.xml
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- zm config end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\application\\zimon.txt"), content, pos, "true")
                pos1 = content.find("</manifest>")
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- zm permission end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\zimon.txt"), content, pos1, "true")
        elif '1020' not in self._plugin_ids:
            self.deleteJar("b_zm_", self._dst_path + "\\B\\libs")
            if os.path.exists(self._project_path + "\\assets\\zmfiles"):
                shutil.rmtree(self._project_path + "\\assets\\zmfiles")
            if os.path.exists(self._project_path + "\\assets\\skymobi_a"):
                os.remove(self._project_path + "\\assets\\skymobi_a")
            if os.path.exists(self._project_path + "\\assets\\ZM_ChannelID"):
                os.remove(self._project_path + "\\assets\\ZM_ChannelID")
            if os.path.exists(self._project_path + "\\assets\\ZYF_ChannelID"):
                os.remove(self._project_path + "\\assets\\ZYF_ChannelID")
#             if os.path.exists(self._B_path + "\\B\\zimon"):
#                 shutil.rmtree(self._B_path + "\\B\\zimon")
            if os.path.exists(self._dst_path + "\\B\\libs\\zimon.jar"):
                os.remove(self._dst_path + "\\B\\libs\\zimon.jar")
            if os.path.exists(self._dst_path + "\\B\\libs\\AndroidPay_UniPay.jar"):
                os.remove(self._dst_path + "\\B\\libs\\AndroidPay_UniPay.jar")
            if os.path.exists(self._dst_path + "\\B\\libs\\newpay_sdk_maxture.jar"):
                os.remove(self._dst_path + "\\B\\libs\\newpay_sdk_maxture.jar")
            if os.path.exists(self._dst_path + "\\B\\libs\\armeabi\\libzimon.so"):
                os.remove(self._dst_path + "\\B\\libs\\armeabi\\libzimon.so")

            if startNO1 != -1:
                pyutils().modifyXML(self._project_path + "\\res\\values\\strings.xml", startNO1,
                                   'g_class_name" />', '<string name="g_class_name" />', contentString, pos2, "false")

            if startNO != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                             startNO, "<!-- zm config end -->", "", content, pos, "false")
                pos1 = content.find("</manifest>")
                startNO_zimonPermission = content.find(
                    "<!-- zm permission start -->")
                if startNO_zimonPermission != -1:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_zimonPermission, "<!-- zm permission end -->", "", content, pos1, "false")

        # letu
        startNO = content.find("<!-- lt config start -->")
        pos = content.find("</application>")
        if '1030' in self._plugin_ids:
            if not os.path.exists(self._dst_path + "\\B\\libs\\lyhtghPayJar.jar"):
                shutil.copyfile(self._B_path + "\\B_LETU\\libs\\lyhtghPayJar.jar",
                                self._dst_path + "\\B\\libs\\lyhtghPayJar.jar")
            self.moveJar('b_lt_', self._dst_path + "\\B\\libs",
                         self._in_path + "\\jars")
            if not os.path.exists(self._B_path + "\\B\\libs\\armeabi\\libn0base.so"):
                shutil.copyfile(self._B_path + "\\B_LETU\\libs\\armeabi\\libn0base.so",
                                self._dst_path + "\\B\\libs\\armeabi\\libn0base.so")
            if startNO == -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- lt config end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\application\\letu.txt"), content, pos, "true")
                pos1 = content.find("</manifest>")
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- lt permission end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\letu.txt"), content, pos1, "true")
            if not os.path.exists(self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_LETU\\llappcode.dat"):
                print self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_LETU\\llappcode.dat" + " dose not exist."
                pyutils().record('17', '乐途所需的文件不存在')
                exit(1)
            shutil.copyfile(self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_LETU\\llappcode.dat", self._project_path + "\\assets\\llappcode.dat")

        elif '1030' not in self._plugin_ids:
            if os.path.exists(self._dst_path + "\\B\\libs\\lyhtghPayJar.jar"):
                os.remove(self._dst_path + "\\B\\libs\\lyhtghPayJar.jar")
            self.deleteJar("b_lt_", self._dst_path + "\\B\\libs")
            if os.path.exists(self._dst_path + "\\B\\libs\\armeabi\\libn0base.so"):
                os.remove(self._dst_path + "\\B\\libs\\armeabi\\libn0base.so")
            if os.path.exists(self._project_path + "\\assets\\llappcode.dat"):
                os.remove(self._project_path + "\\assets\\llappcode.dat")
            if startNO != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                             startNO, "<!-- lt config end -->", "letu.txt", content, pos, "false")
                pos1 = content.find("</manifest>")
                startNO_letuPermission = content.find(
                    "<!-- letu permission start -->")
                if startNO_letuPermission != -1:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_letuPermission, "<!-- lt permission end -->", "", content, pos1, "false")
#         self.createB_COCO(self._B_path)
        startNO = content.find("<!-- zh_p_start -->")
        pos = content.find("</application>")
        if '1050' in self._plugin_ids:           
            if not os.path.exists(self._project_path + "\\libs\\sdkzhangzhifu_4.4.04.jar"):
                shutil.copyfile(self._in_path + '\\default\\Add_Zhang\\sdkzhangzhifu_4.4.04.jar',
                                self._dst_path + "\\B\\libs\\sdkzhangzhifu_4.4.04.jar")
            self.moveJar('b_zh_', self._dst_path +
                         "\\B\\libs", self._in_path + "\\jars")
            if os.path.exists(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_Zhang'):
                shutil.copyfile(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_Zhang\\realpinfoz.json',
                                self._project_path + "\\assets\\json\\plugin\\realpinfoz.json")
                shutil.copyfile(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_Zhang\\zbaseinfo.json',
                                self._project_path + "\\assets\\json\\plugin\\zbaseinfo.json")
            else:
                print('have not add config file zhang pay')
                input()

            if startNO == -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- zh_p_end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\application\\zhang.txt"), content, pos, "true")
                pos1 = content.find("</manifest>")
                startNO_letuPermission = content.find("<!-- zh_permission_start -->")
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- zh_permission_end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\zhang.txt"), content, pos1, "true")
        else:
            self.deleteJar('b_zh_', self._dst_path + "\\B\\libs")
            self.deleteJar('sdkzhangzhifu_', self._dst_path + "\\B\\libs")
            if startNO != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                             startNO, "<!-- zh_p_end -->", "", content, pos, "false")
                pos1 = content.find("</manifest>")
                startNO_iapmmPermission = content.find(
                    "<!-- zh_permission_start-->")
                if startNO_iapmmPermission != -1:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_iapmmPermission, "<!-- zh_permission_end -->", "", content, pos1, "false")
        #UUC
        startNO = content.find("<!-- uuc config start -->")
        if '1060' in self._plugin_ids:  
            #_in_path configfiles         
            if not os.path.exists(self._dst_path + "\\B\\libs\\loft_sdk_0.0.4.jar"):
                shutil.copyfile(self._in_path + '\\default\\Add_uucpay\\B\\loft_sdk_0.0.4.jar',
                                self._dst_path + "\\B\\libs\\loft_sdk_0.0.4.jar")
            
            if not os.path.exists(self._dst_path + "\\B\\libs\\armeabi\\liblocSDK4d.so"):
                shutil.copyfile(self._in_path + '\\default\\Add_uucpay\\B\\armeabi\\liblocSDK4d.so',
                                self._dst_path + "\\B\\libs\\armeabi\\liblocSDK4d.so")

            if not os.path.exists(self._dst_path + "\\B\\libs\\armeabi\\libplugin_phone.so"):
                shutil.copyfile(self._in_path + '\\default\\Add_uucpay\\B\\armeabi\\libplugin_phone.so',
                                self._dst_path + "\\B\\libs\\armeabi\\libplugin_phone.so")
            #copty to A
            if not os.path.exists(self._project_path + "\\assets\\UU_ChannelId"):
                shutil.copyfile(self._in_path + '\\default\\Add_uucpay\\A\\UU_ChannelId',
                                self._project_path + "\\assets\\UU_ChannelId")

            if not os.path.isfile(self._project_path + "\\assets\\Sonnenblume"):
                os.makedirs(self._project_path + "\\assets\\Sonnenblume")
                shutil.copyfile(self._in_path + '\\default\\Add_uucpay\\A\\Sonnenblume\\res.bin',
                                self._project_path + "\\assets\\Sonnenblume\\res.bin")
            else:
                if not os.path.exists(self._project_path + "\\assets\\Sonnenblume\\res.bin"):
                    shutil.copyfile(self._in_path + '\\default\\Add_uucpay\\A\\Sonnenblume\\res.bin',
                                    self._project_path + "\\assets\\Sonnenblume\\res.bin")

            self.moveJar('b_uucpay_', self._dst_path +
                         "\\B\\libs", self._B_path + '\\B_UUC\\export')

            
            #copy to 主工程
            if os.path.exists(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_uucpay'):
                shutil.copyfile(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_uucpay\\realpayinfouucun.json',
                                self._project_path + "\\assets\\json\\plugin\\realpayinfouucun.json")
                shutil.copyfile(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_uucpay\\uucunpayinfo.json',
                                self._project_path + "\\assets\\json\\plugin\\uucunpayinfo.json")
            else:
                print('have not add config file uucpay pay')
                input()


            if startNO == -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- uuc config end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\application\\uuc.txt"), content, pos, "true")
                
                startNO= content.find("<!-- uuc permission start -->")
                pos1 = content.find("</manifest>")

                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- uuc permission end -->",
                                             pyutils().getContent(self._in_path + "\\manifestAdd\\manifest\\uuc.txt"), content, pos1, "true")

        else:
            self.deleteJar('b_uucpay_', self._dst_path + "\\B\\libs")

        #wechat
        startNO = content.find("<!-- wechat config start -->")
        if '1070' in self._plugin_ids:  
            if not os.path.exists(self._dst_path + "\\B\\libs\\libammsdk.jar"):
                shutil.copyfile(self._in_path + '\\default\\Add_wechat\\libammsdk.jar',
                                self._dst_path + "\\B\\libs\\libammsdk.jar")
            if not os.path.exists(self._dst_path + "\\B\\libs\\tbu_wx.jar"):
                shutil.copyfile(self._in_path + '\\default\\Add_wechat\\tbu_wx.jar',
                                self._dst_path + "\\B\\libs\\tbu_wx.jar")
            self.moveJar('b_wechat_', self._dst_path +
                         "\\B\\libs", self._B_path + '\\B_WECHAT\\export')
            
            #TODO:按包名生成一个路径存放Java文件类
            #if os.path.exists(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_wechat\\activity'):
                #souredir=self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_wechat\\activity\\com'
                #destdir=self._dst_path + "\\B\\src\\com"
                #self.copythisFiles(souredir,destdir)
            #copy to 主工程
            if os.path.exists(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_wechat'):
                if not os.path.exists(self._project_path + "\\assets\\json\\wx\\wexininfo.json"):
                    shutil.copyfile(self._in_path + '\\default\\'+ self._config_data.get_tbu_id()+'\\Add_wechat\\wexininfo.json',
                                    self._project_path + "\\assets\\json\\wx\\wexininfo.json")     
            else:
                print('have not add config file  wechat')
                input()

            if startNO == -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- wechat config end -->",
                                             pyutils().getContent(self._in_path + "\\default\\"+ self._config_data.get_tbu_id()+"\\Add_wechat\\wechat.txt"), content, pos, "true")
        else:
            self.deleteJar('b_wechat_', self._dst_path + "\\B\\libs") 
            self.deleteJar('libammsdk', self._dst_path + "\\B\\libs") 
            self.deleteJar('tbu_wx', self._dst_path + "\\B\\libs") 


    # 利用excle生成json,当excle不存在时,使用工程目录下原来的json文件
    def modifyFiles(self):
        payui_path = self._project_path + "\\assets\\payui"
        print('start to modify uitopay.json')
        uitopay = "UiToPay.xlsx"
        if not os.path.exists(self._in_path + "\\" + uitopay):
            print("UiToPay.xlsx does not exist")
        else:
            data = xlrd.open_workbook(self._in_path + "\\" + uitopay)
            table = data.sheet_by_index(0)
            jsonfilename = uitopay.split('.')[0].lower() + ".json"
            f = codecs.open(jsonfilename, "w", "utf-8")
            f.write(u'{\n\t"' + 'uipoints' + '\":[')
            for r in range(1, table.nrows):
                f.write(u'\n\t\t\t\t{')
                for c in range(table.ncols):
                    key = str(table.cell_value(0, c)).strip()
                    val = str(table.cell_value(r, c)).strip()
                    try:
                        float(val)
                        temp = ' "' + key + '\": ' + str(int(float(val)))
                    except:
                        temp = ' "' + key + '\": "' + val + '"'
                    f.write(temp)
                    if c < table.ncols - 1:
                        f.write(u',')
                    else:
                        f.write(u' }')
                if r < table.nrows - 1:
                    f.write(u',')
            f.write(u"\n\t]\n}\n")
            f.close()
            shutil.copy(jsonfilename, payui_path + "\\" + jsonfilename)
            os.remove(jsonfilename)
            print('Modify uitopay.json successfully')

        # 修改paypointui.json
        print('start to modify paypointui.json')
        PaypointUi = "PaypointUi.xlsx"
        if not os.path.exists(self._in_path + "\\" + PaypointUi):
            print("PaypointUi.xlsx does not exist")
        else:
            data = xlrd.open_workbook(self._in_path + "\\" + PaypointUi)
            table = data.sheet_by_index(0)
            jsonfilename = PaypointUi.split('.')[0].lower() + ".json"
            f = codecs.open(jsonfilename, "w", "utf-8")
            f.write(u'{\n\t' + pyutils().getContent(self._in_path + "\\default\\" +
                                                   self._tbuid + "\\Others\\paypointuiConfig.txt") + ',' + '\n\t"paypoints' + '":[')
            for r in range(table.nrows):
                if r > 0:
                    if str(table.cell_value(r, 0)).strip() <> str(table.cell_value(r - 1, 0)).strip():
                        f.write(u'\n\t\t{ ')
                        f.write(u'\n\t\t\t"' + str(table.cell_value(0, 0)).strip() +
                                '": ' + str(int(table.cell_value(r, 0))).strip() + ',')
                        f.write(u'\n\t\t\t"elements": [')
                    f.write(u'\n\t\t\t\t{')
                    for c in range(1, table.ncols):
                        key = str(table.cell_value(0, c)).strip()
                        val = str(table.cell_value(r, c)).strip()
                        try:
                            float(val)
                            temp = ' "' + key + '\": ' + str(int(float(val)))
                        except:
                            temp = ' "' + key + '\": "' + val + '"'
                        f.write(temp)
                        if c < table.ncols - 1:
                            f.write(u',')
                    f.write(u' }')
                    if r < table.nrows - 1 and str(table.cell_value(r, 0)).strip() == str(table.cell_value(r + 1, 0)).strip():
                        f.write(u'')
                    else:
                        f.write(u'\n\t\t\t]')
                        f.write(u'\n\t\t}')
                    if r < table.nrows - 1:
                        f.write(u',')
            f.write(u"\n\t]\n}\n")
            f.close()
            shutil.copy(jsonfilename, (payui_path + "\\" + jsonfilename))
            os.remove(jsonfilename)
            print('Modify paypointui.json successfully')

        # 修改APP Name
        print('start to modify app_name')
        stree = et.parse(self._project_path + "\\res\\values\\strings.xml")
        sroot = stree.getroot()
        sroot[0].attrib['name'] = "app_name"
        sroot[0].text = self._config_data.get_show_app_name()
        stree.write(self._project_path + "\\res\\values\\strings.xml",
                    encoding='utf-8', xml_declaration=True)
        print('modify app_name successfully')

        self.deleteGen()
        print('Push successfully')

    def modifyEncryptedJson(self):
        pay_path = self._in_path + '\\default\\' + self._tbuid
        # pxpayinfo
        print("start to modify pxpayinfo.json")
        if not os.path.exists(self._project_path + "\\assets\\json\\plugin"):
            os.mkdir(self._project_path + "\\assets\\json\\plugin")
        f = open(self._project_path +
                 "\\assets\\json\\plugin\\pxpinfo.json", 'w')
        f.truncate()
        f.write(u'{"appid":"' + str(self._config_data.get_zhimeng_app_id()) +
                '","gameid":"' + str(self._config_data.get_poxiao_game_id()) + '"}')
        f.close()
#         pyutils().encryptJson(self._B_path,project_path + "\\assets\\json\\plugin\\pxpayinfo.json")
        print('Modify pxpayinfo.json successfully')

        # mmplatform
        print("start to modify mmplatform.json")
        shutil.copy(self._in_path + "\\default\\Add_Others\\mmplatform.json",
                    self._project_path + "\\assets\\json\\plugin\\mmplatform.json")
        print("Modify mmplatform.json successfully")

        # iocconfig
        print("start to modify iocconfig.json")
        shutil.copy(self._in_path + "\\default\\Add_Others\\iocconfig.json",
                    self._project_path + "\\assets\\json\\iocconfig.json")
        print("Modify iocconfig.json successfully")

        # pluginconfig
        print("start to modify pluginconfig.json")
        shutil.copy(self._in_path + "\\default\\Add_Others\\pluginconfig.json",
                    self._project_path + "\\assets\\json\\pluginconfig.json")
        print("Modify pluginconfig.json successfully")

        # avosconfig
        print("start to modify avosconfig.json")
        # appInfo = open(self._in_path + "\\default\\" + self._tbuid + "\\Add_Avos\\appInfo.txt", 'r')
        # content = appInfo.read()
        # appInfo.close()
        f = open(self._project_path + "\\assets\\json\\avosconfig.json", 'w')
        f.truncate()
        f.write(u'{"openextendpush":' + self._config_data.get_px_ad() + ',' + u'"appid":"' + str(
            self._config_data.get_avos_app_id()) + '",' + u'"appkey":"' + str(self._config_data.get_avos_app_key()) + '"}')
        f.close()
#         pyutils().encryptJson(self._B_path,project_path + "\\assets\\json\\avosconfig.json")
        print('Modify avosconfig.json successfully')


        # paypoint
        print("start to modify paypoint.json")
        payPoint = "PayPoint.xlsx"
        if not os.path.exists(pay_path + "\\" + payPoint):
            print("PayPoint.xlsx does not exist")
        else:
            data = xlrd.open_workbook(pay_path + "\\" + payPoint)
            table = data.sheet_by_index(0)
            jsonfilename = payPoint.split('.')[0].lower() + ".json"
            f = codecs.open(jsonfilename, "w", "utf-8")
            f.write(u'{\n\t"' + 'paypoint' + '\":[')
            for r in range(1, table.nrows):
                f.write(u'\n\t\t{')
                f.write(' "' + str(table.cell_value(0, 0)).strip() +
                        '": ' + str(int(table.cell_value(r, 0))).strip() + ',')
                f.write(' "' + str(table.cell_value(0, 1)).strip() +
                        '": "' + str(table.cell_value(r, 1)).strip() + '",')
                f.write(' "' + str(table.cell_value(0, 2)).strip() +
                        '": ' + str(int(table.cell_value(r, 2))).strip() + ',')
                f.write(' "' + str(table.cell_value(0, 3)).strip() +
                        '": "' + str(table.cell_value(r, 3)).strip() + '",')
                prop_id_key = str(table.cell_value(0, 4)).strip()
                prop_id_val = str(table.cell_value(r, 4)).strip()
                prop_num_key = str(table.cell_value(0, 5)).strip()
                prop_num_val = str(table.cell_value(r, 5)).strip()
                temp = ''
                if prop_id_val == '' or prop_num_val == '':
                    print "prop_id_val or prop_num_val is null"
                    os.system('pause')
                    pyutils().record(self._dict, '15', 'PayPoint.xlsx中prop_id_val和prop_num_val不存在或数量不匹配')
                    exit(1)
                elif prop_num_val.count(',') == 0 or prop_num_val.count(',') == 0:
                    f.write('"describe": [ { "' + prop_id_key + '": ' + str(int(float(
                        prop_id_val))) + ', "' + prop_num_key + '": ' + str(int(float(prop_num_val))) + ' } ]')
                elif prop_num_val.count(',') <> prop_num_val.count(','):
                    print "not match prop_id_val and prop_num_val"
                    os.system('pause')
                    pyutils().record(self._dict, '15', 'PayPoint.xlsx中prop_id_val和prop_num_val不存在或数量不匹配')
                    exit(1)
                else:
                    temp = temp + \
                        self.string_split(
                            prop_id_key, prop_id_val, prop_num_key, prop_num_val)
                    f.write(temp)
                f.write(u' }')
                if r < table.nrows - 1:
                    f.write(u',')
            f.write(u"\n\t],")
            f.write(u'\n\t"' + str(table.cell_value(0, 6)).strip() +
                    '": ' + str(int(table.cell_value(1, 6))).strip())
            f.write(u'\n}\n')
            f.close()
            shutil.copy(jsonfilename, self._project_path +
                        "\\assets\\json\\" + jsonfilename)
            os.remove(jsonfilename)
#             pyutils().encryptJson(self._B_path,project_path + "\\assets\\json\\" + jsonfilename)
            print('Modify paypoint.json successfully')

        # event2pay
        print("start to modify event2pay.json")
        event2pay = "event2p.xlsx"
        if not os.path.exists(pay_path + "\\" + event2pay):
            print("event2pay.xlsx does not exist")
        else:
            data = xlrd.open_workbook(pay_path + "\\" + event2pay)
            table = data.sheet_by_index(0)
            jsonfilename = event2pay.split('.')[0].lower() + ".json"
            f = codecs.open(jsonfilename, "w", "utf-8")
            f.write(u'{\n\t"' + 'event2p' + '\":[')
            for r in range(1, table.nrows):
                f.write(u'\n\t\t{')
                f.write(' "' + str(table.cell_value(0, 0)).strip() +
                        '": ' + str(int(table.cell_value(r, 0))).strip() + ',')
                f.write(' "' + str(table.cell_value(0, 1)).strip() +
                        '": ' + str(int(table.cell_value(r, 1))).strip() + ',')
                f.write(' "' + str(table.cell_value(0, 2)).strip() +
                        '": "' + str(table.cell_value(r, 2)).strip() + '",')
                f.write(' "' + str(table.cell_value(0, 3)).strip() +
                        '": "' + str(table.cell_value(r, 3)).strip() + '"')
                f.write(u' }')
                if r < table.nrows - 1:
                    f.write(u',')
            f.write(u"\n\t],")
            f.write(u'\n\t"' + str(table.cell_value(0, 6)).strip() +
                    '": ' + str(int(table.cell_value(1, 6))).strip() + ',')
            f.write(u'\n\t"' + str(table.cell_value(0, 7)).strip() +
                    '": ' + str(int(table.cell_value(1, 7))).strip())
            f.write(u'\n}\n')
            f.close()
            shutil.copy(jsonfilename, self._project_path +
                        "\\assets\\json\\" + jsonfilename)
            os.remove(jsonfilename)
#             pyutils().encryptJson(self._B_path,project_path + "\\assets\\json\\" + jsonfilename)
            print('Modify event2pay.json successfully')

        # payconfig
        print("start to modify payconfig.json")
        f = open(self._project_path + "\\assets\\json\\pconfig.json", 'w')
        f.truncate()
        content = '"P_SEQ_CM":"' + self._config_data.get_PAY_SEQ_CM() + '","P_SEQ_CT":"' + self._config_data.get_PAY_SEQ_CT() + \
            '","P_SEQ_CU":"' + self._config_data.get_PAY_SEQ_CU() + '","P_SEQ_DEFAULT":"' + \
            self._config_data.get_PAY_SEQ_DEFAULT() + '"'
        f.write(u'{\n\t"pconfig":[\n\t\t{ ' + content + ', "DEFAULT_P_LISTS": "' + self._config_data.get_plugin_lists() + '","APPID":"' + str(
            self._config_data.get_zhimeng_app_id()) + '","GAMEID":"' + str(self._config_data.get_poxiao_game_id()) + '" }')
        f.write(u'\n\t]\n}')
        f.close()
#         pyutils().encryptJson(self._B_path,project_path + "\\assets\\json\\payconfig.json")
        print('Modify payconfig.json successfully')

        # paytosp
        print("start to modify paytosp.json")
        paytosp = "paytosp.xlsx"
        if not os.path.exists(pay_path + "\\" + paytosp):
            if os.path.exists(self._project_path + "\\assets\\json\\paytosp.json"):
                os.remove(self._project_path + "\\assets\\json\\paytosp.json")
            print("paytosp.xlsx does not exist")
        else:
            data = xlrd.open_workbook(pay_path + "\\" + paytosp)
            table = data.sheet_by_index(0)
            jsonfilename = paytosp.split('.')[0].lower() + ".json"
            f = codecs.open(jsonfilename, "w", "utf-8")
            f.write(u'{\n\t"' + 'paytosp' + '\":[')
            for r in range(1, table.nrows):
                f.write(u'\n\t\t\t\t{')
                for c in range(table.ncols):
                    key = str(table.cell_value(0, c)).strip()
                    val = str(table.cell_value(r, c)).strip()
                    temp = ' "' + key + '\": "' + val + '"'
                    f.write(temp)
                    if c < table.ncols - 1:
                        f.write(u',')
                    else:
                        f.write(u' }')
                if r < table.nrows - 1:
                    f.write(u',')
            f.write(u"\n\t]\n}\n")
            f.close()
            shutil.copy(jsonfilename, self._project_path +
                        "\\assets\\json\\" + jsonfilename)
            os.remove(jsonfilename)
#             pyutils().encryptJson(self._B_path,project_path + "\\assets\\json\\" + jsonfilename)
            print('Modify paytosp.json successfully')

        # skypayinfo {"appid":"","merchantpasswd":"","merchantid":""}
        if "1020" in self._plugin_ids:
            print("start to modify skypayinfo.json")

            if not os.path.exists(self._project_path + "\\assets\\json\\plugin"):
                os.mkdir(self._project_path + "\\assets\\json\\plugin")
            f = open(self._project_path +
                     "\\assets\\json\\plugin\\spinfo.json", 'w')
            f.truncate()
            f.write(u'{"appid":"' + str(self._config_data.get_zhimeng_app_id()) + '",' + '"merchantpasswd":"' +
                    self._config_data.get_zhimeng_merchant_passwd() + '","merchantid":"' + self._config_data.get_zhimeng_merchant_id() + '"' + '}')
            f.close()
#                 pyutils().encryptJson(self._B_path,project_path + "\\assets\\json\\plugin\\skypayinfo.json")
            print('Modify skypayinfo.json successfully')
        else:
            if os.path.exists(self._project_path + "\\assets\\json\\plugin\\spinfo.json"):
                os.remove(self._project_path +
                          "\\assets\\json\\plugin\\spinfo.json")
        # cmmmpayinfo
#         print("start to modify cmmmpayinfo.json")
#         f = open(project_path + "\\assets\\json\\plugin\\cmmmpayinfo.json", 'w')
#         f.truncate()
#         f.write(u'{"appid":"300009213300","appkey":"FCCF24EC62E5233AF0649A6C705F827A"}')
#         f.close()
#         pyutils().encryptJson(self._B_path,project_path + "\\assets\\json\\plugin\\cmmmpayinfo.json")
#         print('Modify cmmmpayinfo.json successfully')
            # 加密
        if self._debug_model == "false":
            filelist = os.listdir(self._project_path + "\\assets\\json")
            for i in filelist:
                if i.endswith(".json"):
                    print "json/" + i
                    pyutils().encryptJson(self._B_path, self._project_path + "\\assets\\json\\" + i)
        filelist = os.listdir(self._project_path + "\\assets\\json\\plugin")
        for i in filelist:
            print i
            pyutils().encryptJson(self._B_path, self._project_path + "\\assets\\json\\plugin\\" + i)

    def string_split(self, prop_id_key, prop_id_val, prop_num_key, prop_num_val):
        prop_id_vals = prop_id_val.split(',')
        prop_num_vals = prop_num_val.split(',')
        i = 0
        s = ' "describe": ['
        for l in prop_id_vals:
            temp = ' { "' + prop_id_key + '": ' + str(int(
                prop_id_vals[i])) + ', "' + prop_num_key + '": ' + str(int(prop_num_vals[i])) + ' }'
            s = s + temp
            i = i + 1
            if i < len(prop_id_vals):
                s = s + ','
            else:
                s = s + ' ]'
        return s

    def replaceXml(self):
        print("start to modify manifest.xml")
        isTbuId = False
        fileXml = self._project_path + "\\AndroidManifest.xml"
        print fileXml
        dom = minidom.parse(fileXml)
        root = dom.documentElement

        for node in dom.getElementsByTagName('manifest'):
            node.setAttribute("android:versionCode", str(
                self._config_data.get_game_version()))
            node.setAttribute("android:versionName",
                              self._config_data.get_game_show_version().strip())

        for node in root.getElementsByTagName('meta-data'):
            if node.getAttribute("android:name") == "lltt_merchantid":
                node.setAttribute(
                    "android:value", self._config_data.get_letu_merchant_id())
            elif node.getAttribute("android:name") == "lltt_mappid":
                node.setAttribute("android:value", str(
                    self._config_data.get_letu_app_id()))
            elif node.getAttribute("android:name") == "ZMAppId":
                node.setAttribute("android:value", str(
                    self._config_data.get_zhimeng_app_id()))
            elif node.getAttribute("android:name") == "debug_model":
                node.setAttribute("android:value", "false")
                print 'self._debug_model=' + self._debug_model
            elif node.getAttribute("android:name") == "tbu_id":
                node.setAttribute("android:value", str(
                    self._config_data.get_tbu_id()))
                isTbuId = True
        savefile = open(fileXml, 'w')
        dom.writexml(savefile)
        savefile.close()
        if isTbuId is False:
            manifestXml = open(fileXml, 'r')
            content = manifestXml.read()
            manifestXml.close()
            pos = content.find("</application>")
            content = pyutils().modifyXML(fileXml, -1, '', u'\t\t<meta-data android:name="tbu_id" android:value="' +
                                         self._tbuid + '"/>', content, pos, 'true')

        print("modify modify manifest.xml successfully")

    def deleteGen(self):
        if os.path.exists(self._project_path + "\\gen"):
            shutil.rmtree(self._project_path + "\\gen")
        print('add PayPlugin successfully')

    def compare(self, x, y):
        stat_x = os.stat(self.fromDir + "\\" + x)
        stat_y = os.stat(self.fromDir + "\\" + y)
        if stat_x.st_ctime < stat_y.st_ctime:
            return -1
        elif stat_x.st_ctime > stat_y.st_ctime:
            return 1
        else:
            return 0

    def moveJar(self, head, toDir, fromDir):
        self.fromDir = fromDir
        # 先删掉B/libs下head为头的jar包
        self.deleteJar(head, toDir)
        filelist = os.listdir(fromDir)
        # 只将符合head要求的最后一个生成的jar包导入到指定目录
        filelist.sort(self.compare)
        for i in filelist:
            tt_match = re.search(head + '*', i)
            if tt_match:
                if not os.path.exists(toDir + "\\" + i):
                    shutil.copyfile(fromDir + "\\" + i, toDir + "\\" + i)
                break

    def deleteJar(self, head, toDir):
        filelist = os.listdir(toDir)
        filelist.sort()
        for i in filelist:
            tt_match = re.search(head + '*', i)
            if tt_match:
                print i
                if os.path.exists(toDir + "\\" + i):
                    os.remove(toDir + "\\" + i)

    def modifyDependence(self):
        print "start to modify dependence "
        project_properties_path = self._project_path + "\\project.properties"
        project_properties_path1 = self._project_path + "\\project1.properties"
        infile = open(project_properties_path, 'r')
        outfile = open(project_properties_path1, 'w')
        lib_num = 0
        lib_name_list = []
        for i in range(len(self._config_data.get_other_libraries())):
            fileXml = self._dst_path + '\\D' + str(i) + '\\.project'
            dom = minidom.parse(fileXml)
            root = dom.documentElement
            itemlist = root.getElementsByTagName('name')
            item = itemlist[0]
            lib_name_list.append(item.firstChild.data)
        print lib_name_list
        for line in infile:
            if "android.library.reference" in line:
                print line
                print lib_num
                print len(lib_name_list)
                if lib_num == len(lib_name_list):
                    outfile.write("\nandroid.library.reference." +
                                  str(lib_num + 1) + "=" + '../B')
                else:
                    outfile.write("\nandroid.library.reference." +
                                  str(lib_num + 1) + "=" + '../D' + str(lib_num))
                lib_num += 1
            else:
                outfile.write(line)
        infile.close()
        outfile.close()
        os.remove(project_properties_path)
        os.rename(project_properties_path1, project_properties_path)
        print "modify dependence successfully"


    def copythisFiles(self,sourceDir, targetDir): 
        for f in os.listdir(sourceDir):
            sourceF = os.path.join(sourceDir, f)  
            targetF = os.path.join(targetDir, f)  
            if os.path.isfile(sourceF):   
                #创建目录   
                if not os.path.exists(targetDir):   
                    os.makedirs(targetDir)                 
                #文件不存在，或者存在但是大小不同，覆盖   
                if not os.path.exists(targetF) or (os.path.exists(targetF) and (os.path.getsize(targetF) != os.path.getsize(sourceF))):   
                    #2进制文件  
                    open(targetF, "wb").write(open(sourceF, "rb").read())   ; 

            if os.path.isdir(sourceF):   
                self.copythisFiles(sourceF, targetF)
            