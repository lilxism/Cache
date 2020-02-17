#include "Set.h"
class Cache{
private:
  int addSize; //the size of memory address in bits
  int cacheSize;//size of cache in bytes
  int blockSize;//size of blocks in bytes
  int blocksPerSet;//number of blocks per set
  std::vector<Set*>sets;

public:
  Cache(int m, int c, int b, int e);

  //return 0 for cache hit
  //return 1 for cache miss
  //return 2 fro a cache miss with a write back on eviction
  int read(unsigned long memoryAdd);

  int write(unsigned long memoryAdd);

  //dump the cache and return how many cache values need to be written back to main memory
  int dump();

  //dump the contents of the cache to the screen for debugging
  void display();
  
};
