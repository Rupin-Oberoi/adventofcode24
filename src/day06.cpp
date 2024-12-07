# include <bits/stdc++.h>
# include <chrono>

using namespace std;

unordered_set<int> visited;

int num_steps(int* start_loc, const vector<string>& mat) {
    vector<int> grid_size = {(int)mat.size(), (int)mat[0].size()};
    int curr_loc[] = {start_loc[0], start_loc[1]};
    int direction = 0; // facing up
    // to turn right, add 1 to direction mod 4
    //unordered_set<int> visited; // stored as row*grid_size[1] + col
    visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
    set<vector<int>> obs_visited;

    while (true) {
        if (curr_loc[0] < 0 || curr_loc[0] >= mat.size() || curr_loc[1] < 0 || curr_loc[1] >= mat[0].size()) {
            // exiting the grid
            return -visited.size();
        }
        vector<int> next_obs = {0, 0};
        if (direction == 0) {
            while (curr_loc[0] > 0) {
                if (mat[curr_loc[0]-1][curr_loc[1]] == '#') {
                    next_obs[0] = curr_loc[0]-1;
                    next_obs[1] = curr_loc[1];
                    break;
                }
                visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
                curr_loc[0]--;
            }
            if (curr_loc[0] == 0) {
                visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
                curr_loc[0]--;
            }
        }
        else if (direction == 1) {
            while (curr_loc[1] < mat[0].size()-1) {
                if (mat[curr_loc[0]][curr_loc[1]+1] == '#') {
                    next_obs[0] = curr_loc[0];
                    next_obs[1] = curr_loc[1]+1;
                    break;
                }
                visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
                curr_loc[1]++;
            }
            if (curr_loc[1] == mat[0].size()-1) {
                visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
                curr_loc[1]++;
            }
        }
        else if (direction == 2) {
            while (curr_loc[0] < mat.size()-1) {
                if (mat[curr_loc[0]+1][curr_loc[1]] == '#') {
                    next_obs[0] = curr_loc[0]+1;
                    next_obs[1] = curr_loc[1];
                    break;
                }
                visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
                curr_loc[0]++;
            }
            if (curr_loc[0] == mat.size()-1){
                visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
                curr_loc[0] ++;
            }
        }
        else if (direction == 3) {
            while (curr_loc[1] > 0) {
                if (mat[curr_loc[0]][curr_loc[1]-1] == '#') {
                    next_obs[0] = curr_loc[0];
                    next_obs[1] = curr_loc[1]-1;
                    break;
                }
                visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
                curr_loc[1]--;
            }
            if (curr_loc[1] == 0) {
                visited.insert(curr_loc[0]*grid_size[1] + curr_loc[1]);
                curr_loc[1]--;
            }
        }
        direction = (direction+1)%4;
        if (obs_visited.find({next_obs[0]*grid_size[1] + next_obs[1], direction}) != obs_visited.end()) {
            // already visited this obstacle in this direction, so we are in a loop
            return visited.size();
        }
        
        obs_visited.insert({next_obs[0]*grid_size[1] + next_obs[1], direction});
    }
    return -visited.size();
}

int main() {
    auto t_start = chrono::high_resolution_clock::now();
    ifstream input ("../inputs/day6.txt");
    string s;
    vector<string> mat;
    int curr_loc[] = {0, 0};
    int row_num = 0;
    while (getline(input, s)) {
        mat.push_back(s);        
        for (int i=0; i<s.size(); i++) {
            if (s[i] == '^') {
                curr_loc[0] = row_num;
                curr_loc[1] = i;
            }
        }
        row_num++;
    }
    int count1 = 0;    
    int count2 = 0;
    count1 = abs(num_steps(curr_loc, mat));
    unordered_set<int> visited1 = visited;
    for (int i=0; i<mat.size(); i++) {
        for (int j=0; j<mat[0].size(); j++) {
            if (visited1.find(i * mat[0].size() + j) != visited1.end()) {
                mat[i][j] = '#';
                if (num_steps(curr_loc, mat) > 0) {
                    count2++;
                }
                mat[i][j] = '.';
            }
        }
    }
    auto t_end = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration<double, std::milli>(t_end-t_start).count() << "ms" << endl;
    cout << count1 << endl;
    cout << count2 << endl;
}