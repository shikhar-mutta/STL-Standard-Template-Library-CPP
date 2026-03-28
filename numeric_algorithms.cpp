// ============================================================
// Numeric Algorithms — <numeric> <algorithm>    [C++20 Edition]
// compile: g++ -std=c++20 -O2 numeric_algorithms.cpp
// New: std::gcd/lcm, std::reduce, ranges fold, <numbers>
// ============================================================
#include <numeric>
#include <algorithm>
#include <ranges>
#include <vector>
#include <string>
#include <cmath>
#include <climits>
#include <functional>
#include <format>
#include <numbers>
#include <iostream>

using namespace std;

template<typename T>
void print_vec(const string& label, const vector<T>& v) {
    cout << label << ": "; for (auto& x : v) cout << x << " "; cout << "\n";
}

int main() {
    cout << "========== Numeric Algorithms [C++20] ==========\n";

    // 1. accumulate
    cout << "\n--- 1. accumulate ---\n";
    vector<int> v = {1,2,3,4,5};
    int sum = accumulate(v.begin(), v.end(), 0);
    cout << "sum:     " << sum << "\n";
    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
    cout << "product: " << product << "\n";
    string concat = accumulate(v.begin(), v.end(), string(""),
        [](string acc, int x){ return acc + to_string(x) + " "; });
    cout << "concat:  " << concat << "\n";

    // 2. reduce (C++17) — Parallelizable accumulate
    cout << "\n--- 2. reduce ---\n";
    int rsum = reduce(v.begin(), v.end());
    cout << "reduce (sum): " << rsum << "\n";
    int rmax = reduce(v.begin(), v.end(), INT_MIN,
                      [](int a, int b){ return max(a, b); });
    cout << "reduce (max): " << rmax << "\n";

    // 3. fold equivalents (C++20 uses accumulate; fold_left is C++23)
    cout << "\n--- 3. accumulate / fold ---\n";
    int fl = accumulate(v.begin(), v.end(), 0, plus<int>());
    cout << "accumulate (sum): " << fl << "\n";
    string fl_str = accumulate(v.begin(), v.end(), string(""),
        [](string acc, int x){ return acc + to_string(x) + "-"; });
    cout << "accumulate (concat): " << fl_str << "\n";
    int fr = accumulate(v.rbegin(), v.rend(), 0, plus<int>());
    cout << "reduce from right (sum): " << fr << "\n";
    auto fl_first = accumulate(next(v.begin()), v.end(), v.front(), plus<int>());
    cout << "fold_left_first equiv: " << fl_first << "\n";

    // 4. partial_sum — Prefix sums
    cout << "\n--- 4. partial_sum (Prefix Sum) ---\n";
    vector<int> prefix(v.size());
    partial_sum(v.begin(), v.end(), prefix.begin());
    print_vec("v",      v);
    print_vec("prefix", prefix);
    int l = 1, r = 3;
    int range_sum = prefix[r] - (l > 0 ? prefix[l-1] : 0);
    cout << "range_sum[" << l << "," << r << "]: " << range_sum << "\n";
    // Difference array
    vector<int> diff = {0,0,0,0,0};
    diff[1]+=3; diff[4]-=3;
    partial_sum(diff.begin(), diff.end(), diff.begin());
    print_vec("diff array (add 3 to [1,3])", diff);

    // 5. iota — Fill with sequence
    cout << "\n--- 5. iota ---\n";
    vector<int> idx(6);
    iota(idx.begin(), idx.end(), 0);
    print_vec("iota(0..5)", idx);
    // Argsort pattern
    vector<int> arr = {3,1,4,1,5};
    vector<int> order(arr.size());
    iota(order.begin(), order.end(), 0);
    ranges::sort(order, [&](int i, int j){ return arr[i] < arr[j]; });
    print_vec("argsort of {3,1,4,1,5}", order);

    // 6. inner_product — Dot product
    cout << "\n--- 6. inner_product ---\n";
    vector<int> a = {1,2,3}, b = {4,5,6};
    int dot = inner_product(a.begin(), a.end(), b.begin(), 0);
    cout << "dot product {1,2,3}·{4,5,6}: " << dot << "\n";
    int conv = inner_product(a.begin(), a.end(), b.begin(), 0,
                             plus<int>(), [](int x, int y){ return x*y*2; });
    cout << "convolution (x*y*2): " << conv << "\n";

    // 7. GCD & LCM (C++17)
    cout << "\n--- 7. GCD & LCM ---\n";
    cout << "gcd(48,18):    " << gcd(48,18) << "\n";
    cout << "lcm(4,6):      " << lcm(4,6)   << "\n";
    cout << "gcd(0,5):      " << gcd(0,5)   << "  (gcd(0,n)=n)\n";
    // GCD of array using accumulate (fold_left is C++23)
    vector<int> gc_arr = {12,18,24,36};
    int arr_gcd = accumulate(gc_arr.begin(), gc_arr.end(), 0,
                             [](int a, int b){ return gcd(a,b); });
    cout << "gcd of {12,18,24,36}: " << arr_gcd << "\n";
    long long arr_lcm = accumulate(gc_arr.begin(), gc_arr.end(), 1LL,
                                   [](long long a, long long b){ return lcm(a,b); });
    cout << "lcm of {12,18,24,36}: " << arr_lcm << "\n";

    // 8. <cmath> Functions
    cout << "\n--- 8. <cmath> ---\n";
    cout << format("sqrt(2):      {:.6f}\n", sqrt(2.0));
    cout << "pow(2,10):    " << pow(2,10)      << "\n";
    cout << "abs(-42):     " << abs(-42)       << "\n";
    cout << "ceil(3.2):    " << ceil(3.2)      << "\n";
    cout << "floor(3.8):   " << floor(3.8)     << "\n";
    cout << "round(3.5):   " << round(3.5)     << "\n";
    cout << format("log(e):       {:.6f}\n", log(numbers::e));
    cout << "log2(8):      " << log2(8.0)      << "\n";
    cout << "log10(100):   " << log10(100.0)   << "\n";
    cout << format("exp(1):       {:.6f}\n", exp(1.0));
    cout << format("fmod(10.5,3.2): {:.4f}\n", fmod(10.5,3.2));
    cout << "hypot(3,4):   " << hypot(3.0,4.0)<< "\n";
    cout << format("pi:           {:.6f}\n", numbers::pi);
    cout << format("e:            {:.6f}\n", numbers::e);

    // 9. <climits> Constants
    cout << "\n--- 9. <climits> Constants ---\n";
    cout << "INT_MAX:   " << INT_MAX   << "\n";
    cout << "INT_MIN:   " << INT_MIN   << "\n";
    cout << "LLONG_MAX: " << LLONG_MAX << "\n";
    cout << "numeric_limits<int>::max():         " << numeric_limits<int>::max()    << "\n";
    cout << "numeric_limits<double>::epsilon():  " << numeric_limits<double>::epsilon() << "\n";

    // 10. sort & variants
    cout << "\n--- 10. Sort Variants ---\n";
    vector<int> sv2 = {5,3,1,4,2};
    ranges::sort(sv2); print_vec("ranges::sort", sv2);
    vector<int> ps = {5,3,1,4,2,6};
    partial_sort(ps.begin(), ps.begin()+3, ps.end());
    print_vec("partial_sort (top 3 sorted)", ps);
    vector<int> ne = {5,3,1,4,2};
    ranges::nth_element(ne, ne.begin()+2);
    cout << "nth_element (median at idx 2): " << ne[2] << "\n";
    vector<pair<int,char>> sp = {{2,'a'},{1,'b'},{2,'c'},{1,'d'}};
    stable_sort(sp.begin(), sp.end());
    cout << "stable_sort: ";
    for (auto [n,c] : sp) cout << n << c << " "; cout << "\n";

    // 11. Binary Search
    cout << "\n--- 11. Binary Search ---\n";
    vector<int> bv = {1,2,3,4,5,6,7,8,9,10};
    auto lo = ranges::lower_bound(bv, 4);
    auto hi2 = ranges::upper_bound(bv, 7);
    cout << "lower_bound(4):  " << *lo  << "\n";
    cout << "upper_bound(7):  " << *hi2 << "\n";
    cout << "binary_search(5): " << ranges::binary_search(bv,5) << "\n";
    cout << "count in [4,7]:   " << distance(lo, hi2) << "\n";

    // 12. Transform, Replace, Remove
    cout << "\n--- 12. Transform / Replace / Remove ---\n";
    vector<int> tv = {1,2,3,4,5};
    vector<int> sq(tv.size());
    ranges::transform(tv, sq.begin(), [](int x){ return x*x; });
    print_vec("transform (square)", sq);
    ranges::transform(tv, tv.begin(), [](int x){ return x*2; });
    print_vec("transform in-place (x2)", tv);
    vector<int> rv2 = {1,2,3,2,1};
    ranges::replace(rv2, 2, 99);
    print_vec("replace 2 with 99", rv2);
    vector<int> ev = {1,2,3,4,5,6};
    auto [new_end, dummy] = ranges::remove_if(ev, [](int x){ return x%2==0; });
    ev.erase(new_end, ev.end());
    print_vec("remove evens", ev);

    // 13. min / max / clamp
    cout << "\n--- 13. min / max / clamp ---\n";
    cout << "min(3,7):           " << min(3,7) << "\n";
    cout << "max(3,7):           " << max(3,7) << "\n";
    cout << "min({3,1,4,1,5}):   " << min({3,1,4,1,5}) << "\n";
    cout << "max({3,1,4,1,5}):   " << max({3,1,4,1,5}) << "\n";
    auto [mn,mx] = ranges::minmax({3,1,4,1,5});
    cout << "minmax: min=" << mn << " max=" << mx << "\n";
    cout << "clamp(5, 1,10):  " << clamp(5,1,10)  << "\n";
    cout << "clamp(15,1,10):  " << clamp(15,1,10) << "\n";
    cout << "clamp(-5,1,10):  " << clamp(-5,1,10) << "\n";

    // 14. Set Operations
    cout << "\n--- 14. Set Operations ---\n";
    vector<int> s1 = {1,2,3,4,5}, s2 = {3,4,5,6,7}, out;
    set_union(s1.begin(),s1.end(), s2.begin(),s2.end(), back_inserter(out));
    print_vec("union", out); out.clear();
    set_intersection(s1.begin(),s1.end(), s2.begin(),s2.end(), back_inserter(out));
    print_vec("intersection", out); out.clear();
    set_difference(s1.begin(),s1.end(), s2.begin(),s2.end(), back_inserter(out));
    print_vec("difference (s1-s2)", out); out.clear();
    set_symmetric_difference(s1.begin(),s1.end(), s2.begin(),s2.end(), back_inserter(out));
    print_vec("symmetric difference", out);

    // 15. Ranges as Numeric Pipelines (C++20)
    cout << "\n--- 15. Ranges as Numeric Pipelines ---\n";
    // Sum of squares of even numbers in 1..20
    auto even_squares = views::iota(1,21)
        | views::filter([](int x){ return x%2==0; })
        | views::transform([](int x){ return x*x; });
    int sum_sq_even = reduce(even_squares.begin(), even_squares.end(), 0);
    cout << "sum of squares of even 1..20: " << sum_sq_even << "\n";

    // Running maximum via inclusive_scan
    vector<int> stream2 = {3,1,4,1,5,9,2,6};
    vector<int> running_max(stream2.size());
    inclusive_scan(stream2.begin(), stream2.end(), running_max.begin(),
                   [](int a, int b){ return max(a,b); });
    print_vec("running max", running_max);

    // exclusive_scan (C++17)
    vector<int> excl(v.size());
    exclusive_scan(v.begin(), v.end(), excl.begin(), 0);
    print_vec("exclusive_scan of {1..5}", excl);

    // transform_reduce (C++17) — weighted sum
    vector<int> weights2 = {2,3,1,4,5};
    int weighted = transform_reduce(v.begin(), v.end(), weights2.begin(), 0);
    cout << "weighted dot product {1..5}·{2,3,1,4,5}: " << weighted << "\n";

    return 0;
}
