This project I evaluate how real applications respond to a variety of page replacement algorithms. 
For  this,  I  wrote  a  memory  simulator  and evaluate  memory  performance  using  provided  traces  from real applications.
The following replacement policies are implemented:
1- FIFO   2- LRU  3- Segemted-FIFO

use make to compile all the files together
or g++ -std=c++11 -o memsim main.cpp algorithms.cpp fifo.cpp lru.cpp segmented-fifo.cpp

The command line takes the following argument format:
memsim <tracefile> <nframes> <lru|fifo|vms> <debug|quiet>  
where,
  tracefile  - file name with traces
  nframes    -  number  of  page frames  in  the  simulated  memory
  lru|fifo|vms - page  replacement  algorithm  
  debug|quiet -  type of output. Debug gives a detailed analysis while quiet gives outcome at the end
  
In case of segmented fifo(vms) there is an additional argument in the form:
memsim <tracefile> <nframes> <lru|fifo|vms> <p> <debug|quiet>   
where “p” will be a number between 1 to 100 indicating percentage of primary memory space
  
