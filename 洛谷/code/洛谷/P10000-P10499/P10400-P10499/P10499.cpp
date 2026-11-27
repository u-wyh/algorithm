// https://www.luogu.com.cn/problem/P10499
// 题意：给 N 个开关的初始与目标状态，以及联动关系 I,J。
// 操作 I 时，I 和与它联动的 J 都翻转。
// 每个开关至多操作一次，统计能达到目标的操作集合数，
// 无解输出 Oh,it's impossible~!!。
// 数据范围：1 ≤ K ≤ 10 组，1 ≤ N < 29，状态均为 0 或 1。
// 算法标签：高斯消元、位运算

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 32;

int mat[MAXN][MAXN];
int cnt = 0;
int pow2[MAXN];
int n;

void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i && mat[j][j] == 1) {
                continue;
            }
            if (mat[j][i] == 1) {
                swap(mat[i],mat[j]);
                break;
            }
        }
        if (mat[i][i] == 1) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] == 1) {
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

signed main()
{
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = (pow2[i - 1] * 2);
    }
    int test;
    cin>>test;
    while(test--){
        cin>>n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n + 1; j++) {
                mat[i][j] = 0;
            }
            mat[i][i]=1;
        }
        for(int i=1;i<=n;i++){
            cin>>mat[i][n+1];
        }
        for(int i=1;i<=n;i++){
            int k;
            cin>>k;
            mat[i][n+1]^=k;
        }
        int u,v;
        cin>>u>>v;
        while((u+v)!=0){
            mat[v][u]=1;
            cin>>u>>v;
        }
        gauss(n);
        bool flag=false;
        int main_count = 0; // 主元的数量
        for (int i = 1; i <= n; i++) {
            if (mat[i][i] == 1) {
                main_count++;
            }
            if(mat[i][i]==0&&mat[i][n+1]!=0){
                flag=true;
                break;
            }
        }
        if(flag){
            cout<<"Oh,it's impossible~!!"<<endl;
            continue;
        }
        cout<<pow2[n - main_count]  <<endl;
    }
    return 0;
}
