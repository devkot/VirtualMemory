#include "Utilities.h"

class Mem_Manager{
  Counter *count;
  Inv_PT* ipt;
  FWF_stack *proc0,*proc1;
  int mem_frames;
  int traces_read;
public:
  Mem_Manager(int memory_frames,int fwf_frames);
  void New_Trace(int pid,int page,bool write);
  void Stats();
  ~Mem_Manager();
};
