// ============================================================
// std::string — Dynamic String                  [C++20 Edition]
// compile: g++ -std=c++20 -O2 string.cpp
// ============================================================
#include <string>
#include <string_view>
#include <format>
#include <ranges>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cctype>
#include <numeric>
#include <iostream>

using namespace std;

int main()
{
    cout << "========== std::string [C++20] ==========\n";

    // 1. Initialization
    cout << "\n--- 1. Initialization ---\n";
    string s1;
    string s2 = "hello";
    string s3(5, 'x');
    string s5 = s2 + " " + "world";
    // ***
    string_view sv = "hello world";
    cout << "s2:                " << s2 << "\n";
    cout << "s3 (5 x's):        " << s3 << "\n";
    cout << "s5:                " << s5 << "\n";
    cout << "sv (string_view):  " << sv << "\n";
    cout << "sv.substr(6,5):    " << sv.substr(6, 5) << "\n";

    // 2. Size & Capacity
    cout << "\n--- 2. Size & Capacity ---\n";
    string s = "competitive";
    cout << "size():    " << s.size() << "\n";
    cout << "length():  " << s.length() << "\n";
    cout << "capacity():" << s.capacity() << "\n";
    cout << "empty():   " << s.empty() << "\n";
    s.reserve(100);
    cout << "after reserve(100): capacity=" << s.capacity() << "\n";
    s.shrink_to_fit();
    s.resize(5);
    cout << "after resize(5): " << s << "\n";

    // 3. Element Access
    cout << "\n--- 3. Element Access ---\n";
    string str = "abcdef";
    cout << "str[2]:    " << str[2] << "\n";
    cout << "str.at(2): " << str.at(2) << "\n";
    cout << "front():   " << str.front() << "\n";
    cout << "back():    " << str.back() << "\n";
    cout << "c_str():   " << str.c_str() << "\n";
    str[0] = 'A';
    cout << "after str[0]='A': " << str << "\n";

    // 4. Modifiers
    cout << "\n--- 4. Modifiers ---\n";
    string m = "hello";
    m += " world";
    cout << "+=:                " << m << "\n";
    m.append("!!!");
    cout << "append():          " << m << "\n";
    m.append(3, '?');
    cout << "append(3,'?'):     " << m << "\n";
    m.push_back('!');
    cout << "push_back:         " << m << "\n";
    m.pop_back();
    cout << "pop_back:          " << m << "\n";
    m.insert(5, " C++20");
    cout << "insert(5,...):     " << m << "\n";
    m.erase(0, 6);
    cout << "erase(0,6):        " << m << "\n";
    m.replace(0, 5, "Hi");
    cout << "replace(0,5,...):  " << m << "\n";
    m.assign("brand new string");
    cout << "assign():          " << m << "\n";

    // 5. Search
    cout << "\n--- 5. Search ---\n";
    string text = "the cat sat on the mat";
    cout << "find(\"cat\"):                 " << text.find("cat") << "\n";
    cout << "find(\"dog\"):                 " << (text.find("dog") == string::npos ? "npos" : "found") << "\n";
    cout << "rfind(\"the\"):                " << text.rfind("the") << "\n";
    cout << "find(\"the\",5):               " << text.find("the", 5) << "\n";
    cout << "find_first_of(vowels):       " << text.find_first_of("aeiou") << "\n";
    cout << "find_last_of(vowels):        " << text.find_last_of("aeiou") << "\n";
    string trimable = "   hello   ";
    size_t sp = trimable.find_first_not_of(' '), ep = trimable.find_last_not_of(' ');
    cout << "trimmed:                     '" << trimable.substr(sp, ep - sp + 1) << "'\n";
    cout << "contains(\"cat\") via find:    " << (text.find("cat") != string::npos) << "\n";
    cout << "contains(\"dog\") via find:    " << (text.find("dog") != string::npos) << "\n";
    cout << "starts_with(\"the\"):          " << text.starts_with("the") << "\n";
    cout << "ends_with(\"mat\"):            " << text.ends_with("mat") << "\n";

    // 6. Substring & Compare
    cout << "\n--- 6. Substring & Compare ---\n";
    string base = "abcdefgh";
    cout << "substr(2,4):       " << base.substr(2, 4) << "\n";
    cout << "substr(5):         " << base.substr(5) << "\n";
    cout << "compare(abc,abc):  " << string("abc").compare("abc") << "\n";
    cout << "\"abc\" < \"abd\":     " << (string("abc") < string("abd")) << "\n";

    // 7. Conversions
    cout << "\n--- 7. Conversions ---\n";
    cout << "stoi(\"42\"):              " << stoi("42") << "\n";
    cout << "stoll(\"123456789012\"):   " << stoll("123456789012") << "\n";
    cout << "stod(\"3.14\"):            " << stod("3.14") << "\n";
    cout << "to_string(12345):          " << to_string(12345) << "\n";
    string formatted = format("Pi={:.4f}, Answer={}", 3.14159, 42);
    cout << "format result:         " << formatted << "\n";
    cout << "right-align: '" << format("{:>10}", "hello") << "'\n";
    cout << "left-align:  '" << format("{:<10}", "hello") << "'\n";
    cout << "center:      '" << format("{:^10}", "hello") << "'\n";
    cout << "fill zero:   '" << format("{:05}", 42) << "'\n";

    // 8. Algorithms on Strings (C++20 ranges)
    cout << "\n--- 8. Algorithms on Strings ---\n";
    string alg_s = "programming";
    ranges::sort(alg_s);
    cout << "sorted:   " << alg_s << "\n";
    alg_s = "programming";
    ranges::reverse(alg_s);
    cout << "reversed: " << alg_s << "\n";
    alg_s = "programming";
    cout << "count('g'): " << ranges::count(alg_s, 'g') << "\n";

    string uniq_s = "aabbccdde";
    ranges::sort(uniq_s);
    auto [new_end, dummy] = ranges::unique(uniq_s);
    uniq_s.erase(new_end, uniq_s.end());
    cout << "unique chars of 'aabbccdde': " << uniq_s << "\n";

    string mixed = "Hello World 123";
    string lower_s = mixed;
    ranges::transform(lower_s, lower_s.begin(), ::tolower);
    cout << "tolower: " << lower_s << "\n";

    // ***
    string pal = "racecar";
    bool isPalin = ranges::equal(pal, pal | views::reverse);
    cout << "\"racecar\" palindrome: " << isPalin << "\n";

    // 9. string_view
    cout << "\n--- 9. string_view ---\n";
    //    ***
    auto process = [](string_view sv2)
    {
        cout << "sv length=" << sv2.length() << "  starts_with 'H': " << sv2.starts_with('H') << "\n";
    };
    string str2 = "Hello, World";
    process(str2);
    process("literal");
    process(sv.substr(0, 5));

    // 10. Stringstream
    cout << "\n--- 10. Stringstream ---\n";
    string line = "hello world cpp20";
    stringstream ss(line);
    string token;
    cout << "tokens: ";
    // ***
    while (ss >> token)
        cout << token << " ";
    cout << "\n";

    string csv = "alice,bob,charlie";
    stringstream csv_ss(csv);
    cout << "CSV: ";
    while (getline(csv_ss, token, ','))
        cout << token << " ";
    cout << "\n";

    string nums_str = "10 20 30 40 50";
    stringstream num_ss(nums_str);
    vector<int> nums;
    int nn;
    while (num_ss >> nn)
        nums.push_back(nn);
    cout << "parsed nums sum= " << reduce(nums.begin(), nums.end()) << "\n";

    // 11. CP Patterns
    cout << "\n--- 11. CP Patterns ---\n";
    string s_orig = "abcde", s_rot = "cdeab";
    string doubled = s_orig + s_orig;
    cout << "\"cdeab\" rotation of \"abcde\": " << (doubled.find(s_rot) != string::npos) << "\n";

    string freq_s = "abracadabra";
    int freq[26] = {};
    for (char c : freq_s)
    {
        freq[c - 'a']++;
    }
    cout << "char freq in 'abracadabra': ";
    for (int i = 0; i < 26; i++)
    {
        if (freq[i])
        {
            cout << (char)('a' + i) << ":" << freq[i] << " ";
            cout << "\n";
        }
    }

    return 0;
}
