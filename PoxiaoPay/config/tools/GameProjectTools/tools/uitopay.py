# -*- coding:utf8 -*-
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

uitopay_path = ".\\in"
uitopay = "uitopay.xlsx"

def xlsx_json():
    
    data = xlrd.open_workbook(uitopay_path+"\\"+uitopay)
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

    shutil.copy(jsonfilename, (uitopay_path+"\\"+jsonfilename))
    os.remove(jsonfilename)

if __name__ == "__main__":
    xlsx_json()
