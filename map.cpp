// ============================================================
// std::map — Ordered Map (BST)                  [C++20 Edition]
// compile: g++ -std=c++20 -O2 map.cpp
// ============================================================
#include <map>
#include <string>
#include <ranges>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <typename K, typename V, typename Cmp = less<K>>
void print_map(const string &label, const map<K, V, Cmp> &m)
{
    cout << label << ": ";
    for (auto &[k, v] : m)
    {
        cout << k << ":" << v << " ";
    }
    cout << "\n";
}

int main()
{
    cout << "========== std::map [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    map<string, int> m1;
    map<string, int> m2 = {{"apple", 5}, {"banana", 2}, {"cherry", 8}};
    map<string, int, greater<string>> m_desc = {{"a", 1}, {"b", 2}, {"c", 3}};
    print_map("m2 (sorted)", m2);
    print_map("m_desc (descending)", m_desc);

    // 2. Insert & Access
    cout << "\n--- 2. Insert & Access ---\n";
    map<string, int> m;
    m["dog"] = 3;
    m["cat"] = 7;
    m["dog"] = 10;
    cout << "m[\"bird\"] (creates key!): " << m["bird"] << " \n";
    // ***
    auto [iter, ok] = m.insert({"cat", 99});
    cout << "insert(cat,99) ok: " << ok << " (0=already exists) \n";
    // ***
    m.insert_or_assign("cat", 99);
    cout << "after insert_or_assign(cat,99): " << m["cat"] << " \n";
    // ***
    m.try_emplace("cat", 500);
    m.try_emplace("lion", 500);
    cout << "cat after try_emplace (unchanged): " << m["cat"] << " \n";
    print_map("full map", m);

    // 3. Lookup
    cout << "\n--- 3. Lookup ---\n";
    map<string, int> lm = {{"a", 1}, {"b", 2}, {"c", 3}, {"e", 5}};
    if (auto fit = lm.find("b"); fit != lm.end())
    {
        cout << "find(b): " << fit->second << " \n";
    }
    cout << "contains(a): " << lm.contains("a") << " \n";
    cout << "contains(z): " << lm.contains("z") << " \n";
    cout << "count(a):    " << lm.count("a") << " \n";
    cout << "at(c):       " << lm.at("c") << " \n";
    auto lb = lm.lower_bound("b"), ub = lm.upper_bound("c");
    cout << "lower_bound(b): " << lb->first << ":" << lb->second << " \n";
    cout << "upper_bound(c): " << ub->first << ":" << ub->second << " \n";
    auto [lo, hi] = lm.equal_range("c");
    cout << "equal_range(c): key=" << lo->first << " \n";

    // 4. Erase
    cout << "\n--- 4. Erase ---\n";
    map<string, int> em = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}};
    em.erase("b");
    print_map("after erase('b')", em);
    em.erase(em.find("c"));
    print_map("after erase by iter", em);
    em.erase(em.begin(), em.find("d"));
    print_map("after range erase", em);
    em.clear();
    cout << "after clear, size: " << em.size() << " \n";

    // 5. Iterators
    cout << "\n--- 5. Iterators ---\n";
    map<int, string> im = {{1, "one"}, {2, "two"}, {3, "three"}};
    cout << "forward: ";
    for (auto &[k, v] : im)
    {
        cout << k << ":" << v << " ";
    }
    cout << " \n";
    cout << "forward: ";
    for (auto rit = im.begin(); rit != im.end(); ++rit)
    {
        cout << rit->first << ":" << rit->second << " ";
    }
    cout << " \n";
    cout << "reverse: ";
    for (auto rit = im.rbegin(); rit != im.rend(); ++rit)
    {
        cout << rit->first << ":" << rit->second << " ";
    }
    cout << " \n";

    // 6. Merge & Swap (C++17)
    cout << "\n--- 6. Merge & Swap ---\n";
    map<int, int> MA = {{1, 10}, {2, 20}}, MB = {{2, 99}, {3, 30}};
    // ***
    MA.merge(MB);
    print_map("A after merge", MA);
    print_map("B after merge (overlapping stays)", MB);
    map<int, int> X = {{1, 1}}, Y = {{2, 2}};
    X.swap(Y);
    cout << "X after swap, first key: " << X.begin()->first << " \n";

    // 7. Ranges on map (C++20)
    cout << "\n--- 7. Ranges on map ---\n";
    map<string, int> scores = {{"alice", 85}, {"bob", 92}, {"carol", 78}, {"dave", 95}};
    auto high = scores | views::filter([](auto &p)
                                       { return p.second >= 90; });
    cout << "scores >= 90: ";
    for (auto &[k, v] : high)
        cout << k << ":" << v << " ";
    cout << "\n";
    vector<string> keys;
    for (auto &[k, v] : scores)
        keys.push_back(k);
    cout << "keys: ";
    for (auto &k : keys)
        cout << k << " ";
    cout << "\n";
    vector<int> vals;
    for (auto &[k, v] : scores)
        vals.push_back(v);
    cout << "vals: ";
    for (int v : vals)
        cout << v << " ";
    cout << "\n";
    auto max_it = ranges::max_element(scores, [](auto &a, auto &b)
                                      { return a.second < b.second; });
    cout << "top scorer: " << max_it->first << " = " << max_it->second << "\n";

    // 8. CP Patterns
    cout << "\n--- 8. CP Patterns ---\n";
    string words[] = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    map<string, int> freq;
    for (auto &w : words)
        freq[w]++;
    cout << "word frequencies:\n";
    for (auto &[w, c] : freq)
        cout << "  " << w << ": " << c << "\n";

    map<int, int> sdata = {{10, 1}, {20, 2}, {30, 3}, {40, 4}, {50, 5}};
    int L = 20, R = 40;
    cout << "keys in [" << L << "," << R << "]: ";
    for (auto it = sdata.lower_bound(L); it != sdata.upper_bound(R); ++it)
        cout << it->first << ":" << it->second << " ";
    cout << "\n";

    vector<int> data_arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    map<int, int> cnt;
    for (int x : data_arr)
        cnt[x]++;
    cout << "distinct elements: " << cnt.size() << "\n";
    auto max_elem = *ranges::max_element(cnt, [](auto &a, auto &b)
                                         { return a.second < b.second; });
    cout << "most frequent: " << max_elem.first << " (appears " << max_elem.second << " times)\n";

    return 0;
}
