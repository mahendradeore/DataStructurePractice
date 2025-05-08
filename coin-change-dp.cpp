/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int coinchangecombi(vector<int> &coins, int amount){
    
    vector<int>dp (amount+1,0);
    dp[0] = 1;
    
    for(int coin : coins){
        for(int i = coin; i <= amount;++i){
            dp[i]= dp[i] + dp[i-coin];
        }
    }
    return dp[amount];
    
}

void dfsbacktracking(vector<int> &coins, int index,int amount,vector<vector<int>> & result, vector<int> & path){
    
    if(amount == 0 ){
        result.push_back(path);
        return;
    }
    for(int i = index; i < coins.size();++i ){
        if(coins[i] <= amount){
            path.push_back(coins[i]);//pushing coin in path as it is less tha ammont
            dfsbacktracking(coins,i,amount-coins[i],result,path);//substract coin from amount and send it back to tracking.
            path.pop_back();
        }
    }
    
}
void printAllCombinations(vector<int> &coins, int amount){
    
     vector<vector<int>> result;
     vector<int> path;
     
     dfsbacktracking(coins,0,amount,result,path);
     
     cout << "Combinations to make " << amount << ":\n";
     for (const auto& combo : result) {
        for (int coin : combo) cout << coin << " ";
        cout << "\n";
    }
     
}
int main()
{
    
    vector<int> coins = {1,2,5};
    cout << "Combinatrion for change fpr amount 5 =  " <<  coinchangecombi(coins,5) << endl;
    cout << "Combinatrion for change amount 7 =  " <<  coinchangecombi(coins,10) << endl;
    cout << "Combinatrion for change amount 10 =  " <<  coinchangecombi(coins,10) << endl;
    
    printAllCombinations(coins, 5);
    printAllCombinations(coins, 10);
    printAllCombinations(coins, 15);

    return 0;
}