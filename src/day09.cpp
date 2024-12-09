#include <bits/stdc++.h>
#include <chrono>

using namespace std;

void print_vec(vector<int> v) {
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << "";
    }
    cout << endl;
}


vector<int> expand(string s) {
    vector<int> expanded;
    int curr_id = 0;
    for (int i=0; i<s.size(); i++) {
        if (i%2==0) {
            for (int j=0; j<s[i] - '0'; j++){
                expanded.push_back(curr_id);
            } 
            curr_id++;
        }
        else {
            for (int j=0; j<s[i] - '0'; j++){
                expanded.push_back(-1);
            }
        }
    }
    return expanded;
}

vector<vector<int>> expand2(string s) {
    // will store the int and number of blocks taken by the file
    vector<vector<int>> expanded;
    int curr_id = 0;
    for (int i=0; i<s.size(); i++) {
        if (i%2==0) {
            expanded.push_back({curr_id, s[i] - '0'});
            curr_id++;
        }
        else {
            expanded.push_back({-1, s[i] - '0'});
        }
    }
    return expanded;
}

vector<int> rearrange (vector<int> expanded) {
    int ptr1 = 0, ptr2 = expanded.size()-1;
    while (ptr1 < ptr2) {
        while (expanded[ptr1] != -1) {
            ptr1++;
        }
        while (expanded[ptr2] == -1) {
            ptr2--;
        }
        if (ptr1 < ptr2) {
            int temp = expanded[ptr1];
            expanded[ptr1] = expanded[ptr2];
            expanded[ptr2] = temp;
        }
    }
    return expanded;
}


vector<vector<int>> rearrange2(vector<vector<int>> expanded) {
    int ptr2 = expanded.size()-1;
    //int ptr1 = 0;
    while (ptr2 >= 0) {
        while (expanded[ptr2][0] == -1){
            ptr2 --;
        }
        for (int i=0; i<ptr2; i++) {
            if (expanded[i][0] == -1 && expanded[i][1] >= expanded[ptr2][1]) {
                expanded.insert(expanded.begin() + i, expanded[ptr2]);
                //expanded.erase(expanded.begin() + ptr2 + 1);
                if (ptr2 < expanded.size()-2) {
                    if (expanded[ptr2][0] == -1 && expanded[ptr2+2][0] == -1) {
                        expanded[ptr2][1] += expanded[ptr2+1][1];
                        expanded[ptr2][1] += expanded[ptr2+2][1];
                        expanded.erase(expanded.begin() + ptr2 + 2);
                        expanded.erase(expanded.begin() + ptr2 + 1);                    
                    }
                    else if (expanded[ptr2+2][0] == -1) {
                        expanded[ptr2+2][1] += expanded[ptr2+1][1];
                        expanded.erase(expanded.begin() + ptr2 + 1);
                    }
                    else if (expanded[ptr2][0] == -1) {
                        expanded[ptr2][1] += expanded[ptr2+1][1];
                        expanded.erase(expanded.begin() + ptr2 + 1);
                    }
                    else {
                        //cout << "hi5" << endl;
                        expanded[ptr2][0] = -1;
                    }
                }
                else {
                    //cout << "out of range" << endl;
                    if (expanded[ptr2][0] == -1) {
                        expanded[ptr2][1] += expanded[ptr2+1][1];
                        expanded.erase(expanded.begin() + ptr2 + 1);
                    }
                    else {
                        expanded[ptr2][0] = -1;
                    }
                }
                expanded[i+1][1] -= expanded[i][1];
                break;
            }
        }
        ptr2--;
    }
    return expanded;
}

long long calc_checksum(vector<int> defrag) {
    long long checksum = 0;
    for (int i=0; i<defrag.size(); i++) {
        if (defrag[i] == -1){
            break;
        }
        checksum += defrag[i] * i;
    }
    return checksum;
}

long long calc_checksum(vector<vector<int>> defrag) {
    long long checksum = 0;
    int pos = 0;
    for (int i=0; i<defrag.size(); i++) {
        if (defrag[i][0] != -1) {
            for (int j=0; j<defrag[i][1]; j++) {
                checksum += defrag[i][0] * pos;
                pos++;
            }
        }
        else{
            pos += defrag[i][1];
        }
    }
    return checksum;
}

int main(){
    auto t_start = chrono::high_resolution_clock::now();
    ifstream input ("../inputs/day9.txt");
    string s;
    getline(input, s);
    input.close();
    vector<int> expanded = expand(s);
    vector<int> rearranged = rearrange(expanded);
    long long checksum = calc_checksum(rearranged);

    vector<vector<int>> expanded2 = expand2(s);
    vector<vector<int>> rearranged2 = rearrange2(expanded2);
    long long checksum2 = calc_checksum(rearranged2);

    auto t_end = chrono::high_resolution_clock::now();
    cout << "Checksum: " << checksum << endl;
    cout << "Checksum: " << checksum2 << endl;
    cout << "Time: " << chrono::duration<double, milli>(t_end-t_start).count() << " ms" << endl;
}