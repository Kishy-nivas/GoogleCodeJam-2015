// Copyright (c) 2015 kamyu. All rights reserved.

/*
 * Google Code Jam 2015 Round 1B - Problem B. Noisy Neighbors
 * https://code.google.com/codejam/contest/8224486/dashboard#s=p1
 *
 * Time  : O(RClogRC)
 * Space : O(RC)
 *
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::greater;
using std::max;

int Unhappiness(const int R, const int C, const int N) {
    int answer = 0;
    if (N > (R * C + 1) / 2) {
        const int vacant_num = R * C - N;
        vector<pair<int, int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<int> edges[2];
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                int count = 0;
                for (const auto& d : directions) {
                    if (i + d.first < 0 || i + d.first >= R ||
                        j + d.second < 0 || j + d.second >= C) {
                        continue;
                    }
                    ++count;
                }
                edges[(i + j) % 2].emplace_back(count);
            }
        }
        // Sort by the edge number of the room.
        sort(edges[0].begin(), edges[0].end(), greater<int>());
        sort(edges[1].begin(), edges[1].end(), greater<int>());

        // Max edge number of vacant even rooms.
        int even_edges = accumulate(edges[0].cbegin(),
                                    edges[0].cbegin() + vacant_num, 0);
        // Max edge number of vacant odd rooms.
        int odd_edges = accumulate(edges[1].cbegin(),
                                   edges[1].cbegin() + vacant_num, 0);
        // (total edge number) - (max edge numbers of vacant rooms).
        answer = (R * (C - 1) + (R - 1) * C) - max(even_edges, odd_edges);
    }
    return answer;
}

int main() {
    int T;
    cin >> T;

    for (int test = 1; test <= T; ++test) {
        int R, C, N; cin >> R >> C >> N;
        cout << "Case #" << test << ": " << Unhappiness(R, C, N) << endl;
    }
    return 0;
}
