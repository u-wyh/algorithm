// https://www.luogu.com.cn/problem/P8766
// 题意：输入 T 和 T 个整数 n_1..n_T
// 对每个 n_i 输出满足 1 <= a, b, c <= n_i、a xor b xor c = 0 且边长 a, b, c 能构成非退化三角形的三元组 (a, b, c) 个数。
// 数据范围：1 <= T <= 100000，1 <= n_i <= 2^30。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 32;

int f[MAXN][8][2];
int n;

int dfs(int x,int now,int free){
    if(x<0){
        return now==7;
    }
    if(f[x][now][free]!=-1){
        return f[x][now][free];
    }
    int v=(n>>x)&1;
    int ans=0;
    if(free){
        ans+=dfs(x-1,now,1);
        if((now&1)&&(now&2)){
            ans+=dfs(x-1,now|4,1);
        }

        ans+=dfs(x-1,now|1,1);
        ans+=dfs(x-1,now|2,1);
    }
    else{
        if(v==0){
            ans+=dfs(x-1,now,0);
            if((now&1)&&(now&2)){
                ans+=dfs(x-1,now|4,0);
            }
        }
        else{
            ans+=dfs(x-1,now,1);
            if((now&1)&&(now&2)){
                ans+=dfs(x-1,now|4,1);
            }
            ans+=dfs(x-1,now|1,0);
            ans+=dfs(x-1,now|2,0);
        }
    }
    f[x][now][free]=ans;
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=0;i<=31;i++){
            for(int j=0;j<8;j++){
                f[i][j][0]=-1;
                f[i][j][1]=-1;
            }
        }
        cout<<dfs(31,0,0)*3<<endl;
    }
    return 0;
}