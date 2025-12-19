#include "bits/stdc++.h"
using namespace std;

int a[10][10], d, xx1, yy1, xx2, yy2;
int fx[4] = {0, 0, 1, -1}, fy[4] = {1, -1, 0, 0};

inline bool check() {
    for (register int i = 1; i <= 4; ++i)
        if (a[i][1] == a[i][2] && a[i][2] == a[i][3] && a[i][3] == a[i][4]) return true;

    for (register int j = 1; j <= 4; ++j)
        if (a[1][j] == a[2][j] && a[2][j] == a[3][j] && a[3][j] == a[4][j]) return true;

    if (a[1][1] == a[2][2] && a[2][2] == a[3][3] && a[3][3] == a[4][4]) return true;

    if (a[4][1] == a[3][2] && a[3][2] == a[2][3] && a[2][3] == a[1][4]) return true;

    return false;
}

bool dfs(int ax, int ay, int bx, int by, int col, int dep) {
    if (dep > d) {
        if (check()) return true;
        return false;
    }
    for (register int i = 0; i < 4; ++i) {
        int nx = ax + fx[i];
        int ny = ay + fy[i];
        if (nx > 0 && nx <= 4 && ny > 0 && ny <= 4 && a[nx][ny] == col) {
            swap(a[ax][ay], a[nx][ny]);
            if (dfs(nx, ny, bx, by, (col == 1) ? 2 : 1, dep + 1)) return true;
            swap(a[ax][ay], a[nx][ny]);
        }
    }
    for (register int i = 0; i < 4; ++i) {
        int nx = bx + fx[i];
        int ny = by + fy[i];
        if (nx > 0 && nx <= 4 && ny > 0 && ny <= 4 && a[nx][ny] == col) {
            swap(a[bx][by], a[nx][ny]);
            if (dfs(ax, ay, nx, ny, (col == 1) ? 2 : 1, dep + 1)) return true;
            swap(a[bx][by], a[nx][ny]);
        }
    }
    return false;
}

int main() {
    for (register int i = 1; i <= 4; ++i)
        for (register int j = 1; j <= 4; ++j) {
            char ch;
            cin >> ch;
            if (ch == 'B') a[i][j] = 1;
            else if (ch == 'W') a[i][j] = 2;
            else {
                if (xx1) xx2 = i, yy2 = j;
                else xx1 = i, yy1 = j;
                a[i][j] = 0;
            }
        }
    if(check()){
        cout<<0<<endl;
        return 0;
    }
    for (d = 1;; d++) {
        if (dfs(xx1, yy1, xx2, yy2, 1, 1)) break;
        if (dfs(xx1, yy1, xx2, yy2, 2, 1)) break;
    }
    cout << d;
    return 0;
}
