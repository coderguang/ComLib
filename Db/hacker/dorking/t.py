#!/usr/bin/python

import ConfigParser
import MySQLdb

#read config.ini
config=ConfigParser.ConfigParser()
config.readfp(open('../../../../config.ini'))

host=config.get("dbconfig","host")
user=config.get("dbconfig","user")
passwd=config.get("dbconfig","passwd")

#connect to mysql db

conn=MySQLdb.connect(host=host,user=user,passwd=passwd)
conn.select_db('hacker')

#get curs point
curs=conn.cursor()

#create tables

createTableFront="create table if not exists dorking_"

createTableEnd="(ip varchar(32) not null primary key,p135 int default 0,p137 int default 0,p138 int default 0,p139 int default 0,p445 int default 0,p593 int default 0,p1025 int default 0,p1900 int default 0,p2745 int default 0,p3389 int default 0,p6129 int default 0,user varchar(32),passwd varchar(32));"

for i in range(1,255):
  createStr=createTableFront+str(i)+createTableEnd
  curs.execute(createStr)

#free the curs
curs.close();

#close the connection
conn.close();

