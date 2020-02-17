#include <vector>

#include "Block.h"

class Set{
private:
  int blockSize;
  int blocksPerSet;
  std::vector <Block*> blocks;
  
  struct Timestamp{
    int hour;
    int min;
    int sec;
    long usec;
  };
  
public:
  Set(int blockSize,int blocksPerSet);
  
  //read method
  //return 0 for cache hit
  //return 1 for cache miss
  //return 2 fro a cache miss with a write back on eviction
  int read(unsigned int tag);
  //write method
  int write(unsigned int tag);
  
  //check to see if the memory is in set
  int checkSet(unsigned int tag);
  
  //return the index of the least recently used blockPerSet
  int getLRU();
  //display the contents of the set
  void display();
  
  //get dirty blocks
  int getDirtyBlocks();
};
  
  
