#!/bin/bash
source ../../config

mysql -h $host -u$user -p$passwd  <<EOF 

#create hacker db if not exits
create database if not exists hacker;

use hacker;

#create datbase
create table if not exists hacker_dorking(
  ip varchar(32) not null primary key,
  p135 int default 0,
  p137 int default 0,
  p138 int default 0,
  p139 int default 0,
  p445 int default 0,
  p593 int default 0,
  p1025 int default 0,
  p1900 int default 0,
  p2745 int default 0,
  p3389 int default 0,
  p6129 int default 0,
  user varchar(32),
  passwd varchar(32) 
  );

EOF
