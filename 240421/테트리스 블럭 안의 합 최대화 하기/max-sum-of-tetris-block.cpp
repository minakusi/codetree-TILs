#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int n, m;
int ans = 0;
vector<vector<int>> grid;
vector<vector<bool>> visited;

void search(int cnt, int cur_x, int cur_y, int total){
    if (cnt == 4) {
        if (ans < total) ans = total;
        return;
    }

    for (int i = 0; i < 4; ++i){
        int nxt_x = cur_x + dx[i];
        int nxt_y = cur_y + dy[i];

        if (nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= m) continue;
        if (visited[nxt_x][nxt_y]) continue;

        visited[nxt_x][nxt_y] = true;
        search(cnt+1, nxt_x, nxt_y, total + grid[nxt_x][nxt_y]);
        visited[nxt_x][nxt_y] = false;
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        vector<int> tmp(m);
        vector<bool> v(m, false);
        for(int j = 0; j < m; ++j) cin >> tmp[j];
        grid.push_back(tmp);
        visited.push_back(v);
    }    

    ans = 0;
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j) {
            visited[i][j] = true;
            search(1, i, j, grid[i][j]);
            visited[i][j] = false;

            int min = 1000;
            int total = grid[i][j];
            int cnt = 0;
            for (int k = 0; k < 4; ++k){
                int nxt_x = i + dx[k];
                int nxt_y = j + dy[k];
                if (nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= m) continue;
                ++cnt;
                if (grid[nxt_x][nxt_y] < min) min = grid[nxt_x][nxt_y];
                total += grid[nxt_x][nxt_y];
            }

            if (cnt == 3) {
                if (ans < total) ans = total;
            }
            else if (cnt == 4){
                total -= min;
                if (ans < total) ans = total;
            }
        }
    }    

    cout << ans;
    return 0;
}