#include <iostream>
#include <vector>

using namespace std;

void printFibonacci(int n) {
    vector<int> fib(n + 1, 0);
    if (n >= 1) fib[1] = 1;

    for (int i = 2; i <= n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    for (int i = 0; i <= n; ++i)
        cout << fib[i] << " ";
}

int main (){

    int num = 5;

    printFibonacci(num);
}