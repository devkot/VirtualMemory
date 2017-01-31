#include "Memory_Manager_Unit.h"
#include <iostream>

using namespace std;

Mem_Manager::Mem_Manager(int memory_frames,int fwf_frames):mem_frames(memory_frames),traces_read(0){
  int stack_size = fwf_frames;
  if(memory_frames/2 < fwf_frames){
    cout << "FWF stack size is set to memory_frames/2 = " << memory_frames/2 << endl;
    stack_size=memory_frames/2;
  }
  count = new Counter();
  ipt = new Inv_PT(mem_frames,count);
  proc0 = new FWF_stack(0,stack_size,ipt);
  proc1 = new FWF_stack(1,stack_size,ipt);
}

Mem_Manager::~Mem_Manager(){
  delete count;
  delete ipt;
  delete proc0;
  delete proc1;
}

void Mem_Manager::New_Trace(int pid,int page,bool write){
  traces_read++;
  if(pid==0) proc0->New_Trace(page,write);
  else if(pid==1) proc1->New_Trace(page,write);
  else cout << "Pid " << pid << " is out of bound" << endl;
}

void Mem_Manager::Stats(){
  cout << "Page Faults: " << count->get_pf() << endl;
  cout << "Write Backs: " << count->get_wb() << endl;
  cout << "Memory Frames: " << mem_frames << endl;
  cout << "Traces Read: " << traces_read << endl;
  ipt->Print_Test();
}
