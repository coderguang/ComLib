#python
#***********************************************
#
#      Filename: check.py
#
#      Author: coderguang 
#      Email: royalchen@royalchen.com
#      website: www.royalchen.com
#      Description: ----
#      example: python checkNullConn.py

#     Create: 2016-01-13 20:30:35
#     Last Modified: 2016-01-13 20:30:35
#***********************************************


#
#
#

import ConfigParser
import MySQLdb

#read config.ini

localConfig=ConfigParser.ConfigParser()
localConfig.readfp(open('nullConn.ini'))

globalFile=localConfig.get("nullConnConfig","dbconfig")
dbname=localConfig.get("nullConnConfig","dbname")
tableName=localConfig.get("nullConnConfig","tablename")


config=ConfigParser.ConfigParser()
config.readfp(open(globalFile))

host=config.get("dbconfig","host")
user=config.get("dbconfig","user")
passwd=config.get("dbconfig","passwd")

#connect to mysql db

conn=MySQLdb.connect(host=host,user=user,passwd=passwd)
conn.select_db(dbname)

#get curs point
curs=conn.cursor()

#create tables

checkStr="select * from "+tableName+" ;"
curs.execute(checkStr)

numrows=int(curs.rowcount)
results=curs.fetchall()
for line in  results:
  if line:
   ip=line[0]
   print ip,

#free the curs
curs.close();

#close the connection
conn.close();

