#include <bits/stdc++.h>
using namespace std;
const int MAXM = 1<<21;
const int MAXN = 105;

string nums[MAXN];
int val[MAXN];
int cnt[MAXM];

bool vis[MAXM];

int p[10] = {63,6,91,79,102,108,125,7,127,111};

int main() {
    cnt[0]=0;
    for(int i = 1; i < MAXM; i++) {
        cnt[i] = cnt[i-(i&-i)] + 1;
    }
    int T;
    cin >> T;
    while(T--) {
        int n, m;
        cin >> n >> m;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
        }
        if(n == 1) {
            cout << 0 << endl;
            continue;
        }
        for(int i = 1; i <= n; i++) {
            val[i] = 0;
            for(int j = 0; j < m; j++) {
                val[i] |= (p[nums[i][j] - '0'] << (j * 7));
            }
        }
        int ans = m * 7;
        int all = (1 << (m * 7));
        for(int s = 1; s < all; s++) {
            if(cnt[s] >= ans) 
                continue;
            bool flag=true;
            for(int i = 1; i <= n; i++) {
                if(vis[val[i]&s]){
                    flag=false;
                    break;
                }
                vis[val[i]&s]=true;
            }
            if(flag) {
                ans = min(ans, cnt[s]);
            }
            for(int i = 1; i <= n; i++) {
                vis[val[i]&s]=false;
            }
        }
        cout << ans << endl;
    }
    return 0;
}