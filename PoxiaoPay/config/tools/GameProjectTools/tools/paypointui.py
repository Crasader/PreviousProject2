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

PaypointUi_path = ".\\in"
PaypointUi = "PaypointUi.xlsx"

def xlsx_json():
    
    data = xlrd.open_workbook(PaypointUi_path+"\\"+PaypointUi)
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

    shutil.copy(jsonfilename, (PaypointUi_path+"\\"+jsonfilename))
    os.remove(jsonfilename)

if __name__ == "__main__":
    xlsx_json()
