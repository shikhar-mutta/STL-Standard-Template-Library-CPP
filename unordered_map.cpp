// ============================================================
// std::unordered_map — Hash Map                 [C++20 Edition]
// compile: g++ -std=c++20 -O2 unordered_map.cpp
// ============================================================
#include <unordered_map>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename K, typename V>
void print_um(const string &label, const unordered_map<K, V> &um)
{
    cout << label << ": \n";
    for (const auto &[k, v] : um)
    {
        cout << k << ":" << v << " " << " \n";
    }
    cout << " \n";
}

int main()
{
    cout << "\n========== std::unordered_map [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    unordered_map<string, int> um1;
    unordered_map<string, int> um2 = {{"apple", 5}, {"banana", 2}, {"cherry", 8}};
    print_um("um2 (unordered)", um2);

    // 2. Size & Hash Stats
    cout << "\n--- 2. Size & Hash Stats ---\n";
    cout << "size():           " << um2.size() << " \n";
    cout << "bucket_count():   " << um2.bucket_count() << " \n";
    cout << "load_factor():    " << um2.load_factor() << " \n";
    cout << "max_load_factor():" << um2.max_load_factor() << " \n";
    um2.reserve(100);
    um2.rehash(50);

    // 3. Insert & Access
    cout << "\n--- 3. Insert & Access ---\n";
    unordered_map<string, int> um;
    um["dog"] = 3;
    um["cat"] = 7;
    cout << "um[\"bird\"] (auto-inserts 0): " << um["bird"] << "\n";
    auto [iter, ok] = um.insert({"cat", 99});
    cout << "insert(cat,99) ok: " << ok << " (0=exists)\n";
    um.insert_or_assign("cat", 99);
    cout << "after insert_or_assign(cat,99): " << um["cat"] << "\n";
    um.try_emplace("cat", 500);
    um.try_emplace("lion", 500);
    cout << "cat unchanged: " << um["cat"] << "\n";
    print_um("full map", um);

    // 4. Lookup — O(1) average
    cout << "\n--- 4. Lookup ---\n";
    unordered_map<string, int> lm = {{"a", 1}, {"b", 2}, {"c", 3}};
    cout << "contains(a): " << lm.contains("a") << " \n";
    cout << "contains(z): " << lm.contains("z") << " \n";
    if (auto fit = lm.find("b"); fit != lm.end())
    {
        cout << "find(b): " << fit->second << " \n";
    }
    cout << "count(a): " << lm.count("a") << " \n";
    cout << "at(c):    " << lm.at("c") << " \n";
    cout << "bucket for 'a': " << lm.bucket("a") << " \n";

    // 5. Erase
    cout << "\n--- 5. Erase ---\n";
    unordered_map<string, int> em = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}};
    em.erase("b");
    print_um("after erase(b)", em);
    em.erase(em.find("c"));
    print_um("after erase by iter", em);
    em.clear();
    cout << "after clear: size=" << em.size() << " \n";

    // 6. Merge (C++17)
    cout << "\n--- 6. Merge ---\n";
    unordered_map<int, int> A = {{1, 10}, {2, 20}}, B = {{2, 99}, {3, 30}};
    A.merge(B);
    print_um("A after merge", A);
    print_um("B (conflicting stays)", B);

    // 7. Custom Hash (pair<int,int> keys)
    cout << "\n--- 7. Custom Hash ---\n";
    struct PairHash
    {
        size_t operator()(const pair<int, int> &p) const noexcept
        {
            return hash<long long>{}((long long)p.first << 32 | (unsigned)p.second);
        }
    };
    unordered_map<pair<int, int>, string, PairHash> grid;
    grid[{0, 0}] = "origin";
    grid[{1, 2}] = "right-down";
    cout << "grid[{0,0}]: " << grid[{0, 0}] << "\n";
    cout << "grid[{1,2}]: " << grid[{1, 2}] << "\n";

    // 8. Ranges (C++20)
    cout << "\n--- 8. Ranges ---\n";
    unordered_map<string, int> scores = {{"alice", 85}, {"bob", 92}, {"carol", 78}};
    auto high = scores | views::filter([](auto &p)
                                       { return p.second >= 90; });
    cout << "score >= 90: ";
    for (auto [k, v] : high)
        cout << k << ":" << v << " ";
    cout << "\n";

    // 10. CP Patterns
    cout << "\n--- 10. CP Patterns ---\n";
    string ss = "programming";
    unordered_map<char, int> freq;
    for (char c : ss)
        freq[c]++;
    cout << "char freq in '" << ss << "': ";
    vector<pair<char, int>> fv(freq.begin(), freq.end());
    ranges::sort(fv, [](auto &a, auto &b)
                 { return a.second < b.second; });
    for (auto [c, cnt] : fv)
        cout << c << ":" << cnt << " ";
    cout << "\n";

    vector<int> arr = {2, 7, 11, 15};
    int target = 9;
    unordered_map<int, int> seen;
    cout << "two-sum pairs summing to " << target << ": ";
    for (int i = 0; i < (int)arr.size(); i++)
    {
        if (seen.contains(target - arr[i]))
        {
            cout << "[" << seen[target - arr[i]] << "," << i << "] ";
            break;
        }
        seen[arr[i]] = i;
    }
    cout << "\n";

    vector<int> nums2 = {1, 1, 1, 2, -1, 3};
    int k = 3, count_sub = 0, prefix = 0;
    unordered_map<int, int> prefix_cnt = {{0, 1}};
    for (int n : nums2)
    {
        prefix += n;
        count_sub += prefix_cnt[prefix - k];
        prefix_cnt[prefix]++;
    }
    cout << "subarrays summing to " << k << ": " << count_sub << "\n";

    return 0;
}
