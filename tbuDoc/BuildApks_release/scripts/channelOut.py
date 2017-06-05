# -*- coding: UTF-8 -*-
from xml.dom import minidom
from tools.pyutils import pyutils
import os
import shutil
import time
import json
from configData import configData


class channelOut:
    _config_data = configData()
    _output_name = ''
    _project_path = ''
    _save_path = ''
    _in_path = ''
    _b_project_path=''

    def __init__(self, config_data, **dict_local):
        self._config_data = config_data
        self._in_path = config_data.get_config_files_path()
        self._project_path = config_data.get_dst_path() + "\\A"
        self._output_name = config_data.get_output_name()
        self._save_path = config_data.get_save_path()
        self._b_project_path = config_data.get_dst_path() + "\\B"
        # os.popen("javac -d classes src/*.java src/inner/*.java" )
        os.system("%s %s %s"%(self._in_path+"\\stringtool\\encry.bat",self._in_path+"\\stringtool\\StringEncoder.jar",self._b_project_path+"\\src\\d\\b"))
        os.system("%s %s %s"%(self._in_path+"\\pictool\\sss.bat",self._in_path+"\\pictool\\encriptPng.jar",self._project_path+"\\assets\\pui"))
        # os.chdir(self._b_project_path + "\\src\\b\\a\\impl")
        # os.system("javac GamePImpl.java")


        for i in range(len(config_data.get_special_data())):
            channel_id = config_data.get_special_data()[i].get_channel_id()
            zhang_qd = config_data.get_special_data()[i].get_zhang_qd()
            uuc_own_channel = config_data.get_special_data()[i].get_uuc_own_channel()
            log= pyutils().getpwd()+"/log.txt"
            log_path=open(log,'a')
            log_path.write('\npackage '+ str(i) +' info:')
            log_path.write('\n\tchannel_id:'+channel_id)
            log_path.write('\n\tzhang_qd:'+zhang_qd)
            log_path.write('\n\uuc_own_channel:'+uuc_own_channel)
            log_path.write('\n\tletu_uikey:'+self._config_data.get_special_data()[i].get_letu_key())
            log_path.close()
            self.configureLetuJson(i)
            self.configureZhangJson(zhang_qd,i) 
            self.configureUUCJson(uuc_own_channel,i)
            self.configureWechatJson(i)  
            self.addYoutouAd(config_data.get_special_data()[i])
            self.addOuxinAd()
            self.changeChannelId(channel_id)
            apk_name = self.outApk(config_data.get_special_data()[i])
            os.chdir(self._in_path+"\\apkSignModifyer\\")
            if  os.path.exists(self._save_path + "\\" + self._config_data.get_client_order_id()+'\\newsign') is False:
                os.mkdir(self._save_path + "\\" +self._config_data.get_client_order_id()+'\\newsign')
            os.system("%s %s %s %s"%(self._in_path+"\\apkSignModifyer\\apkResModifyerCMD-random-python.bat",self._in_path+"\\apkSignModifyer\\apkResModifyer.jar",self._save_path + "\\" +self._config_data.get_client_order_id(),self._save_path + "\\" +self._config_data.get_client_order_id()+'newsign'))
        pyutils().record(dict_local, "0", '打包成功')
#         self.deleteProjectCopy()
        print "Congratulations!"

    def deleteProjectCopy(self):
        shutil.rmtree(self._config_data.get_dst_path())

    def configureLetuJson(self, i):
        print i
        # letupayinfo
        # {"appid":"","merchantKey":"","merchantid":"","showuikey":"","appname":""}
        if "1030" in self._config_data.get_plugin_lists():
            print("start to modify letupayinfo.json")
            f = open(self._project_path +
                     "\\assets\\json\\plugin\\ltpinfo.json", 'w')
            f.truncate()
            f.write(u'{"appid":"' + str(self._config_data.get_letu_app_id()) + '",' + '"merchantKey":"' + self._config_data.get_letu_merchant_key() +
                    '","merchantid":"' + self._config_data.get_letu_merchant_id() + '" ,"showuikey":"' + self._config_data.get_special_data()[i].get_letu_key() + '"}')
            f.close()
            pyutils().encryptJson(self._config_data.get_b_up_path(),
                                 self._project_path + "\\assets\\json\\plugin\\ltpinfo.json")
            print('Modify letupayinfo.json successfully')
        else:
            if os.path.exists(self._project_path + "\\assets\\json\\plugin\\ltpinfo.json"):
                os.remove(self._project_path +"\\assets\\json\\plugin\\ltpinfo.json")


    def configureZhangJson(self, zhang_qd,i):
        print i
        # letupayinfo
        # {"appid":"","merchantKey":"","merchantid":"","showuikey":"","appname":""}
        if "1050" in self._config_data.get_plugin_lists():
            print("start to modify zhangpayinfo.json")
            if(zhang_qd =='NA'):
                print "zhangpayinfo qd is null."
                pyutils().record(dict_local,'23', '没有填写正确的掌支付渠道号')
                exit(1)
            f = open(self._project_path + "\\assets\\json\\plugin\\zbaseinfo.json", 'w')
            f.truncate()
            f.write(u' {"zinfo":{"key":"' + self._config_data.get_zhang_key() + '",' + '"appId":"' + str(self._config_data.get_zhang_app_id()) +
                    '","channelId":"' + self._config_data.get_zhang_channel_id() + '" ,"qd":"' + zhang_qd +'"}}')
            f.close()
            pyutils().encryptJson(self._config_data.get_b_up_path(),
                                 self._project_path + "\\assets\\json\\plugin\\zbaseinfo.json")
            print('Modify letupayinfo.json successfully')
        else:
            if os.path.exists(self._project_path + "\\assets\\json\\plugin\\zbaseinfo.json"):
                os.remove(self._project_path +"\\assets\\json\\plugin\\zbaseinfo.json")

    def configureUUCJson(self, uuc_own_channel,i):
        print i
        # uucunpayinfo
        # {"uucpayinfo":{"merchant_key":"aIoTGHPxhdLEPupLtKjJbiZFmVAWCLyt","secret_key":"tCTuG0","own_channel":"true"}}
        if "1060" in self._config_data.get_plugin_lists():
            print("start to modify uucunpayinfo.json")
            if(uuc_own_channel =='NA'):
                print "uucunpayinfo own_channel is null."
                pyutils().record(dict_local,'24', '没有填写正确的悠悠村own_channel')
                exit(1)
            f = open(self._project_path + "\\assets\\json\\plugin\\uucunpayinfo.json", 'w')
            f.truncate()
            print"---------------------get_uuc_merchant_key:"+self._config_data.get_uuc_merchant_key()
            f.write(u' {"uucpayinfo":{"merchant_key":"' + self._config_data.get_uuc_merchant_key() + '",' + '"secret_key":"' + str(self._config_data.get_uuc_secret_key()) +
                    '" ,"own_channel":"' + uuc_own_channel +'"}}')
            f.close()
            pyutils().encryptJson(self._config_data.get_b_up_path(),
                                 self._project_path + "\\assets\\json\\plugin\\uucunpayinfo.json")
            print('Modify uucunpayinfo.json successfully')
        else:
            if os.path.exists(self._project_path + "\\assets\\json\\plugin\\uucunpayinfo.json"):
                os.remove(self._project_path +"\\assets\\json\\plugin\\uucunpayinfo.json")

    def configureWechatJson(self, i):
        print i
        # wexininfo
        # {"appId":"wx884476f603eeb8be","partnerId":"1318535301"}
        if "1070" in self._config_data.get_plugin_lists():
            print("start to modify weixininfo.json")
            f = open(self._project_path +
                     "\\assets\\json\\wx\\wexininfo.json", 'w')
            f.truncate()
            f.write(u'{"appId":"' + str(self._config_data.get_wechat_app_id()) + '",' + '"partnerId":"' + self._config_data.get_wechat_merchant_id() + '"}')
            f.close()
            pyutils().encryptJson(self._config_data.get_b_up_path(),
                                 self._project_path + "\\assets\\json\\wx\\wexininfo.json")
            print('Modify wexininfo.json successfully')
        else:
            if os.path.exists(self._project_path + "\\assets\\json\\wx\\wexininfo.json"):
                os.remove(self._project_path +"\\assets\\json\\wx\\wexininfo.json")

    def changeChannelId(self, channel_id):
        print("start to modify channel id in manifest.xml")
        fileXml = self._project_path + "\\AndroidManifest.xml"
        isAvosChannelId = False
        dom = minidom.parse(fileXml)
        root = dom.documentElement

        for node in root.getElementsByTagName('meta-data'):
            if node.getAttribute("android:name") == "Channel ID":
                isAvosChannelId = True
                node.setAttribute("android:value", channel_id)
            elif node.getAttribute("android:name") == "lltt_cpchannelid":
                node.setAttribute("android:value", channel_id)

            if node.getAttribute("android:name") == "UMENG_CHANNEL":
                node.setAttribute("android:value", channel_id)

        if isAvosChannelId is False:
            manifestXml = open(fileXml, 'r')
            content = manifestXml.read()
            manifestXml.close()
            pos = content.find("</application>")
            content = pyutils().modifyXML(fileXml, -1, '',
                                         '<meta-data android:name="Channel ID" android:value="' + channel_id + '"/>', content, pos, 'true')

        savefile = open(fileXml, 'w')
        dom.writexml(savefile)
        savefile.close()
        print("modify modify EnterId in manifest.xml successfully")
        print("start to modify ZYF_ChannelID")
        ZYF_ChannelID_path = self._project_path + "\\assets\\ZYF_ChannelID"
        if os.path.exists(ZYF_ChannelID_path):
            f = open(ZYF_ChannelID_path, 'w')
            f.truncate()
            f.write(channel_id)
            f.close()
        print("modify ZYF_ChannelID successfully")

    def outApk(self, spe_data):
        print('start to change package name')
        build_path = self._project_path + "\\build.xml"
        apk_path = self._project_path + "\\bin"
        dom = minidom.parse(build_path)
        root = dom.documentElement
        for node in dom.getElementsByTagName('project'):
            projectName = node.getAttribute("name")
        for node in root.getElementsByTagName('property'):
            if node.getAttribute("name") == "gb.newpackage":
                node.setAttribute("value", spe_data.get_package_name())
        print('change package name successfully')
        savefile = open(build_path, 'w')
        dom.writexml(savefile)
        savefile.close()
        old_apk = projectName + "-release.apk"
        new_apk = self._save_path + "\\" + self._config_data.get_client_order_id() + "\\" + self._output_name + \
            "-" + spe_data.get_channel_id() +"-"+str(self._config_data.get_game_show_version())+ "-" + time.strftime('%Y%m%d%H%M',time.localtime()) + ".apk"
        os.chdir(self._project_path)
        os.system('ant')
        os.chdir(apk_path)
        if os.path.exists(self._save_path + "\\" + self._config_data.get_client_order_id()) is False:
            os.mkdir(self._save_path + "\\" +self._config_data.get_client_order_id())
        shutil.copyfile(old_apk, new_apk)
        return new_apk

    def addOuxinAd(self):
        manifestXml = open(self._project_path + "\\AndroidManifest.xml", 'r')
        content = manifestXml.read()
        manifestXml.close()
        pos = content.find("</manifest>")
        startNO = content.find("<!-- OX permission start -->")
        if self._config_data.get_ox_ad() == 'true':
            print ''
            # if not os.path.exists(self._config_data.get_dst_path() + "\\B\\libs\\core.jar"):
            #     shutil.copyfile(self._in_path + "\\default\\Add_OX\\libs\\core.jar",
            #                     self._config_data.get_dst_path() + "\\B\\libs\\core.jar")
            # if not os.path.exists(self._config_data.get_dst_path() + "\\B\\libs\\armeabi\\liblive.so"):
            #     shutil.copyfile(self._in_path + "\\default\\Add_OX\\libs\\armeabi\\liblive.so",
            #                     self._config_data.get_dst_path() + "\\B\\libs\\armeabi\\liblive.so")
            # if startNO == -1:
            #     content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, '<!-- OX permission end -->',
            #                                  pyutils().getContent(self._in_path + "\\default\\Add_OX\\manifest_permission.txt"), content, pos, "true")
            #     pos1 = content.find('</application>')
            #     startNO = content.find("<!-- OX plugin start -->")
            #     content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- OX plugin end -->", pyutils().getContent(self._in_path +
            #                                                                                                                                       "\\default\\" + self._config_data.get_tbu_id() + "\\Add_OX\\manifest_application.txt"), content, pos1, "true")
        else:
            if os.path.exists(self._config_data.get_dst_path() + "\\B\\libs\\core.jar"):
                os.remove(self._config_data.get_dst_path() +
                          "\\B\\libs\\core.jar")
            if os.path.exists(self._config_data.get_dst_path() + "\\B\\libs\\armeabi\\liblive.so"):
                os.remove(self._config_data.get_dst_path() +
                          "\\B\\libs\\armeabi\\liblive.so")
            if startNO != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                             startNO, "<!-- OX permission end -->", "", content, pos, "false")
                pos1 = content.find("</application>")
                startNO_Permission = content.find("<!-- OX plugin start -->")
                if startNO_Permission != -1:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_Permission, "<!-- OX plugin end -->", "", content, pos1, "false")

    def addYoutouAd(self, spe_data):
        manifestXml = open(self._project_path + "\\AndroidManifest.xml", 'r')
        content = manifestXml.read()
        manifestXml.close()
        pos = content.find("</manifest>")
        startNO = content.find("<!-- UU permission start -->")
        if self._config_data.get_yt_ad() == 'true':
            if not os.path.exists(self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_UU\\porting_pkg_" + spe_data.get_package_name() + "\\uu_release.jar"):
                print self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_UU\\porting_pkg_" + spe_data.get_package_name() + "\\uu_release.jar" + " dose not exist."
                pyutils().record('17', '优投对应包名所需的文件不存在')
                exit(1)
            shutil.copyfile(self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_UU\\porting_pkg_" +
                            spe_data.get_package_name() + "\\uu_release.jar", self._config_data.get_dst_path() + "\\B\\libs\\uu_release.jar")
            if not os.path.exists(self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_UU\\porting_pkg_" + spe_data.get_package_name() + "\\uuconfig.json"):
                print self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_UU\\porting_pkg_" + spe_data.get_package_name() + "\\uuconfig.json" + " dose not exist."
                pyutils().record('17', '优投对应包名所需的配置文件不存在')
                exit(1)
            shutil.copyfile(self._in_path + "\\default\\" + self._config_data.get_tbu_id() + "\\Add_UU\\porting_pkg_" +
                            spe_data.get_package_name() + "\\uuconfig.json", self._project_path + "\\assets\\json\\uuconfig.json")
            pyutils().encryptJson(self._config_data.get_b_up_path(), self._project_path + "\\assets\\json\\uuconfig.json")
            if startNO == -1:
                pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, '<!-- UU permission end -->',
                                   pyutils().getContent(self._in_path + "\\default\\Add_UU\\manifest_permission.txt"), content, pos, "true")
                pos1 = content.find('</application>')
                startNO = content.find("<!-- UU start -->")
                pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml", startNO, "<!-- UU end -->", pyutils().getContent(self._in_path + "\\default\\" +
                                                                                                                                 self._config_data.get_tbu_id() + "\\Add_UU\\porting_pkg_" + spe_data.get_package_name() + "\\manifest_application.txt"), content, pos1, "true")
        else:
            if os.path.exists(self._config_data.get_dst_path() + "\\B\\libs\\uu_release.jar"):
                os.remove(self._config_data.get_dst_path() +
                          "\\B\\libs\\uu_release.jar")
            if os.path.exists(self._config_data.get_dst_path() + "\\B\\libs\\uuconfig.json"):
                os.remove(self._config_data.get_dst_path() +
                          "\\B\\libs\\uuconfig.json")
            if startNO != -1:
                content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                             startNO, "<!-- UU permission end -->", "", content, pos, "false")
                pos1 = content.find("</application>")
                startNO_Permission = content.find("<!-- UU start -->")
                if startNO_Permission != -1:
                    content = pyutils().modifyXML(self._project_path + "\\AndroidManifest.xml",
                                                 startNO_Permission, "<!-- UU end -->", "", content, pos1, "false")
