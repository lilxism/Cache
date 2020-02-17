#include "Set.h"
#include <sys/time.h>
#include <iostream>
using namespace std;

Set::Set(int b,int e){
  blockSize=b;
  blocksPerSet=e;

  //put the blocks into set
  int i=0;
  for(i=0;i<blocksPerSet;i++){
    blocks.push_back(new Block(blockSize));
  }
}

//read method
//return 0 for cache hit
//return 1 for cache miss
//return 2 fro a cache miss with a write back on eviction
int Set::read(unsigned int tag){
  int value;
  struct timeval tv;
  struct tm* tm;
  struct timezone tz;
    
  int i=checkSet(tag);
  if(i!=-1){
    //tag is found!
    value=0; //hit
  }else{
    //tag is not found
    value=1;//miss
    i=0;
    while(i<blocksPerSet && blocks[i]->isValid()==1){
      i++;
    }
    if(i==blocksPerSet){ //the set is full
      i=getLRU();
	  
      if(blocks[i]->isDirty()==1){
	value=2;//miss and write back
      }
    }
  //update the tag, dirty, validity
  blocks[i]->setTag(tag);
  blocks[i]->setDirty(0);
  blocks[i]->setValid(1);
  }

  //create a timestamp
  gettimeofday(&tv,&tz);
  tm=localtime(&tv.tv_sec);
  int hour =tm->tm_hour;
  int min=tm->tm_min;
  int sec=tm->tm_sec;
  long usec=tv.tv_usec;
  
  //set timestamp
  blocks[i]->setTimestamp(hour,min,sec,usec);
  
  return value;
}
//write method
int Set::write(unsigned int tag){
  int value;
  int i=checkSet(tag);
  struct timeval tv;
  struct tm* tm;
  struct timezone tz;
  if(i!=-1){
    //tag is found!
    value=0; //hit

  }else{
    //tag is not found
    value=1;//miss
    i=0;
    while(i<blocksPerSet && blocks[i]->isValid()==1){
      i++;
    }
    if(i==blocksPerSet){ //the set is full
      i=getLRU();
      if(blocks[i]->isDirty()==1){
	value=2;//miss and write back
      }
    }
  //update the tag, valid
  blocks[i]->setTag(tag); 
  blocks[i]->setValid(1);

  }
  //update dirty and time
  blocks[i]->setDirty(1);

  //create a timestamp
  gettimeofday(&tv,&tz);
  tm=localtime(&tv.tv_sec);
  int hour =tm->tm_hour;
  int min=tm->tm_min;
  int sec=tm->tm_sec;
  long usec=tv.tv_usec;
  
  //set timestamp
  blocks[i]->setTimestamp(hour,min,sec,usec);
  return value;
  }

//check to see if the memory is in set
int Set::checkSet(unsigned int tag){
  int i=0;
  int found=-1;
  for(i=0;i<blocksPerSet;i++){
    if(blocks[i]->getTag()==tag && (blocks[i]->isValid()==1)){
      found=i;
    }
  }
  return found; 
  }

//return the index of the least recently used blockPerSet
int Set::getLRU(){
  int LRUIndex = 0;
  
  int i=1;
  while(i<blocksPerSet){
	  int LRUhour=blocks[LRUIndex]->getHour();
  int LRUmin=blocks[LRUIndex]->getMin();
  int LRUsec=blocks[LRUIndex]->getSec();
  long LRUusec=blocks[LRUIndex]->getUsec();
  
	   int hour=blocks[i]->getHour();
		int min=blocks[i]->getMin();
		int sec=blocks[i]->getSec();
		long usec=blocks[i]->getUsec();
	  if(LRUhour>hour){
		 LRUIndex=i;
	  }else if(LRUhour==hour){
		  if(LRUmin>min){
			  LRUIndex=i;
		  }else if(LRUmin==min){
			  if(LRUsec>sec){
				  LRUIndex=i;
			  }else if(LRUsec==sec){
				  if(LRUusec>usec){
					  LRUIndex=i;
				  }
			  }
		  }
	  }
	  i++;
  }
  return LRUIndex;
}
//display the contents of the set
void Set::display(){
  int i=0;
  for(i=0;i<blocksPerSet;i++){
    //display validity
    cout<<"Block "<<i<<endl;
    if(blocks[i]->isValid()==1){
      cout<<"Block:valid "<<endl;
    }else{
      cout<<"Block:invalid "<<endl;
    }
    
    //display tag
    if(blocks[i]->getTag()==-1){
      cout<<"Tag: not set"<<endl;
    }else{
      cout<<"Tag: "<<blocks[i]->getTag()<<endl;
    }
    
    //display if it is dirty
    if(blocks[i]->isDirty()==1){
      cout<<"Dirty: yes"<<endl;
    }else{
      cout<<"Dirty: no"<<endl;
    }
    
    //Display time
    cout<<"Last used: "<< blocks[i]->getHour() <<"hrs : "<< blocks[i]->getMin() <<"min :"<< blocks[i]->getSec() <<"sec :"<< blocks[i]->getUsec() <<"usec"<<endl;
    
  }
}

//get dirty blocks
int Set::getDirtyBlocks(){
  int total=0;
  int i=0;
  for(i=0;i<blocksPerSet;i++){
    if(blocks[i]->isDirty()==1){
	total++;
    }
  }
  return total;
}


