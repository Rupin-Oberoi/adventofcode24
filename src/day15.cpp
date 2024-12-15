#include <bits/stdc++.h>
#include <chrono>

using namespace std;

char index(const vector<string>& grid, int pos) {
    int row = pos / grid[0].size();
    int col = pos % grid[0].size();
    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size()) {
        return '-';
    }
    return grid[row][col];
}

int move(vector<string>& grid, int pos, int dir) {
    // 1 for up, 2 for right, 3 for down, 4 for left
    int row = pos / grid[0].size();
    int col = pos % grid[0].size();
    int row_size = grid.size();
    int col_size = grid[0].size();

    int rob_pos = pos;

    int count = 0;
    if (dir == 1) {
        while (index(grid, pos) == 'O' || index(grid, pos) == '@') {
            pos -= col_size;
            count++;
        }

        if (index(grid, pos) == '#') {
            // hit a wall just after initial position / the boxes ended
            return rob_pos;
        }

        row = pos / grid[0].size();
        col = pos % grid[0].size();
        for (int i=0; i< count; i++) {
            grid[row][col] = index(grid, pos + col_size);
            pos += col_size;
            row++;
        }
        grid[row][col] = '.';
        return rob_pos - col_size;
    }

    if (dir == 2) {
        while (index(grid, pos) == 'O' || index(grid, pos) == '@') {
            pos += 1;
            count++;
        }

        if (index(grid, pos) == '#') {
            return rob_pos;
        }

        row = pos / grid[0].size();
        col = pos % grid[0].size();
        for (int i=0; i< count; i++) {
            grid[row][col] = index(grid, pos - 1);
            pos -= 1;
            col--;
        }
        grid[row][col] = '.';
        return rob_pos + 1;
    }

    if (dir == 3) {
        while (index(grid, pos) == 'O' || index(grid, pos) == '@') {
            pos += col_size;
            count++;
        }

        if (index(grid, pos) == '#') {
            return rob_pos;
        }

        row = pos / grid[0].size();
        col = pos % grid[0].size();
        for (int i=0; i< count; i++) {
            grid[row][col] = index(grid, pos - col_size);
            pos -= col_size;
            row--;
        }
        grid[row][col] = '.';
        return rob_pos + col_size;
    }

    if (dir == 4) {
        while (index(grid, pos) == 'O' || index(grid, pos) == '@') {
            pos -= 1;
            count++;
        }

        if (index(grid, pos) == '#') {
            return rob_pos;
        }

        row = pos / grid[0].size();
        col = pos % grid[0].size();
        for (int i=0; i< count; i++) {
            grid[row][col] = index(grid, pos + 1);
            pos += 1;
            col++;
        }
        grid[row][col] = '.';
        return rob_pos - 1;
    }
    return rob_pos;
}

vector<int> pushes_another(int pos, const vector<string>& grid, int dir) {
    // uses the index of the left edge
    vector<int> pushes;
    int row = pos / grid[0].size();
    int col = pos % grid[0].size();
    if (dir == 1) {
        char up1 = index(grid, pos - grid[0].size());
        char up2 = index(grid, pos - grid[0].size() + 1);
        if (up1 == '#' || up2 == '#') {
            // hit a wall
            pushes.push_back(-1);
            return pushes;
        }
        if (up1 == ']') {
            pushes.push_back(pos - grid[0].size() - 1);
        }
        if (up2 == '[') {
            pushes.push_back(pos - grid[0].size() + 1);
        }
        if (up1 == '[') {
            pushes.push_back(pos - grid[0].size());
        }
        return pushes;
    }
    else if (dir == 3) {
        char down1 = index(grid, pos + grid[0].size());
        char down2 = index(grid, pos + grid[0].size() + 1);
        if (down1 == '#' || down2 == '#') {
            pushes.push_back(-1);
            return pushes;
        }
        if (down1 == ']') {
            pushes.push_back(pos + grid[0].size() - 1);
        }
        if (down2 == '[') {
            pushes.push_back(pos + grid[0].size() + 1);
        }
        if (down1 == '[') {
            pushes.push_back(pos + grid[0].size());
        }
        return pushes;
    }
    return pushes;

}

int move2(vector<string>& grid, int pos, int dir) {
    int row = pos / grid[0].size();
    int col = pos % grid[0].size();
    int row_size = grid.size();
    int col_size = grid[0].size();

    int rob_pos = pos;

    int count = 0;
    if (dir == 1) {
        queue<int> box_queue;
        set<int> to_push;
        char up = index(grid, pos - col_size);
        if (up == '#') {
            return rob_pos;
        }
        if (up == '['){
            box_queue.push(pos - col_size);
            to_push.insert(pos - col_size);
        }
        if (up == ']') {
            box_queue.push(pos - col_size - 1);
            to_push.insert(pos - col_size - 1);
        }
        while (box_queue.size() > 0) {
            int box1 = box_queue.front();
            box_queue.pop();
            vector<int> pushes = pushes_another(box1, grid, 1);
            if (pushes.size() > 0 && pushes[0] == -1) {
                return rob_pos;
            }
            if (pushes.size() == 0) {
                // no box to push
                continue;
            }
            for (int i=0; i<pushes.size(); i++) {
                box_queue.push(pushes[i]);
                to_push.insert(pushes[i]);
            }
        }
        for (auto it = to_push.begin(); it != to_push.end(); it++) {
            int row = *it / grid[0].size();
            int col = *it % grid[0].size();
            grid[row][col] = '.';
            grid[row][col + 1] = '.';
            grid[row - 1][col] = '[';
            grid[row - 1][col + 1] = ']';
        }
        row = rob_pos / grid[0].size();
        col = rob_pos % grid[0].size();
        grid[row][col] = '.';
        grid[row - 1][col] = '@';
        return rob_pos - col_size;
    }
    if (dir == 2) {
        while (index(grid, pos) == '@' || index(grid, pos) == '[' || index(grid,pos) == ']') {
            pos += 1;
            count++;
        }

        if (index(grid, pos) == '#') {
            return rob_pos;
        }

        row = pos / grid[0].size();
        col = pos % grid[0].size();
        for (int i=0; i< count; i++) {
            grid[row][col] = index(grid, pos - 1);
            pos -= 1;
            col--;
        }
        grid[row][col] = '.';
        return rob_pos + 1;
    }

    if (dir==3) {
        queue<int> box_queue;
        set<int, greater<int>> to_push;

        char down = index(grid, pos + col_size);
        if (down == '#') {
            return rob_pos;
        }
        if (down == '['){
            box_queue.push(pos + col_size);
            to_push.insert(pos + col_size);
        }
        if (down == ']') {
            box_queue.push(pos + col_size - 1);
            to_push.insert(pos + col_size - 1);
        }
        while (box_queue.size() > 0) {
            int box1 = box_queue.front();
            box_queue.pop();
            vector<int> pushes = pushes_another(box1, grid, 3);
            if (pushes.size() > 0 && pushes[0] == -1) {
                return rob_pos;
            }
            if (pushes.size() == 0) {
                continue;
            }
            for (int i=0; i<pushes.size(); i++) {
                box_queue.push(pushes[i]);
                to_push.insert(pushes[i]);
            }
        }
        for (auto it = to_push.begin(); it != to_push.end(); it++) {
            int row = *it / grid[0].size();
            int col = *it % grid[0].size();
            grid[row][col] = '.';
            grid[row][col + 1] = '.';
            grid[row + 1][col] = '[';
            grid[row + 1][col + 1] = ']';
        }
        row = rob_pos / grid[0].size();
        col = rob_pos % grid[0].size();
        grid[row][col] = '.';
        grid[row + 1][col] = '@';
        return rob_pos + col_size;
    }

    if (dir==4) {
        while (index(grid, pos) == '@' || index(grid, pos) == '[' || index(grid,pos) == ']') {
            pos -= 1;
            count++;
        }
        if (index(grid, pos) == '#') {
            return rob_pos;
        }
        row = pos / grid[0].size();
        col = pos % grid[0].size();
        for (int i=0; i< count; i++) {
            grid[row][col] = index(grid, pos + 1);
            pos += 1;
            col++;
        }
        grid[row][col] = '.';
        return rob_pos - 1;
    }
    return rob_pos;
}

long long box_pos(const vector<string>& grid) {
    long long sum = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j] == 'O' || grid[i][j] == '[') {
                sum += 100*i + j;
            }
        }
    }
    return sum;
}

vector<string> expand_grid(const vector<string>& grid) {
    vector<string> new_grid;
    for (int i=0; i < grid.size(); i++) {
        string s = "";
        for (int j=0; j < grid[i].size(); j++) {
            if (grid[i][j] == '#') {
                s += "##";
            }
            else if (grid[i][j] == '@') {
                s += "@.";
            }
            else if (grid[i][j] == 'O') {
                s += "[]";
            }
            else {
                s += "..";
            }
        }
        new_grid.push_back(s);
    }
    return new_grid;
}

int main() {
    auto t_start = chrono::high_resolution_clock::now();
    ifstream in("../inputs/day15.txt");
    string s;
    vector<string> grid;
    string moves = "";
    int start_row = 0, start_col = 0;
    bool f1 = true;
    int count = 0;
    while (getline(in, s)) {
        if (s == "") {
            f1 = false;
            continue;
        }
        if (f1) {
            grid.push_back(s);
            if (s.find("@") != string::npos) {
                start_row = count;
                start_col = s.find("@");
            }
        }
        else {
            moves += s;
        }
        count++;
    }
    vector<string> grid2 = expand_grid(grid);

    unordered_map<char, int> dir_map;
    dir_map['^'] = 1;
    dir_map['>'] = 2;
    dir_map['v'] = 3;
    dir_map['<'] = 4;
    int pos = start_row * grid[0].size() + start_col;
    for (int i=0; i<moves.size(); i++) {
        pos = move(grid, pos, dir_map[moves[i]]);
    }
    long long ans1 = box_pos(grid);

    int pos2 = start_row * 2 * grid[0].size() + 2 * start_col;
    for (int i=0; i<moves.size(); i++) {
        pos2 = move2(grid2, pos2, dir_map[moves[i]]);
    }
    long long ans2 = box_pos(grid2);

    auto t_end = chrono::high_resolution_clock::now();
    cout << "Part 1: " << ans1 << endl;
    cout << "Part 2: " << ans2 << endl;
    cout << "Time: " << chrono::duration<double, milli>(t_end-t_start).count() << " ms" << endl;
}