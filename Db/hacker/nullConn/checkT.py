#python
#***********************************************
#
#      Filename: checkT.py
#
#      Author: coderguang 
#      Email: royalchen@royalchen.com
#      website: www.royalchen.com
#      Description: ----
#      example: python checkT.py 3389

#     Create: 2016-01-13 20:29:23
#     Last Modified: 2016-01-13 20:29:23
#***********************************************


import ConfigParser
import MySQLdb
import re
import sys

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

pattern=re.compile(r'\d+')

for i in range(254):
  tableName="dorking_"+str(i+1)
  checkStr="select ip from "+tableName+" where p"+str(sys.argv[1])+"='1\'"
  curs.execute(checkStr)
  #get the result rowcount
  numrows=int(curs.rowcount)
  results=curs.fetchall()
  for line in results:
    ipStr=line[0]
    print ipStr
      
#free the curs
curs.close();

#close the connection
conn.close();

