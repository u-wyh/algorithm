// https://www.luogu.com.cn/problem/P2436
// 题意：选手从 1 开始编号，循环分组。
// 每轮先有 A 位神犇，再有 B 位蒟蒻。
// 每组给 N 名神犇和 M 名蒟蒻的编号。
// 输出：求满足这些身份的正整数 A、B。
// 优先使 A 最小，再使 B 最小；无解输出 NO。
// 数据范围：多组至 EOF，T <= 10。
// 1 <= N, M <= 1000。
// 编号在 [1, 10*(N+M)] 内。
// 难度评分：1200（洛谷分级换算）
// 算法标签：枚举、取模

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
int a[MAXN], b[MAXN];

void solve(int n, int m){
    int limit = 0;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        limit = max(limit, a[i]);
    }
    for(int i = 0; i < m; ++i){
        cin >> b[i];
        limit = max(limit, b[i]);
    }

    int best_a = INT_MAX, best_b = INT_MAX;
    // 周期不小于最大编号时，各编号在周期内的位置不再变化。
    for(int period = 2; period <= limit; ++period){
        int required = 1;
        for(int i = 0; i < n; ++i){
            required = max(required, (a[i] - 1) % period + 1);
            if(required > best_a || required == period){
                break;
            }
        }
        if(required > best_a || required == period){
            continue;
        }
        bool possible = true;
        for(int i = 0; i < m; ++i){
            if((b[i] - 1) % period + 1 <= required){
                possible = false;
                break;
            }
        }
        if(possible && (required < best_a || period - required < best_b)){
            best_a = required;
            best_b = period - required;
        }
    }

    if(best_a == INT_MAX){
        cout << "NO\n";
    }else{
        cout << best_a << ' ' << best_b << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while(cin >> n >> m){
        solve(n, m);
    }
    return 0;
}
