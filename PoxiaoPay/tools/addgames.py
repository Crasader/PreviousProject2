#coding=utf-8
from Tkinter import *
import MySQLdb
#import socket

#请修改以下路径
base_path = "D:\\WinneShen\\Workspace\\PoxiaoMoneyGame"

def dbconnection():
    print("start to add the new game...")
    #ip = socket.gethostbyname(socket.gethostname())
    db = MySQLdb.connect(host="172.23.1.101",user="root",passwd="123456",db="gameDB",charset='utf8' ) 
    cursor = db.cursor()
    insert = "insert into gameInfo values ('"+gameName.get()+"','"+projectName.get()+"','"+tbucloud.get()+"',"+str(coco.get())+",'"+gameid.get()+"','"+letuappid.get()+"','"+skyappid.get()+"',"+gamenameid.get()+");"
    try:
        cursor.execute(insert)
       # db.commit()
        create = "CREATE TABLE gamedb."+projectName.get()+" (  packagename VARCHAR(35) NOT NULL,letukey VARCHAR(40) NULL DEFAULT NULL,PRIMARY KEY (packagename));"
        cursor.execute(create)
        db.commit()
        print("add successfully!")
    except:
        db.rollback()
    db.close()

def addInfo():
    print("gameName="+gameName.get()+";projectName="+projectName.get()+";tbucloud="+tbucloud.get()+";coco="+str(coco.get()))

if __name__ == "__main__":
   
    
    window = Tk()                 # 创建一个窗口  
    window.title("add games")  # 设置标题
    frame1 = Frame(window)        # 创建一个框架  
    frame1.pack()                 # 将框架frame1放置在window中  

    labal_gameName = Label(frame1,text="Game Name: ")
    labal_projectName = Label(frame1,text="Project Name: ")
    labal_tbucloud = Label(frame1,text="Tbucloudfor Who: ")
    label_gameid = Label(frame1,text="Game ID: ")
    label_gamenameid = Label(frame1,text="Game Name ID: ")
    label_letuappid = Label(frame1,text="Latu Appid: ")
    label_skyappid = Label(frame1,text="Sky Appid: ")
    lable_cocos2d = Label(frame1,text="With Cocos2d: ")

    gameName = StringVar()
    projectName = StringVar()
    tbucloud = StringVar()
    gameid = StringVar()
    gamenameid = StringVar()
    letuappid = StringVar()
    skyappid = StringVar()
    coco = IntVar()
    
    entry_gameName = Entry(frame1,textvariable=gameName)
    entry_projectName = Entry(frame1,textvariable=projectName)
    entry_tbucloud = Entry(frame1,textvariable=tbucloud)
    entry_gameid = Entry(frame1,textvariable=gameid)
    entry_gamenameid = Entry(frame1,textvariable=gamenameid)
    entry_letuappid = Entry(frame1,textvariable=letuappid)
    entry_skyappid = Entry(frame1,textvariable=skyappid)
    rb_no = Radiobutton(frame1,text="no",variable=coco,value=0,  
                            command=addInfo)
    rb_yes = Radiobutton(frame1,text="yes",variable=coco,value=1,  
                            command=addInfo)
    button_submit = Button(frame1,text="   submit  ",command=dbconnection)
    #button_mGamepaypluginPX = Button(frame1,text="modify gamepayplugin.px",command=modifyGamepaypluginPX)
    
    labal_gameName.grid(row=1,column=1)
    labal_projectName.grid(row=2,column=1)
    labal_tbucloud.grid(row=3,column=1)
    label_gameid.grid(row=4,column=1)
    label_gamenameid.grid(row=5,column=1)
    label_letuappid.grid(row=6,column=1)
    label_skyappid.grid(row=7,column=1)
    lable_cocos2d.grid(row=8,column=1)
    
    entry_gameName.grid(row=1,column=2)
    entry_projectName.grid(row=2,column=2)
    entry_tbucloud.grid(row=3,column=2)
    entry_gameid.grid(row=4,column=2)
    entry_gamenameid.grid(row=5,column=2)
    entry_letuappid.grid(row=6,column=2)
    entry_skyappid.grid(row=7,column=2)
    rb_no.grid(row=9,column=1)
    rb_yes.grid(row=9,column=2)
    button_submit.grid(row=10,column=1)

    # 监测事件直到window被关闭  
    window.mainloop()
    # Get Name按钮点击函数

    
