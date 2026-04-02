// ============================================================
// std::array — Fixed-Size Array                 [C++20 Edition]
// compile: g++ -std=c++20 -O2 array.cpp
// ============================================================
#include <array>
#include <algorithm>
#include <numeric>
#include <span>
#include <format>
#include <ranges>
#include <iostream>

using namespace std;

int main()
{
    cout << "========== std::array [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    array<int, 5> a1{}; // Zero-initialized
    array<int, 5> a2 = {1, 2, 3, 4, 5};
    array a3 = {10, 20, 30, 40}; // C++17 CTAD
    array<int, 5> a4;
    // ***
    a4.fill(7);

    cout << "a1 (zero):   ";
    for (int x : a1)
    {
        cout << x << " ";
    }
    cout << "\n";
    cout << "a2:          ";
    for (int x : a2)
    {
        cout << x << " ";
    }
    cout << "\n";
    cout << "a3 (CTAD):   ";
    for (int x : a3)
    {
        cout << x << " ";
    }
    cout << "\n";
    cout << "a4 (fill 7): ";
    for (int x : a4)
    {
        cout << x << " ";
    }
    cout << "\n";
    // 2. Size & Metadata
    cout << "\n--- 2. Size & Metadata ---\n";
    cout << "size():      " << a2.size() << "\n";
    cout << "max_size():  " << a2.max_size() << "\n";
    cout << "empty():     " << a2.empty() << "\n";
    constexpr size_t SZ = tuple_size_v<decltype(a2)>;
    cout << "constexpr size: " << SZ << "\n";

    // 3. Access
    cout << "\n--- 3. Access ---\n";
    array<int, 5> a = {10, 20, 30, 40, 50};
    cout << "a[2]:     " << a[2] << "\n";
    cout << "a.at(2):  " << a.at(2) << "\n";
    cout << "a.front():" << a.front() << "\n";
    cout << "a.back(): " << a.back() << "\n";
    // ***
    cout << "data():   " << (void *)a.data() << "\n";

    // 4. Structured Bindings (C++17)
    cout << "\n--- 4. Structured Bindings ---\n";
    array<int, 3> pt = {1, 2, 3};
    auto [x, y, z] = pt;
    cout << "3D point: (" << x << ", " << y << ", " << z << ")\n";

    array<string, 2> edge = {"alice", "bob"};
    auto [from, to] = edge;
    cout << "edge: " << from << " -> " << to << "\n";

    // 5. Iterators
    cout << "\n--- 5. Iterators ---\n";
    array<int, 5> arr = {5, 3, 1, 4, 2};
    cout << "forward: ";
    for (int v : arr)
    {
        cout << v << " ";
    }
    cout << "\n";
    cout << "reverse: ";
    // ***
    for (auto rit = arr.rbegin(); rit != arr.rend(); ++rit)
    {
        cout << *rit << " ";
    }
    cout << "\n";

    // 6. Algorithms (C++20 ranges)
    cout << "\n--- 6. Algorithms ---\n";
    array<int, 5> alg = {5, 3, 1, 4, 2};
    ranges::sort(alg);
    cout << "sorted:   ";
    for (int v : alg)
    {
        cout << v << " ";
    }
    cout << "\n";
    ranges::reverse(alg);
    cout << "reversed: ";
    for (int v : alg)
    {
        cout << v << " ";
    }
    cout << "\n";
    cout << "min: " << ranges::min(alg) << "  max: " << ranges::max(alg) << "\n";
    cout << "sum: " << reduce(alg.begin(), alg.end()) << "\n";
    ranges::sort(alg);
    cout << "binary_search(3): " << ranges::binary_search(alg, 3) << "\n";

    array<int, 5> idx{};
    // ***
    iota(idx.begin(), idx.end(), 0);
    cout << "iota: ";
    for (int v : idx)
    {
        cout << v << " ";
    }
    cout << "\n";

    // 7. std::span (C++20)
    cout << "\n--- 7. std::span ---\n";
    array<int, 8> big = {1, 2, 3, 4, 5, 6, 7, 8};
    span<int> full_span{big};
    // ***
    span<int> half = full_span.subspan(2, 4);
    cout << "full:        ";
    for (int v : full_span)
    {
        cout << v << " ";
    }
    cout << "\n";
    cout << "subspan(2,4):";
    for (int v : half)
    {
        cout << v << " ";
    }
    cout << "\n";
    auto sum_span = [](span<const int> sp)
    { return reduce(sp.begin(), sp.end()); };
    cout << "sum of subspan: " << sum_span(half) << "\n";

    // 8. constexpr Array
    cout << "\n--- 8. constexpr Array ---\n";
    // ***   creates an array at compile-time with fixed values.
    constexpr array<int, 5> powers = {1, 2, 4, 8, 16};
    static_assert(powers[3] == 8);
    cout << "powers of 2: ";
    for (int v : powers)
    {
        cout << v << " ";
    }
    cout << "\n";
    cout << "sum: " << reduce(powers.begin(), powers.end()) << "\n";

    // 9. 2D Array
    cout << "\n--- 9. 2D Array ---\n";
    array<array<int, 3>, 3> mat = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
    cout << "3x3 matrix:\n";
    for (auto &row : mat)
    {
        cout << "  ";
        for (int v : row)
        {
            cout << v << " ";
        }
        cout << "\n";
    }
    auto [r0, r1, r2] = mat;
    cout << "row 0: ";
    for (int v : r0)
    {
        cout << v << " ";
    }
    cout << "\n";

    // 10. Comparison
    cout << "\n--- 10. Comparison ---\n";
    array<int, 3> p1 = {1, 2, 3}, p2 = {1, 2, 4}, p3 = {1, 2, 3};
    cout << "p1 == p3: " << (p1 == p3) << "\n";
    cout << "p1 <  p2: " << (p1 < p2) << "\n";
    auto cmp = p1 <=> p2;
    cout << "p1 <=> p2 is less: " << (cmp < 0) << "\n";

       // 11. CP Patterns
    cout << "\n--- 11. CP Patterns ---\n";
    // ***
    constexpr array<array<int, 2>, 4> dirs4 = {{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};
    int R = 5, C = 5, r = 2, c = 2;
    cout << "neighbors of (" << r << "," << c << "): ";
    for (auto [dr, dc] : dirs4)
    {
        int nr = r + dr, nc = c + dc;
        if (nr >= 0 && nr < R && nc >= 0 && nc < C)
            cout << "(" << nr << "," << nc << ") ";
    }
    cout << "\n";
    constexpr array<int, 5> data2 = {1, 2, 3, 4, 5};
    cout << "sum of data: " << reduce(data2.begin(), data2.end()) << "\n";

    return 0;
}
