#include <bits/stdc++.h>
#include <chrono>
#include <regex>

using namespace std;

int main() {
    auto t_start = chrono::high_resolution_clock::now();
    ifstream input("../inputs/day3.txt");
    ostringstream oss;
    oss << input.rdbuf();
    string s = oss.str();

    regex re("(mul\\((\\d{1,3}),(\\d{1,3})\\))|(do\\(\\))|(don't\\(\\))");
    smatch match;
    long long ans1 = 0, ans2 = 0;
    bool mode = true;
    while (regex_search(s, match, re)) {
        if (match.str() == "do()") {
            mode = true;
        }
        else if (match.str() == "don't()") {
            mode = false;
        }
        else {
            if (mode) {
                ans2 += stoll(match[2]) * stoll(match[3]);
            }
            ans1 += stoll(match[2]) * stoll(match[3]);
        }
        s = match.suffix().str();
    }
    auto t_end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration<double, std::milli>(t_end-t_start).count() << "ms" << endl;
    cout << "Part 1: " << ans1 << endl;
    cout << "Part 2: " << ans2 << endl;
}
