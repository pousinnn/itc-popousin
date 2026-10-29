//Fibonacci
#include <iostream>
#include <unordered_map>
using namespace std;
unordered_map<int, int> memo= {{0, 0},{1, 1}};

int fib(int n) {
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    int f= fib(n-1) + fib(n-2);
    memo[n]= f;
    return f;
}

int main() {
    int n;
    cout << "n: ";
    cin >> n;
    cout << "fib(" << n << ") = " << fib(n) << endl;
    return 0;
}