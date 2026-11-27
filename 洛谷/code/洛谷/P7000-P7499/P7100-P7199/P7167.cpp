// https://www.luogu.com.cn/problem/P7167
// 题意：N 个圆盘自上而下编号 1~N，直径 D_i、容量 C_i；
// 水溢出后会往下流到下方首个直径严格更大的圆盘（否则流入水池 0）。
// Q 次独立询问向第 R_i 个圆盘倒入 V_i 的水最终停在何处。
// 数据范围：2 <= N <= 10^5，1 <= Q <= 2*10^5，
// 1 <= C_i <= 1000，1 <= D_i, V_i <= 10^9
// 1 <= R_i <= N。
// 算法标签：倍增、ST表、二分查找
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100010;

int n,q,d[MAXN],c[MAXN],rmax[MAXN][20],f[MAXN][20],g[MAXN][20],log_2[MAXN];

int query_max(int A,int B){
    int x=log_2[B-A+1];
    return max(rmax[A][x],rmax[B-(1<<x)+1][x]);
}

int main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>d[i]>>c[i];
    }
    log_2[0]=-1;
    for(int i=1;i<=n;i++){
        log_2[i]=log_2[i>>1]+1;
        rmax[i][0]=d[i];
    }
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i<=n-(1<<j)+1;i++){
            rmax[i][j]=max(rmax[i][j-1],rmax[i+(1<<(j-1))][j-1]);
        }
    }
    c[n+1]=1e9;
    for(int i=1;i<n;i++){
        int l=i+1,r=n+1,mid;
        while(l<r){
            mid=(l+r)/2;
            if(query_max(i+1,mid)<=d[i])
                l=mid+1;
            else
                r=mid;
        }
        f[i][0]=l;
        g[i][0]=c[f[i][0]];
    }
    f[n][0]=n+1;
    g[n][0]=c[f[n][0]];
    for(int t=1;t<=16;t++){
        for(int i=1;i<=n;i++){
            f[i][t]=f[f[i][t-1]][t-1];
            g[i][t]=g[i][t-1]+g[f[i][t-1]][t-1];
        }
    }
    while(q--){
        int r,v;
        cin>>r>>v;
        if(v>c[r]){
            v-=c[r];
            for(int t=16;t>=0;t--){
                if(v>g[r][t]){
                    v-=g[r][t];
                    r=f[r][t];
                }
            }
            r=f[r][0];
        }
        if(r==n+1)
            r=0;
        cout<<r<<endl;
    }
    return 0;
}
