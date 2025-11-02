#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace chrono;

// (a) Naive algorithm 
vector<long long> naiveDivisors(long long n) {
    vector<long long> divisors;
    for (long long i = 1; i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
        }
    }
    return divisors;
}

// (b) Optimized algorithm
vector<long long> optimizedDivisors(long long n) {
    vector<long long> smallDivisors;
    vector<long long> largeDivisors;
    
    long long sqrtN = sqrt(n);
    
    for (long long i = 1; i <= sqrtN; i++) {
        if (n % i == 0) {
            smallDivisors.push_back(i);
            if (i != n / i) {
                largeDivisors.push_back(n / i);
            }
        }
    }
    
    // largeDivisors in reverse order
    for (int i = largeDivisors.size() - 1; i >= 0; i--) {
        smallDivisors.push_back(largeDivisors[i]);
    }
    
    return smallDivisors;
}

//  execution time for a function
double measureTime(vector<long long> (*func)(long long), long long n, int runs = 10) {
    double totalTime = 0.0;
    
    for (int i = 0; i < runs; i++) {
        auto start = high_resolution_clock::now();
        vector<long long> result = func(n);
        auto end = high_resolution_clock::now();
        
        duration<double> elapsed = end - start;
        totalTime += elapsed.count();
    }
    
    return totalTime / runs;
}

int main() {
    cout << fixed << setprecision(6);
    
    cout << "========================================" << endl;
    cout << "(a) NAIVE ALGORITHM MEASUREMENTS" << endl;
    cout << "========================================" << endl;
    
    vector<long long> naiveTestValues = {
        1000000,      // 1×10^6
        10000000,     // 1×10^7
        100000000,    // 1×10^8
        1000000000    // 1×10^9
    };
    
    cout << "\nn (value)\t\tExecution time (s)" << endl;
    cout << "------------------------------------------------" << endl;
    
    for (long long n : naiveTestValues) {
        cout << "Testing n = " << n << "..." << flush;
        double avgTime = measureTime(naiveDivisors, n);
        cout << "\r" << scientific << n << "\t\t" << fixed << avgTime << endl;
    }
    
    // Time estimation for 1e18
    cout << "\n--- Time Estimation for 1×10^18 ---" << endl;
    cout << "Based on linear relationship (O(n)):" << endl;
    cout << "If 1×10^9 takes t seconds," << endl;
    cout << "then 1×10^18 would take approximately 10^9 × t seconds" << endl;
    cout << "Example: if 1e9 takes 1 second, 1e18 would take ~31,710 years" << endl;
    
    cout << "\n========================================" << endl;
    cout << "(b) OPTIMIZED ALGORITHM MEASUREMENTS" << endl;
    cout << "========================================" << endl;
    
    vector<long long> optimizedTestValues = {
        100000000LL,           // 1×10^8
        1000000000LL,          // 1×10^9
        1000000000000LL,       // 1×10^12
        100000000000000000LL,  // 1×10^17
        1000000000000000000LL  // 1×10^18
    };
    
    cout << "\nn (value)\t\tExecution time (s)" << endl;
    cout << "------------------------------------------------" << endl;
    
    for (long long n : optimizedTestValues) {
        cout << "Testing n = " << scientific << n << "..." << flush;
        double avgTime = measureTime(optimizedDivisors, n);
        cout << "\r" << scientific << n << "\t\t" << fixed << avgTime << endl;
    }
    
    cout << "\n========================================" << endl;
    cout << "ANALYSIS" << endl;
    cout << "========================================" << endl;
    cout << "Naive Algorithm: O(n) - Linear complexity" << endl;
    cout << "  Time grows proportionally with n" << endl;
    cout << "\nOptimized Algorithm: O(√n) - Square root complexity" << endl;
    cout << "  Time grows proportionally with √n" << endl;
    cout << "  Much more efficient for large values!" << endl;
    
    return 0;
}