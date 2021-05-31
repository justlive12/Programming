import socket
from threading import Thread

import sqlite3 as sql3
import random
import string
import sys


name_db=['users.db','rooms.db']


create_users="""
    CREATE TABLE USERS (
        id INTEGER NOT NULL ,
        name TEXT NOT NULL PRIMARY KEY,
        password TEXT,
        points INTEGER,
        wins INTEGER);"""
create_rooms="""
    CREATE TABLE ROOMS (
        id INTEGER NOT NULL ,
        name TEXT NOT NULL PRIMARY KEY,
        user1 TEXT,
        user1_ready INTEGER,
        user2 TEXT,
        user2_ready INTEGER,
        freedoom INTEGER,
        password_room TEXT);
"""
def init_db(name_db,cmd):
    con = sql3.connect(name_db)
    try:
        with con:
            con.execute(cmd)
    except:
        pass


init_db(name_db[0],create_users)
init_db(name_db[1],create_rooms)


def sql_cmd_select_all(name_db,name_table):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        data = cur.execute("SELECT * FROM "+name_table)
        #data = cur.fetchone()
        for row in data:
            print(row)

def get_count(name_db,name_table):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        try:
            cur.execute("SELECT COUNT(*) FROM "+name_table)
            data=cur.fetchone()
            return data[0]
        except:
            return 0

def add_data_user(name_db,name_table, data):
    i = get_count(name_db,name_table)
    data.insert(0,i)
    print(i)
    print(data)
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute("INSERT INTO USERS VALUES(?,?, ?, ?, ?);", tuple(data))
        con.commit()
def add_data_room(name_db,name_table, data):
    i = get_count(name_db,name_table)
    data.insert(0,i)
    print(i)
    print(data)
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute("INSERT INTO ROOMS VALUES(?,?,?,?,?,?,?,?);", tuple(data))
        con.commit()

def del_line(name_db,name_table, name):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute("DELETE FROM "+name_table+" WHERE name='"+name+"';")
        con.commit()

def find(name_db,name_table, name):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute("SELECT * FROM "+name_table+" WHERE name='"+name+"';")
        data = cur.fetchone()
        print("find=",data)
        return(data)


def Login(login, password):
    data=find('users.db',"USERS",login)
    if (data[1]==login and data[2]==password):
        print("Login: Ok")
        return "1"
    else:
        print("Login: No")
        return "0"

def get_all_stat(name_db):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute("SELECT name, points, wins FROM USERS ORDER BY points DESC LIMIT 10")
        data = cur.fetchall()
        
        for row in data:
            print(row)
        return(data)

def create_room(name_db,Name_room, USER):
    nameroom=Name_room
    user1=USER
    user2=""
    freedoom=1
    passwd=""
    for i in range(5):
        passwd+=str(random.randint(100,999))
    data=[nameroom, user1,"0", user2,"0", freedoom, passwd]
    try:
        add_data_room(name_db,"ROOMS",data)
    except:
        return "0"
    ans=get_line_room(name_db,Name_room)
    if ans!=None or ans!=0 or ans!="":
        return "1"
    else:
        return "0"

def get_line_room(name_db,name_room):
    try:
        data=find(name_db,"ROOMS",name_room)
        print("line room=",data)
    except:
        print("er")
    return data

def find_room(name_db,Name_room, USER):
    ans=get_line_room(name_db,Name_room)
    print(ans[6])
    if ans!=None and ans!=0 and ans!="" and ans[6]==1:
        try:
            update_user2_freedom(name_db, [USER,0, Name_room])
            return "1"
        except:
            return "0"
    else:
        return "0"

def update_user2_freedom(name_db, data):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute('''UPDATE ROOMS SET user2=?, freedoom=? WHERE name=?''',(data[0],data[1],data[2]))
        con.commit()

def check_freedoom(name_db, data):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute("SELECT freedoom FROM ROOMS WHERE name='"+data+"';")
        data = cur.fetchone()
        print("check_freedoom=",data[0])
        return(str(data[0]))


def get_user(name_db, data,n):
    con = sql3.connect(name_db)
    if n=='1':
        with con:
            cur = con.cursor()
            cur.execute("SELECT user1 FROM ROOMS WHERE name='"+data+"';")
            data = cur.fetchone()
            print("get_user1=",data)
            return(data[0])
    elif n=='2':
        with con:
            cur = con.cursor()
            cur.execute("SELECT user2 FROM ROOMS WHERE name='"+data+"';")
            data = cur.fetchone()
            print("get_user2=",data)
            return(data[0])


def update_win_point(name_db, data):
    con = sql3.connect(name_db)
    with con:
        try:
            cur = con.cursor()
            cur.execute('''UPDATE USERS SET points=?, wins=? WHERE name=?''',(data[0],data[1],data[2]))
            con.commit()
            return "1"
        except:
            return "0"

def get_data1(name_db, name_table,param,name):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute("SELECT "+param+" FROM "+name_table+" WHERE name='"+name+"';")
        data = cur.fetchone()
        return data

def statistic_u(name_db, name):
    con = sql3.connect(name_db)
    with con:
        cur = con.cursor()
        cur.execute("SELECT points, wins FROM USERS WHERE name='"+name+"';")
        data = cur.fetchall()
        #print("find=",data)
        return(data[0])

def set_win(name_db, data):
    ans=get_data1(name_db,"USERS","points",data[2])
    print("ans=",ans[0])
    data[0]+=int(ans[0])
    ans=get_data1(name_db,"USERS","wins",data[2])
    print("ans=",ans[0])
    data[1]+=int(ans[0])
    print("data=",data)
    return update_win_point(name_db, data)
def set_exp(name_db, data):
    con = sql3.connect(name_db)
    with con:
        try:
            cur = con.cursor()
            cur.execute('''UPDATE USERS SET points=? WHERE name=?''',(data[0],data[1]))
            con.commit()
            return "1"
        except:
            return "0"
            
def set_ready(name_db, data):
    con = sql3.connect(name_db)
    with con:
        try:
            cur = con.cursor()
            cur.execute('''UPDATE ROOMS SET user1_ready=?, user2_ready=? WHERE name=?''',(data[0],data[1],data[2]))
            con.commit()
            return "1"
        except:
            return "0"

def test():
    con = sql3.connect("users.db")
    with con:
        cur = con.cursor()
        cur.execute("SELECT name FROM USERS;")
        data=[]
        d="0"
        while(d!=None):
            d = cur.fetchone()
            if d!=None:
                d=d[0]
                data.append(d)
        print("check_freedoom=",data)
        for usr in data:
            set_exp("users.db",[50,usr])
        print("USERS")
        sql_cmd_select_all("users.db","USERS")

"""
test()

def add_us():
    name="admin"
    password="admin"
    points=1
    wins=2
    data=[name, password, points, wins]
    add_data_user('users.db',"USERS",data)
def add_ru():
    name="keks"
    user1="sss"
    user2="sss"
    freedoom=1
    data=[name, user1, user2, freedoom]
    add_data_room('rooms.db',"ROOMS",data)
print(find('users.db',"USERS","sssssssss"))
add_us()
add_ru()

find('users.db',"USERS","keks")
find('rooms.db',"ROOMS","keks")
print(Login("keks","sss"))
print(Login("keks","sss1"))
update_win_point('users.db',[999,987,"keks"])
update_user2_freedom('rooms.db',["kinoha",0,"keks"])

print("USERS")
sql_cmd_select_all("users.db","USERS")
print("ROOMS")
sql_cmd_select_all("rooms.db","ROOMS")


del_line('users.db',"USERS","keks")
del_line('rooms.db',"ROOMS","keks")


print("USERS")
sql_cmd_select_all("users.db","USERS")
print("ROOMS")
sql_cmd_select_all("rooms.db","ROOMS")


for i in range(11):
    name=''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10))
    password=''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10))
    points=random.randint(10,100)
    wins=random.randint(0,10)
    data=[name, password, points, wins]
    add_data_user('users.db',"USERS",data)

for i in range(11):
    name=''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10))
    user1=''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10))
    user2=''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10))
    freedoom=0
    data=[name, user1, user2, freedoom]
    add_data_room('rooms.db',"ROOMS",data)
"""
#--------------------------------------
#SERVER
#-------------------
def send_data(connection, data):
    connection.send(data.encode('UTF-8'))


def get_data(connection):
    return connection.recv(1024).decode().strip()


def run(connection, addr_user):
    try:
        """
        while True:
            data = conn.recv(1024)
            print(data.decode('utf-8'))
            if not data:
                break
                """
        data = get_data(connection)
        data=data.split('|')
        print(addr_user, data)
        if data[1]=='login':
            answer=str(Login(data[2],data[3]))
        elif data[1]=='reg':
            cou=find('users.db',"USERS",data[2])
            if cou==None:
                add_data_user('users.db',"USERS",[data[2],data[3], 0, 0])
                answer="1"
            else:
                answer="0"
        else:
            answer=str(Login(data[2],data[3]))
            if answer=="1":
                if data[1]=="statistic":
                    cou=find('users.db',"USERS",data[2])
                    cou=list(cou)
                    answer="-"+str(cou[3])+"-"+str(cou[4])+"-"
                if data[1]=="statistic_all":
                    cou=get_all_stat("users.db")
                    cou=list(cou)
                    answer="-"+str(cou)+"-"
                if data[1]=="create_room":
                    cou=create_room("rooms.db",data[4],data[5])
                    answer="-"+str(cou)+"-"
                if data[1]=="find_room":
                    cou=find_room("rooms.db",data[4],data[5])
                    answer="-"+str(cou)+"-"
                if data[1]=="check_freedoom":
                    cou=check_freedoom("rooms.db",data[4])
                    answer="-"+str(cou)+"-"
                if data[1]=="get_user":
                    cou=get_user("rooms.db",data[4],data[5])
                    answer="-"+str(cou)+"-"
                if data[1]=="statistic_u":
                    cou=statistic_u("users.db",data[4])
                    cou="-"+str(cou[0])+"-"+str(cou[1])+"-"
                    answer=cou
                if data[1]=="room_pass":
                    ans=get_line_room("rooms.db",data[4])
                    cou="-0-"
                    us1=ans[2].split('=')[0]
                    us2=ans[4].split('=')[0]
                    print("us=",us1,"|",us2,"|",data[2])
                    if str(data[2])==str(us1) or str(data[2])==str(us2):
                        print("us=",us1,"|",us2)
                        cou="-"+str(ans[7])+"-"
                    answer=cou
                if data[1]=="set_win":
                    cou=set_win("users.db",[5,1,data[4]])
                    answer="-"+str(cou)+"-"
                if data[1]=="get_ready":
                    ans="2"
                    line=get_line_room("rooms.db",data[4])
                    if data[5]=="-1":
                        if line[3]==1 and line[5]==0:
                            ans="1"
                        else:
                            ans="0"
                    elif data[5]=="1":
                        if line[3]==0 and line[5]==1:
                            ans="1"
                        else:
                            ans="0"
                    answer="-"+str(ans)+"-"
                if data[1]=="set_ready":
                    ans="2"
                    if data[5]=="-1":
                        ans=set_ready("rooms.db",["0","1",data[4]])
                    elif data[5]=="1":
                        ans=set_ready("rooms.db",["1","0",data[4]])
                    answer="-"+str(ans)+"-"
                if data[1]=="set_exp":
                    cou=set_exp("users.db",[data[5],data[4]])
                    answer="-"+str(cou)+"-"
            else:
                answer="0"

        print("answer=", answer)
        print("USERS")
        sql_cmd_select_all("users.db","USERS")
        print("ROOMS")
        sql_cmd_select_all("rooms.db","ROOMS")
        send_data(connection, answer)
    except Exception as e:
        print(e)
    finally:
        connection.close()




if __name__ == '__main__':
    if len(sys.argv)>2:
        HOST=sys.argv[1]
        PORT=int(sys.argv[2])
    else:
        HOST='localhost'
        PORT=5555
    # print("HOST=",HOST,"\n","PORT=",PORT)
    print("Server started successfully")
    list_ip=[]
    #if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.bind((HOST, PORT))
    sock.listen(50)

    while True:
        connection, addr_user = sock.accept()
        list_ip.append([addr_user, connection])
        print('Connected by', addr_user)
        try:
            thread = Thread(
                target=run,
                args=(connection, addr_user),
                daemon=True)
            thread.start()
        except (Exception, KeyboardInterrupt) as e:
            print(e)
            connection.close()
            break





