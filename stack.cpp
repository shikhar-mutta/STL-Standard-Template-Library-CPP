// ============================================================
// std::stack                                    [C++20 Edition]
// compile: g++ -std=c++20 -O2 stack.cpp
// ============================================================
#include <stack>
#include <vector>
#include <ranges>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    cout << "========== std::stack [C++20] ==========\n";

    // 1. Basic Operations
    cout << "\n--- 1. Basic Stack ---\n";
    stack<int> s;
    s.push(1); s.push(2); s.push(3); s.push(4); s.emplace(5);
       cout << "top:   " << s.top()  << " \n";
    cout << "size:  " << s.size() << " \n";
    cout << "empty: " << s.empty()<< " \n";
    cout << "pop order (LIFO): ";
    while (!s.empty()) { cout << s.top() << " "; s.pop(); }
    cout << " \n";

    stack<int,vector<int>> vec_stack;
    vec_stack.push(10); vec_stack.push(20);
    cout << "vector-backed stack top: " << vec_stack.top() << " \n";

    stack<int> sa, sb;
    sa.push(1); sb.push(99);
    sa.swap(sb);
    cout << "after swap, sa.top = " << sa.top() << " \n";

    // 2. Balanced Parentheses
    cout << "\n--- 2. Balanced Parentheses ---\n";
    auto isBalanced = [](string_view expr) {
        stack<char> stk;
        for (char c : expr) {
            if (c=='(' || c=='[' || c=='{') stk.push(c);
            else if (c==')' || c==']' || c=='}') {
                if (stk.empty()) return false;
                char top = stk.top(); stk.pop();
                if ((c==')' && top!='(') || (c==']' && top!='[') || (c=='}' && top!='{')) return false;
            }
        }
        return stk.empty();
    };
    cout << "\"{[()]}\"  balanced: " << isBalanced("{[()]}") << "\n";
    cout << "\"{[(])}\"  balanced: " << isBalanced("{[(])}") << "\n";
    cout << "\"(((\"     balanced: " << isBalanced("(((")    << "\n";

    // 3. Next Greater Element — Monotonic Stack
    cout << "\n--- 3. Next Greater Element ---\n";
    vector<int> arr = {4,5,2,10,8,3,6};
    vector<int> nge(arr.size(), -1);
    stack<int> mono;
    for (int i = 0; i < (int)arr.size(); i++) {
        while (!mono.empty() && arr[mono.top()] < arr[i]) {
            nge[mono.top()] = arr[i]; mono.pop();
        }
        mono.push(i);
    }
    cout << "array: "; for (int x : arr) cout << x << " "; cout << "\n";
    cout << "NGE:   "; for (int x : nge) cout << x << " "; cout << "\n";

    // 4. Daily Temperatures
    cout << "\n--- 4. Daily Temperatures ---\n";
    vector<int> temps = {73,74,75,71,69,72,76,73};
    vector<int> wait(temps.size(), 0);
    stack<int> ts;
    for (int i = 0; i < (int)temps.size(); i++) {
        while (!ts.empty() && temps[ts.top()] < temps[i]) {
            wait[ts.top()] = i - ts.top(); ts.pop();
        }
        ts.push(i);
    }
    cout << "temps: "; for (int x : temps) cout << x << " "; cout << "\n";
    cout << "days:  "; for (int x : wait)  cout << x << " "; cout << "\n";

    // 5. Largest Rectangle in Histogram
    cout << "\n--- 5. Largest Rectangle in Histogram ---\n";
    vector<int> heights = {2,1,5,6,2,3};
    int max_area = 0;
    stack<int> hist_stk;
    for (int i = 0; i <= (int)heights.size(); i++) {
        int h = (i == (int)heights.size()) ? 0 : heights[i];
        while (!hist_stk.empty() && heights[hist_stk.top()] > h) {
            int height = heights[hist_stk.top()]; hist_stk.pop();
            int width = hist_stk.empty() ? i : i - hist_stk.top() - 1;
            max_area = max(max_area, height * width);
        }
        hist_stk.push(i);
    }
    cout << "histogram: "; for (int x : heights) cout << x << " "; cout << "\n";
    cout << "largest rectangle area: " << max_area << "\n";

    // 6. Min Stack
    cout << "\n--- 6. Min Stack ---\n";
    struct MinStack {
        stack<int> main_stk, min_stk;
        void push(int val) {
            main_stk.push(val);
            if (min_stk.empty() || val <= min_stk.top()) min_stk.push(val);
        }
        void pop() {
            if (main_stk.top() == min_stk.top()) min_stk.pop();
            main_stk.pop();
        }
        int top()    { return main_stk.top(); }
        int getMin() { return min_stk.top();  }
    };
    MinStack ms;
    for (int x : {5,3,7,1,4,1,6}) ms.push(x);
    cout << "top: " << ms.top() << "  min: " << ms.getMin() << "\n";
    ms.pop(); ms.pop();
    cout << "after 2 pops — top: " << ms.top() << "  min: " << ms.getMin() << "\n";

    // 7. Evaluate Postfix Expression
    cout << "\n--- 7. Postfix Evaluation ---\n";
    auto evalRPN = [](vector<string> tokens) {
        stack<long long> stk;
        for (auto& tok : tokens) {
            if (tok=="+" || tok=="-" || tok=="*" || tok=="/") {
                long long b = stk.top(); stk.pop();
                long long a = stk.top(); stk.pop();
                if (tok=="+") stk.push(a+b);
                else if (tok=="-") stk.push(a-b);
                else if (tok=="*") stk.push(a*b);
                else stk.push(a/b);
            } else stk.push(stoll(tok));
        }
        return stk.top();
    };
    cout << "2 1 + 3 * = " << evalRPN({"2","1","+","3","*"}) << "  (expected 9)\n";
    cout << "4 13 5 / + = " << evalRPN({"4","13","5","/","+"}) << "  (expected 6)\n";

    // 8. DFS using explicit stack
    cout << "\n--- 8. DFS (Explicit Stack) ---\n";
    int V = 6;
    vector<vector<int>> adj(V);
    adj[0]={1,2}; adj[1]={3}; adj[2]={3,4}; adj[3]={5}; adj[4]={5};
    vector<bool> vis(V, false);
    stack<int> dfs_stk;
    dfs_stk.push(0); vis[0]=true;
    cout << "DFS order: ";
    while (!dfs_stk.empty()) {
        int node = dfs_stk.top(); dfs_stk.pop();
        cout << node << " ";
        for (int nb : adj[node] | views::reverse)
            if (!vis[nb]) { vis[nb]=true; dfs_stk.push(nb); }
    }
    cout << "\n";

    return 0;
}
