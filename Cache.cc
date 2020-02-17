#include <iostream>
#include <vector>
#include <cmath>
#include "Cache.h"
using namespace std;

  Cache::Cache(int m, int c, int b, int e){
    addSize=m;
    cacheSize=c;
    blockSize=b;
    blocksPerSet=e;
    
    int i=0;
	//S = (C/(B*E))
    int setSize=(cacheSize/(blockSize*blocksPerSet));
    for(i=0;i<setSize;i++){
      sets.push_back(new Set(blockSize,blocksPerSet));
    }
  }

  
  int Cache::read(unsigned long memoryAdd){
	 
    //calculate the space needed to store block index
    int b=log2(blockSize); //bits to store block
    int s=log2((cacheSize/(blockSize*blocksPerSet))); //bits to store set
    int t=addSize-b-s; //bits to store tag
    
    unsigned int mask=0;
    int k=0;
    for(k=0;k<s;k++){
      mask=(mask<<1)|1;
    }
    
    //extracts the set index and the tag from the address
    unsigned int setIndex=(memoryAdd>>b)&mask;
    //cout<<setIndex<<" set "<<endl;
    unsigned int tagIndex=(memoryAdd>>(addSize-t));
    return sets[setIndex]->read(tagIndex);
    
  }

  int Cache::write(unsigned long memoryAdd){
   //calculate the space needed to store index
    int b=log2(blockSize); //bits to store block
    int s=log2((cacheSize/(blockSize*blocksPerSet))); //bits to store set
    int t=addSize-b-s; //bits to store tag

    unsigned int mask=0;
    int k=0;
    for(k=0;k<s;k++){
      mask=(mask<<1)|1;
    }
    
    //extracts the set index and the tag from the address
    unsigned int setIndex=(memoryAdd>>b)&mask;
    unsigned int tagIndex=(memoryAdd>>addSize-t);
    return sets[setIndex]->write(tagIndex);
  }

  //dump how many cache values need to be written back to main memory
  int Cache::dump(){
    int total=0;
	int i=0;
	for(i=0;i<(cacheSize/(blockSize*blocksPerSet));i++){
		total+=sets[i]->getDirtyBlocks();
	}
	return total;
  }

  //dump the contents of the cache to the screen for debugging
  void Cache::display(){
    int i=0;
	for(i=0;i<(cacheSize/(blockSize*blocksPerSet));i++){
		sets[i]->display();
	}
  }
  
