#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};

    vector<string> phoneMap = {
        "",     "",     "abc", "def",  // 0,1,2,3
        "ghi", "jkl", "mno",          // 4,5,6
        "pqrs","tuv", "wxyz"          // 7,8,9
    };

    vector<string> result = {""};

    for (char digit : digits) {
        vector<string> temp;
        string letters = phoneMap[digit - '0'];

        for (const string& prefix : result) {
            for (char letter : letters) {
                temp.push_back(prefix + letter);
            }
        }
        std::cout <<"before swap Result =>" <<std::endl;
        for(auto str: result){
            std::cout << str << " " ;
        }
         std::cout << std::endl;
        std::cout <<"before swap temp =>" <<std::endl;
        for(auto str: temp){
            std::cout << str << " " ;
        }
         std::cout << std::endl;
        result.swap(temp);
         std::cout <<"after swap result => " <<std::endl;
         for(auto str: result){
            std::cout << str << " " ;
        }
         std::cout << std::endl;
         std::cout <<"after swap temp =>" <<std::endl;
        for(auto str: temp){
            std::cout << str << " " ;
        }
         std::cout << std::endl;
    }

    return result;
}

int main() {
    vector<string> res = letterCombinations("23");
    for (const string& s : res) cout << s << " ";
    cout << endl;

    return 0;
}
