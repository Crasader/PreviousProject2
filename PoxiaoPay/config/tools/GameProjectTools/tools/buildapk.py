# -*- coding: cp936 -*-
import os
import shutil
import re
from xml.dom import minidom
import sys
import time
import xlrd
reload(sys)
sys.setdefaultencoding( "utf-8" )


versionCode = "11"
versionName = "1.2.1"
project_path = "E:\\PoxiaoMoneyGame\\CatchFish_3"
enterId_path = ".\\in\\Entid.xlsx"
save_file = "E:\\apk"
gamepayplugin_px = ".\\in\\"
#projectName = "JumpGame"

#下面变量不用修改
androidManifest_xml = project_path+"\\AndroidManifest.xml"
gameinfo_px = project_path+"\\assets\\gameinfo.px"
apk_path = project_path+"\\bin"
ZYF_ChannelID = project_path+"\\assets\\ZYF_ChannelID"
build_path = project_path+"\\build.xml"
    
def replaceXml(fileXml, enterId, versionCode, versionName):
    dom = minidom.parse(fileXml)
    root = dom.documentElement
    for node in dom.getElementsByTagName('manifest'):
        node.setAttribute("android:versionCode", versionCode)
        node.setAttribute("android:versionName", versionName)
        
    for node in root.getElementsByTagName('meta-data'):
        if node.getAttribute("android:name")=="Channel ID":
            node.setAttribute("android:value", enterId)
        if node.getAttribute("android:name")=="Spr_ChannelId":
            node.setAttribute("android:value", enterId)
        if node.getAttribute("android:name")=="switch_app_channel_id":
            node.setAttribute("android:value", enterId)
        if node.getAttribute("android:name")=="oc_channel_id":
            node.setAttribute("android:value", enterId)
        if node.getAttribute("android:name")=="UMENG_CHANNEL":
            node.setAttribute("android:value", enterId)

    savefile = open(fileXml, 'w')
    dom.writexml(savefile)
    savefile.close()

def replaceGameinfo(filePx, enterId):
    f = open(filePx, 'w')
    f.truncate()
    f.write("ENTER_ID=")
    f.write(enterId)
    f.close

    f = open(ZYF_ChannelID, 'w')
    f.truncate()
    f.write(enterId)
    f.close

def outApk(v):
    dom = minidom.parse(build_path)
    for node in dom.getElementsByTagName('project'):
       projectName = node.getAttribute("name")
    old_apk = projectName+"-"+versionCode+"-"+versionName+"-release.apk"
    new_apk = save_file+"\\"+projectName+"-" + versionCode+"-"+v+"-"+ time.strftime('%Y%m%d',time.localtime(time.time()))+".apk"
    os.chdir(project_path)
    os.system('ant')
    os.chdir(apk_path)
    shutil.move(old_apk, new_apk)

def readEnterId(fn):
    ids = []
    data = xlrd.open_workbook(fn)
    table = data.sheet_by_index(0)
    for r in range(1,table.nrows):
        try:
            val = str(int(table.cell_value(r,0)))
        except:
            val = str(table.cell_value(r,0)).strip()
        ids.append(val)
    
    return ids;

def replaceGamepayplugin(filePx, project_path):
    try:
        if os.path.exists(filePx):
            shutil.copy(filePx, (project_path+"\\assets\\gamepayplugin.px")) 
        else:
            print("no "+filePx)
    except:
        print("load error: "+filePx)

if __name__ == "__main__":
    try:
        if os.path.exists(save_file):
            shutil.rmtree(save_file)   
    finally:
        os.mkdir(save_file)       
        enterIds = readEnterId(enterId_path)
        for v in enterIds:
            print("build start apk: "+v)
            replaceXml(androidManifest_xml, v, versionCode, versionName)
            replaceGameinfo(gameinfo_px, v)
            replaceGamepayplugin(gamepayplugin_px+"\\gamepayplugin.px", project_path)
            outApk(v)
        
        
