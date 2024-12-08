#include <bits/stdc++.h>
#include <chrono>
using namespace std;


int solve(vector<string>& map, unordered_map<string, vector<int>>& ant_loc_map) {
    unordered_set<int> an_loc;
    for (auto i : ant_loc_map) {
        string ant_type = i.first;
        for (int j = 0; j < i.second.size(); j++) {
            for (int k=j+1; k<i.second.size(); k++) {
                int loc1 = i.second[j];
                int loc2 = i.second[k];
                int x1 = loc1 / map[0].size();
                int y1 = loc1 % map[0].size();
                int x2 = loc2 / map[0].size();
                int y2 = loc2 % map[0].size();
                //cout << loc1 << " " << loc2 << endl;
                // find an closer to loc1
                // int x = x1 - (x2 - x1);
                // int y = y1 - (y2 - y1);
                // if (x >= 0 && x < map.size() && y >= 0 && y < map[0].size()) {
                //     an_loc.insert(x * map[0].size() + y);
                // }
                // // find an closer to loc2
                // x = x2 - (x1 - x2);
                // y = y2 - (y1 - y2);
                // if (x >= 0 && x < map.size() && y >= 0 && y < map[0].size()) {
                //     an_loc.insert(x * map[0].size() + y);
                // }
                int hcd = __gcd(x2 - x1, y2 - y1);
                //cout <<"hcd" << hcd << endl;
                float step = 1.0 / hcd;
                for (float k = 0; k < INT_MAX; k += step) {
                    int x = x1 + k * (x2 - x1);
                    int y = y1 + k * (y2 - y1);
                    if (x >= 0 && x < map.size() && y >= 0 && y < map[0].size()) {
                        an_loc.insert(x * map[0].size() + y);
                    }
                    else {
                        break;
                    }
                }
                for (int k = -step; k > INT_MIN ; k-=step) {
                    int x = x1 + k * (x2 - x1);
                    int y = y1 + k * (y2 - y1);
                    if (x >= 0 && x < map.size() && y >= 0 && y < map[0].size()) {
                        an_loc.insert(x * map[0].size() + y);
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
    return an_loc.size();
}

int main(){
    auto t_start = chrono::high_resolution_clock::now();
    ifstream input ("../inputs/day8.txt");
    string line;
    vector<string> map;

    while (getline(input, line)) {
        map.push_back(line);
    }
    vector<int> grid_size = {(int)map.size(), (int)map[0].size()};
    unordered_map<string, vector<int>> ant_loc_map;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[0].size(); j++) {
            if (map[i][j] != '.') {
                ant_loc_map[to_string(map[i][j])].push_back(grid_size[1] * i + j);
            }
        }
    }
    int ans = solve(map, ant_loc_map);
    auto t_end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration<double, milli>(t_end-t_start).count() << " ms" << endl;
    cout << ans << endl;
}