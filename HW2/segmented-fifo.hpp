#pragma once
#include<iostream>
#include <queue>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

void sfifo(int val, char rw, std::queue<int> &pt, int cap, int percentage, std::set<int> &mp, std::map<int,int> &secondaryBuffer, int &f, int &h, std::map<int,int> &write);