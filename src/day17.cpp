#include <bits/stdc++.h>
#include <chrono>
#define ll long long
using namespace std;

ll combo_operand(ll op, ll a, ll b, ll c) {
    if (op >= 0 && op <= 3)
        return op;
    if (op == 4)
        return a;
    if (op == 5)
        return b;
    if (op == 6)
        return c;
    return -1;
}

pair<ll, ll> process_instruction(int opcode, ll operand, ll& a, ll& b, ll& c) {
    // return pair of (updated instruction pointer, output)
    ll co = combo_operand(operand, a, b, c);
    if (opcode == 0) {
        a = a >> co;
        return pair<ll, ll>(-1, -1);
    }
    if (opcode == 1) {
        b = b ^ operand;
        return pair<ll, ll>(-1, -1);
    }
    if (opcode == 2){
        b = co & 7;
        return pair<ll, ll>(-1, -1);
    }
    if (opcode == 3) {
        if (a == 0)
            return pair<ll, ll>(-1, -1);
        else
            return pair<ll, ll>(operand, -1);
    }
    if (opcode == 4) {
        b = b ^ c;
        return pair<ll, ll>(-1, -1);
    }
    if (opcode == 5)
        return pair<ll, ll>(-1, co & 7);
    if (opcode == 6) {
        b = a >> co;
        return pair<ll, ll>(-1, -1);
    }
    if (opcode == 7) {
        c = a >> co;
        return pair<ll, ll>(-1, -1);
    }
    return pair<ll, ll>(-1, -1);
}

void run_program(vector<int>& output, ll& regA, ll& regB, ll& regC, vector<int>& prog) {
    ll ip = 0;
    while (ip < prog.size()) {
        int opcode = prog[ip];
        ll operand = prog[ip + 1];
        pair<ll, ll> result = process_instruction(opcode, operand, regA, regB, regC);
        if (result.first != -1)
            ip = result.first;
        else
            ip += 2;
        if (result.second != -1)
            output.push_back(result.second);
    }
}

// task 2
bool check(ll a, int out) {
    ll b = a % 8;
    b = b ^ 5;
    ll c = a >> b;
    b = b ^ 6;
    b = b ^ c;
    return b % 8 == out;
}
void dfs(int depth, ll a, const vector<int>& outs, ll& min_ans) {
    if (depth == outs.size()) {
        min_ans = min(min_ans, a);
        return;
    }
    for (int rem = 0; rem < 8; rem++) {
        if (check(a * 8 + rem, outs[outs.size() - 1 - depth])) {
            dfs(depth + 1, a * 8 + rem, outs, min_ans);
        }
    }
}


int main() {
    auto t_start = chrono::high_resolution_clock::now();
    ifstream in("../inputs/day17.txt");
    string s;
    int count = 0;
    ll regA = 0, regB = 0, regC = 0;
    vector<int> prog;
    while (getline(in, s)) {
        if (count == 0) {
            int pos = s.find(":");
            regA = stoll(s.substr(pos + 2));
        }

        else if (count == 1) {
            int pos = s.find(":");
            regB = stoll(s.substr(pos + 2));
        }

        else if (count == 2) {
            int pos = s.find(":");
            regC = stoll(s.substr(pos + 2));
        }

        else if (count == 4) {
            int pos = s.find(":");
            string prog1 = s.substr(pos + 2);
            stringstream ss(prog1);
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                prog.push_back(stoll(substr));
            }
        }
        count++;
    }
    
    vector<int> output;
    ll ans2 = LONG_LONG_MAX;
    run_program(output, regA, regB, regC, prog);
    dfs(0, 0, prog, ans2);

    auto t_end = chrono::high_resolution_clock::now();
    for (int i = 0; i < output.size()-1; i++) {
        cout << output[i] << ",";
    }
    cout << output[output.size()-1] << endl;
    cout << ans2 << endl;
        cout << "Time: " << chrono::duration<double, milli>(t_end-t_start).count() << " ms" << endl;
}