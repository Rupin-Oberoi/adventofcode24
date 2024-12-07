#include <bits/stdc++.h>
#include <chrono>
using namespace std;

int countHorizontal(int x_loc, int y_loc, const vector<string>& mat) {
    int count = 0;
    if (x_loc >= 3) {
        // check inverted
        if (mat[y_loc].substr(x_loc-3, 4) == "SAMX") {
            count++;
        }
    }
    if (x_loc <= mat[0].size()-4) {
        // check normal
        if (mat[y_loc].substr(x_loc, 4) == "XMAS") {
            count++;
        }
    }
    return count;
}

int countVertical(int x_loc, int y_loc, const vector<string>& mat) {
    int count = 0;
    if (y_loc >= 3) {
        // check inverted
        if (mat[y_loc-3][x_loc] == 'S' && mat[y_loc-2][x_loc] == 'A' && mat[y_loc-1][x_loc] == 'M' && mat[y_loc][x_loc] == 'X') {
            count++;
        }
    }
    if (y_loc <= mat.size()-4) {
        // check normal
        if (mat[y_loc][x_loc] == 'X' && mat[y_loc+1][x_loc] == 'M' && mat[y_loc+2][x_loc] == 'A' && mat[y_loc+3][x_loc] == 'S') {
            count++;
        }
    }
    return count;
}

int countDiagonal(int x_loc, int y_loc, const vector<string>& mat) {
    int count = 0;
    if (x_loc <= mat[0].size()-4 && y_loc <= mat.size()-4) {
        // check SE
        if (mat[y_loc][x_loc] == 'X' && mat[y_loc+1][x_loc+1] == 'M' && mat[y_loc+2][x_loc+2] == 'A' && mat[y_loc+3][x_loc+3] == 'S') {
            count++;
        }
    }
    if (x_loc >= 3 && y_loc <= mat.size()-4) {
        // check SW
        if (mat[y_loc][x_loc] == 'X' && mat[y_loc+1][x_loc-1] == 'M' && mat[y_loc+2][x_loc-2] == 'A' && mat[y_loc+3][x_loc-3] == 'S') {
            count++;
        }
    }
    if (x_loc >= 3 && y_loc >= 3) {
        // check NW
        if (mat[y_loc][x_loc] == 'X' && mat[y_loc-1][x_loc-1] == 'M' && mat[y_loc-2][x_loc-2] == 'A' && mat[y_loc-3][x_loc-3] == 'S') {
            count++;
        }
    }
    if (x_loc <= mat[0].size()-4 && y_loc >= 3) {
        // check NE
        if (mat[y_loc][x_loc] == 'X' && mat[y_loc-1][x_loc+1] == 'M' && mat[y_loc-2][x_loc+2] == 'A' && mat[y_loc-3][x_loc+3] == 'S') {
            count++;
        }
    }
    return count;
}

int countPart2_1(int x_loc, int y_loc, const vector<string>& mat) {
    if (y_loc <= mat.size()-3) {
        if (mat[y_loc+1][x_loc+1] == 'A') {
            if (mat[y_loc+2][x_loc] == 'M' && mat[y_loc+2][x_loc+2] == 'S') {
                return 1;
            }
        }
    }
    return 0;
}

int countPart2_2(int x_loc, int y_loc, const vector<string>& mat) {
    if (y_loc <= mat.size()-3) {
        if (mat[y_loc+1][x_loc+1] == 'A') {
            if (mat[y_loc+2][x_loc] == 'M' && mat[y_loc+2][x_loc+2] == 'M') {
                return 1;
            }
        }
    }
    return 0;
}

int countPart2_3(int x_loc, int y_loc, const vector<string>& mat) {
    if (y_loc <= mat.size()-3) {
        if (mat[y_loc+1][x_loc+1] == 'A') {
            if (mat[y_loc+2][x_loc] == 'S' && mat[y_loc+2][x_loc+2] == 'S') {
                return 1;
            }
        }
    }
    return 0;
}

int countPart2_4(int x_loc, int y_loc, const vector<string>& mat) {
    if (y_loc <= mat.size()-3) {
        if (mat[y_loc+1][x_loc+1] == 'A') {
            if (mat[y_loc+2][x_loc] == 'S' && mat[y_loc+2][x_loc+2] == 'M') {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    ifstream input ("../inputs/day4.txt");
    
    auto t_start = chrono::high_resolution_clock::now();

    vector<string> mat;
    string s;
    while (getline(input, s)) {
        mat.push_back(s);
    }
    int count = 0;
    int count2 = 0;
    for (int i=0; i<mat.size(); i++) {
        for (int j=0; j<mat[0].size(); j++) {
            if (mat[i][j] == 'X') {
                count += countHorizontal(j, i, mat);
                count += countVertical(j, i, mat);
                count += countDiagonal(j, i, mat);
            }
            if (mat[i][j] == 'M' && j < mat.size()-2 && mat[i][j+2] == 'S') {
                count2 += countPart2_1(j, i, mat);
            }
            if (mat[i][j] == 'M' && j < mat.size()-2 && mat[i][j+2] == 'M') {
                count2 += countPart2_3(j, i, mat);
            }
            if (mat[i][j] == 'S' && j < mat.size()-2 && mat[i][j+2] == 'S') {
                count2 += countPart2_2(j, i, mat);
            }
            if (mat[i][j] == 'S' && j < mat.size()-2 && mat[i][j+2] == 'M') {
                count2 += countPart2_4(j, i, mat);
            }
        }
    }
    auto t_end = chrono::high_resolution_clock::now();
    cout << count << endl;
    cout << count2 << endl;
    chrono::duration<double, std::milli> ms_double = t_end - t_start;
    cout << ms_double.count() << "ms" << endl;
    return 0;

}