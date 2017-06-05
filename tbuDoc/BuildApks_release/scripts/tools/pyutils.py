# -*- coding: utf-8 -*-
'''
工具类
'''
import urllib2
import urllib
import json
import sys
import os
import codecs
import shutil
from cgi import log
class pyutils:
    #上传打包记录的url
    url_process='http://183.131.152.31:1395/process'

    #修改XML
    def modifyXML(self, newXml_path, startNO, end, contentadd, content, pos, add):
        if add == "true" :
            content = content[:pos] + contentadd + "\n" + content[pos:]
            newXml = open(newXml_path, 'w')
            newXml.write(content)
            newXml.close()
        else:
            endNO = content.find(end)
            content = content[:startNO] + content[endNO + len(end):]
            newXml = open(newXml_path, 'w')
            newXml.write(content)
            newXml.close()
        return content
    
    #文件加密方法
    def encryptJson(self, B_path,file_path):
        f = open(B_path + "\\FileUtil\\filename", 'w')
        f.truncate()
        f.write(file_path)
        f.close()
        fi = open(file_path,'r')
        content = fi.read()
        fi.close()
        try:
            decoded = json.loads(content)
            # pretty printing of json-formatted string
            os.chdir(B_path + "\\FileUtil\\src")
            os.system("javac JsonUtil.java")
            os.system("java JsonUtil")
        except (ValueError, KeyError, TypeError):
            print "JSON format error"
        print 'encrypt '+file_path+' successfully'

        #文件加密方法
    def encryptStringJson(self, B_path,file_path):
        f = open(B_path + "\\FileUtil\\filestringname", 'w')
        f.truncate()
        f.write(file_path)
        f.close()
        fi = open(file_path,'r')
        content = fi.read()
        fi.close()
        try:
            decoded = json.loads(content)
            # pretty printing of json-formatted string
            os.chdir(B_path + "\\FileUtil\\src")
            os.system("javac JsonStringUtil.java")
            os.system("java JsonStringUtil")
        except (ValueError, KeyError, TypeError):
            print "JSON format error"
        print 'encrypt '+file_path+' successfully'
        
        
    #读取文件内容
    def getContent(self, content_path):
        addFile = open(content_path, "r")
        contentadd = addFile.read()
        addFile.close()
        return contentadd 

    #获取当前路径
    def getpwd(self):
        pwd = sys.path[0]
        if os.path.isfile(pwd):
            pwd = os.path.dirname(pwd)
        return pwd
        
    # list 转 string
    def list2str(self, list):
        re = ","
        for i in range(0, list.__len__()):
            list[i] = str(list[i])
        re = re.join(list)
        print re
        return re
    


    #jar包移动
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

    
    #jar包移除
    def deleteJar(self, head, toDir):
        filelist = os.listdir(toDir)
        filelist.sort()
        for i in filelist:
            tt_match = re.search(head + '*', i)
            if tt_match:
                print i
                if os.path.exists(toDir + "\\" + i):
                    os.remove(toDir + "\\" + i)
    
    
    #发送http请求
    def http_post(self, url,data=None):
        try:
            if data is not None:
                req = urllib2.Request(url,urllib.urlencode(data)) 
            else:
                req = urllib2.Request(url)   
            response = urllib2.urlopen(req)
            return json.load(response)
        except:
            print 'cannot connect to the network'
            return None



    #上传打包记录
    def record(self,value,error_code,desc):
        log= self.getpwd()+"/log.txt"
        log_path=open(log,'a')
        log_path.write('\nerror_code:')
        log_path.write(error_code)
        log_path.write('\ndesc:')
        log_path.write(desc)
        
        if value.has_key('save_path') and value['save_path'] != 'NA' and os.path.exists(value['save_path'] + "\\" +value['client_order_id']):
            log_path.close()
            shutil.copy(log, value['save_path'] + "\\" +value['client_order_id']+"\\log.txt")
            os.remove(log)
        else:
            log_path.write('\nothers:您所填写的输出路径save_path可能正在被占用中，或者在获取save_path值前，程序就出现异常。')
            log_path.close()
            print 'log.txt is in the current directory.'
        values=dict({'error_code':int(error_code),'desc':desc}.items()+value.items())
        print values
        re=self.http_post(self.url_process,values)
        if re is not None:
            print "error_code:"+error_code+".Exit and upload."
            print "Result="+str(re['result'])
            print "desc="+re['errormsg']
        # if re is None :
        #     if not os.path.exists(self.getpwd()+"/review"):
        #         os.mkdir(self.getpwd()+"/review")
        #     review_json=codecs.open(self.getpwd()+'/review/localgameconfig.json','r')
        #     review_json.write('{\n\t"result":-1,"\n\tdesc":"cannot connect network",'+'"\n\tdata":'+value+'}')
        #     review_json.close()
        # if re['result']!=0:
        #     if not os.path.exists(self.getpwd()+"/review"):
        #         os.mkdir(self.getpwd()+"/review")
        #     review_json=codecs.open(self.getpwd()+'/review/localgameconfig.json','r')
        #     review_json.write('{\n\t"result":'+str(re['errormsg'])+',"\n\tdesc":"'+re['errormsg']+'",'+'"\n\tdata":'+value+'}')
        #     review_json.close()
    
 
        
        
        
        