#include "algorithms.hpp"

int convert(std::string num) {
   int len = num.size();
   int base = 1;
   int temp = 0;
   for (int i=len-1; i>=0; i--) {
      if (num[i]>='0' && num[i]<='9') {
         temp += (num[i] - 48)*base;
         base = base * 16;
      }
      else if (num[i]>='a' && num[i]<='f') {
         temp += (num[i] - 87)*base;
         base = base*16;
      }
   }
   return temp;
}

int getPageNumber(std::string address){
    return convert(address.substr(0,5));
}