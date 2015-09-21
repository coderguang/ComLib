#!/usr/bin/python

import ConfigParser
import MySQLdb
import re

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

#make the pattern 
pattern=re.compile(r'\d+')

#get data file

fileReader=open("../../../../data/hacker/data.txt")
while True:
  line=fileReader.readline();
  if line:
    datas=pattern.findall(line)
    if datas:
      tableName="dorking_"+str(datas[0])
      ipStr='.'.join(datas[:-1])
      portStr=datas[-1]
      #at first ,encure the tables has no this record
      checkStr="select ip from "+tableName+" where ip=\'"+ipStr+"\'"
      curs.execute(checkStr)
      #get the result rowcount
      numrows=int(curs.rowcount)
      if numrows==0:
        #insert a null record at first
        insertStr="insert into "+tableName+" values(\'"+ipStr+"\',0,0,0,0,0,0,0,0,0,0,0,0,NULL,NULL);"
        #insert/update the record to db
        curs.execute(insertStr)
      #commit the change
      conn.commit()
      #update the recored
      updateStr="update "+tableName+" set "+"p"+str(portStr)+"=1 where ip=\'"+ipStr+"\'"
      curs.execute(updateStr)
      conn.commit()
  else:
    break;   


#free the curs
curs.close();

#close the connection
conn.close();

