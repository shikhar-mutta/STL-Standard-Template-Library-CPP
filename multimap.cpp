// ============================================================
// std::multimap                                 [C++20 Edition]
// compile: g++ -std=c++20 -O2 multimap.cpp
// ============================================================
#include <map>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    cout << "========== std::multimap [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    multimap<string, int> mm = {
        {"apple", 5}, {"banana", 2}, {"apple", 8}, {"cherry", 1}, {"banana", 7}};
    cout << "mm (sorted by key, dups allowed): ";
    for (auto &[k, v] : mm)
    {
        cout << " \n"
             << k << ":" << v << " ";
    }
    cout << "\n";

    // 2. Size
    cout << "\n--- 2. Size ---\n";
    cout << "size():         " << mm.size() << " \n";
    cout << "count(apple):   " << mm.count("apple") << " \n";

    // 3. Insert
    cout << "\n--- 3. Insert ---\n";
    multimap<int, string> m;
    m.insert({1, "one"});
    m.insert({2, "two"});
    m.insert({1, "uno"});
    m.insert({1, "eins"});
    m.emplace(3, "three");
    cout << "after inserts: ";
    for (auto &[k, v] : m)
    {
        cout << " \n"
             << k << ":" << v << " ";
    }
    cout << " \n";

    // 4. Lookup & equal_range
    cout << "\n--- 4. Lookup ---\n";
    cout << "count(1):    " << m.count(1) << " \n";
    cout << "contains(1): " << m.contains(1) << " \n";
    auto [lo, hi] = m.equal_range(1);
    cout << "all values for key=1: ";
    for (auto it = lo; it != hi; ++it)
    {
        cout << it->second << " ";
    }
    cout << "\n";
    auto lb = m.lower_bound(2);
    cout << "lower_bound(2): " << lb->first << ":" << lb->second << "\n";

    // 5. Erase
    cout << "\n--- 5. Erase ---\n";
    multimap<int, string> em = {{1, "a"}, {1, "b"}, {2, "c"}, {3, "d"}};
    em.erase(1);
    cout << "after erase(1) all: ";
    for (auto &[k, v] : em)
    {
        cout << " \n"
             << k << ":" << v << " ";
    }
    cout << " \n";
    em.erase(em.find(2));
    cout << "after erase(find(2)): ";
    for (auto &[k, v] : em)
    {
        cout << " \n"
             << k << ":" << v << " ";
    }
    cout << "\n";

    // 6. Grouping Pattern
    cout << "\n--- 6. Group by Key Pattern ---\n";
    multimap<string, string> index = {
        {"cpp", "vector"}, {"cpp", "map"}, {"java", "ArrayList"}, {"cpp", "set"}, {"java", "HashMap"}};
    auto git = index.begin();
    while (git != index.end())
    {
        string key = git->first;
        cout << "  " << key << ":";
        auto [s, e] = index.equal_range(key);
        for (auto it = s; it != e; ++it)
            cout << " " << it->second;
        cout << "\n";
        git = e;
    }

    // 7. Ranges (C++20)
    cout << "\n--- 7. Ranges ---\n";
    auto high = m | views::filter([](auto &p)
                                  { return p.first >= 2; });
    cout << "keys >= 2: ";
    for (auto &[k, v] : high)
        cout << k << ":" << v << " ";
    cout << "\n";

    // Unique keys via set
    vector<int> unique_keys;
    for (auto it = m.begin(); it != m.end(); it = m.upper_bound(it->first))
        unique_keys.push_back(it->first);
    cout << "unique keys: ";
    for (int k : unique_keys)
        cout << k << " ";
    cout << "\n";

    return 0;
}
