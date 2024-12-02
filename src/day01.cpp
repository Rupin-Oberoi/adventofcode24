#include <bits/stdc++.h>

using namespace std;

int calc(const vector<int>& l1, const vector<int>& l2) {
    long long res1 = 0, res2 = 0;

    unordered_map<int, int> m2;
    for (int i=0; i<l1.size(); i++) {
        res1 += abs(l1[i] - l2[i]);
        if (m2.find(l2[i]) == m2.end()) {
            m2[l2[i]] = 1;
        } else {
            m2[l2[i]]++;
        }
    }

    for (int i=0; i<l1.size(); i++) {
        if (m2.find(l1[i]) != m2.end()) {
            res2 += l1[i] * m2[l1[i]];
        }
    }

    cout << res1 << endl;
    cout << res2 << endl;
    
    return 0;
}

int main() {
    ifstream input("../inputs/day1.txt");
    if (!input) {
        cerr << "Error reading input" << endl;
        return 1;
    }
    vector<int> l1;
    vector<int> l2;

    string line;
    while (getline(input, line)) {
        int e1, e2;
        istringstream(line) >> e1 >> e2;
        l1.push_back(e1);
        l2.push_back(e2);
    }

    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    calc(l1, l2);
    return 0;
}

