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

bool isSafe2(const vector<int>& l) {
    bool order = false;
    // if asc then true, if desc then false
    if (l.size() <= 2) {
        return true;
    }
    else if (l.size() == 3) {
        bool a = abs(l[0] - l[1]) <= 3 && abs(l[0] - l[1]) >= 1;
        bool b = abs(l[1] - l[2]) <= 3 && abs(l[1] - l[2]) >= 1;
        bool c = abs(l[0] - l[2]) <= 3 && abs(l[0] - l[2]) >= 1;
        return a || b || c;
    }
    else {
        bool a = l[0] <= l[1];
        bool b = l[1] <= l[2];
        bool c = l[2] <= l[3];
        int d = a + b + c;
        if (d >= 2) {
            order = true;
        }
        
        vector<int> violations;

        for (int i=0; i<l.size()-1; i++) {
            int diff = l[i+1] - l[i];
            if (order) {
                if (diff < 1 || diff > 3) {
                    violations.push_back(i);
                }
                if (violations.size() > 2) {
                    return false;
                }
            }
            else {
                if (diff > -1 || diff < -3) {
                    violations.push_back(i);
                }
                if (violations.size() > 2) {
                    return false;
                }
            }
        }
        if (violations.size() == 0) {
            return true;
        }
        if (violations.size() == 1 && (violations[0] == 0 || violations[0] == l.size()-2))
            return true;
        if (violations.size() == 2 && (violations[0] == 0 && violations[1] == l.size()-2))
            return false;
        
        if (violations.size()==2 && violations[1] - violations[0] == 1) {
            int err_ind = violations[1];
            // remove err_ind
            if (order) {
                if (l[err_ind+1] - l[err_ind-1] <= 3 && l[err_ind+1] - l[err_ind-1] >= 1) {
                    return true;
                }
            }
            else {
                if (l[err_ind+1] - l[err_ind-1] >= -3 && l[err_ind+1] - l[err_ind-1] <= -1) {
                    return true;
                }
            }
        } 

        if (violations.size() == 1) {
            int err_ind = violations[0];
            if (order) {
                // remove err_ind+1
                if ((err_ind < l.size()-2)&&(l[err_ind+2] - l[err_ind] <= 3 && l[err_ind+2] - l[err_ind] >= 1)) {
                    return true;
                }
                // remove err_ind
                if (l[err_ind+1] - l[err_ind-1] <= 3 && l[err_ind+1] - l[err_ind-1] >= 1) {
                    return true;
                }
            }
            else {
                // remove err_ind+1
                if ((err_ind < l.size()-2)&&(l[err_ind+2] - l[err_ind] >= -3 && l[err_ind+2] - l[err_ind] <= -1)) {
                    return true;
                }
                // remove err_ind
                if (l[err_ind+1] - l[err_ind-1] >= -3 && l[err_ind+1] - l[err_ind-1] <= -1) {
                    return true;
                }
            }
        }
        return false;
    }
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
    int count = 1;
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
        
        if (isSafe2(l)) {
            res2++;
        }
        count++;
    }
    cout << res << endl;
    cout << res2 << endl;
    cout << endl;
}