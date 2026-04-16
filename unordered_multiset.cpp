// ============================================================
// std::unordered_multiset & std::unordered_multimap [C++20 Edition]
// compile: g++ -std=c++20 -O2 unordered_multiset.cpp
// ============================================================
#include <unordered_set>
#include <unordered_map>
#include <ranges>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

// ============= Print Helper Functions =============
template <typename Container>
void print_ums(const string &label, const Container &c)
{
    cout << label << ": ";
    for (const auto &x : c)
        cout << x << " ";
    cout << "\n";
}

template <typename K, typename V>
void print_umm(const string &label, const unordered_multimap<K, V> &umm)
{
    cout << label << ": ";
    for (const auto &[k, v] : umm)
        cout << k << ":" << v << " ";
    cout << "\n";
}

void demo_unordered_multiset()
{
    cout << "========== unordered_multiset ==========\n";

    unordered_multiset<int> ums = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    print_ums("ums (with dups, unordered)", ums);
    cout << "size: " << ums.size() << "  count(5): " << ums.count(5) << " \n";

    ums.insert(10);
    ums.insert(10);
    ums.emplace(7);
    cout << "after inserts, count(10): " << ums.count(10) << " \n";

    cout << "contains(5):  " << ums.contains(5) << " \n";
    cout << "contains(99): " << ums.contains(99) << " \n";

    auto er = ums.equal_range(5);
    cout << "equal_range(5): ";
    for (auto it = er.first; it != er.second; ++it)
    {
        cout << *it << " ";
    }
    cout << "(count=" << distance(er.first, er.second) << ") \n";
    ums.erase(1);
    cout << "after erase(1): count(1)= " << ums.count(1) << " \n";

    auto oneit = ums.find(5);
    if (oneit != ums.end())
        ums.erase(oneit);
    cout << "after erase one 5: count(5)= " << ums.count(5) << " \n";

    // Merge
    unordered_multiset<int> A = {1, 2, 2}, B = {2, 3, 3};
    A.merge(B);
    print_ums("A after merge", A);
    print_ums("B after merge (empty)", B);

    // Ranges
    auto evens = ums | views::filter([](int x)
                                     { return x % 2 == 0; });
    vector<int> evens_vec(evens.begin(), evens.end());
    ranges::sort(evens_vec);
    print_ums("evens (sorted)", evens_vec);

    cout << "bucket_count: " << ums.bucket_count()
         << "  load_factor: " << ums.load_factor() << " \n";
}

void demo_unordered_multimap()
{
    cout << "\n========== unordered_multimap ==========\n";

    unordered_multimap<string, int> umm;

    umm.insert({"apple", 5});
    umm.insert({"banana", 2});
    umm.insert({"apple", 8});
    umm.insert({"cherry", 1});
    umm.insert({"banana", 7});
    umm.emplace("date", 3);

    print_umm("umm (unordered, dups)", umm);

    cout << "count(apple):    " << umm.count("apple") << " \n";
    cout << "contains(apple): " << umm.contains("apple") << " \n";

    auto [lo, hi] = umm.equal_range("apple");
    cout << "apple values: ";
    for (auto it = lo; it != hi; ++it)
    {
        cout << it->second << " ";
    }
    cout << " \n";

    if (auto fit = umm.find("banana"); fit != umm.end())
    {
        cout << "find(banana): (one entry) " << fit->second << " \n";
    }

    umm.erase("banana");
    cout << "after erase(banana): count(banana)= " << umm.count("banana") << " \n";

    auto eit = umm.find("apple");
    if (eit != umm.end())
    {
        umm.erase(eit);
    }
    cout << "after erase one apple: count(apple)= " << umm.count("apple") << " \n";

    // Grouping pattern
    unordered_multimap<string, string> index;
    index.insert({"cpp", "vector"});
    index.insert({"cpp", "map"});
    index.insert({"java", "ArrayList"});
    index.insert({"cpp", "set"});
    index.insert({"java", "HashMap"});

    unordered_set<string> printed;
    cout << "grouped: \n";
    for (auto &[lang, _] : index)
    {
        if (printed.contains(lang))
        {
            continue;
        }
        printed.insert(lang);
        cout << "  " << lang << ":";
        auto [ss, ee] = index.equal_range(lang);
        for (auto it = ss; it != ee; ++it)
        {
            cout << " " << it->second;
        }
        cout << " \n";
    }

    // Merge
    unordered_multimap<int, int> Ma, Mb;
    Ma.emplace(1, 10);
    Ma.emplace(2, 20);
    Mb.emplace(2, 99);
    Mb.emplace(3, 30);
    Ma.merge(Mb);
    print_umm("Ma after merge", Ma);
    print_umm("Mb (empty)", Mb);

    // Ranges
    auto filtered = index | views::filter([](auto &p)
                                          { return p.first == "cpp"; });
    cout << "cpp entries: ";
    for (auto &[k, v] : filtered)
        cout << v << " ";
    cout << " \n";
}

int main()
{
    demo_unordered_multiset();
    demo_unordered_multimap();
    return 0;
}