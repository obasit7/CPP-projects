To compile the program:
- Run make, to compile all the files.
- Make sure to include main.c and readerwriter.h on the same directory.
- Alternatively, could also run gcc -o rwmain main.c -l pthread.

To run the program:
- Include scenarios.txt to run an scenario for the program.
- In addition, you could modify that scenario to test other scenarios (1 scenario per run). 
- run ./rwmain to see the result.
- The following sccenarios were tested:
  rwrrrrwrr wwrrrrwr  

- An example fro when the process runs for rwrrrrwrr is as follows:

$ make 
gcc     -o    rwmain     main.c   -l    pthread
 ./rwmain
Scenario Starts:
Create Reader
Reader is reading...
Create Writer
Create Reader
Create Reader
Create Reader
Create Reader
Create Writer
Create Reader
Create Reader
Reader is done reading
Writer is now writing
Writer is done writing
Reader is reading...
Reader is reading...
Reader is reading...
Reader is reading...
Reader is done reading
Reader is done reading
Reader is done reading
Reader is done reading
Writer is now writing
Writer is done writing
Reader is reading...
Reader is reading...
Reader is done reading
Reader is done reading
