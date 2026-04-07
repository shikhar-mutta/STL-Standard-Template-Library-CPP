// ============================================================
// std::multiset                                 [C++20 Edition]
// compile: g++ -std=c++20 -O2 multiset.cpp
// ============================================================
#include <set>
#include <ranges>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void print_ms(const string &label, const multiset<int> &ms)
{
    cout << label << ": ";
    for (int x : ms)
        cout << x << " ";
    cout << "\n";
}

int main()
{
    cout << "========== std::multiset [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    multiset<int> ms = {5, 1, 3, 2, 4, 3, 5, 1};
    multiset<int, greater<int>> ms_desc = {5, 3, 1, 4, 2, 3};
    print_ms("ms (with dups, sorted)", ms);
    cout << "ms_desc: ";
    for (int x : ms_desc)
{        cout << x << " ";}
    cout << " \n";
    
    // 2. Insert
    cout << "\n--- 2. Insert ---\n";
    multiset<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(10);
    s.insert({5, 25, 20});
    s.emplace(15);
    print_ms("after inserts", s);

    // 3. Lookup
    cout << "\n--- 3. Lookup ---\n";
    multiset<int> ls = {1, 3, 3, 5, 5, 5, 7};
    cout << "count(3):    " << ls.count(3) << "\n";
    cout << "count(5):    " << ls.count(5) << "\n";
    cout << "contains(5): " << ls.contains(5) << "\n";
    cout << "contains(9): " << ls.contains(9) << "\n";
    if (auto fit = ls.find(5); fit != ls.end())
        cout << "find(5): found " << *fit << "\n";
    auto lb = ls.lower_bound(3), ub = ls.upper_bound(5);
    cout << "lower_bound(3): " << *lb << "\n";
    cout << "upper_bound(5): " << *ub << "\n";
    auto [lo, hi] = ls.equal_range(5);
    cout << "equal_range(5): ";
    for (auto it = lo; it != hi; ++it)
        cout << *it << " ";
    cout << "(count=" << distance(lo, hi) << ")\n";

    // 4. Erase
    cout << "\n--- 4. Erase ---\n";
    multiset<int> es = {1, 2, 2, 3, 3, 3, 4};
    print_ms("original", es);
    es.erase(3);
    print_ms("after erase(3) all", es);
    auto one = es.find(2);
    es.erase(one);
    print_ms("after erase one 2", es);
    multiset<int> es2 = {1, 2, 2, 2, 3};
    es2.erase(es2.lower_bound(2), es2.upper_bound(2));
    print_ms("after range erase all 2s", es2);

    // 5. Merge (C++17)
    cout << "\n--- 5. Merge ---\n";
    multiset<int> MA = {1, 2, 2}, MB = {2, 3, 3};
    MA.merge(MB);
    print_ms("A after merge", MA);
    cout << "B empty: " << MB.empty() << "\n";

    // 6. Sorted Bag — Running Min/Max
    cout << "\n--- 6. Sorted Bag (Running Min/Max) ---\n";
    multiset<int> bag = {5, 1, 9, 2, 8, 3};
    cout << "min: " << *bag.begin() << "\n";
    cout << "max: " << *bag.rbegin() << "\n";
    bag.erase(bag.begin());
    bag.erase(prev(bag.end()));
    print_ms("after removing min/max", bag);
    bag.insert(10);
    cout << "median (approx): " << *next(bag.begin(), bag.size() / 2) << "\n";

    // 7. K-th Smallest
    cout << "\n--- 7. K-th Smallest ---\n";
    multiset<int> kth = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int k = 4;
    auto kit = kth.begin();
    advance(kit, k - 1);
    cout << k << "-th smallest: " << *kit << "\n";

    // 8. Ranges
    cout << "\n--- 8. Ranges ---\n";
    multiset<int> rs = {1, 2, 2, 3, 3, 3, 4, 5};
    auto freq2 = rs | views::filter([](int x)
                                    { return x >= 3; });
    cout << "elements >= 3: ";
    for (int x : freq2)
        cout << x << " ";
    cout << "\n";

    return 0;
}
