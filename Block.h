class Block{
private:
  int blockSize;
  int tag;
  int valid;
  int dirty;

  struct Timestamp{
    int hour;
    int min;
    int sec;
    long usec;
  };

  Timestamp timestamp;

public:

  Block(int blockSize);
  int getTag();
  
  int isValid();
  
  int isDirty();
  
  void setTag(unsigned int newTag);
  
  void setValid(int valid);
  
  void setDirty(int newDirty);
  
  void setTimestamp(int hour,int min,int sec,long usec);
  
  int getHour();
  
  int getMin();
  
  int getSec();
  
  long getUsec();

};
