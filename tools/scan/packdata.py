#!/usr/bin/python

#get all ip and port in log.txt
#and save all ip and port in logdata.txt which will use to log to db

import re

pattern=re.compile(r'\d+')

file=open("log.txt","r")
while True:
  line=file.readline();
  if line:
    datas=pattern.findall(line)
    if datas:
      print '.'.join(datas[:-1]) ,
      print datas[-1]
  else:
    break

file.close()

