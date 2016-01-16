#python		
#***********************************************		
#		
#      Filename: writeT.py		
#		
#      Author: coderguang 		
#      Email: royalchen@royalchen.com		
#      website: www.royalchen.com		
#      Description: ----		
#      example: change fileReader to your data file path in dorking.ini		
		
#     Create: 2016-01-13 20:31:18		
#     Last Modified: 2016-01-13 20:31:18		
#***********************************************		
		
		
import ConfigParser		
import MySQLdb		
import re		
		
#read config.ini		
#read config.ini		
		
localConfig=ConfigParser.ConfigParser()		
localConfig.readfp(open('dorking.ini'))		
		
globalConfigPath=localConfig.get("dorkingConfig","dbconfig")		
dbname=localConfig.get("dorkingConfig","dbname")		
ipSrc=localConfig.get("dorkingFile","datafile")		
		
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
		
#make the pattern 		
pattern=re.compile(r'\d+')		
		
#get data file		
		
fileReader=open(ipSrc)		
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
