#include <queue>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

//using namespace std;

//void fifo(int val, char rw, std::queue<int> &pt, int cap, std::set<int> &mp, int &f, int &h, std::map<int,int> &write); //first in first out
//void lru(int val, char rw, int cap, std::map<int,int> &lruMap, int&faults, int &hits, std::map<int,int> &write); //least recently used
//void sfifo(int val, char rw, std::queue<int> &pt, int cap, int percentage, std::set<int> &mp, std::map<int,int> &secondaryBuffer, int &f, int &h, std::map<int,int> &write); //segmented-fifo
//helper functions
int convert(std::string num); //converts the hexadecimal address into a decimal value
int getPageNumber(std::string address); //uses the convert function to convert the first 20 bits of address to decimal page number
