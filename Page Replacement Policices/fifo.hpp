#pragma once
#include<iostream>
#include <queue>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

void fifo(int val, char rw, std::queue<int> &pt, int cap, std::set<int> &mp, int &diskRead, int &diskWrite, std::map<int,int> &write);