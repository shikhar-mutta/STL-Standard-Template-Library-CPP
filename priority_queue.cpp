// ============================================================
// std::priority_queue — Binary Heap             [C++20 Edition]
// compile: g++ -std=c++20 -O2 priority_queue.cpp
// ============================================================
#include <queue>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main()
{
    cout << "========== std::priority_queue [C++20] ==========\n";

    // 1. Basic Max-Heap
    cout << "\n--- 1. Max-Heap ---\n";
    priority_queue<int> maxpq;
    for (int x : {3, 1, 4, 1, 5, 9, 2})
    {
        maxpq.push(x);
    }
    cout << "pop order (max first): ";
    while (!maxpq.empty())
    {
        cout << maxpq.top() << " ";
        maxpq.pop();
    }
    cout << "\n";
    vector<int> v = {5, 3, 1, 4, 2};
    priority_queue<int> pq(v.begin(), v.end());
    cout << "top:  " << pq.top() << " \n";
    cout << "size: " << pq.size() << " \n";

    // 2. Min-Heap
    cout << "\n--- 2. Min-Heap ---\n";
    priority_queue<int, vector<int>, greater<int>> minpq;
    for (int x : {5, 3, 8, 1, 9, 2})
    {
        minpq.push(x);
    }
    cout << "pop order (min first): ";
    while (!minpq.empty())
    {
        cout << minpq.top() << " ";
        minpq.pop();
    }
    cout << " \n";

    // 3. Custom Comparator (pair heap — min by first)
    cout << "\n--- 3. Custom Comparator ---\n";
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<>> pair_pq;
    pair_pq.push({3, 'a'});
    pair_pq.push({1, 'c'});
    pair_pq.push({2, 'b'});
    cout << "pair min-heap (priority:char): ";
    while (!pair_pq.empty())
    {
        auto [pri, val] = pair_pq.top();
        pair_pq.pop();
        cout << pri << ":" << val << " ";
    }
    cout << " \n";

    // 4. K Largest / K Smallest
    cout << "\n--- 4. K Largest / K Smallest ---\n";
    vector<int> data = {3, 2, 1, 5, 6, 4};
    int k = 3;
    // K largest using min-heap of size k
    priority_queue<int, vector<int>, greater<>> k_large;
    for (int x : data)
    {
        k_large.push(x);
        if ((int)k_large.size() > k)
        {
            k_large.pop();
        }
    }
    cout << "k=" << k << " largest: kth=" << k_large.top() << " \n";
    // kth largest via ranges::nth_element (C++20)
    vector<int> d2 = data;
    ranges::nth_element(d2, d2.begin() + k - 1, greater<>{});
    cout << "kth largest (nth_element): " << d2[k - 1] << " \n";
    priority_queue<int> k_small;
    for (int x : data)
    {
        k_small.push(x);
        if ((int)k_small.size() > k)
        {
            k_small.pop();
        }
    }
    cout << "k=" << k << " smallest: kth=" << k_small.top() << " \n";

    // 5. Dijkstra's Algorithm
    cout << "\n--- 5. Dijkstra's Algorithm ---\n";
    const int INF = 1e9;
    int nn = 5;
    vector<vector<pair<int, int>>> adj(nn);
    adj[0].push_back({1, 4});
    adj[0].push_back({2, 1});
    adj[2].push_back({1, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({3, 5});
    adj[3].push_back({4, 3});
    vector<int> dist(nn, INF);
    dist[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> dijkstra_pq;
    dijkstra_pq.push({0, 0});
    while (!dijkstra_pq.empty())
    {
        auto [d, u] = dijkstra_pq.top();
        dijkstra_pq.pop();
        if (d > dist[u])
            continue;
        for (auto [vv, w] : adj[u])
            if (dist[u] + w < dist[vv])
            {
                dist[vv] = dist[u] + w;
                dijkstra_pq.push({dist[vv], vv});
            }
    }
    cout << "Dijkstra from 0: ";
    for (int i = 0; i < nn; i++)
        cout << i << ":" << dist[i] << " ";
    cout << "\n";

    // 6. Merge K Sorted Arrays
    cout << "\n--- 6. Merge K Sorted Arrays ---\n";
    vector<vector<int>> arrays = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> merge_pq;
    for (int i = 0; i < (int)arrays.size(); i++)
        merge_pq.push({arrays[i][0], i, 0});
    cout << "merged: ";
    while (!merge_pq.empty())
    {
        auto [val, ai, ei] = merge_pq.top();
        merge_pq.pop();
        cout << val << " ";
        if (ei + 1 < (int)arrays[ai].size())
            merge_pq.push({arrays[ai][ei + 1], ai, ei + 1});
    }
    cout << "\n";

    // 7. Task Scheduler
    cout << "\n--- 7. Task Scheduler ---\n";
    vector<int> tasks = {1, 1, 2, 2, 3, 3};
    int cooldown = 2;
    priority_queue<int> task_pq(tasks.begin(), tasks.end());
    int time_units = 0;
    while (!task_pq.empty())
    {
        vector<int> temp;
        int cycle = cooldown + 1;
        while (cycle-- && !task_pq.empty())
        {
            temp.push_back(task_pq.top() - 1);
            task_pq.pop();
            time_units++;
        }
        for (int t : temp)
            if (t > 0)
                task_pq.push(t);
        if (!task_pq.empty())
            time_units += cycle + 1;
    }
    cout << "min time to complete tasks: " << time_units << "\n";

    // 8. Median of Stream (Two Heaps)
    cout << "\n--- 8. Median of Stream ---\n";
    priority_queue<int> lower;
    priority_queue<int, vector<int>, greater<int>> upper;
    auto addNum = [&](int num)
    {
        lower.push(num);
        upper.push(lower.top());
        lower.pop();
        if (upper.size() > lower.size() + 1)
        {
            lower.push(upper.top());
            upper.pop();
        }
    };
    auto getMedian = [&]() -> double
    {
        if (lower.size() == upper.size())
            return (lower.top() + upper.top()) / 2.0;
        return upper.top();
    };
    for (int x : {5, 15, 1, 3})
    {
        addNum(x);
        cout << "after adding " << x << ": median=" << getMedian() << "\n";
    }

    // 9. Priority Queue from Ranges (C++20)
    cout << "\n--- 9. From Ranges ---\n";
    auto source = views::iota(1, 11) | views::transform([](int x)
                                                        { return x * x; });
    priority_queue<int> from_range(source.begin(), source.end());
    cout << "max of squares 1..10: " << from_range.top() << "\n";

    return 0;
}
