// ============================================================
// std::bitset                                   [C++20 Edition]
// compile: g++ -std=c++20 -O2 bitset.cpp
// ============================================================
#include <iostream>
#include <bitset>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>
#include <numeric>
#include <cmath>

using namespace std;

int main() {
    cout << "========== std::bitset [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    bitset<8> b1;               // All zeros
    bitset<8> b2(0b10110101);   // From integer
    bitset<8> b3("11001010");   // From string (MSB first)
    bitset<8> b4(0xFF);         // 11111111
    cout << "b1 (zero):      " << b1.to_string() << "\n";
    cout << "b2 (0b10110101):" << b2.to_string() << "\n";
    cout << "b3 (string):    " << b3.to_string() << "\n";
    cout << "b4 (0xFF):      " << b4.to_string() << "\n";

    // 2. Bit Access & Modification
    cout << "\n--- 2. Bit Access ---\n";
    bitset<8> b(0b10110101);
    cout << "b:          " << b.to_string() << "\n";
    cout << "b[0] (LSB): " << b[0] << "\n";
    cout << "b[7] (MSB): " << b[7] << "\n";
    cout << "b.test(2):  " << b.test(2) << "\n";
    b.set(1); b.reset(0); b.flip(3);
    cout << "after set(1),reset(0),flip(3): " << b.to_string() << "\n";
    b.set();  cout << "after set() all:   " << b.to_string() << "\n";
    b.reset();cout << "after reset() all: " << b.to_string() << "\n";
    b.flip(); cout << "after flip() all:  " << b.to_string() << "\n";

    // 3. Bitwise Operations
    cout << "\n--- 3. Bitwise Operations ---\n";
    bitset<8> bx(0b10110101), by(0b01101110);
    cout << "x:    " << bx.to_string() << "\n";
    cout << "y:    " << by.to_string() << "\n";
    cout << "x&y:  " << (bx & by).to_string() << "\n";
    cout << "x|y:  " << (bx | by).to_string() << "\n";
    cout << "x^y:  " << (bx ^ by).to_string() << "\n";
    cout << "~x:   " << (~bx).to_string() << "\n";
    cout << "x<<2: " << (bx << 2).to_string() << "\n";
    cout << "x>>2: " << (bx >> 2).to_string() << "\n";

    // 4. Queries
    cout << "\n--- 4. Queries ---\n";
    bitset<8> q(0b10110101);
    cout << "count():  " << q.count() << "\n";
    cout << "size():   " << q.size()  << "\n";
    cout << "any():    " << q.any()   << "\n";
    cout << "none():   " << q.none()  << "\n";
    cout << "all():    " << q.all()   << "\n";

    // 5. Conversions
    cout << "\n--- 5. Conversions ---\n";
    bitset<8> conv(0b10110101);
    cout << "to_ulong():  " << conv.to_ulong()  << "\n";
    cout << "to_ullong(): " << conv.to_ullong() << "\n";
    cout << "to_string(): " << conv.to_string() << "\n";
    string bit_str = conv.to_string();
    cout << "lower 4 bits: " << bit_str.substr(4) << "\n";

    // 6. Sieve of Eratosthenes
    cout << "\n--- 6. Sieve of Eratosthenes ---\n";
    const int LIMIT = 50;
    bitset<LIMIT+1> is_prime;
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for (int p = 2; p*p <= LIMIT; p++)
        if (is_prime[p])
            for (int j = p*p; j <= LIMIT; j += p) is_prime[j] = 0;
    cout << "primes up to " << LIMIT << ": ";
    for (int i = 2; i <= LIMIT; i++) if (is_prime[i]) cout << i << " ";
    cout << "\ncount: " << is_prime.count() << "\n";

    // 7. Bitmask DP — Subset Sum
    cout << "\n--- 7. Bitmask DP (Subset Sum) ---\n";
    vector<int> weights = {1, 3, 5, 7};
    int W = 16;
    bitset<17> dp; dp[0] = 1;
    for (int w : weights) dp |= (dp << w);
    cout << "achievable sums 0.." << W << ": ";
    for (int s = 0; s <= W; s++) if (dp[s]) cout << s << " ";
    cout << "\n";
    cout << "can achieve sum 8:  " << (bool)dp[8]  << "\n";
    cout << "can achieve sum 9:  " << (bool)dp[9]  << "\n";

    // 8. Bitmask DP — TSP-style
    cout << "\n--- 8. Bitmask DP (TSP-style) ---\n";
    int N = 4;
    vector<vector<int>> can_reach(1 << N, vector<int>(N, 0));
    vector<vector<int>> adj = {{1,2},{0,2,3},{0,1,3},{1,2}};
    can_reach[1][0] = 1;
    for (int mask = 1; mask < (1 << N); mask++)
        for (int u = 0; u < N; u++) {
            if (!can_reach[mask][u]) continue;
            for (int v : adj[u])
                if (!(mask & (1 << v))) can_reach[mask|(1<<v)][v] = 1;
        }
    int full = (1<<N)-1, paths = 0;
    for (int v = 0; v < N; v++) paths += can_reach[full][v];
    cout << "paths visiting all " << N << " cities: " << paths << "\n";

    // 9. Subset Enumeration
    cout << "\n--- 9. Subset Enumeration ---\n";
    int mask = 0b1011;
    cout << "subsets of " << bitset<4>(mask) << ": ";
    for (int sub = mask; sub > 0; sub = (sub-1) & mask) cout << bitset<4>(sub) << " ";
    cout << "0000\n";
    int bits = 0b10110111;
    cout << "__builtin_popcount(10110111): " << __builtin_popcount(bits) << "\n";
    cout << "__builtin_ctz (trailing zeros): " << __builtin_ctz(bits) << "\n";
    cout << "__builtin_clz (leading zeros):  " << __builtin_clz(bits) << "\n";

    // 10. Bitwise CP Tricks
    cout << "\n--- 10. Bitwise CP Tricks ---\n";
    int n = 42;
    cout << "n = " << n << "\n";
    cout << "Is power of 2: " << ((n & (n-1)) == 0) << "\n";
    cout << "Lowest set bit:        " << (n & (-n))  << "\n";
    cout << "Turn off lowest bit:   " << (n & (n-1)) << "\n";
    cout << "XOR trick (n^n=0):     " << (n ^ n)     << "\n";
    cout << "XOR trick (n^0=n):     " << (n ^ 0)     << "\n";
    cout << "Multiply by 2 (<<1):   " << (n << 1)    << "\n";
    cout << "Divide by 2 (>>1):     " << (n >> 1)    << "\n";
    cout << "Set bit k=3:           " << (n | (1<<3))<< "\n";
    cout << "Clear bit k=5:         " << (n & ~(1<<5))<< "\n";
    cout << "Toggle bit k=1:        " << (n ^ (1<<1))<< "\n";
    cout << "Check bit k=3:         " << ((n >> 3) & 1)<< "\n";
    cout << "Parity of " << n << ":  " << (__builtin_parity(n) ? "odd" : "even") << "\n";

    return 0;
}
