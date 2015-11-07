#!/bin/bash


ip=$1


echo "start scanning..." 

#function scan(){
#for i in `seq 1 65535`;do
      nc -z $ip 1-65535
#done 
#}

#scan 
echo "end scanning..."
