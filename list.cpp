// ============================================================
// std::list & std::forward_list                 [C++20 Edition]
// compile: g++ -std=c++20 -O2 list.cpp
// ============================================================
#include <list>
#include <forward_list>
#include <ranges>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>

using namespace std;

void print_list(const string& label, const list<int>& l) {
    cout << label << ": "; for (int x : l) cout << x << " "; cout << "\n";
}
void print_fl(const string& label, const forward_list<int>& fl) {
    cout << label << ": "; for (int x : fl) cout << x << " "; cout << "\n";
}

int main() {
    cout << "========== std::list [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    list<int> l1;
    list<int> l2 = {1,2,3,4,5};
    list<int> l3(5,42);
    list<int> l4(l2.begin(), l2.end());
    print_list("l2", l2);
    print_list("l3 (5x42)", l3);

    // 2. Push/Pop O(1)
    cout << "\n--- 2. Push/Pop ---\n";
    list<int> l = {2,3,4};
    l.push_front(1); l.push_back(5);
    l.emplace_front(0); l.emplace_back(6);
    print_list("after push both ends", l);
    l.pop_front(); l.pop_back();
    print_list("after pop both ends", l);

    // 3. Insert & Erase O(1) with iterator
    cout << "\n--- 3. Insert & Erase ---\n";
    l = {1,2,4,5};
    auto it = ranges::find(l, 4);
    l.insert(it, 3);
    print_list("after insert(3 before 4)", l);
    it = ranges::find(l, 3);
    l.erase(it);
    print_list("after erase(3)", l);

    // 4. List-Specific Algorithms
    cout << "\n--- 4. List-Specific Algorithms ---\n";
    list<int> ls = {3,1,4,1,5,9,2,6,5,3,5};
    ls.sort();    print_list("sorted", ls);
    ls.unique();  print_list("unique", ls);
    ls.reverse(); print_list("reversed", ls);
    ls.remove(5); print_list("remove(5)", ls);
    ls.remove_if([](int x){ return x < 3; }); print_list("remove_if(<3)", ls);

    // 5. Splice — O(1)
    cout << "\n--- 5. Splice ---\n";
    list<int> src = {10,20,30,40}, dst = {1,2,3};
    auto dst_mid = ranges::find(dst, 2);
    dst.splice(dst_mid, src);
    print_list("dst after splice(src)", dst);
    cout << "src empty: " << src.empty() << "\n";

    list<int> A = {1,2,3}, B = {10,20,30};
    A.splice(next(A.begin()), B, B.begin());
    print_list("A after splice one element from B", A);
    print_list("B after splice", B);

    // 6. Merge Sorted Lists
    cout << "\n--- 6. Merge Sorted Lists ---\n";
    list<int> m1 = {1,3,5,7}, m2 = {2,4,6,8};
    m1.merge(m2);
    print_list("merged", m1);
    cout << "m2 empty: " << m2.empty() << "\n";

    // 7. Iterators
    cout << "\n--- 7. Iterators ---\n";
    list<int> il = {10,20,30,40};
    cout << "forward: "; for (int x : il) cout << x << " "; cout << "\n";
    cout << "reverse: "; for (auto rit = il.rbegin(); rit != il.rend(); ++rit) cout << *rit << " "; cout << "\n";

    // 8. Ranges on list
    cout << "\n--- 8. Ranges on list ---\n";
    list<int> rl = {5,3,1,4,2};
    auto big = rl | views::filter([](int x){ return x > 2; });
    cout << "elements > 2: "; for (int x : big) cout << x << " "; cout << "\n";
    auto sq = rl | views::transform([](int x){ return x*x; });
    cout << "squared:      "; for (int x : sq) cout << x << " "; cout << "\n";

    // ============================================================
    cout << "\n========== std::forward_list ==========\n";

    // 9. Initialization
    cout << "\n--- 9. Initialization ---\n";
    forward_list<int> fl = {1,2,3,4,5};
    print_fl("fl", fl);

    // 10. Push/Pop (front only)
    cout << "\n--- 10. Push/Pop (front only) ---\n";
    fl.push_front(0); fl.emplace_front(-1);
    print_fl("after push_front x2", fl);
    fl.pop_front();
    print_fl("after pop_front", fl);

    // 11. insert_after / erase_after
    cout << "\n--- 11. insert_after / erase_after ---\n";
    forward_list<int> fl2 = {1,2,4,5};
    auto fit2 = fl2.before_begin();
    advance(fit2, 2);
    fl2.insert_after(fit2, 3);
    print_fl("after insert_after", fl2);
    advance(fit2, 1);
    fl2.erase_after(fit2);
    print_fl("after erase_after", fl2);

    // 12. Sort, Unique, Reverse, Remove
    cout << "\n--- 12. forward_list Algorithms ---\n";
    forward_list<int> fa = {5,3,1,4,2,3,5};
    fa.sort();    print_fl("sorted", fa);
    fa.unique();  print_fl("unique", fa);
    fa.reverse(); print_fl("reversed", fa);
    fa.remove_if([](int x){ return x > 4; }); print_fl("remove_if(>4)", fa);

    forward_list<int> fA = {1,3,5}, fB = {2,4,6};
    fA.merge(fB);
    print_fl("merged", fA);
    cout << "fB empty: " << fB.empty() << "\n";

    return 0;
}
