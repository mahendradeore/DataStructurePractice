#include<climits>
#include <vector>
#include <iostream>
//using namespace std;

int stockOptimizer(std::vector<int> prices) {
   int stockPrice = 0;
    int lowprice = INT_MAX;
    int maxindex;
   for(auto dayprice:prices){
      if(lowprice >= dayprice){
        lowprice = dayprice;
      }else {
        if(dayprice > lowprice){
          int newstockPrice = dayprice - lowprice;
          if(stockPrice < newstockPrice){
            stockPrice = newstockPrice;
          }
        }
      }
   }
  
    return stockPrice;
}


int main(int argc, char** argv) {
   
  
  if(6 == stockOptimizer({14,20,9})){
    std::cout <<"Success =  6 "<<std::endl;
  }else{
    std::cout <<"Failed  6 != " << stockOptimizer({14,20,9});
  }
   
  if(15 == stockOptimizer({5,20,15,13,3,15,5,10})){
    std::cout <<"Success =  15 "<< std::endl;
  }else{
    std::cout <<"Failed  15 != " << stockOptimizer({5,20,15,13,3,15,5,10});
  }
  if(10 == stockOptimizer({1,6,11,2})){
    std::cout <<"Success =  10 "<< std::endl;
  }else{
    std::cout <<"Failed  10 != " << stockOptimizer({5,20,15,13,3,15,5,10});
  }

  if(10 == stockOptimizer({15,5,2,0,5,8,7,4,2,10,1})){
    std::cout <<"Success =  10 "<< std::endl;
  }else{
    std::cout <<"Failed  10 != " << stockOptimizer({15,5,2,0,5,8,7,4,2,10,1});
  }

  if(15 == stockOptimizer({14,3,16,8,9,7,8,18,15,10,9})){
    std::cout <<"Success =  15 "<< std::endl;
  }else{
    std::cout <<"Failed  15 != " << stockOptimizer({14,3,16,8,9,7,8,18,15,10,9});
  }

}
