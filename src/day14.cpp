#include <bits/stdc++.h>
#include <chrono>
#include <regex>
#include <iostream>
#define ll long long

using namespace std;

int GRID_WIDTH = 101;
int GRID_HEIGHT = 103;

//vector<int> getgridval(int x, int y, const vector<vector<int>>& grid) {}
void move(vector<int>& pos, vector<int> vel) {
    pos[0] += vel[0];
    pos[0] = (GRID_WIDTH + pos[0]) % GRID_WIDTH;
    pos[1] += vel[1];
    pos[1] = (GRID_HEIGHT + pos[1]) % GRID_HEIGHT;
}

// bool is_xmas_tree(vector<vector<int>>& pos) {

// }

void write_grid(vector<vector<int>>& pos, int moves) {
    ofstream out("../grid.txt", ios::app);
    out << "Move: " << moves << endl;
    vector<string> grid(GRID_HEIGHT, string(GRID_WIDTH, '.'));
    for (int i = 0; i < pos.size(); i++) {
        grid[pos[i][1]][pos[i][0]] = '#';
    }
    for (int i = 0; i < GRID_HEIGHT; i++) {
        out << grid[i] << endl;
    }
    out << endl;
    out.close();
}

int quarter(vector<int> pos) {
    if (pos[0] > GRID_WIDTH/2 && pos[1] < GRID_HEIGHT/2) {
        return 1;
    } else if (pos[0] > GRID_WIDTH/2 && pos[1] > GRID_HEIGHT/2) {
        return 2;
    } else if (pos[0] < GRID_WIDTH/2 && pos[1] > GRID_HEIGHT/2) {
        return 3;
    } else if (pos[0] < GRID_WIDTH/2 && pos[1] < GRID_HEIGHT/2) {
        return 4;
    }
    else {
        return 5;
    }
}

int main() {
    auto t_start = chrono::high_resolution_clock::now();
    ifstream in("../inputs/day14.txt");
    string s;
    regex r1 = regex("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");
    vector<vector<int>> pos;
    vector<vector<int>> vel;
    while (getline(in, s)) {
        smatch match;
        if (regex_match(s, match, r1)) {
            vector<int> t1;
            t1.push_back(stoi(match[1]));
            t1.push_back(stoi(match[2]));
            pos.push_back(t1);
            t1.clear();
            t1.push_back(stoi(match[3]));
            t1.push_back(stoi(match[4]));
            vel.push_back(t1);
        }
    }


    for (int m = 0; m < 100; m++) {
        for (int i = 0; i < pos.size(); i++) {
            move(pos[i], vel[i]);
        }
        //write_grid(pos, m);
    }
    unordered_map<int, int> q_count;
    for (int i = 0; i < pos.size(); i++) {
        q_count[quarter(pos[i])]++;
    }
    long long ans = 1;
    for (auto it = q_count.begin(); it != q_count.end(); it++) {
        if (it->first == 5) {
            continue;
        }
        ans *= it->second;
    }
    auto t_end = chrono::high_resolution_clock::now();
    cout << "Answer: " << ans << endl;    
    cout << "Time: " << chrono::duration<double, milli>(t_end-t_start).count() << " ms" << endl;

}