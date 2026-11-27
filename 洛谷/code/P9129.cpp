// https://www.luogu.com.cn/problem/P9129
// 题意：给定长为 N 的数字序列 a_i (1..9) 和区间 [A, B]。
// Q 次询问区间 [l_i, r_i]，按从左到右顺序对每张纸片选择放到栈顶、栈底或不放，最后从顶到底读出一个整数。
// 求 3^{r_i-l_i+1} 种方案中结果在 [A, B] 内的方案数，对 10^9+7 取模。
// 数据范围：1 <= N <= 300，1 <= a_i <= 9，1 <= A <= B < 10^18，1 <= Q <= 5*10^4
// 1 <= l_i <= r_i <= N。
// 算法标签：数位动态规划、区间动态规划
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 305;
const int MAXM = 20;
const int MOD = 1e9+7;

int n,q;
int val[MAXN];
int l,r;
int lt[MAXN][MAXN];
int rt[MAXN][MAXN];
int f[MAXM][MAXM][3];
int len;
int nums[MAXM];

int compare(int a,int b){
    if (a < b) return 0;  // 小于
    if (a == b) return 1; // 等于
    return 2;             // 大于
}

void solve(int limit,int ans[][MAXN]){
    int len=0;
    while(limit){
        nums[++len]=limit%10;
        limit/=10;
    }

    for(int i=1;i<=n;i++){
        memset(f,0,sizeof(f));
        for(int j=i;j<=n;j++){

            for(int x=len;x>=1;x--){
                for(int y=1;y<x;y++){
                    
                    if(x>1){
                        if(val[j]>nums[x]){
                            for(int k=0;k<2;k++){
                                f[x][y][2]=(f[x][y][2]+f[x-1][y][k])%MOD;
                            }
                        }
                        else if(val[j]==nums[x]){
                            for(int k=0;k<2;k++){
                                f[x][y][k]=(f[x][y][k]+f[x-1][y][k])%MOD;
                            }
                        }
                        else{
                            for(int k=0;k<2;k++){
                                f[x][y][0]=(f[x][y][0]+f[x-1][y][k])%MOD;
                            }
                        }
                    }

                    f[x][y][2]=(f[x][y][2]+f[x][y+1][2])%MOD;
                    f[x][y][0]=(f[x][y][0]+f[x][y+1][0])%MOD;
                    int cmp=compare(val[j],nums[y]);
                    f[x][y][cmp]=(f[x][y][cmp]+f[x][y+1][1])%MOD;

                }
            }

            for(int x=1;x<=len;x++){
                int cmp=compare(val[j],nums[x]);
                f[x][x][cmp]=(f[x][x][cmp]+2)%MOD;
            }

            int res=0;
            for(int x=1;x<=len;x++){
                res=(res+f[x][1][0])%MOD;
                res=(res+f[x][1][1])%MOD;
                if(x<len)
                    res=(res+f[x][1][2])%MOD;
            }
            ans[i][j]=res;
        }
    }
}

signed main()
{
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    solve(l-1,lt);
    solve(r,rt);
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        int ans=rt[x][y]-lt[x][y];
        ans=(ans%MOD+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}