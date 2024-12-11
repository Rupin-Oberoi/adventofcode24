#include <bits/stdc++.h>
#include <chrono>
#define ll long long
using namespace std;

unordered_map<ll, vector<vector<ll>>> cache_map;
unordered_map<ll, ll> freq;

vector<ll> blink(ll stone) {
    if (stone == 0) {
        return {1};
    }
    else {
        double a = floor(log10(stone));
        if (fmod(a, 2) == 1) {
            return {stone / (ll)(pow(10, (a+1)/2)), stone % (ll)(pow(10, (a+1)/2))};
        }
        else {
            return {stone * 2024};
        }
    }
}

// void cache(ll stone, int steps) {
//     if (cache_map.find(stone) != cache_map.end() && steps <= cache_map[stone].size()) {
//         return;
//     }
//     else if (cache_map.find(stone) != cache_map.end()) {
//         vector<ll> new_vec = blink()
//     }
// }

int main() {
    auto t_start = chrono::high_resolution_clock::now();
    ifstream input("../inputs/day11.txt");
    string s;
    getline(input, s);

    vector<ll> l;
    // split the string by space
    istringstream iss(s);
    string token;
    while (getline(iss, token, ' ')) {
        l.push_back(stoll(token));
    }
    for (ll i : l) {
        freq[i]++;
    }
    int NUM_BLINKS = 75;
    for (int i =0; i<NUM_BLINKS; i++) {
        vector<ll> keys;
        for (auto i : freq) {
            keys.push_back(i.first);
        }
        unordered_map<ll, ll> new_freq;
        for (auto i : keys) {
            vector<ll> new_stones = blink(i);
            for (ll j : new_stones) {
                new_freq[j] += freq[i];
            }
            freq.erase(i);
        }
        freq = new_freq;
    }
    ll ans = 0;
    for (auto i : freq) {
        ans += i.second;
    }
    auto t_end = chrono::high_resolution_clock::now();
    cout << ans << endl;
    cout << "Time taken: " << chrono::duration<double, milli>(t_end-t_start).count() << " ms" << endl;
}