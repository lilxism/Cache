#include <iostream>
#include "Cache.h"

using namespace std;
//drive the simulation
//create new Cache
//read write tests to determine cache performs
int main(){
 
  //first cache
 cout<<"Following test uses cache(4,8,2,1):"<<endl;

  Cache* c1 = new Cache(4,8,2,1);
  int i=0;
  int total1=0;  
  for(i=0;i<16;i++){
    total1+=c1->read(i);
  }
  total1+=c1->dump();
  cout<<"1)"<<total1<<endl;
  
  //2
  int total2=0;
  total2+= c1->read(0);
  total2+= c1->read(8);
  total2+= c1->read(1);
  total2+= c1->read(9);
  total2+=c1->dump();
  cout<<"2)"<<total2<<endl;
  
  //second cache
  cout<<"Following test uses cahce(4,8,2,2):"<<endl;
  //3
  int total3=0;
  Cache* c2 = new Cache(4,8,2,2);  
  for(i=0;i<16;i++){
    total3+=c2->read(i);	 
  }
  total3+=c2->dump();
  cout<<"3)"<<total3<<endl;

  //4
  int total4=0;
  total4 += c2->read(0);
  total4 += c2->read(8);
  total4 += c2->read(1);
  total4 += c2->read(9);
  total4+=c2->dump();
  cout<<"4)"<<total4<<endl;

 cout<<"Following test uses cache(4,8,2,2):"<<endl;
 Cache* c3=new Cache(4,8,2,2); 
  //5
  int total5=0;
  total5+=c3->read(0);
  total5+=c3->read(4);
  total5+=c3->read(8);
  total5+=c3->read(0);
  total5+=c3->dump();
  cout<<"5)"<<total5<<endl;
  
  //6
  Cache* c4=new Cache(4,8,2,2);
  int total6=0;
  total6+=c4->read(0);
  total6+=c4->read(0);
  total6+=c4->write(4);
  total6+=c4->read(8);
  total6+=c4->dump();
  cout<<"6)"<<total6<<endl;
   
   //7
  cout<<"Following test uses cache(16,256,16,4):"<<endl;
  Cache* c5 = new Cache(16,256,16,4);
  int total7=0;
  for(i=0;i<8192;i++){
    total7+=c5->read(i);
    total7+=c5->write(i);
  }
  total7+=c5->dump();
  cout<<"7)"<<total7<<endl;
 
 Cache* c6 = new Cache(16,256,16,4);
   //8
   int total8=0;
   i=0;
   while(i<8192){
     total8+=c6->read(i);
     total8+=c6->write(i);
     i=i+16;
   }
  total8+=c6->dump();
   cout<<"8)"<<total8<<endl;
 
}
