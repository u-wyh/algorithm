#include<bits/stdc++.h>
using namespace std;

#define N 25

int n;
int a[N][N];
int r[N][2], c[N][2]; //r记录每行0、1个数，c记录每列0、1个数
int vr[N * 100], vc[N * 100]; //vr记录填完的每一行的值，vc记录填完的每一列的值

bool check(int x, int y) {
    if(r[x][0] <= n / 2 && r[x][1] <= n / 2 && c[y][0] <= n / 2 && c[y][1] <= n / 2) {
        if(x == n) {
            if(c[y][0] != n / 2 || c[y][1] != n / 2)return false;
        }
        if(y == n) {
            if(r[x][0] != n / 2 || r[x][1] != n / 2)return false;
        }
        if(x > 2) {
            if(a[x - 1][y] == a[x][y] && a[x - 2][y] == a[x][y])return false;
        }
        if(y > 2) {
            if(a[x][y - 1] == a[x][y] && a[x][y - 2] == a[x][y])return false;
        }
        return true;
    } else
        return false;
}

int get(int x, int opt) {
    int res = 0;
    for(int i = 1; i <= n; i++) {
        if(a[x][i] && opt == 1)res += (1 << i);
        if(a[i][x] && opt == 2)res += (1 << i);
    }
    return res;
}

void dfs(int x, int y) {
    if(x == n + 1) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++)
                cout << a[i][j];
            cout << endl;
        }
        exit(0);
    }
    int flag = (a[x][y] == -1);
    for(int i = 0; i <= 1; i++) {
        if(i == a[x][y])continue;
        if(flag) {
            a[x][y] = i;
            r[x][i]++;
            c[y][i]++;
        }
        if(check(x, y)) {
            if(y == n) {
                int sum = get(x, 1);
                if(!vr[sum]) {
                    vr[sum] = 1;
                    dfs(x + 1, 1);
                    vr[sum] = 0;
                }
            } else {
                if(x == n) {
                    int sum = get(y, 2);
                    if(!vc[sum]) {
                        vc[sum] = 1;
                        dfs(x, y + 1);
                        vc[sum] = 0;
                    }
                } else
                    dfs(x, y + 1);
            }
        }
        if(flag) {
            r[x][i]--;
            c[y][i]--;
            a[x][y] = -1;
        }
    }
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            char z;
            cin >> z;
            if(z == '_')a[i][j] = -1;
            else {
                a[i][j] = z - '0';
                r[i][a[i][j]]++;
                c[j][a[i][j]]++;
            }
        }
    dfs(1, 1);
    return 0;
}
