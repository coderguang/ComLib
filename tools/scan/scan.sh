#!/bin/bash


front=$1
pos=$2

port=(135 137 138 139 445 593 1025 1900 2745 3127 3389 6129) 
one=1
len=`expr ${#port[@]} - 1`
point="."
dir="../../../data/hacker/logEx/"

echo "start scanning..." >>$dir$pos$front

function scan(){
for i in `seq 1 255`;do
  for j in `seq 1 255`;do
    for k in `seq 0 $len`;do
      nc -w 5 $front$point$i$point$j -z ${port[$k]}
    done
  done
done 
}

scan 1&>>$dir$pos$front
echo "end scanning...">>$dir$pos$front
