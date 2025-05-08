#include <iostream>
#include <vector>
#include <string>

using namespace std;

//recursive solution 2^n
int recursiveSubsequncesol(string &str1,string &str2,int i, int j){

    if(str1[i] == '\0' || str2[j] == '\0')
        return 0;

    if(str1[i] == str2[j])
    return 1 + recursiveSubsequncesol(str1,str2,i+1,j+1); //if match found move both string 
    else {
        return max(recursiveSubsequncesol(str1,str2,i+1,j),recursiveSubsequncesol(str1,str2,i,j+1)); //match not found move index of one string ahead, get max result of that.
    }
}

//iterative solution m*n
int lcsIterative(string &str1,string &str2){
    int m = str1.size(), n = str2.size();
    //use 2d matric M+1,n+1. initilise it with 0
    vector<vector<int>> result(m+1,vector<int>(n+1,0));

    //matric we need to traverse for result;
    for(int i = 1 ; i <= m; ++i){
        for(int j= 1;j <=n ;++j){
            if(str1[i-1] == str2[j-1]){
                result[i][j] = 1 + result[i-1][j-1];
            }else {
                result[i][j] = max(result[i-1][j],result[i][j-1]);
            }
        }
    }
    return result[m][n];
}

int main(){

    string str1("abdcef");
    string str2("abc");

    cout << "recursive longest subsequence = "<< recursiveSubsequncesol(str1,str2,0,0)<< endl;
     cout << "Iterative longest subsequence = "<< lcsIterative(str1,str2)<< endl;
}