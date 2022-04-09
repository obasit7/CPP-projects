#pragma once
#include<iostream>
#include <queue>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

void lru(int val, char rw, int cap, std::map<int,int> &lruMap, int&faults, int &hits, std::map<int,int> &write);