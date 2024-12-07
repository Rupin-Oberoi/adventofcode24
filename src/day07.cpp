# include <bits/stdc++.h>
# include <chrono>

# define ll long long

using namespace std;

vector<int> next_seq(vector<int>& seq, int n) {
    bool carry_flag = true;
    for (int i=0; i<seq.size(); i++) {
        if (seq[i] != n-1) {
            carry_flag = false;
        }
        seq[i] = (seq[i]+1)%n;
        if (!carry_flag) {
            break;
        }
    }
    return seq;
}

bool possible(ll trg, vector<int> operands) {
    unsigned int ops = 0;
    // 0 for + , 1 for *
    ll res = operands[0];
    
    while (ops < pow(2, operands.size()-1)) {
        int temp = ops;
        for (int i=1; i<operands.size(); i++) {
            if (temp % 2 ==0) {
                res += operands[i];
            }
            else {
                res *= operands[i];
            }
            temp >>= 1;
        }
        if (res == trg) {
            return true;
        }
        res = operands[0];
        ops++;
    }
    return false;
}

bool possible2(ll trg, vector<int> operands) {
    vector<int> seq(operands.size()-1, 0);
    for (int i=0; i<pow(3, operands.size()-1); i++) {
        // 0 for +, 1 for *, 2 for ||
        ll res = operands[0];
        for (int j=1; j<operands.size(); j++) {
            if (seq[j-1] == 0) {
                res += operands[j];
            }
            else if (seq[j-1] == 1) {
                res *= operands[j];
            }
            else if (seq[j-1] == 2) {
                res = stoll(to_string(res) + to_string(operands[j]));
            }
            if (res > trg) {
                break;
            }
        }
        if (res == trg) {
            return true;
        }
        seq = next_seq(seq, 3);
    }
    return false;
}

int main() {
    ifstream input ("../inputs/day7.txt");
    string s;
    auto t_start = chrono::high_resolution_clock::now();
    vector<ll> res;
    ll ans = 0;
    ll ans2 = 0;
    vector<vector<int>> operands;
    while (getline(input, s)) {
        int colon = s.find(":");
        res.push_back(stoll(s.substr(0, colon)));
        vector<int> temp;
        int start = colon+2;
        while (start < s.size()) {
            int space = s.find(" ", start);
            if (space == string::npos) {
                temp.push_back(stoi(s.substr(start)));
                break;
            }
            temp.push_back(stoi(s.substr(start, space-start)));
            start = space+1;
        }
        operands.push_back(temp);
    }
    vector<int> l;
    for (int i=0; i<res.size(); i++) {
        if (possible(res[i], operands[i])) {
            ans+= res[i];
        }
        if (possible2(res[i], operands[i])) {
            ans2+= res[i];
            l.push_back(i);
        }
    }

    auto t_end = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration<double, std::milli>(t_end-t_start).count() << "ms" << endl;
    cout << ans << endl;
    cout << ans2 << endl;
}