#!/bin/bash


ip=$1


echo "start scanning..." 

function scan(){
for i in `seq 1 10000`;do
      nc -z $ip $i
done 
}

scan 
echo "end scanning..."
