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

icon_path = 'E:\\PoxiaoMoneyGame\\CatchFish_3\\res'

if __name__ == "__main__":
    print("icon copy start")
    if not os.path.exists(icon_path):
        print('no res files')
        os.system('pause')
        exit(0)
    
    if not os.path.exists('.\\in\\icon\\36.png'):
        print('no have 36.png')
    else:
        shutil.copy ('.\\in\\icon\\36.png', icon_path+'\\drawable-ldpi\\ic_launcher.png')

    if not os.path.exists('.\\in\\icon\\48.png'):
        print('no have 48.png')
    else:
        shutil.copy ('.\\in\\icon\\48.png', icon_path+'\\drawable-mdpi\\ic_launcher.png')

    if not os.path.exists('.\\in\\icon\\72.png'):
        print('no have 72.png')
    else:
        shutil.copy ('.\\in\\icon\\72.png', icon_path+'\\drawable-hdpi\\ic_launcher.png')

    if not os.path.exists('.\\in\\icon\\96.png'):
        print('no have 96.png')
    else:
        shutil.copy ('.\\in\\icon\\96.png', icon_path+'\\drawable-xhdpi\\ic_launcher.png')
        shutil.copy ('.\\in\\icon\\96.png', icon_path+'\\drawable-xxhdpi\\ic_launcher.png')

    print("icon copy end")
    os.system('pause')
    exit(0)
    
