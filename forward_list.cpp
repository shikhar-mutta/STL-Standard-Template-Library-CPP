// ============================================================
// std::forward_list — Singly Linked List        [C++20 Edition]
// compile: g++ -std=c++20 -O2 forward_list.cpp
// ============================================================
#include <forward_list>
#include <ranges>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>

using namespace std;

void print_fl(const string &label, const forward_list<int> &fl)
{
    cout << label << ": ";
    for (int x : fl)
    {
        cout << x << " ";
    }
    cout << "\n";
}

int main()
{
    cout << "========== std::forward_list [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    forward_list<int> fl1;
    forward_list<int> fl2 = {1, 2, 3, 4, 5};
    forward_list<int> fl3(5, 0);
    forward_list<int> fl4(fl2.begin(), fl2.end());
    print_fl("fl2", fl2);
    print_fl("fl3 (5 zeros)", fl3);
    // ***
    cout << "size of fl2 (O(n)): " << ranges::distance(fl2) << " \n";

    // 2. Push/Pop (FRONT only)
    cout << "\n--- 2. Push/Pop Front ---\n";
    forward_list<int> fl = {2, 3, 4};
    fl.push_front(1);
    fl.emplace_front(0);
    print_fl("after push_front x2", fl);
    fl.pop_front();
    print_fl("after pop_front", fl);
    cout << "front: " << fl.front() << " \n";

    // 3. before_begin + insert_after / erase_after
    cout << "\n--- 3. insert_after / erase_after ---\n";
    forward_list<int> il = {1, 2, 4, 5};
    auto pos = il.before_begin();
    advance(pos, 2);
    il.insert_after(pos, 3);
    print_fl("after insert_after (3 after 2)", il);

    pos = next(il.before_begin(), 4);
    il.insert_after(pos, {99, 88});
    print_fl("after range insert_after", il);

    pos = il.before_begin();
    advance(pos, 4);
    il.erase_after(pos);
    print_fl("after erase_after", il);

    auto first_it = il.begin(), last_it = next(first_it, 3);
    il.erase_after(first_it, last_it);
    print_fl("after erase_after range", il);

    // 4. List Algorithms
    cout << "\n--- 4. List Algorithms ---\n";
    forward_list<int> lal = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    lal.sort();
    print_fl("sorted", lal);
    lal.unique();
    print_fl("unique", lal);
    lal.reverse();
    print_fl("reversed", lal);
    lal.remove(6);
    print_fl("remove(6)", lal);
    lal.remove_if([](int x)
                  { return x < 3; });
    print_fl("remove_if(<3)", lal);

    // 5. Splice After
    cout << "\n--- 5. Splice After ---\n";
    forward_list<int> src = {10, 20, 30}, dst = {1, 2, 3};
    dst.splice_after(dst.begin(), src);
    print_fl("dst after splice_after", dst);
    cout << "src empty: " << src.empty() << "\n";

    // 6. Merge Sorted Lists
    cout << "\n--- 6. Merge ---\n";
    forward_list<int> mA = {1, 3, 5, 7}, mB = {2, 4, 6, 8};
    mA.merge(mB);
    print_fl("merged sorted", mA);
    cout << "mB empty: " << mB.empty() << "\n";

    // 7. Ranges (C++20)
    cout << "\n--- 7. Ranges ---\n";
    forward_list<int> rl = {1, 2, 3, 4, 5, 6};
    auto evens = rl | views::filter([](int x)
                                    { return x % 2 == 0; });
    cout << "evens:   ";
    for (int x : evens)
        cout << x << " ";
    cout << "\n";
    auto doubled = rl | views::transform([](int x)
                                         { return x * 2; });
    cout << "doubled: ";
    for (int x : doubled)
        cout << x << " ";
    cout << "\n";
    int sum = accumulate(rl.begin(), rl.end(), 0, plus<int>());
    cout << "sum (accumulate): " << sum << "\n";

    // 8. CP Patterns
    cout << "\n--- 8. CP Patterns ---\n";
    forward_list<int> rev_list = {1, 2, 3, 4, 5};
    rev_list.reverse();
    print_fl("reversed list", rev_list);

    forward_list<int> part = {3, 1, 4, 1, 5, 9, 2, 6};
    forward_list<int> evens_list, odds_list;
    for (int x : part)
    {
        if (x % 2 == 0)
            evens_list.push_front(x);
        else
            odds_list.push_front(x);
    }
    evens_list.sort();
    odds_list.sort();
    print_fl("evens partition", evens_list);
    print_fl("odds partition", odds_list);

    return 0;
}
