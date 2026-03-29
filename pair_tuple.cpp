// ============================================================
// std::pair & std::tuple                        [C++20 Edition]
// compile: g++ -std=c++20 -O2 pair_tuple.cpp
// ============================================================
#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string>
#include <cmath>
#include <optional>
#include <iostream>

using namespace std;

int main() {
    cout << "========== std::pair [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    pair<int,string> p1;
    pair<int,string> p2(42, "hello");
    auto p3 = make_pair(3.14, 'A');
    auto p4 = pair{10, string("world")};
    cout << "p2: (" << p2.first << ", " << p2.second << ")\n";
    cout << "p3: (" << p3.first << ", " << p3.second << ")\n";
    cout << "p4: (" << p4.first << ", " << p4.second << ")\n";

    // 2. Structured Bindings
    cout << "\n--- 2. Structured Bindings ---\n";
    auto [num, name] = pair{99, string("ninety-nine")};
    cout << "structured binding: " << num << " = " << name << "\n";
    vector<pair<string,int>> kvs = {{"a",1},{"b",2},{"c",3}};
    cout << "map-like iteration: ";
    for (auto& [k,v] : kvs) {
        cout << k << ":" << v << " \n";
    }
    kvs.emplace_back("d", 4);
    cout << "after emplace: " << kvs.size() << " elements\n";

    // 3. Comparison (lexicographic)
    cout << "\n--- 3. Comparison ---\n";
    pair<int,int> a={1,2}, b={1,3}, c={2,0};
    cout << "a < b (first equal, compare second): " << (a < b) << "\n";
    cout << "b < c (compare first: 1 < 2):        " << (b < c) << "\n";
    cout << "a == a:  " << (a == a) << "\n";
    auto cmp = a <=> b;
    cout << "a <=> b is less: " << (cmp < 0) << "\n";

    // 4. Swap
    cout << "\n--- 4. Swap ---\n";
    pair<int,int> x={1,2}, y={3,4};
    x.swap(y);
    cout << "after x.swap(y): x=(" << x.first << "," << x.second << ") y=(" << y.first << "," << y.second << ")\n";
    swap(x, y);
    cout << "after std::swap:  x=(" << x.first << "," << x.second << ")\n";

    // 5. Pairs in Containers & Algorithms
    cout << "\n--- 5. Sorting Pairs ---\n";
    vector<pair<int,int>> edges = {{3,2},{1,5},{4,1},{1,3},{2,4}};
    ranges::sort(edges);
    cout << "sorted by default: ";
    for (auto [u,v] : edges) {
        cout << "(" << u << "," << v << ") \n";
    }

    ranges::sort(edges, [](auto& p, auto& q){ return -p.second < -q.second; });
    cout << "sorted by 2nd desc: ";
    for (auto [u,v] : edges) {
        cout << "(" << u << "," << v << ") \n";
    }

    vector<tuple<int,int,int>> graph = {{4,0,1},{2,0,2},{3,1,2},{1,2,3},{5,1,3}};
    ranges::sort(graph);
    cout << "Kruskal edges sorted by weight:\n";
    for (auto [w,u,v] : graph) {
        cout << "  u=" << u << " v=" << v << " w=" << w << "\n";
    }

    // ============================================================
    cout << "\n========== std::tuple [C++20] ==========\n";

    // 6. Initialization
    cout << "\n--- 6. Initialization ---\n";
    tuple<int,string,double> t1(1, "hello", 3.14);
    auto t2 = make_tuple(42, string("world"), 2.72);
    auto t3 = tuple{10, string("abc"), 'Z'};
    cout << "t1: (" << get<0>(t1) << ", " << get<1>(t1) << ", " << get<2>(t1) << ")\n";
    cout << "t2: (" << get<0>(t2) << ", " << get<1>(t2) << ", " << get<2>(t2) << ")\n";

    // 7. Structured Bindings
    cout << "\n--- 7. Structured Bindings ---\n";
    auto [ta, tb, tc] = t3;
    cout << "structured: " << ta << ", " << tb << ", " << tc << "\n";
    cout << "get<0>: " << get<0>(t1) << "\n";
    cout << "get<1>: " << get<1>(t1) << "\n";
    get<0>(t1) = 100;
    cout << "modified t1[0]: " << get<0>(t1) << "\n";

    // 8. tie — Unpack into existing variables
    cout << "\n--- 8. tie ---\n";
    int ti; double td; string ts;
    tie(ti, td, ts) = make_tuple(7, 1.41, string("pi"));
    cout << "tie: " << ti << ", " << td << ", " << ts << "\n";
    tie(ti, ignore, ts) = make_tuple(99, 0.0, string("hi"));
    cout << "tie with ignore: " << ti << ", " << ts << "\n";

    // 9. Metadata
    cout << "\n--- 9. Metadata ---\n";
    using T = tuple<int,double,string,char>;
    cout << "tuple_size: " << tuple_size<T>::value << "\n";

    // 10. Comparison & Swap
    cout << "\n--- 10. Compare & Swap ---\n";
    auto ta2 = make_tuple(1,2,3), tb2 = make_tuple(1,2,4);
    cout << "ta < tb:  " << (ta2 < tb2) << "\n";
    cout << "ta == ta: " << (ta2 == ta2) << "\n";
    swap(ta2, tb2);
    cout << "after swap: ta=(" << get<0>(ta2) << "," << get<1>(ta2) << "," << get<2>(ta2) << ") "
         << "tb=(" << get<0>(tb2) << "," << get<1>(tb2) << "," << get<2>(tb2) << ")\n";

    // 11. tuple_cat
    cout << "\n--- 11. tuple_cat ---\n";
    auto combined = tuple_cat(make_tuple(1,2), make_tuple(string("hello"), 3.14));
    cout << "combined size: " << tuple_size<decltype(combined)>::value << "\n";
    auto [ca,cb,cc,cd] = combined;
    cout << "combined: " << ca << " " << cb << " " << cc << " " << cd << "\n";

    // 12. CP Patterns
    cout << "\n--- 12. CP Patterns ---\n";
    vector<tuple<int,int,int>> events = {{3,1,5},{1,0,2},{3,0,3},{2,1,4}};
    ranges::sort(events);
    cout << "sorted events:\n";
    for (auto [t,type,id] : events) {
        cout << "  t=" << t << " type=" << type << " id=" << id << "\n";
    }

    auto divmod = [](int a, int b){ return pair{a/b, a%b}; };
    auto [quot, rem] = divmod(17, 5);
    cout << "17 / 5 = " << quot << " rem " << rem << "\n";

    auto safe_sqrt = [](double x) -> optional<double> {
        if (x < 0) return nullopt;
        return sqrt(x);
    };
    if (auto r = safe_sqrt(16.0)) cout << "sqrt(16) = " << *r << "\n";
    if (!safe_sqrt(-1.0))         cout << "sqrt(-1): no value (negative)\n";

    return 0;
}
