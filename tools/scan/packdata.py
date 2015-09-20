#!/usr/bin/python

#get all ip and port in log.txt
#and save all ip and port in logdata.txt which will use to log to db

import re

pattern=re.compile(r'\d+')

fileReader=open("../../../data/hacker/log.txt","r")
fileWriter=open("../../../data/hacker/data.txt","w+")
while True:
  line=fileReader.readline();
  if line:
    datas=pattern.findall(line)
    if datas:
      ipStr='.'.join(datas[:-1])
      portStr=datas[-1]
      fileWriter.write(ipStr+' '+portStr+'\n')
      print ipStr,portStr
  else:
    break

fileReader.close()
fileWriter.close()

