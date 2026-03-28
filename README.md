# 📚 C++20 STL Reference Library

> A complete, hands-on C++20 Standard Template Library reference — 20 files covering every major container and algorithm, each with working CP (Competitive Programming) patterns.

---

## 🗂️ File Overview

| # | File | Container / Topic | Key C++20 Features |
|---|------|-------------------|--------------------|
| 01 | `array.cpp` | `std::array` | `std::span`, constexpr, structured bindings |
| 02 | `bitset.cpp` | `std::bitset` | Bitmask DP, Sieve of Eratosthenes |
| 03 | `vector.cpp` | `std::vector` | Ranges views pipeline, coordinate compression |
| 04 | `deque.cpp` | `std::deque` | Sliding window max/min, circular buffer |
| 05 | `forward_list.cpp` | `std::forward_list` | `insert_after`, `splice_after`, merge |
| 06 | `list.cpp` | `std::list` | O(1) splice, bidirectional iteration |
| 07 | `map.cpp` | `std::map` | `contains()`, range queries, frequency count |
| 08 | `multimap.cpp` | `std::multimap` | `equal_range`, grouping pattern |
| 09 | `multiset.cpp` | `std::multiset` | K-th smallest, sorted bag, running min/max |
| 10 | `set.cpp` | `std::set` | Custom comparator, deduplication, sliding window |
| 11 | `stack.cpp` | `std::stack` | Monotonic stack, histogram area, min stack, DFS |
| 12 | `queue.cpp` | `std::queue` | BFS level-order, 2D grid shortest path |
| 13 | `priority_queue.cpp` | `std::priority_queue` | Dijkstra, merge K arrays, median of stream |
| 14 | `pair_tuple.cpp` | `std::pair` / `std::tuple` | `tuple_cat`, Kruskal sort, `<=>` spaceship |
| 15 | `string.cpp` | `std::string` | `std::format`, KMP search, `string_view` |
| 16 | `unordered_map.cpp` | `std::unordered_map` | Custom hash, Two Sum, prefix sum map |
| 17 | `unordered_set.cpp` | `std::unordered_set` | Longest consecutive, duplicate detection |
| 18 | `unordered_multimap.cpp` | `std::unordered_multimap` | Grouping, merge, frequency count |
| 19 | `unordered_multiset.cpp` | `std::unordered_multiset` | `equal_range`, merge, TSP bitmask |
| 20 | `numeric_algorithms.cpp` | `<numeric>` / `<algorithm>` | GCD/LCM, prefix sum, set ops, transform |

---

## ⚡ Quick Start — `run.ps1`

A single PowerShell script handles **compile + run + cleanup** for any file.

### Run one file
```powershell
.\run.ps1 array
.\run.ps1 vector.cpp        # extension is optional
```

### Run multiple files
```powershell
.\run.ps1 stack queue priority_queue
```

### Run all 20 files
```powershell
.\run.ps1 all
```

### Show help & file list
```powershell
.\run.ps1                   # no arguments = help menu
```

> **What the script does:**
> 1. Compiles with `g++ -std=c++20 -O2 -Wall`
> 2. Runs the binary
> 3. Deletes the `.exe` — keeps the repo source-only

> 💡 **The PowerShell script `run.ps1` handles all semicolon chaining automatically!**

---

## 🛠️ Requirements

| Tool | Version | Install |
|------|---------|---------|
| **GCC** | 13+ (tested on GCC 15.2) | [MSYS2](https://www.msys2.org/) |
| **PowerShell** | 5.1+ | Built into Windows |
| **C++ Standard** | C++20 | via `-std=c++20` flag |

### Install GCC via MSYS2
```bash
# In MSYS2 MinGW64 shell:
pacman -S mingw-w64-x86_64-gcc
```

Compiler path expected by `run.ps1`:
```
C:\msys64\mingw64\bin\g++.exe
```

### Verify installation
```powershell
C:\msys64\mingw64\bin\g++ --version
# Should print: g++ (Rev?, Built by MSYS2 project) 15.x.x
```

---

## 📖 What Each File Covers

### `array.cpp` — `std::array`
- Initialization, CTAD, `fill()`
- Element access, `std::span` subspan
- `constexpr` arrays and `static_assert`
- 2D array of arrays
- Grid BFS neighbor pattern (competitive programming)

### `bitset.cpp` — `std::bitset`
- Bitwise operations (`&`, `|`, `^`, `~`, `<<`, `>>`)
- `count()`, `any()`, `none()`, `all()`
- **Sieve of Eratosthenes** using bitset
- **Bitmask DP** — Subset Sum
- **TSP-style** bitmask DP
- Subset enumeration & `__builtin_popcount` tricks

### `vector.cpp` — `std::vector`
- Full modifier API (`push_back`, `emplace_back`, `insert`, `erase`)
- `std::span` integration
- Ranges views pipeline: `filter | transform | take`
- **Coordinate compression**
- **All permutations** with `ranges::next_permutation`
- **Two-pointer** two-sum

### `deque.cpp` — `std::deque`
- O(1) push/pop at both ends
- **Sliding window maximum** (monotonic deque)
- **Sliding window minimum**
- **Circular buffer** pattern

### `forward_list.cpp` — `std::forward_list`
- `insert_after` / `erase_after` with `before_begin()`
- `sort()`, `unique()`, `reverse()`, `remove_if()`
- `merge()` sorted lists, `splice_after()`

### `list.cpp` — `std::list` + `std::forward_list`
- O(1) `splice()` — move nodes without copying
- **Merge sorted lists**
- `remove_if()`, `stable sort`, `unique()`

### `map.cpp` — `std::map`
- `contains()` (C++20), `try_emplace`, `insert_or_assign`
- `lower_bound` / `upper_bound` range queries
- **Word frequency count**
- **Range query** by key interval
- `merge()`, `swap()`

### `multimap.cpp` — `std::multimap`
- `equal_range()` for all values of a key
- **Grouping pattern** — iterate unique keys

### `multiset.cpp` — `std::multiset`
- **K-th smallest** element
- **Sorted bag** — dynamic min/max with O(log n) delete
- `equal_range()` for range erase

### `set.cpp` — `std::set`
- Predecessor / successor via `prev()` / `next()`
- **Sliding window** with set
- **Custom comparator** (sort strings by length)
- `merge()`, deduplication

### `stack.cpp` — `std::stack`
- **Balanced parentheses** checker
- **Next Greater Element** (monotonic stack)
- **Daily Temperatures**
- **Largest Rectangle in Histogram**
- **Min Stack** (O(1) getMin)
- **Postfix expression evaluator**
- **DFS** with explicit stack

### `queue.cpp` — `std::queue` + `std::deque`
- **BFS** level-order traversal
- **2D Grid BFS** shortest path
- Monotonic deque sliding window

### `priority_queue.cpp` — `std::priority_queue`
- Max-heap / Min-heap
- **K largest / K smallest** elements
- **Dijkstra's Algorithm**
- **Merge K Sorted Arrays**
- **Task Scheduler**
- **Median of Stream** (two heaps)

### `pair_tuple.cpp` — `std::pair` / `std::tuple`
- Structured bindings everywhere
- Spaceship operator `<=>`
- `tuple_cat`, `tie`, `ignore`
- **Kruskal MST** edge sorting
- **Event sorting** by (time, type, id)
- `std::optional` for safe return values

### `string.cpp` — `std::string`
- `std::format` with alignment/padding (C++20)
- `string_view` — zero-copy views
- `starts_with` / `ends_with` (C++20)
- **KMP pattern matching**
- **Rotation check**
- **Stringstream** tokenization & CSV parsing

### `unordered_map.cpp` — `std::unordered_map`
- `contains()`, `try_emplace`, `insert_or_assign`
- **Custom hash** for `pair<int,int>` keys
- **Two Sum** — O(n)
- **Subarray sum = k** (prefix sum + hash map)
- `merge()` with conflict handling

### `unordered_set.cpp` — `std::unordered_set`
- **Two Sum** — O(n)
- **Duplicate detection** — O(n)
- **Longest Consecutive Sequence** — O(n)
- **Custom hash** for `pair<int,int>`

### `unordered_multimap.cpp` — `std::unordered_multimap`
- `equal_range()`, `count()`, `contains()`
- **Grouping pattern** by key
- Frequency counting with `count()`

### `unordered_multiset.cpp` — `std::unordered_multiset` + `std::unordered_multimap`
- `erase()` single vs all occurrences
- `merge()` (moves all elements)
- Ranges `filter` on unordered containers

### `numeric_algorithms.cpp` — `<numeric>` + `<algorithm>`
- `accumulate`, `reduce`, `partial_sum`, `inclusive_scan`, `exclusive_scan`
- `transform_reduce` — weighted dot product
- `iota` + **argsort** pattern
- `inner_product` — dot product & convolution
- **GCD / LCM** of arrays (C++17)
- **Prefix sum** + **difference array**
- `partial_sort`, `nth_element`, `stable_sort`
- **Set operations**: union, intersection, difference, symmetric difference
- **Ranges as numeric pipelines**: sum of squares of even numbers

---

## 🏆 Competitive Programming Patterns Index

| Pattern | File(s) |
|---------|---------|
| Two Sum (O(n)) | `unordered_map.cpp`, `unordered_set.cpp` |
| Sliding Window Max/Min | `deque.cpp`, `queue.cpp` |
| Prefix Sum + Range Query | `numeric_algorithms.cpp`, `array.cpp` |
| Monotonic Stack | `stack.cpp` |
| BFS (Graph / Grid) | `queue.cpp` |
| DFS (Explicit Stack) | `stack.cpp` |
| Dijkstra's Algorithm | `priority_queue.cpp` |
| Kruskal MST (edge sort) | `pair_tuple.cpp` |
| K-th Smallest/Largest | `multiset.cpp`, `priority_queue.cpp` |
| Median of Stream | `priority_queue.cpp` |
| Sieve of Eratosthenes | `bitset.cpp` |
| Bitmask DP | `bitset.cpp` |
| Coordinate Compression | `vector.cpp` |
| Frequency Count | `map.cpp`, `unordered_map.cpp` |
| Longest Consecutive Sequence | `unordered_set.cpp` |
| KMP Pattern Matching | `string.cpp` |
| Subarray Sum = K | `unordered_map.cpp` |
| Argsort (sorted indices) | `numeric_algorithms.cpp` |
| Merge K Sorted Arrays | `priority_queue.cpp` |
| Next Greater Element | `stack.cpp` |
| Largest Rectangle Histogram | `stack.cpp` |

---

## 📁 Repository Structure

```
Programming Practice/
├── array.cpp
├── bitset.cpp
├── deque.cpp
├── forward_list.cpp
├── list.cpp
├── map.cpp
├── multimap.cpp
├── multiset.cpp
├── numeric_algorithms.cpp
├── pair_tuple.cpp
├── priority_queue.cpp
├── queue.cpp
├── set.cpp
├── stack.cpp
├── string.cpp
├── unordered_map.cpp
├── unordered_multimap.cpp
├── unordered_multiset.cpp
├── unordered_set.cpp
├── vector.cpp
├── run.ps1                  ← compile & run script
├── STL_Study_Tracker.xlsx   ← study progress tracker
└── README.md                ← this file
```

---

## 🔧 Manual Compilation (PowerShell)

### ⚠️ IMPORTANT: PowerShell vs Bash Syntax

**PowerShell uses `;` to chain commands, NOT `&&`**

| Shell | Syntax | Your Shell |
|-------|--------|-----------|
| PowerShell (Windows) | `command1; command2` | ✅ Use this |
| Bash / Git Bash | `command1 && command2` | ❌ Don't use in PowerShell |
| CMD | `command1 & command2` | ❌ Don't use in PowerShell |

### Brief way to compile & run
```powershell
g++ -std=c++20 -O2 -Wall -o output.exe array.cpp; .\output.exe
```
---

## 📝 C++20 Features Used

| Feature | Used In |
|---------|---------|
| **`std::span`** | `array.cpp`, `vector.cpp` |
| **`std::format`** | `string.cpp`, `numeric_algorithms.cpp` |
| **`contains()`** on associative containers | `map.cpp`, `set.cpp`, `unordered_map.cpp`, `unordered_set.cpp` |
| **`ranges::sort / find / count`** | all container files |
| **`views::filter / transform / take`** | `vector.cpp`, `string.cpp`, `deque.cpp` |
| **`views::iota`** | `vector.cpp`, `priority_queue.cpp` |
| **`views::reverse`** | `string.cpp` (palindrome check) |
| **`views::keys / values`** | `unordered_map.cpp` |
| **Structured bindings** (`auto [a,b]`) | all files |
| **Spaceship operator `<=>`** | `pair_tuple.cpp`, `array.cpp` |
| **CTAD** (Class Template Argument Deduction) | `array.cpp`, `vector.cpp` |
| **`constexpr`** improvements | `array.cpp` |
| **`std::numbers::pi / e`** | `numeric_algorithms.cpp` |
| **`ranges::nth_element`** | `priority_queue.cpp` |
| **`ranges::unique`** | `vector.cpp`, `string.cpp` |

---

*Compiler: GCC 15.2.0 — Standard: C++20 — All 20 files: ✅ 20/20 PASS*
