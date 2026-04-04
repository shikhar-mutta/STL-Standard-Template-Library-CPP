// ============================================================
// std::deque — Double-Ended Queue               [C++20 Edition]
// compile: g++ -std=c++20 -O2 deque.cpp
// ============================================================
#include <deque>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
void print_deque(const string &label, const deque<T> &d)
{
    cout << label << ": ";
    for (auto &x : d)
    {
        cout << x << " ";
    }
    cout << "\n";
}

int main()
{
    cout << "========== std::deque [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    deque<int> d1;
    deque<int> d2 = {1, 2, 3, 4, 5};
    deque<int> d3(5, 42);
    deque<int> d4(d2.begin(), d2.end());
    auto rng = views::iota(1, 6);
    deque<int> d_range(rng.begin(), rng.end());
    print_deque("d2", d2);
    print_deque("d3 (5x42)", d3);
    print_deque("d_range", d_range);

    // 2. Size
    cout << "\n--- 2. Size ---\n";
    cout << "size():     " << d2.size() << " \n";
    cout << "max_size(): " << d2.max_size() << " \n";
    cout << "empty():    " << d1.empty() << " \n";
    d2.resize(7, 99);
    print_deque("after resize(7,99)", d2);

    // 3. Access
    cout << "\n--- 3. Access ---\n";
    deque<int> d = {10, 20, 30, 40, 50};
    cout << "d[2]:   " << d[2] << " \n";
    cout << "at(2):  " << d.at(2) << " \n";
    cout << "front:  " << d.front() << " \n";
    cout << "back:   " << d.back() << " \n";

    // 4. Push/Pop Both Ends — O(1)
    cout << "\n--- 4. Push/Pop Both Ends ---\n";
    d = {2, 3, 4};
    d.push_front(1);
    d.push_back(5);
    d.emplace_front(0);
    d.emplace_back(6);
    print_deque("after push both", d);
    d.pop_front();
    d.pop_back();
    print_deque("after pop both", d);

    // 5. Insert & Erase (middle O(n))
    cout << "\n--- 5. Insert & Erase ---\n";
    d.insert(d.begin() + 1, 99);
    print_deque("after insert(1,99)", d);
    d.insert(d.end(), {100, 200});
    print_deque("after insert range", d);
    d.erase(d.begin());
    print_deque("after erase(begin)", d);
    d.erase(d.begin(), d.begin() + 2);
    print_deque("after erase [0,2)", d);
    d.clear();
    cout << "after clear, size: " << d.size() << " \n";

    // 6. Algorithms
    cout << "\n--- 6. Algorithms ---\n";
    deque<int> ad = {5, 3, 1, 4, 2};
    ranges::sort(ad);
    print_deque("sorted", ad);
    ranges::reverse(ad);
    print_deque("reversed", ad);
    ranges::sort(ad);
    auto lb = ranges::lower_bound(ad, 3);
    auto ub = ranges::upper_bound(ad, 3);
    cout << "lower_bound(3): " << *lb << " \n";
    cout << "upper_bound(3): " << *ub << " \n";
    cout << "binary_search(3): " << ranges::binary_search(ad, 3) << " \n";

    // 7. Monotonic Deque — Sliding Window Maximum
    cout << "\n--- 7. Sliding Window Maximum ---\n";
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    deque<int> dq;
    vector<int> result;
    for (int i = 0; i < (int)nums.size(); i++)
    {
        while (!dq.empty() && dq.front() < i - k + 1)
            dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            result.push_back(nums[dq.front()]);
    }
    cout << "window max (k=" << k << ") -> ";
    for (int x : result)
        cout << x << " ";
    cout << "\n";

    // 8. Sliding Window Minimum
    cout << "\n--- 8. Sliding Window Minimum ---\n";
    deque<int> dq_min;
    vector<int> min_result;
    for (int i = 0; i < (int)nums.size(); i++)
    {
        while (!dq_min.empty() && dq_min.front() < i - k + 1)
            dq_min.pop_front();
        while (!dq_min.empty() && nums[dq_min.back()] > nums[i])
            dq_min.pop_back();
        dq_min.push_back(i);
        if (i >= k - 1)
            min_result.push_back(nums[dq_min.front()]);
    }
    cout << "window min (k=" << k << ") -> ";
    for (int x : min_result)
        cout << x << " ";
    cout << "\n";

    // 9. Circular Buffer Pattern
    cout << "\n--- 9. Circular Buffer Pattern (capacity=4) ---\n";
    int capacity = 4;
    deque<int> circ;
    for (int x : {1, 2, 3, 4, 5, 6, 7})
    {
        circ.push_back(x);
        if ((int)circ.size() > capacity)
            circ.pop_front();
        cout << "add " << x << " -> [";
        for (int v : circ)
            cout << v << " ";
        cout << "]\n";
    }

    // 10. Ranges & Views
    cout << "\n--- 10. Ranges on Deque ---\n";
    deque<int> rd = {1, 2, 3, 4, 5, 6, 7, 8};
    auto pipeline = rd | views::filter([](int x)
                                       { return x % 2 != 0; }) |
                    views::transform([](int x)
                                     { return x * x; });
    cout << "odd squares: ";
    for (int x : pipeline)
        cout << x << " ";
    cout << "\n";
    cout << "sum: " << reduce(rd.begin(), rd.end(), 0) << "\n";
    vector<int> prefix(rd.size());
    partial_sum(rd.begin(), rd.end(), prefix.begin());
    cout << "prefix sums: ";
    for (int x : prefix)
        cout << x << " ";
    cout << "\n";

    return 0;
}
