# -*- coding: utf-8 -*-
import os
import shutil
import re
import xlrd
import codecs
import sys
import time
import MySQLdb
from xml.dom import minidom

import xml.etree.ElementTree as et
reload(sys)
sys.setdefaultencoding( "utf-8" )

GAME_NAME = ""              #游戏名称
APP_NAME = ""               #游戏显示名称
PACKAGE_NAME = ""           #包名
GAMEID = ""                 #GAMEID
VERSION_CODE = ""           #版本号（数字）
VERSION_NAME = ""           #版本显示信息
OPEN_EXTEND_PUSH = ""       #push开关
OPEN_OUXIN = ""             #欧昕广告开关
RECORD_GAME_DETAIL = ""     #游戏记录开关
DEFAULT_GAME_PLGIN = ""     #默认支付
LETU_APPID = ""             #Letu支付appId
LETU_UIKEY = ""             #Letu支付UiKey
SKY_APPID = ""              #Sky支付appId
PERMISION = ""              #限制权限
DEMANDER = ""               #申请人
PROJECT_NAME = ""           #主工程名
TBUCLOUDFOR_WHO = ""
WITH_COCO = ""
PLUGINIDS = ""
GAMENAMEID = ""

#请修改以下路径
base_path = "D:\\WinneShen\\Workspace\\PoxiaoMoneyGame"
save_file = "D:\\apks1"
B_path = "D:\\WinneShen\\Workspace\\PoxiaoMoneyGame\\B"
appconfig_path = "D:\\WinneShen\\Workspace\\TbuPay\\AppConfig"
OUXIN_path = "C:\\Users\\Administrator\\Desktop\\ouxin-v432_0625_poxiao"#请将欧昕广告文件夹名称禁止出现中文，并把每个游戏的bat名称改为工程名，如捕鱼为CatchFish_3.bat
PLUGINIDS = '2,3,4'

OPEN_EXTEND_PUSH = ""
RECORD_GAME_DETAIL = ""
Letu_appId = ""
Sky_appId = ""

def ReadGameInfo(xls_path):
    #全局变量
    global GAME_NAME 
    global APP_NAME 
    global PACKAGE_NAME
    global GAMEID
    global VERSION_CODE
    global VERSION_NAME
    global OPEN_EXTEND_PUSH
    global OPEN_OUXIN
    global RECORD_GAME_DETAIL
    global DEFAULT_GAME_PLGIN
    global LETU_APPID
    global LETU_UIKEY
    global SKY_APPID
    global PERMISSION
    global DEMANDER
    global PROJECT_NAME
    global TBUCLOUDFOR_WHO
    global WITH_COCO
    #global PLUGINIDS
    global GAMENAMEID

    print("start to read gameinfo")
    db = MySQLdb.connect(host="172.23.1.101",user="root",passwd="123456",db="gamedb",charset="utf8" )
    cursor = db.cursor()
    
    data = xlrd.open_workbook(xls_path)
    table = data.sheet_by_index(0)
    
    GAME_NAME           = str(table.cell_value(1,1)).strip()
    APP_NAME            = str(table.cell_value(2,1)).strip()
    PACKAGE_NAME        = str(table.cell_value(3,1)).strip()
    #GAMEID              = str(int(table.cell_value(4,1))).strip()
    VERSION_CODE        = str(int(table.cell_value(4,1))).strip()
    VERSION_NAME        = str(table.cell_value(5,1)).strip()
    OPEN_EXTEND_PUSH    = str(table.cell_value(6,1)).strip()
    OPEN_OUXIN          = str(table.cell_value(7,1)).strip()
    RECORD_GAME_DETAIL  = str(table.cell_value(8,1)).strip()
    DEFAULT_GAME_PLGIN  = str(table.cell_value(9,1)).strip()
    #LETU_APPID          = str(int(table.cell_value(11,1))).strip()
    #LETU_UIKEY          = str(table.cell_value(12,1)).strip()
    #SKY_APPID           = str(int(table.cell_value(13,1))).strip()
    PERMISSION          = str(table.cell_value(10,1)).strip()
    DEMANDER            = str(table.cell_value(11,1)).strip()
    
    # SQL 查询语句
    try:
        sql = "SELECT * FROM gameinfo WHERE gamename = '"+GAME_NAME+"';"
        print("GAME_NAME:"+GAME_NAME)
    
        cursor.execute(sql)
        # print(cursor)
        results = cursor.fetchall()
        print(results)
        if results:
            for row in results:
                PROJECT_NAME = row[1]
                TBUCLOUDFOR_WHO = row[2]
                WITH_COCO = str(row[3])
                GAMEID = row[4]
                LETU_APPID = row[5]
                SKY_APPID = row[6]
                GAMENAMEID = str(row[7])
        else:
            print("no this game name in the database")
            sys.exit(0)
        select = "select * from "+PROJECT_NAME+" where packagename = '"+PACKAGE_NAME+"'"
        print(select)
        cursor.execute(select)
        results = cursor.fetchall()
        print(results)
        if results:
            for row in results:
                LETU_UIKEY = row[1]
            print("LETU_UIKEY=========================>"+LETU_UIKEY)
        else:
            print("no this package name in the database")
            sys.exit(0)
        db.commit()
           
    except:
        print "Error!"
        sys.exit(0)
        
    db.close()

        
def changeUitopay(payui_path,in_path):
    uitopay="UiToPay.xlsx"
    data = xlrd.open_workbook(in_path+"\\"+uitopay)
    table = data.sheet_by_index(0)
    table_name = table.name
    
    jsonfilename = uitopay.split('.')[0]+".json"
    #print fn.split('.')[0]
    f = codecs.open(jsonfilename, "w", "utf-8")
    f.write(u'{\n\t"'+'uipoints'+'\":[')
    for r in range(1,table.nrows):         
        f.write(u'\n\t\t\t\t{')
        for c in range(table.ncols):
            key = str(table.cell_value(0,c)).strip()
            val = str(table.cell_value(r,c)).strip()
            try:
                float(val)
                #print str(int(float(val)))
                temp = ' "'+key+'\": '+str(int(float(val)))
            except:
                temp = ' "'+key+'\": "'+val+'"'
            f.write(temp)
            if c<table.ncols-1:
                f.write(u',')
            else:
                f.write(u' }')
        if r<table.nrows-1:
                f.write(u',')
    f.write(u"\n\t]\n}\n")
    f.close()      
    shutil.copy(jsonfilename, payui_path+"\\"+jsonfilename)
    os.remove(jsonfilename)
    
def changePaypointUi(payui_path,paypointUi_path):
    PaypointUi = "PaypointUi.xlsx"
    data = xlrd.open_workbook(paypointUi_path+"\\"+PaypointUi)
    table = data.sheet_by_index(0)
    table_name = table.name

    jsonfilename = PaypointUi.split('.')[0]+".json"
    #print jsonfilename
    f = codecs.open(jsonfilename, "w", "utf-8")
    f.write(u'{\n\t"'+'paypoints'+'\":[')
    for r in range(table.nrows):
        if r>0:         
            if str(table.cell_value(r,0)).strip()<>str(table.cell_value(r-1,0)).strip():
                f.write(u'\n\t\t{ ')
                f.write(u'\n\t\t\t"'+str(table.cell_value(0,0)).strip()+'": '+str(int(table.cell_value(r,0))).strip()+',')
                f.write(u'\n\t\t\t"elements": [')
            f.write(u'\n\t\t\t\t{')
            for c in range(1,table.ncols):
                key = str(table.cell_value(0,c)).strip()
                val = str(table.cell_value(r,c)).strip()
                try:
                    float(val)
                    #print str(int(float(val)))
                    temp = ' "'+key+'\": '+str(int(float(val)))
                except:
                    temp = ' "'+key+'\": "'+val+'"'
                f.write(temp)
                if c<table.ncols-1:
                    f.write(u',')
            f.write(u' }')
            if r<table.nrows-1 and str(table.cell_value(r,0)).strip()==str(table.cell_value(r+1,0)).strip():
                f.write(u'')
            else:
                f.write(u'\n\t\t\t]')
                f.write(u'\n\t\t}')
            if r<table.nrows-1:
                    f.write(u',')
    f.write(u"\n\t]\n}\n")
    f.close()

    shutil.copy(jsonfilename, (payui_path+"\\"+jsonfilename))
 
    os.remove(jsonfilename)
    
def ModifyPayPoint(xls_path):
    data = xlrd.open_workbook(xls_path)
    table = data.sheet_by_index(0)
    outfile = open(appconfig_path+'\\src\\com\\tallbigup\\appconfig\\PayPointManager.java','w')

    outfile.write("package com.tallbigup.appconfig;"+'\n')
    outfile.write('\n')
    outfile.write("import com.tbu.androidtools.app.configuration.plugin.IPayPointManager;"+'\n')
    outfile.write("import com.tbu.androidtools.app.configuration.plugin.PayPoint;"+'\n')
    outfile.write('\n')
    outfile.write("public class PayPointManager implements IPayPointManager {"+'\n')
    outfile.write('\n')
    outfile.write('\t'+"@Override"+'\n')
    outfile.write('\t'+"public PayPoint getPayPointByPointId(int pointId) {"+'\n')
    outfile.write('\t\t'+"switch(pointId) {"+'\n')
    for r in range(1,table.nrows):
        pay_type = str(int(table.cell_value(r,0))).strip()
        pay_name = str(table.cell_value(r,1)).strip()
        pay_money = str(int(table.cell_value(r,2))).strip()
        pay_des = str(table.cell_value(r,3)).strip()
        outfile.write('\t\t'+"case "+pay_type+":"+'\n')
        outfile.write('\t\t\t'+"return new PayPoint("+pay_type+', "'+pay_name+'", '+pay_money+', "'+pay_des+'");'+'\n')
    outfile.write('\t\t'+"default:"+'\n')
    outfile.write('\t\t\t'+"return null;"+'\n')
    outfile.write('\t\t'+"}"+'\n')
    outfile.write('\t'+"}"+'\n')
    outfile.write("}"+'\n')


def ModifyGameConfig(project_path):
    #修改GameConfigManager
    print('start to modify GameConfigManager.java')
    infile = open(appconfig_path+'\\src\\com\\tallbigup\\appconfig\\GameConfigManager.java','r')
    outfile = open(appconfig_path+'\\src\\com\\tallbigup\\appconfig\\GameConfigManager1.java','w')
    for line in infile:
        if "OPEN_EXTEND_PUSH =" in line:
            outfile.write('\t'+"private static final boolean OPEN_EXTEND_PUSH = "+OPEN_EXTEND_PUSH+";"+'\n')
        elif "RECORD_GAME_DETAIL =" in line:
            outfile.write('\t'+"private static final boolean RECORD_GAME_DETAIL = "+RECORD_GAME_DETAIL+";"+'\n')
        elif "DEFAULT_GAME_PLGIN =" in line:
            outfile.write('\t'+'private static final String DEFAULT_GAME_PLGIN = "'+DEFAULT_GAME_PLGIN+'";'+'\n')
        else:
            outfile.write(line)
    infile.close()
    outfile.close()
    os.remove(appconfig_path+"\\src\\com\\tallbigup\\appconfig\\GameConfigManager.java")
    os.rename(appconfig_path+"\\src\\com\\tallbigup\\appconfig\\GameConfigManager1.java",appconfig_path+"\\src\\com\\tallbigup\\appconfig\\GameConfigManager.java")
    print('Modify GameConfigManager.java successfully')
    
    #修改LetuPayInfoManager
    print('start to modify LetuPayInfoManager.java')
    infile = open(appconfig_path+'\\src\\com\\tallbigup\\appconfig\\LetuPayInfoManager.java','r')
    outfile = open(appconfig_path+'\\src\\com\\tallbigup\\appconfig\\LetuPayInfoManager1.java','w')
    for line in infile:
        if "appId ="in line:
            outfile.write('\t'+'private static final String appId = "'+LETU_APPID+'";'+'\n')
        elif "showUiKey =" in line:
            outfile.write('\t'+'private static final String showUiKey = "'+LETU_UIKEY+'";'+'\n')
        elif "appName =" in line:
            outfile.write('\t'+'private static final String appName = "'+APP_NAME+'";'+'\n')
        else:
            outfile.write(line)
    infile.close()
    outfile.close()
    os.remove(appconfig_path+"\\src\\com\\tallbigup\\appconfig\\LetuPayInfoManager.java")
    os.rename(appconfig_path+"\\src\\com\\tallbigup\\appconfig\\LetuPayInfoManager1.java",appconfig_path+"\\src\\com\\tallbigup\\appconfig\\LetuPayInfoManager.java")
    print('Modify LetuPayInfoManager.java successfully')
    
    #修改SkyPayInfoManager
    print('start to modify SkyPayInfoManager.java')
    infile = open(appconfig_path+'\\src\\com\\tallbigup\\appconfig\\SkyPayInfoManager.java','r')
    outfile = open(appconfig_path+'\\src\\com\\tallbigup\\appconfig\\SkyPayInfoManager1.java','w')
    for line in infile:
        if "appId =" in line:
            outfile.write('\t'+'private static final String appId = "'+SKY_APPID+'";'+'\n')
        else:
            outfile.write(line)
    infile.close()
    outfile.close()
    os.remove(appconfig_path+"\\src\\com\\tallbigup\\appconfig\\SkyPayInfoManager.java")
    os.rename(appconfig_path+"\\src\\com\\tallbigup\\appconfig\\SkyPayInfoManager1.java",appconfig_path+"\\src\\com\\tallbigup\\appconfig\\SkyPayInfoManager.java")
    print('Modify SkyPayInfoManager.java successfully')
    
    #添加push的方法：暂时仅有开心捕鱼和疯狂连连看需要修改push
    
    if WITH_COCO == '0':
        tbuCloudFor_path = project_path+"\\src\\com\\tallbigup\\android\\statistics\\TbuCloudFor"+TBUCLOUDFOR_WHO+".java"
        tbuCloudFor_path1 = project_path+"\\src\\com\\tallbigup\\android\\statistics\\TbuCloudFor"+TBUCLOUDFOR_WHO+"1.java"
    else:
        tbuCloudFor_path = project_path+"\\src\\org\\cocos2dx\\cpp\\TbuCloudFor"+TBUCLOUDFOR_WHO+".java"
        tbuCloudFor_path1 = project_path+"\\src\\org\\cocos2dx\\cpp\\TbuCloudFor"+TBUCLOUDFOR_WHO+"1.java"
        
    print('start to push')
    infile = open(tbuCloudFor_path,'r')
    outfile = open(tbuCloudFor_path1,'w')
    need = 0
    lineNum = 0
    isInInitPush = 0    #判断是否进入initPush函数
    leftNum = 0
    rightNum = 0
    if OPEN_EXTEND_PUSH=="true":
        shutil.copyfile(B_path+"\\push_lib\\avoscloud-push-v3.1.5.jar",project_path+"\\libs\\avoscloud-push-v3.1.5.jar")
        for line in infile:
            lineNum += 1                
            if "void initPush" in line:
                isInInitPush = 1
            if isInInitPush == 1 and "try" in line and "//" in line:
                need = 1              
            if isInInitPush == 1:
                if "{" in line:
                    leftNum += 1
                if "}" in line:
                    rightNum += 1
            if leftNum == rightNum and leftNum!=0:
                isInInitPush = 0
            if need == 1 and isInInitPush == 1:
                nPos = line.index("//")
                outfile.write('\t'+'\t'+line[nPos+2:])
            elif lineNum == 2 and "import com.avos.avoscloud.AVInstallation" not in line:
                outfile.write("import com.avos.avoscloud.AVInstallation;\n")
            else:
                outfile.write(line)
             
    else:
        if os.path.exists(project_path+"\\libs\\avoscloud-push-v3.1.5.jar"):
            os.remove(project_path+"\\libs\\avoscloud-push-v3.1.5.jar")
        need = 0
        lineNum = 0
        for line in infile:              
            if "void initPush" in line:
                isInInitPush = 1
            if isInInitPush == 1 and "try" in line and "//" not in line:
                need = 1
            if isInInitPush == 1:
                if '{' in line:
                    leftNum += 1
                if '}' in line:
                    rightNum += 1
            if leftNum == rightNum and leftNum!=0:
                isInInitPush = 0
            if need == 1 and isInInitPush == 1:
                outfile.write("//\t\t"+line[2:])
            elif "import com.avos.avoscloud.AVInstallation;" in line:
                outfile.write("\n")
            else:
                outfile.write(line)
    infile.close()
    outfile.close()
    os.remove(tbuCloudFor_path)
    os.rename(tbuCloudFor_path1,tbuCloudFor_path)

    manifestXml = open(project_path+"\\AndroidManifest.xml",'r')
    content = manifestXml.read()       
    manifestXml.close()        
    pos = content.find("</application>")
    start = content.find("<!-- avos push -->")
    if OPEN_EXTEND_PUSH=="true" and start == -1:
        addXml = open(os.getcwd()+"\\in\\manifestAdd\\avosPush.txt","r")
        contentadd = addXml.read()
        addXml.close()
        content = content[:pos-4]+contentadd+"\n"+content[pos-4:]
        newXml = open(project_path+"\\AndroidManifest.xml",'w')
        newXml.write(content)
        newXml.close()
    elif OPEN_EXTEND_PUSH == "false" and start != -1:
        end = content.find("<!-- avos end -->")
        content = content[:start]+content[end+17:]
        newXml = open(project_path+"\\AndroidManifest.xml",'w')
        newXml.write(content)
        newXml.close()

    print('Push successfully')


    

  

def BuildJar():
    os.chdir(appconfig_path)
    os.system('ant')

def readEnterId(xls_path):
    data = xlrd.open_workbook(xls_path)
    table = data.sheet_by_index(1)
    
    ids = []
    for r in range(1,table.nrows):
        try:
            val = str(int(table.cell_value(r,0)))
        except:
            val = str(table.cell_value(r,0)).strip()
        ids.append(val)
    
    return ids;
        
def replaceXml(fileXml, enterId):
    print("start to modify manifest.xml")
    dom = minidom.parse(fileXml)
    root = dom.documentElement
    for node in dom.getElementsByTagName('manifest'):
        node.setAttribute("android:versionCode", VERSION_CODE)
        node.setAttribute("android:versionName", VERSION_NAME)
        
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
        if node.getAttribute("android:name")=="lltt_cpchannelid":
            node.setAttribute("android:value", enterId)

    savefile = open(fileXml, 'w')
    dom.writexml(savefile)
    savefile.close()
    print("modify manifest.xml successfully!" )
    
def replaceGameinfo(ZYF_ChannelID,filePx,enterId):
    print("start to modify EnterId and ZYF_ChannelID")
    f = open(filePx, 'w')
    f.truncate()
    f.write("ENTER_ID=")
    f.write(enterId)
    f.close()

    if os.path.exists(ZYF_ChannelID):
        f = open(ZYF_ChannelID, 'w')
        f.truncate()
        f.write(enterId)
        f.close()

    print("modify EnterId and ZYF_ChannelID successfully!")

def replaceGamepayplugin(project_path):
    #修改gamepayplugin.px
    print("start to modify gamepayplugin.px")
    outfile = open(project_path+"\\assets\\gamepayplugin.px","w")
    outfile.write("\n")
    outfile.write("APPID="+SKY_APPID)
    outfile.write("\nGAMEID="+GAMEID)
    outfile.write('\nPAYPLUGIN_TYPE='+PLUGINIDS)
    outfile.write('\nGAME_NAME_ID='+GAMENAMEID)
    outfile.write('\nUNICOM_APPID = 90810000305020150601222120563900')
    outfile.write('\nUNICOM_CPID=91001946')
    outfile.write('\nUNICOM_CHANNELID= 25165')
    outfile.write('\nUNICOM_GAMENAME = '+APP_NAME)
    outfile.close()
    print("modify gamepayplugin.px successfully") 

#def changeIcon(project_path):
def changeApp_name(project_path):
    #app_name修改编码，防止中文报错
#    if isinstance(APP_NAME,unicode):
#        app_name=APP_NAME
#    else:
#        app_name=unicode(APP_NAME,"gb2312")
    stree=et.parse(project_path+"\\res\\values\\strings.xml")
    sroot=stree.getroot()
    sroot[0].attrib['name']="app_name"
    sroot[0].text=APP_NAME               
    stree.write(project_path+"\\res\\values\\strings.xml",encoding='utf-8',xml_declaration=True)
    print 'modify app_name successfully!'    


def outApk(sdkmake_path,build_path,project_path,apk_path,v):
    
    print('start to change package name')
    dom = minidom.parse(build_path)
    root = dom.documentElement    
    for node in dom.getElementsByTagName('project'):
       projectName = node.getAttribute("name")
    for node in root.getElementsByTagName('property'):
        if node.getAttribute("name")=="gb.newpackage":
            print('node.getAttribute("name")=="gb.newpackage!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
            print('value=====================>'+node.getAttribute("value"))
            node.setAttribute("value", PACKAGE_NAME)
            print('value=====================>'+node.getAttribute("value"))
    savefile = open(build_path, 'w')
    dom.writexml(savefile)
    savefile.close()
    
    old_apk = projectName+"-"+VERSION_CODE+"-"+VERSION_NAME+"-release.apk"
    new_apk = save_file+"\\"+projectName+"-" + VERSION_CODE+"-"+v+"-"+ DEMANDER+"-"+time.strftime('%Y%m%d',time.localtime(time.time()))+".apk"
    os.chdir(project_path)
    os.system('ant')
    os.chdir(apk_path)
    shutil.move(old_apk, new_apk)
    print("OPEN_OUXIN=================================>"+OPEN_OUXIN)
    if OPEN_OUXIN == "true":
        os.system(sdkmake_path+" "+new_apk)
    
if __name__ == "__main__":
    gameinfo_path = unicode(os.getcwd()+"\\in\\gameConfig.xlsx",'utf8')
    in_path = os.getcwd()+"\\in"
    if not os.path.exists(gameinfo_path):
        print("gameConfig.xlsx does not exist")
    else:
        ReadGameInfo(gameinfo_path)
        print("===========Get gameinfo successfully===========")
        if WITH_COCO == '0' :
            project_path = base_path+"\\"+PROJECT_NAME
            payui_path = project_path+"\\assets\\payui"
            gameinfo_px = project_path+"\\assets\\gameinfo.px"
            ZYF_ChannelID = project_path+"\\assets\\ZYF_ChannelID"
        else :
            project_path = base_path+"\\"+PROJECT_NAME+"\\proj.android"
            payui_path = base_path+"\\"+PROJECT_NAME+"\\Resources\\payui"
            ZYF_ChannelID = base_path+"\\"+PROJECT_NAME+"\\Resources\\ZYF_ChannelID"
            gameinfo_px = base_path+"\\"+PROJECT_NAME+"\\Resources\\gameinfo.px"
        payPoint_path = os.getcwd()+"\\in\\default\\"+PROJECT_NAME+"\\PayPoint.xlsx"
        sdkmake_path = OUXIN_path+"\\"+PROJECT_NAME+".bat"
        if not os.path.exists(in_path+"\\PaypointUi.xlsx"):
            print("PaypointUi.xlsx does not exist")
        else:
            changePaypointUi(payui_path,in_path)
        if not os.path.exists(in_path+"\\UiToPay.xlsx"):
            print("UiToPay.xlsx does not exist")
        else:
            changeUitopay(payui_path,in_path)
        print("project_path==========>"+project_path)
        changeApp_name(project_path)
        ModifyGameConfig(project_path)
        ModifyPayPoint(payPoint_path)
        print("===========Modify GameConfig successfully===========")
        print("===========start to build gameconfig.jar===========")
        BuildJar()
        shutil.copyfile(appconfig_path+'\\dist\\gameconfig.jar',project_path+"\\libs\\gameconfig.jar")
        print("===========copy gameconfig.jar to "+project_path+"\\libs successfully ===========")
        try:
            if os.path.exists(save_file):
                shutil.rmtree(save_file)   
        finally:
            androidManifest_xml = project_path+"\\AndroidManifest.xml"
            print("androidManifest_xml================>"+androidManifest_xml)
            build_path = project_path+"\\build.xml"
            apk_path = project_path+"\\bin"
            os.mkdir(save_file)       
            enterIds = readEnterId(gameinfo_path)
            for v in enterIds:
                print("start to build apk: "+v)
                replaceXml(androidManifest_xml, v)
                replaceGameinfo(ZYF_ChannelID,gameinfo_px, v)
                replaceGamepayplugin(project_path)
                outApk(sdkmake_path,build_path,project_path,apk_path,v)

