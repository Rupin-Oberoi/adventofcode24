#include <bits/stdc++.h>

using namespace std;

bool isSafe(const vector<int>& l) {
    bool order = l[0] <= l[1];
    // if asc then true, if desc then false
    for (int i=0; i<l.size()-1; i++) {
        int diff = l[i+1] - l[i];
        if (order) {
            if (diff < 1 || diff > 3) {
                return false;
            }
        }
        else {
            if (diff > -1 || diff < -3) {
                return false;
            }
        }
    }
    return true;
}


bool isSafe2BruteForce(const vector<int>& l) {
    if (isSafe(l)) {
        return true;
    }
    for (int i=0; i<l.size(); i++) {
        vector<int> l2 = l;
        l2.erase(l2.begin() + i);
        if (isSafe(l2)) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream input("../inputs/day2.txt");
    if (!input) {
        cerr << "Error reading input" << endl;
        return 1;
    }
    int res = 0;
    int res2 = 0;
    string line;
    vector<int> l;
    while (getline(input, line)) {
        l = {};
        istringstream stream(line);
        int num;
        while (stream >> num) {
            l.push_back(num);
        }
        if (isSafe(l)) {
            res++;
        }
        if (isSafe2BruteForce(l)) {
            res2++;
        }
    }
    cout << res << endl;
    cout << res2 << endl;
}