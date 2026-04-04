// ============================================================
// std::queue & std::deque                       [C++20 Edition]
// compile: g++ -std=c++20 -O2 queue.cpp
// ============================================================
#include <queue>
#include <deque>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    cout << "========== std::queue [C++20] ==========\n";

    // 1. Basic Operations
        cout << "\n--- 1. Basic Operations ---\n";
    queue<int> q;
    q.push(1); q.push(2); q.push(3); q.push(4); q.push(5);
    cout << "front: " << q.front() << "  back: " << q.back() << "  size: " << q.size() << "\n";
    cout << "pop order (FIFO): ";
    while (!q.empty()) { cout << q.front() << " "; q.pop(); }
    cout << "\n";

    queue<pair<int,int>> pq;
    pq.emplace(1,2); pq.emplace(3,4);
    auto [f1,f2] = pq.front();
    cout << "front pair: (" << f1 << "," << f2 << ")\n";

    queue<int> qa, qb;
    qa.push(1); qb.push(99);
    qa.swap(qb);
    cout << "after swap, qa.front = " << qa.front() << "\n";

    // 2. BFS — Level-Order Traversal
    cout << "\n--- 2. BFS (Level-Order Traversal) ---\n";
    int n = 7;
    vector<vector<int>> tree(n);
    tree[0]={1,2}; tree[1]={3,4}; tree[2]={5,6};
    vector<bool> visited(n, false);
    queue<int> bfs2;
    bfs2.push(0); visited[0]=true;
    cout << "BFS levels: ";
    while (!bfs2.empty()) {
        int sz = bfs2.size();
        cout << "[";
        while (sz--) {
            int node = bfs2.front(); bfs2.pop();
            cout << node;
            if (sz) cout << ",";
            for (int child : tree[node])
                if (!visited[child]) { visited[child]=true; bfs2.push(child); }
        }
        cout << "] ";
    }
    cout << "\n";

    // 3. BFS — 2D Grid Shortest Path
    cout << "\n--- 3. BFS (2D Grid) ---\n";
    int R = 4, C = 4;
    vector<string> grid = {"....", ".##.", "....", "..#."};
    vector<vector<int>> dist_grid(R, vector<int>(C, -1));
    queue<pair<int,int>> grid_bfs;
    dist_grid[0][0] = 0; grid_bfs.push({0,0});
    int dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};
    while (!grid_bfs.empty()) {
        auto [r,c] = grid_bfs.front(); grid_bfs.pop();
        for (int d = 0; d < 4; d++) {
            int nr=r+dr[d], nc=c+dc[d];
            if (nr>=0 && nr<R && nc>=0 && nc<C && grid[nr][nc]!='#' && dist_grid[nr][nc]==-1) {
                dist_grid[nr][nc] = dist_grid[r][c]+1;
                grid_bfs.push({nr,nc});
            }
        }
    }
    cout << "shortest path to (3,3): " << dist_grid[3][3] << "\n";

    // ============================================================
    cout << "\n========== std::deque ==========\n";

    // 4. Basic Operations
    cout << "\n--- 4. Deque Basics ---\n";
    deque<int> d;
    d.push_back(2); d.push_back(3);
    d.push_front(1); d.push_front(0);
    cout << "deque: "; for (int x : d) cout << x << " "; cout << "\n";
    cout << "front: " << d.front() << "  back: " << d.back() << "\n";
    cout << "d[2]:  " << d[2] << "\n";
    d.pop_front(); d.pop_back();
    cout << "after pop_front/back: "; for (int x : d) cout << x << " "; cout << "\n";
    d.insert(d.begin()+1, 99);
    cout << "after insert(1,99): "; for (int x : d) cout << x << " "; cout << "\n";
    d.erase(d.begin());
    cout << "after erase(begin): "; for (int x : d) cout << x << " "; cout << "\n";

    // 5. Monotonic Deque — Sliding Window Maximum
    cout << "\n--- 5. Sliding Window Maximum ---\n";
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    deque<int> mono_dq;
    vector<int> max_result;
    for (int i = 0; i < (int)nums.size(); i++) {
        while (!mono_dq.empty() && mono_dq.front() < i-k+1) mono_dq.pop_front();
        while (!mono_dq.empty() && nums[mono_dq.back()] < nums[i]) mono_dq.pop_back();
        mono_dq.push_back(i);
        if (i >= k-1) max_result.push_back(nums[mono_dq.front()]);
    }
    cout << "sliding window max (k=" << k << "): ";
    for (int x : max_result) cout << x << " "; cout << "\n";

    // 6. Double-Ended Task Queue
    cout << "\n--- 6. Double-Ended Operations ---\n";
    deque<string> tasks;
    tasks.push_back("task1"); tasks.push_front("urgent");
    tasks.push_back("task2"); tasks.emplace_back("task3");
    cout << "task queue: "; for (auto& t : tasks) cout << t << " "; cout << "\n";
    cout << "processing: ";
    while (!tasks.empty()) { cout << tasks.front() << " "; tasks.pop_front(); }
    cout << "\n";

    // 7. Ranges on Deque
    cout << "\n--- 7. Ranges on Deque ---\n";
    deque<int> rd = {5,3,1,4,2,6};
    ranges::sort(rd);
    cout << "sorted: "; for (int x : rd) cout << x << " "; cout << "\n";
    auto filtered = rd | views::filter([](int x){ return x > 3; });
    cout << "filtered > 3: "; for (int x : filtered) cout << x << " "; cout << "\n";

    return 0;
}
