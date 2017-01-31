#include <iostream>
#include <fstream>

#include <string.h>
#include <stdlib.h>

#include "Memory_Manager_Unit.h"
#define FRAME_SIZE 4096

using namespace std;

int main(int argc,char **argv){ //Arguments Checking

    if(argc!=7 && argc!=9){
        cout << "Wrong Input" << endl;
        cout << "Input format:<-f> memory frames, <-k> FWF argument , <-q> #traces per time , [<-m> max number of traces]" << endl;
        return 1;
    }
    int i,frames=0,q=0,max=-1,k=0;

    for(i=1;i<argc;i=i+2){//get arguments
        if(strcmp("-f",argv[i])==0){
            frames=atoi(argv[i+1]);
        }
        else if(strcmp("-q",argv[i])==0){
            q=atoi(argv[i+1]);
        }
        else if(strcmp("-m",argv[i])==0){
            max=atoi(argv[i+1]);
        }
        else if(strcmp("-k",argv[i])==0){
            k=atoi(argv[i+1]);

        }
        else{
            cout << "Wrong Input" << endl;
            cout << "Input format:<-f> memory frames, <-k> FWF argument , <-q> #traces per time , [<-m> max number of traces]" << endl;
        }
    }
    if(frames==0 || q==0){
        cout << "Wrong Input" << endl;
        cout << "Input format:<-f> memory frames, <-k> FWF argument , <-q> #traces per time , [<-m> max number of traces]" << endl;
        return 3;
    }
    if(max==-1){
        cout << "Simulation will use the whole trace files" << endl;
    }
    Mem_Manager manager(frames,k);

    //Files Parsing
    ifstream first;
    ifstream second;

    first.open("bzip.trace");
    second.open("gcc.trace");

    if(first.is_open()==false){
        cout << "Couldnt open bzip.trace file" << endl;
        return 4;
    }
    if(second.is_open()==false){
        cout << "Couldnt open gcc.trace file" << endl;
        return 4;
    }
    first.eof();
    second.eof();

    unsigned int trace,q_left;
    string order;

    while((first.eof()==false || second.eof()==false) && (max>0 || max==-1)){
        q_left=q;
        while(q_left>0 && (max>0 || max==-1)){
            first >> hex >> trace;
            if(first.good()==false) break; //In case of EOF or error
            first >> order;
            if(order.compare("R")==0){
                manager.New_Trace(0,trace/FRAME_SIZE,false); //Page_Number = Trace / Frame_Size
            }
            else if(order.compare("W")==0){
                manager.New_Trace(0,trace/FRAME_SIZE,true);
            }
            else{
                cout << "Warning: bzip.trace file is harmed,abort line." << endl ;
                continue;
            }
            q_left--;
            if(max!=-1) max--;
        }

        q_left=q;
        while(q_left>0 && (max>0 || max==-1)){
            second >> hex >> trace;
            if(second.good()==false) break;
            second >> order;
            if(order.compare("R")==0){
                manager.New_Trace(1,trace/FRAME_SIZE,false);
            }
            else if(order.compare("W")==0){
                manager.New_Trace(1,trace/FRAME_SIZE,true);
            }
            else{
                cout << "Warning: gcc.trace file is harmed,abort line." << endl;
                continue;
            }
            q_left--;
            if(max!=-1) max--;
        }
    }
    manager.Stats();

    first.close();
    second.close();

    return 0;
}
