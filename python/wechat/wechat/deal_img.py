# -*- coding: UTF-8 -*-

import MySQLdb

class CDataBase:
    def __init__(self,addr,usr,pwd,db):
        self.address = addr
        self.user = usr
        self.password = pwd
        self.database = db
        self.connect = 0
        self.cursor = 0

    def build_connect(self):
        try:
            self.connect = MySQLdb.connect(self.address,self.user,self.password,self.database,charset='utf8')
            self.cursor = self.connect.cursor()
            self.cursor.execute("SELECT VERSION()")
            data = self.cursor.fetchone()
            print "Database version : %s " % data
        except:
            print 'error occur when build a connect'

    def isExistTable(self):
        self.cursor.execute(
            "select count(1) from information_schema.tables  where table_schema = 'nie' and table_name = 'wx_img'")
        data = self.cursor.fetchone()

        if data[0] == 0:
            print 'falg'
            self.cursor.execute("create table wx_img(id INT primary  key AUTO_INCREMENt,name varchar(50),remark varchar(256), img longblob)")

    def exit(self):
        self.connect.close()

    def insert(self, name, remark, img):
        try :
            if self.cursor:
                sql = "insert into wx_img(name,remark,img) VALUES(%s,%s,%s)"
                args = (name, remark, (MySQLdb.Binary(img)))
                self.cursor.execute(sql, args)
                self.connect.commit()
        except:
            print 'error occur when insert data'
            self.connect.rollback()

    def query(self, name):
        try:
            if self.cursor:
                sql = "select * FROM wx_img "
                if name:
                    args = (name,)
                    sql += " where name = %s "
                    self.cursor.execute(sql, args)
                else:
                    self.cursor.execute(sql)
                result = self.cursor.fetchall()
                for i in result:
                    print i[0]
                    print i[1]
                    print i[2]
                    print i[3]

        except:
            print 'error occur when query data'
            self.connect.rollback()
