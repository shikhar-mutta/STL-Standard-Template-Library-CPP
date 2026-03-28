// ============================================================
// std::unordered_multimap                       [C++20 Edition]
// compile: g++ -std=c++20 -O2 unordered_multimap.cpp
// ============================================================
#include <unordered_map>
#include <unordered_set>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    cout << "========== std::unordered_multimap [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    unordered_multimap<string,int> umm;
    umm.insert({"apple",5}); umm.insert({"banana",2});
    umm.insert({"apple",8}); umm.insert({"cherry",1});
    umm.insert({"banana",7}); umm.emplace("apple", 3);
    cout << "umm: ";
    for (auto& [k,v] : umm) cout << k << ":" << v << " "; cout << "\n";

    // 2. Capacity & Hash
    cout << "\n--- 2. Capacity & Hash ---\n";
    cout << "size:         " << umm.size()         << "\n";
    cout << "bucket_count: " << umm.bucket_count() << "\n";
    cout << "load_factor:  " << umm.load_factor()  << "\n";
    umm.reserve(50); umm.rehash(20);

    // 3. Insert
    cout << "\n--- 3. Insert ---\n";
    unordered_multimap<int,string> m;
    m.insert({1,"one"}); m.insert({2,"two"});
    m.insert({1,"uno"}); m.insert({1,"eins"});
    m.emplace(3,"three");
    cout << "after inserts: ";
    for (auto& [k,v] : m) cout << k << ":" << v << " "; cout << "\n";
    cout << "count(1): " << m.count(1) << "\n";

    // 4. Lookup — O(1) average
    cout << "\n--- 4. Lookup ---\n";
    cout << "contains(1): " << m.contains(1) << "\n";
    cout << "contains(9): " << m.contains(9) << "\n";
    if (auto fit = m.find(1); fit != m.end())
        cout << "find(1): " << fit->second << "\n";
    auto [lo,hi] = m.equal_range(1);
    cout << "all values for 1: "; for (auto it=lo; it!=hi; ++it) cout << it->second << " ";
    cout << "(count=" << distance(lo,hi) << ")\n";
    cout << "bucket for key 1: " << m.bucket(1) << "\n";

    // 5. Erase
    cout << "\n--- 5. Erase ---\n";
    unordered_multimap<int,string> em;
    em.insert({1,"a"}); em.insert({1,"b"}); em.insert({2,"c"}); em.insert({3,"d"});
    em.erase(1);
    cout << "after erase(1): "; for (auto& [k,v] : em) cout << k << ":" << v << " "; cout << "\n";
    em.insert({2,"cc"});
    em.erase(em.find(2));
    cout << "after erase(find(2)): "; for (auto& [k,v] : em) cout << k << ":" << v << " "; cout << "\n";
    em.clear(); cout << "after clear: size=" << em.size() << "\n";

    // 6. Merge (C++17)
    cout << "\n--- 6. Merge ---\n";
    unordered_multimap<int,int> A, B;
    A.emplace(1,10); A.emplace(2,20);
    B.emplace(2,99); B.emplace(3,30);
    A.merge(B);
    cout << "A after merge: "; for (auto& [k,v] : A) cout << k << ":" << v << " "; cout << "\n";
    cout << "B after merge (empty): "; for (auto& [k,v] : B) cout << k << ":" << v << " "; cout << "\n";

    // 7. Grouping Pattern
    cout << "\n--- 7. Grouping Pattern ---\n";
    unordered_multimap<string,string> index;
    index.insert({"cpp","vector"}); index.insert({"cpp","map"});
    index.insert({"java","ArrayList"}); index.insert({"cpp","set"});
    index.insert({"java","HashMap"}); index.insert({"python","list"});
    unordered_set<string> seen;
    for (auto& [lang, _] : index) {
        if (seen.contains(lang)) continue;
        seen.insert(lang);
        cout << "  " << lang << ":";
        auto [ss, ee] = index.equal_range(lang);
        for (auto it=ss; it!=ee; ++it) cout << " " << it->second;
        cout << "\n";
    }

    // 8. Ranges (C++20)
    cout << "\n--- 8. Ranges ---\n";
    auto cpp_entries = index | views::filter([](auto& p){ return p.first=="cpp"; });
    cout << "cpp entries: ";
    for (auto [k,v] : cpp_entries) cout << v << " "; cout << "\n";

    // Frequency using multimap count
    unordered_multimap<int,int> freq_m;
    vector<int> data = {1,2,2,3,3,3,4};
    for (int x : data) freq_m.emplace(x,x);
    cout << "frequencies:\n";
    unordered_set<int> shown;
    for (auto& [k,_2] : freq_m) {
        if (!shown.contains(k)) {
            cout << "  " << k << ": " << freq_m.count(k) << "\n";
            shown.insert(k);
        }
    }

    return 0;
}
