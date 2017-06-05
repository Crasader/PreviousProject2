# -*- coding: cp936 -*-
import os
import os.path
import xlrd
import sys
import codecs
import types
import re
import shutil
reload(sys)
sys.setdefaultencoding( "utf-8" )

assets_path = '..\\CatchFish_3\\assets'

if __name__ == "__main__":
    print("payui copy start")
    if os.path.exists(assets_path):
        shutil.rmtree(assets_path)
    os.mkdir(asssts_path)
    shutil.copytree ('.\\in\\payui', assets_path+'\\payui')
    print("payui copy end")
    print

    print("paypointui.json copy start")
    shutil.copy ('.\\in\\PaypointUi.json', assets_path+'\\payui\\PaypointUi.json')
    print("paypointui.json copy end")
    print

    print("uitopay.json copy start")
    shutil.copy ('.\\in\\uitopay.json', assets_path+'\\payui\\uitopay.json')
    print("uitopay.json copy end")
    print

    
