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

localConfig=ConfigParser.ConfigParser()
localConfig.readfp(open('dorking.ini'))

globalConfigPath=localConfig.get("dorkingConfig","dbconfig")
dbname=localConfig.get("dorkingConfig","dbname")

globalConfig=ConfigParser.ConfigParser()
globalConfig.readfp(open(globalConfigPath))

host=globalConfig.get("dbconfig","host") 
user=globalConfig.get("dbconfig","user")
passwd=globalConfig.get("dbconfig","passwd")

#connect to mysql db

conn=MySQLdb.connect(host=host,user=user,passwd=passwd)
conn.select_db(dbname)

#get curs point
curs=conn.cursor()

pattern=re.compile(r'\d+')

tableName="dorking"
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

