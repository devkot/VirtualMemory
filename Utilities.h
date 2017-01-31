
class Counter{//class gia counter
  int page_faults;
  int write_backs;
public:
  Counter():page_faults(0),write_backs(0){};
  void page_fault(){page_faults++;};
  void write_back(){write_backs++;};
  int get_pf(){return page_faults;};
  int get_wb(){return write_backs;};
};

class Inv_PT{
  int n;//arithmos thesewn pinaka
  int *pid;//pinakas pou krataei pid
  int *page;//pinakas pou krataei selides
  bool *dirty;//pinakas gia dirty
  bool *victim;//pinakas gia victim
  Counter *count;//metrhths
public:
  Inv_PT(int,Counter*);//constructor
  void Insert(int pid_arg,int page_arg,bool dirty_bit); //Inserts page at the first victim frame,true if victim was dirty,false otherwise
  void Dirt(int pid_arg,int page_arg);
  void Victimize(int pid_arg); //Victimize every page from proc
  void Print_Test();
  ~Inv_PT();
};

class FWF_stack{
  int pid;
  int n;
  int current;
  int *pages;
  Inv_PT *ipt;
public:
  FWF_stack(int pid_arg,int n_arg,Inv_PT *ipt_arg);
  ~FWF_stack();
  void New_Trace(int page,bool dirty);
};
