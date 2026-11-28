// https://www.luogu.com.cn/problem/P15681
// 题意：支持单点修改序列 a，及询问 m 个篮子时恰好装 k 颗糖的篮子数最大值。
// 输入：首行 c, n, q，次行序列 a_1..a_n，
// 后 q 行操作 1 x y 或 2 m k。
// 规则：1 将 a_x 改为 y；
// 2 每人选不同的 a_i 个篮子各放 1 糖，最大化 k 糖篮数。
// 输出：对每个 2 类操作输出一行最大篮子数。
// 数据范围：1 <= n, q <= 5*10^5，
// 1 <= a_i, y <= 10^6，1 <= x <= n。
// 数据范围：max(a_i) <= m <= 10^12，0 <= k <= n。
// 难度评分：2400（洛谷分级换算）
// 算法标签：树状数组、二分答案
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;
const int MAXM = 1e6 + 5;
const int MAXA = 1000000;

int c, n, q;
long long total;

int a[MAXN];

int cnt[MAXM];          // 个数，用 int 足够
long long all[MAXM];    // 前缀和，必须 long long

int lowbit(int x){
    return x & -x;
}

int sumCnt(int x){
    if(x <= 0) return 0;
    x = min(x, MAXA);

    int ans = 0;
    while(x){
        ans += cnt[x];
        x -= lowbit(x);
    }
    return ans;
}

long long sumAll(int x){
    if(x <= 0) return 0;
    x = min(x, MAXA);

    long long ans = 0;
    while(x){
        ans += all[x];
        x -= lowbit(x);
    }
    return ans;
}

void addCnt(int x,int v){
    while(x <= MAXA){
        cnt[x] += v;
        x += lowbit(x);
    }
}

void addAll(int x,long long v){
    while(x <= MAXA){
        all[x] += v;
        x += lowbit(x);
    }
}

bool check(long long t,long long m,long long k){
    long long rest = m - t;

    long long lt;
    lt = (total - sumAll(rest)) - 1ll * (n - sumCnt(rest)) * rest;

    if(lt > t * k){
        return false;
    }

    long long rt;
    rt = sumAll(t) + 1ll * (n - sumCnt(t)) * t;

    return t * k <= rt;
}

long long compute(long long m,long long k){
    if(k == 0){
        int l = 1, r = MAXA, ans = 1;

        while(l <= r){
            int mid = (l + r) >> 1;

            if(sumCnt(mid) == n){
                ans = mid;
                r = mid - 1;
            }
            else{
                l = mid + 1;
            }
        }

        return max(0ll, m - ans);
    }

    long long l = 0;
    long long r = min(m, total / k);
    long long ans = 0;

    while(l <= r){
        long long mid = (l + r) >> 1;

        if(check(mid, m, k)){
            ans = mid;
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> c >> n >> q;

    for(int i = 1; i <= n; i++){
        cin >> a[i];

        addCnt(a[i], 1);
        addAll(a[i], a[i]);

        total += a[i];
    }

    for(int i = 1; i <= q; i++){
        int op;
        cin >> op;

        if(op == 1){
            int x, y;
            cin >> x >> y;

            addCnt(a[x], -1);
            addAll(a[x], -a[x]);
            total -= a[x];

            a[x] = y;

            total += a[x];
            addCnt(a[x], 1);
            addAll(a[x], a[x]);
        }
        else{
            long long m, k;
            cin >> m >> k;

            cout << compute(m, k) << '\n';
        }
    }

    return 0;
}