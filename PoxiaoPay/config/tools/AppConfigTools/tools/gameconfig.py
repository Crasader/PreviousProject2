# -*- coding: cp936 -*-
import os
import shutil
import re
import xlrd
import sys
import time
reload(sys)
sys.setdefaultencoding( "utf-8" )

OPEN_EXTEND_PUSH = ""
RECORD_GAME_DETAIL = ""
Letu_merchantKey = ""
Letu_merchantId = ""
Letu_appId = ""
Sky_appId = ""
Sky_merchantPasswd = ""
Sky_merchantId = ""

def ModifyPayInfo(xls_path):
    data = xlrd.open_workbook(xls_path)
    table = data.sheet_by_index(0)

    OPEN_EXTEND_PUSH = str(table.cell_value(1,1)).strip()
    RECORD_GAME_DETAIL = str(table.cell_value(2,1)).strip()
    DEFAULT_GAME_PLGIN = '"'+str(table.cell_value(3,1)).strip()+'"'
    Letu_merchantKey = '"'+str(table.cell_value(4,1)).strip()+'"'
    Letu_merchantId = '"'+str(table.cell_value(5,1)).strip()+'"'
    Letu_appId = '"'+str(int(table.cell_value(6,1))).strip()+'"'
    Letu_showUiKey = '"'+str(table.cell_value(7,1)).strip()+'"'
    Letu_appName = '"'+str(table.cell_value(8,1)).strip()+'"'
    Sky_appId = '"'+str(int(table.cell_value(9,1))).strip()+'"'
    Sky_merchantPasswd = '"'+str(table.cell_value(10,1)).strip()+'"'
    Sky_merchantId = '"'+str(int(table.cell_value(11,1))).strip()+'"'

    #GameConfigManager
    print('\nGameConfigManager开始修改')
    infile = open('..//src\\com\\tallbigup\\appconfig\\GameConfigManager.java','r')
    outfile = open('..//src\\com\\tallbigup\\appconfig\\GameConfigManager1.java','w')
    for line in infile:
        if "OPEN_EXTEND_PUSH =" in line:
            outfile.write('\t'+"private static final boolean OPEN_EXTEND_PUSH = "+OPEN_EXTEND_PUSH+";"+'\n')
        elif "RECORD_GAME_DETAIL =" in line:
            outfile.write('\t'+"private static final boolean RECORD_GAME_DETAIL = "+RECORD_GAME_DETAIL+";"+'\n')
        elif "DEFAULT_GAME_PLGIN =" in line:
            outfile.write('\t'+"private static final String DEFAULT_GAME_PLGIN = "+DEFAULT_GAME_PLGIN+";"+'\n')
        else:
            outfile.write(line)
    infile.close()
    outfile.close()
    os.remove("..//src\\com\\tallbigup\\appconfig\\GameConfigManager.java")
    os.rename("..//src\\com\\tallbigup\\appconfig\\GameConfigManager1.java","..//src\\com\\tallbigup\\appconfig\\GameConfigManager.java")
    print('GameConfigManager修改成功')

    print('\LetuPayInfoManager开始修改')
    infile = open('..//src\\com\\tallbigup\\appconfig\\LetuPayInfoManager.java','r')
    outfile = open('..//src\\com\\tallbigup\\appconfig\\LetuPayInfoManager1.java','w')
    for line in infile:
        if "merchantKey =" in line:
            outfile.write('\t'+"private static final String merchantKey = "+Letu_merchantKey+";"+'\n')
        elif "merchantId =" in line:
            outfile.write('\t'+"private static final String merchantId = "+Letu_merchantId+";"+'\n')
        elif "appId =" in line:
            outfile.write('\t'+"private static final String appId = "+Letu_appId+";"+'\n')
        elif "showUiKey =" in line:
            outfile.write('\t'+"private static final String showUiKey = "+Letu_showUiKey+";"+'\n')
        elif "appName =" in line:
            outfile.write('\t'+"private static final String appName = "+Letu_appName+";"+'\n')
        else:
            outfile.write(line)
    infile.close()
    outfile.close()
    os.remove("..//src\\com\\tallbigup\\appconfig\\LetuPayInfoManager.java")
    os.rename("..//src\\com\\tallbigup\\appconfig\\LetuPayInfoManager1.java","..//src\\com\\tallbigup\\appconfig\\LetuPayInfoManager.java")
    print('LetuPayInfoManager修改成功')

    #SkyPayInfoManager
    print('\SkyPayInfoManager开始修改')
    infile = open('..//src\\com\\tallbigup\\appconfig\\SkyPayInfoManager.java','r')
    outfile = open('..//src\\com\\tallbigup\\appconfig\\SkyPayInfoManager1.java','w')
    for line in infile:
        if "appId =" in line:
            outfile.write('\t'+"private static final String appId = "+Sky_appId+";"+'\n')
        elif "merchantPasswd =" in line:
            outfile.write('\t'+"private static final String merchantPasswd = "+Sky_merchantPasswd+";"+'\n')
        elif "merchantId =" in line:
            outfile.write('\t'+"private static final String merchantId = "+Sky_merchantId+";"+'\n')
        else:
            outfile.write(line)
    infile.close()
    outfile.close()
    os.remove("..//src\\com\\tallbigup\\appconfig\\SkyPayInfoManager.java")
    os.rename("..//src\\com\\tallbigup\\appconfig\\SkyPayInfoManager1.java","..//src\\com\\tallbigup\\appconfig\\SkyPayInfoManager.java")
    print('SkyPayInfoManager修改成功')

def ModifyPayPoint(xls_path):
    data = xlrd.open_workbook(xls_path)
    table = data.sheet_by_index(0)
    outfile = open('..//src\\com\\tallbigup\\appconfig\\PayPointManager.java','w')

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

def BulidJar():
    os.chdir('..\\')
    os.system('ant')

if __name__ == "__main__":
    payInfo_path = os.getcwd()+"\\in\\GameConfig.xlsx"
    #print(payInfo_path)
    payPoint_path = os.getcwd()+"\\in\\PayPoint.xlsx"
    #print(payPoint_path)
    if not os.path.exists(payInfo_path):
        print("GameConfig.xlsx文件不存在")
    elif not os.path.exists(payPoint_path): 
        print("PayPoint.xlsx文件不存在")
    else:
        ModifyPayInfo(payInfo_path)
        ModifyPayPoint(payPoint_path)
        print("文件修改完成")
        print("开始编译gameconfig.jar")
        BulidJar()
        print("gameconfig.jar编译完成")
        
        
