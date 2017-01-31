#include "Utilities.h"
#include <iostream>

using namespace std;

Inv_PT::Inv_PT(int n_arg,Counter *count_arg):n(n_arg),count(count_arg){
  pid = new int[n];
  page = new int[n];
  dirty = new bool[n];
  victim = new bool[n];

  int i;
  for(i=0;i<n;i++) dirty[i]=false;
  for(i=0;i<n;i++) victim[i]=true;
}

Inv_PT::~Inv_PT(){
  delete[] pid;
  delete[] page;
  delete[] dirty;
  delete[] victim;
}

void Inv_PT::Insert(int pid_arg,int page_arg,bool dirty_bit){
  int i;
  count->page_fault();//h selida den uparxei ston ipt

  for(i=0;i<n;i++){//scan
    if(victim[i]==true){
      if(dirty[i]) count->write_back();//an einai dirty to bit ths victim
      pid[i]=pid_arg;//pername ta orismata
      page[i]=page_arg;
      dirty[i]=dirty_bit;
      victim[i]=false;
      return;
    }
  }
  cout << "Something is wrong" << endl;
}

void Inv_PT::Dirt(int pid_arg,int page_arg){
  int i;

  for(i=0;i<n;i++){
    if(pid[i]==pid_arg && page[i]==page_arg) dirty[i]=true;//check an einai dirty
  }
}

void Inv_PT::Victimize(int pid_arg){
  int i;

  for(i=0;i<n;i++){
    if(pid[i]==pid_arg) victim[i]=true;//an vrei to arg ginetai victim
  }
}

void Inv_PT::Print_Test(){
  int i;

  cout << "Ipt contains:" << endl;
  for(i=0;i<n;i++){
    cout << "Pid: " << pid[i] << " Page: " << page[i] << " Dirty Bit: " << dirty[i] << " Victim: " << victim[i] << endl;
  }
}

FWF_stack::FWF_stack(int pid_arg,int n_arg,Inv_PT *ipt_arg):pid(pid_arg),n(n_arg),current(0),ipt(ipt_arg){
  int i;
  pages = new int[n];
}

FWF_stack::~FWF_stack(){
  delete[] pages;
}

void FWF_stack::New_Trace(int page,bool dirty){
  int i;
  bool found=false;

  for(i=0;i<current;i++){ //Search page on stack
    if(pages[i]==page){found=true; break;}
  }

  if(found==false && current==n){ //Its Full,we need to Flush
    ipt->Victimize(pid);
    current=0;
    pages[current]=page;
    current++;
    ipt->Insert(pid,page,dirty);
  }
  else if(found==false){ //Ipt Insertion
    pages[current]=page;
    current++;
    ipt->Insert(pid,page,dirty);
  }
  else if(dirty){ //Page found but we have to update the dirty bit on ipt
    ipt->Dirt(pid,page);
  }
}










//lala
