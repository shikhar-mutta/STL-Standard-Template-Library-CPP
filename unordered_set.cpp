// ============================================================
// std::unordered_set                            [C++20 Edition]
// compile: g++ -std=c++20 -O2 unordered_set.cpp
// ============================================================
#include <unordered_set>
#include <ranges>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

// Template function to print any container efficiently
template <typename Container>
void Print_US(const string &label, const Container &cont)
{
    cout << label << ": ";
    for (const auto &elem : cont)
    {
        cout << elem << " ";
    }
    cout << "\n";
}

int main()
{
    cout << "========== std::unordered_set [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    unordered_set<int> us1;
    unordered_set<int> us2 = {5, 3, 1, 4, 2, 3, 5};
    unordered_set<string> words = {"hello", "world", "cpp", "20"};
    Print_US("us2 (unique, unordered)", us2);
    cout << "size: " << us2.size() << " \n";

    // 2. Hash Stats
    cout << "\n--- 2. Hash Stats ---\n";
    cout << "bucket_count: " << us2.bucket_count() << " \n";
    cout << "load_factor:  " << us2.load_factor() << " \n";
    us2.reserve(100);
    us2.rehash(50);

    // 3. Insert
    cout << "\n--- 3. Insert ---\n";
    unordered_set<int> s;
    auto [it1, ok1] = s.insert(10);
    auto [it2, ok2] = s.insert(10);
    s.insert({20, 30, 40});
    s.emplace(50);
    cout << "insert(10) ok:      " << ok1 << " (new element) \n";
    cout << "insert(10) dup ok:  " << ok2 << " (already exists) \n";
    cout << "iterator points to: " << *it1 << " \n";
    Print_US("set", s);

    // 4. Lookup — O(1) average
    cout << "\n--- 4. Lookup ---\n";
    unordered_set<int> ls = {1, 2, 3, 4, 5};
    cout << "contains(3): " << ls.contains(3) << " \n";
    cout << "contains(9): " << ls.contains(9) << " \n";
    if (auto fit = ls.find(3); fit != ls.end())
    {
        cout << "find(3): found " << *fit << " \n";
    }
    cout << "count(3): " << ls.count(3) << " \n";
    cout << "bucket for 3: " << ls.bucket(3) << " \n";

    // 5. Erase
    cout << "\n--- 5. Erase ---\n";
    unordered_set<int> e = {1, 2, 3, 4, 5};
    e.erase(3);
    Print_US("after erase(3)", e);
    e.erase(e.find(4));
    Print_US("after erase(it)", e);
    e.clear();
    cout << "after clear: size=" << e.size() << "\n";

    // 6. Merge (C++17)
    cout << "\n--- 6. Merge ---\n";
    unordered_set<int> A = {1, 2, 3}, B = {3, 4, 5};
    A.merge(B);
    Print_US("A after merge", A);
    Print_US("B (overlap stays)", B);

    // 7. Ranges (C++20)
    cout << "\n--- 7. Ranges ---\n";
    unordered_set<int> rs = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto evens = rs | views::filter([](int x)
                                    { return x % 2 == 0; });
    vector<int> evens_vec(evens.begin(), evens.end());
    ranges::sort(evens_vec);
    Print_US("evens (sorted)", evens_vec);

    vector<int> sorted_vec(rs.begin(), rs.end());
    ranges::sort(sorted_vec);
    Print_US("as sorted vector", sorted_vec);

    // 8. Custom Hash
    cout << "\n--- 8. Custom Hash ---\n";
    struct PairHash
    {
        size_t operator()(const pair<int, int> &p) const noexcept
        {
            return hash<long long>{}((long long)p.first << 32 | (unsigned)p.second);
        }
    };
    unordered_set<pair<int, int>, PairHash> visited;
    visited.insert({0, 0});
    visited.insert({1, 2});
    visited.insert({3, 3});
    cout << "visited {0,0}: " << visited.contains({0, 0}) << "\n";
    cout << "visited {1,1}: " << visited.contains({1, 1}) << "\n";
    cout << "visited count: " << visited.size() << "\n";

    // 9. CP Patterns
    cout << "\n--- 9. CP Patterns ---\n";
    vector<int> arr = {2, 7, 11, 15};
    int target = 9;
    unordered_set<int> seen;
    cout << "Two Sum (" << target << "): ";
    for (int x : arr)
    {
        if (seen.contains(target - x))
        {
            cout << "(" << target - x << "," << x << ")";
            break;
        }
        seen.insert(x);
    }
    cout << "\n";

    vector<int> dup_arr = {1, 2, 3, 1};
    unordered_set<int> dup_check(dup_arr.begin(), dup_arr.end());
    cout << "contains duplicate: " << (dup_check.size() != dup_arr.size()) << "\n";

    vector<int> seq = {100, 4, 200, 1, 3, 2};
    unordered_set<int> seq_set(seq.begin(), seq.end());
    int longest = 0;
    for (int n : seq_set)
    {
        if (!seq_set.contains(n - 1))
        {
            int cur = n, streak = 1;
            while (seq_set.contains(cur + 1))
            {
                cur++;
                streak++;
            }
            longest = max(longest, streak);
        }
    }
    cout << "longest consecutive: " << longest << "  (1,2,3,4 -> 4)\n";

    return 0;
}
