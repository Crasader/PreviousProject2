#coding=utf-8
from Tkinter import *
import MySQLdb
#import socket

#请修改以下路径
base_path = "D:\\WinneShen\\Workspace\\PoxiaoMoneyGame"

def dbconnection():
    print("start to add the new pgname...")
    projectname = ""
    #ip = socket.gethostbyname(socket.gethostname())
    db = MySQLdb.connect(host="172.23.1.101",user="root",passwd="123456",db="gameDB",charset='utf8' ) 
    cursor = db.cursor()
    try:
        select = "select projectname from gameinfo where gamename='"+gameName.get()+"'"
        cursor.execute(select)
        result = cursor.fetchall()
        print(result)
        if result:
            for row in result:
                projectname = row[0]
        else:
            print("no this game name in the database")
            sys.exit(0)
        insert = "insert into "+projectname+" value('"+pgName.get()+"','"+letukey.get()+"')"
        print(insert)
        cursor.execute(insert)
        db.commit()
        print("add successfully!")
    except:
        db.rollback()
    db.close()


if __name__ == "__main__":
   
    
    window = Tk()                 # 创建一个窗口  
    window.title("add pgname")  # 设置标题
    frame1 = Frame(window)        # 创建一个框架  
    frame1.pack()                 # 将框架frame1放置在window中  

    labal_gameName = Label(frame1,text="Game Name: ")
    label_pgName = Label(frame1,text="Package Name: ")
    labal_letukey = Label(frame1,text="Letu Key: ")

    gameName = StringVar()
    pgName = StringVar()
    letukey = StringVar()
    
    entry_gameName = Entry(frame1,textvariable=gameName)
    entry_pgName = Entry(frame1,textvariable=pgName)
    entry_letuKey = Entry(frame1,textvariable=letukey)
    button_submit = Button(frame1,text="   submit  ",command=dbconnection)
    #button_mGamepaypluginPX = Button(frame1,text="modify gamepayplugin.px",command=modifyGamepaypluginPX)
    
    labal_gameName.grid(row=1,column=1)
    label_pgName.grid(row=2,column=1)
    labal_letukey.grid(row=3,column=1)
    
    entry_gameName.grid(row=1,column=2)
    entry_pgName.grid(row=2,column=2)
    entry_letuKey.grid(row=3,column=2)
    button_submit.grid(row=4,column=1)

    # 监测事件直到window被关闭  
    window.mainloop()
    # Get Name按钮点击函数

    

