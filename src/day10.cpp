#include <bits/stdc++.h>
#include <chrono>

using namespace std;

set<vector<int>> dests;
int ans2 = 0;

void dfs(int curr_ind, int start_ind, const vector<string>& map) {
    int row = curr_ind / map[0].size();
    int col = curr_ind % map[0].size();
    int curr_val = map[row][col] - '0';
    if (curr_val == 9) {
        dests.insert({start_ind, curr_ind});
        ans2++;
        return;
    }
    if (row > 0 && map[row-1][col] - '0' == curr_val + 1)
        dfs(curr_ind - map[0].size(), start_ind, map);
    if (row < map.size()-1 && map[row+1][col] - '0' == curr_val + 1) 
        dfs(curr_ind + map[0].size(), start_ind, map);
    if (col > 0 && map[row][col-1] - '0'== curr_val + 1) 
        dfs(curr_ind - 1, start_ind, map);
    if (col < map[0].size() && map[row][col+1] - '0' == curr_val + 1)
        dfs(curr_ind + 1, start_ind, map);
}

int main() {
    auto t_start = chrono::high_resolution_clock::now();
    ifstream input("../inputs/day10.txt");
    vector<string> map;
    string s;
    while (getline(input, s)) {
        map.push_back(s);
    }
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[0].size(); j++) {
            if (map[i][j] == '0') {
                dfs(i*map[0].size() + j, i*map[0].size() + j, map);
            }
        }
    }
    auto t_end = chrono::high_resolution_clock::now();
    cout << "Part 1: " << dests.size() << endl;
    cout << "Part 2: " << ans2 << endl;
    cout << "Time: " << chrono::duration<double, std::milli>(t_end-t_start).count() << "ms" << endl;
}
