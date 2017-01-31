Virtual Memory C++ program developped for the Operating Systems course in University of Athens.

This program simulates a virtual memory and specifically an inverted page table. 
It uses two input files with hexadecimal memory traces and proceeds to read them. It keeps
a record of the page faults and write backs that took place during the simulation. 
There is a data structure called FWF that uses the Flush When Full algorithm to empty the
page table.
