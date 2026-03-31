// ============================================================
// std::vector — Dynamic Array                    [C++20 Edition]
// compile: g++ -std=c++20 -O2 vector.cpp
// ============================================================
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <span>
#include <format>
#include <iostream>
#include <string>

using namespace std;



int main() {
    cout << "========== std::vector [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    vector<int> v1;
    vector<int> v2(5, 42);
    vector<int> v3 = {1, 2, 3, 4, 5};
    vector<int> v4(v3.begin(), v3.end());
    vector<int> v5(v3);
    vector<int> v6(move(v5));  // v5 is now empty

    // C++20: from iota view
    auto rng = views::iota(1, 6);
    vector<int> v_range(rng.begin(), rng.end());

    cout << "v2 (5x42): "; for (auto& x : v2) cout << x << " "; cout << "\n";
    cout << "v3 {1..5}: "; for (auto& x : v3) cout << x << " "; cout << "\n";
    cout << "v_range: "; for (auto& x : v_range) cout << x << " "; cout << "\n";

    // 2. Size & Capacity
    cout << "\n--- 2. Size & Capacity ---\n";
    vector<int> v = {10, 20, 30, 40, 50};
    cout << "size():     " << v.size()     << "\n";
    cout << "capacity(): " << v.capacity() << "\n";
    cout << "empty():    " << v.empty()    << "\n";
    v.reserve(100); cout << "after reserve(100): capacity=" << v.capacity() << "\n";
    v.shrink_to_fit(); cout << "after shrink_to_fit: capacity=" << v.capacity() << "\n";
    v.resize(7, 99);
    cout << "after resize(7,99): "; for (int x : v) cout << x << " "; cout << "\n";

    // 3. Element Access
    cout << "\n--- 3. Element Access ---\n";
    v = {1, 2, 3, 4, 5};
    cout << "v[2]:    " << v[2]    << "\n";
    cout << "v.at(2): " << v.at(2) << "\n";
    cout << "front(): " << v.front()<< "\n";
    cout << "back():  " << v.back() << "\n";
    span<int> sp = v;
    cout << "span[0..2]: " << sp[0] << " " << sp[1] << " " << sp[2] << "\n";
    auto first3 = sp.first(3);
    cout << "span.first(3): "; for (int x : first3) cout << x << " "; cout << "\n";

    // 4. Modifiers
    cout << "\n--- 4. Modifiers ---\n";
    v = {1, 2, 3};
    v.push_back(4); v.emplace_back(5);
    cout << "after push_back/emplace_back: "; for (auto& x : v) cout << x << " "; cout << "\n";
    v.pop_back(); cout << "after pop_back: "; for (auto& x : v) cout << x << " "; cout << "\n";
    v.insert(v.begin()+1, 99); cout << "after insert(1,99): "; for (auto& x : v) cout << x << " "; cout << "\n";
    v.insert(v.end(), {100,200}); cout << "after insert range: "; for (auto& x : v) cout << x << " "; cout << "\n";
    v.erase(v.begin()); cout << "after erase(begin): "; for (auto& x : v) cout << x << " "; cout << "\n";
    v.erase(v.begin(), v.begin()+2); cout << "after erase [0,2): "; for (auto& x : v) cout << x << " "; cout << "\n";
    v.assign({10,20,30,40,50}); cout << "after assign: "; for (auto& x : v) cout << x << " "; cout << "\n";
    v.clear(); cout << "after clear, size: " << v.size() << "\n";

    // 5. Iterators
    cout << "\n--- 5. Iterators ---\n";
    v = {1, 2, 3, 4, 5};
    cout << "forward: "; for (int x : v) cout << x << " "; cout << "\n";
    cout << "reverse: "; for (auto rit = v.rbegin(); rit != v.rend(); ++rit) cout << *rit << " "; cout << "\n";
    const vector<int>& cv = v;
    cout << "cbegin:  "; for (auto it = cv.cbegin(); it != cv.cend(); ++it) cout << *it << " "; cout << "\n";

    // 6. Algorithms (C++20 ranges)
    cout << "\n--- 6. Algorithms ---\n";
    v = {5, 3, 1, 4, 2};
    ranges::sort(v);    cout << "ranges::sort: "; for (auto& x : v) cout << x << " "; cout << "\n";
    ranges::reverse(v); cout << "ranges::reverse: "; for (auto& x : v) cout << x << " "; cout << "\n";
    auto it = ranges::find(v, 3);
    cout << "ranges::find(3): index " << distance(v.begin(), it) << "\n";
    cout << "ranges::count(3): " << ranges::count(v, 3) << "\n";
    ranges::sort(v);
    auto lb = ranges::lower_bound(v, 3);
    auto ub = ranges::upper_bound(v, 3);
    cout << "lower_bound(3): index " << distance(v.begin(), lb) << "\n";
    cout << "upper_bound(3): index " << distance(v.begin(), ub) << "\n";
    cout << "binary_search(3): " << ranges::binary_search(v, 3) << "\n";
    auto [min_it, max_it] = ranges::minmax_element(v);
    cout << "min=" << *min_it << " max=" << *max_it << "\n";

    // 7. Numeric
    cout << "\n--- 7. Numeric ---\n";
    v = {1, 2, 3, 4, 5};
    cout << "reduce (sum):  " << reduce(v.begin(), v.end(), 0) << "\n";
    vector<int> prefix(v.size());
    partial_sum(v.begin(), v.end(), prefix.begin());
    cout << "partial_sum (prefix): "; for (auto& x : prefix) cout << x << " "; cout << "\n";
    vector<int> idx(5);
    iota(idx.begin(), idx.end(), 1);
    cout << "iota(1..5): "; for (auto& x : idx) cout << x << " "; cout << "\n";

    // 8. Ranges & Views Pipeline
    cout << "\n--- 8. Ranges Views Pipeline ---\n";
    v = {1,2,3,4,5,6,7,8,9,10};
    auto pipeline = v
        | views::filter([](int x){ return x % 2 == 0; })
        | views::transform([](int x){ return x * x; })
        | views::take(3);
    cout << "even squares (first 3): "; for (int x : pipeline) cout << x << " "; cout << "\n";

    cout << "iota(1,6): "; for (int x : views::iota(1,6)) cout << x << " "; cout << "\n";

    vector<string> tmp = {"a","b","c"};
    cout << "enumerate (C++20 manual):\n";
    for (size_t i = 0; i < tmp.size(); ++i) cout << "  [" << i << "]=" << tmp[i] << "\n";

    vector<int> keys = {1,2,3}; vector<string> vals = {"one","two","three"};
    cout << "zip (manual): ";
    for (size_t i = 0; i < keys.size(); ++i) cout << keys[i] << ":" << vals[i] << " ";
    cout << "\n";

    auto mult3 = v | views::filter([](int x){ return x % 3 == 0; });
    cout << "multiples of 3: "; for (int x : mult3) cout << x << " "; cout << "\n";

    // 9. 2D Vector
    cout << "\n--- 9. 2D Vector ---\n";
    int R = 3, C = 4;
    vector<vector<int>> grid(R, vector<int>(C, 0));
    for (int r = 0; r < R; r++) for (int c = 0; c < C; c++) grid[r][c] = r*C+c;
    cout << "3x4 grid:\n";
    for (auto& row : grid) { cout << "  "; for (int x : row) cout << x << " "; cout << "\n"; }

    // 10. CP Patterns
    cout << "\n--- 10. CP Patterns ---\n";
    vector<int> raw = {40,10,30,20,10,40,30};
    vector<int> su = raw;
    ranges::sort(su);
    su.erase(ranges::unique(su).begin(), su.end());
    cout << "sorted unique: "; for (auto& x : su) cout << x << " "; cout << "\n";
    vector<int> compressed;
    for (int x : raw) compressed.push_back(distance(su.begin(), ranges::lower_bound(su, x)));
    cout << "coordinate compressed: "; for (auto& x : compressed) cout << x << " "; cout << "\n";

    vector<int> perm = {1,2,3};
    cout << "all permutations: ";
    do { cout << "[" << perm[0] << perm[1] << perm[2] << "] "; } while (ranges::next_permutation(perm).found);
    cout << "\n";

    vector<int> arr = {1,3,5,6,8,9};
    int target = 11, lo = 0, hi = (int)arr.size()-1;
    cout << "two-sum pairs summing to " << target << ": ";
    while (lo < hi) {
        if (arr[lo]+arr[hi] == target) { cout << "(" << arr[lo] << "," << arr[hi] << ") "; lo++; hi--; }
        else if (arr[lo]+arr[hi] < target) lo++; else hi--;
    }
    cout << "\n";

    return 0;
}
