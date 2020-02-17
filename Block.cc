#include "Block.h"

Block::Block(int b){
  blockSize=b;
  
  //initialize the values
  tag=-1;
  valid=0;
  dirty=0;
  
  timestamp.hour=0;
  timestamp.min=0;
  timestamp.sec=0;
  timestamp.sec=0;
  
}
int Block::getTag(){
  return tag;
  }

int Block::isValid(){
  //is valid 0
  //not valid 1
  return valid;
}

int Block::isDirty(){
  //is dirty 0
    //is clean 1
  return dirty;
}

void Block::setTag(unsigned int newTag){
  tag=newTag;
}

void Block::setValid(int newValid){
  valid=newValid;
}

void Block::setDirty(int newDirty){
  dirty=newDirty;
}

void Block::setTimestamp(int hour,int min,int sec,long usec){
  timestamp.hour=hour;
  timestamp.min=min;
  timestamp.sec=sec;
  timestamp.usec=usec;
}
  
int Block::getHour(){
  return timestamp.hour;
}
int Block::getMin(){
  return timestamp.min;
}
int Block::getSec(){
  return timestamp.sec;
}
long Block::getUsec(){
  return timestamp.usec;
}
