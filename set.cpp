// ============================================================
// std::set — Ordered Unique Set (Red-Black BST) [C++20 Edition]
// compile: g++ -std=c++20 -O2 set.cpp
// ============================================================
#include <set>
#include <ranges>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void print_set(const string &label, const set<int> &s)
{
    cout << label << ": ";
    for (int x : s)
    {
        cout << x << " ";
    }
    cout << " \n";
}

int main()
{
    cout << "========== std::set [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    set<int> s1;
    set<int> s2 = {5, 3, 1, 4, 2, 3}; // dups removed, sorted
    set<int, greater<int>> s_desc = {5, 3, 1, 4, 2};
    print_set("s2 (sorted, unique)", s2);
    cout << "s_desc (descending): ";
    for (int x : s_desc)
    {
        cout << x << " ";
    }
    cout << " \n";
    vector<int> v = {5, 3, 1, 4, 2, 3, 5};
    set<int> from_v(v.begin(), v.end());
    print_set("set from vector", from_v);

    // 2. Size
    cout << "\n--- 2. Size ---\n";
    cout << "size():     " << s2.size() << " \n";
    cout << "empty():    " << s1.empty() << " \n";
    cout << "max_size(): " << s2.max_size() << " \n";

    // 3. Insert & Emplace
    cout << "\n--- 3. Insert ---\n";
    set<int> s;
    auto [it1, ok1] = s.insert(10);
    auto [it2, ok2] = s.insert(10); // Duplicate
    s.insert({20, 30, 40});
    s.emplace(15);
    s.emplace(10);
    cout << "insert(10) ok:      " << ok1 << " (1=new) \n";
    cout << "insert(10) dup ok:  " << ok2 << " (0=exists) \n";
    print_set("set", s);

    // 4. Lookup
    cout << "\n--- 4. Lookup ---\n";
    set<int> ls = {1, 3, 5, 7, 9, 11};
    cout << "contains(5):       " << ls.contains(5) << "\n";
    cout << "contains(6):       " << ls.contains(6) << "\n";
    cout << "count(5):          " << ls.count(5) << "\n";
    // ***
    if (auto fit = ls.find(7); fit != ls.end())
    {
        cout << "find(7): found " << *fit << "\n";
    }
    auto lb = ls.lower_bound(5), ub = ls.upper_bound(5);
    cout << "lower_bound(5):    " << *lb << "\n";
    cout << "upper_bound(5):    " << *ub << "\n";
    auto [lo, hi] = ls.equal_range(7);
    cout << "equal_range(7):    [" << *lo << ", " << *hi << ")\n";
    auto it7 = ls.find(7);
    cout << "predecessor of 7:  " << *prev(it7) << "\n";
    cout << "successor of 7:    " << *next(it7) << "\n";

    // 5. Erase
    cout << "\n--- 5. Erase ---\n";
    set<int> es = {1, 2, 3, 4, 5};
    es.erase(3);
    print_set("after erase(3)", es);
    es.erase(es.find(2));
    print_set("after erase(find(2))", es);
    es.erase(es.lower_bound(4), es.end());
    print_set("after erase [lb(4),end)", es);
    es.clear();
    cout << "after clear, size: " << es.size() << " \n";

    // 6. Iterators
    cout << "\n--- 6. Iterators ---\n";
    set<int> is = {10, 20, 30, 40};
    cout << "forward: ";
    for (auto x = is.begin(); x != is.end(); ++x)
    {
        cout << *x << " ";
    }
    cout << " \n";
    cout << "reverse: ";
    for (auto rit = is.rbegin(); rit != is.rend(); ++rit)
    {
        cout << *rit << " ";
    }
    cout << " \n";

    // 7. Merge & Swap (C++17)
    cout << "\n--- 7. Merge & Swap ---\n";
    set<int> A = {1, 3, 5}, B = {3, 4, 5, 6};
    A.merge(B);
    print_set("A after merge", A);
    print_set("B (overlapping stay)", B);
    set<int> X = {1, 2}, Y = {3, 4};
    X.swap(Y);
    print_set("X after swap", X);

    // 8. Ranges on set (C++20)
    cout << "\n--- 8. Ranges ---\n";
    set<int> rng_s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto evens = rng_s | views::filter([](int x)
                                       { return x % 2 == 0; });
    cout << "evens:      ";
    for (int x : evens)
    {
        cout << x << " ";
    }
    cout << " \n";
    // ***
    auto kth = *ranges::next(rng_s.begin(), 3);
    cout << "4th element: " << kth << " \n";

    // 9. Set Operations (C++17)
    cout << "\n--- 9. Set Operations ---\n";
    set<int> set1 = {1, 2, 3, 4, 5};
    set<int> set2 = {3, 4, 5, 6, 7};
    vector<int> result;

    // Union
    // ***
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(result));
    cout << "union:        ";
    for (int x : result)
    {
        cout << x << " ";
    }
    cout << " \n";

    // Intersection
    //   ***
    result.clear();
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(result));
    cout << "intersection: ";
    for (int x : result)
    {
        cout << x << " ";
    }
    cout << " \n";

    // Difference
    // ***
    result.clear();
    set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(result));
    cout << "difference:   ";
    for (int x : result)
    {
        cout << x << " ";
    }
    cout << " \n";

    // 10. CP Patterns
    cout << "\n--- 10. CP Patterns ---\n";
    vector<int> dupes = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    set<int> dedup(dupes.begin(), dupes.end());
    print_set("deduplicated", dedup);

    vector<int> check = {1, 2, 3, 4, 5};
    // ***
    bool all_unique = set<int>(check.begin(), check.end()).size() == check.size();
    cout << "all unique: " << all_unique << " \n";

    vector<int> arr = {1, 3, 1, 4, 3, 2, 1, 3};
    int window = 3;
    // ***
    cout << "sliding window min (w=3): ";
    for (int i = 0; i + window <= (int)arr.size(); i++)
    {
        set<int> win(arr.begin() + i, arr.begin() + i + window);
        cout << *win.begin() << " ";
    }
    cout << " \n";
    // ***
    auto cmp = [](const string &a, const string &b)
    {
        return a.size() != b.size() ? a.size() < b.size() : a < b;
    };
    // ***
    set<string, decltype(cmp)> word_set(cmp);
    word_set.insert({"banana", "fig", "strawberry", "kiwi", "apple"});
    cout << "sorted by length: ";
    for (auto &w : word_set)
    {
        cout << w << " ";
    }
    cout << " \n";

    return 0;
}
