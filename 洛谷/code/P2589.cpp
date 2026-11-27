// https://www.luogu.com.cn/problem/P2589
// 题意：n 个圆台形碗，已知高 h、下底半径 r_1、上底半径 r_2 (r_1 < r_2)。
// 求一种叠放顺序使总高度尽量小。
// 输出最小高度（四舍五入取整）。
// 数据范围：n <= 9，所有输入数绝对值 <= 1000。
#include<bits/stdc++.h>
// 算法标签：二分查找、枚举
using namespace std;
const int MAXN = 15;
const double eps = 1e-9;

int n;
double h[MAXN];
double r1[MAXN];
double r2[MAXN];
double k[MAXN];
double dis[MAXN][MAXN];
double pos[MAXN];
int p[MAXN];

double calc(int i,double x){
    return x*k[i]+r1[i];
}

bool check(int a,int b,double d){
    double l=min(h[b],h[a]-d);
    if(calc(b,0)>calc(a,d)){
        return false;
    }
    if(calc(b,l)>calc(a,d+l)){
        return false;
    }
    return true;
}

double solve(int a,int b){
    double l=0,r=h[a];
    for(int i=1;i<=60;i++){
        double mid=(l+r)/2;
        if(check(a,b,mid)){
            r=mid;
        }
        else{
            l=mid;
        }
    }
    return r;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i]>>r1[i]>>r2[i];
        k[i]=(r2[i]-r1[i])/h[i];
        p[i]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j){
                dis[i][j]=solve(i,j);
            }
        }
    }
    double ans=1e18;
    do{
        for(int i=1;i<=n;i++){
            int u=p[i];
            pos[u]=0;
            for(int j=1;j<i;j++){
                int v=p[j];
                pos[u]=max(pos[u],pos[v]+dis[v][u]);
            }
        }
        double res=0;
        for(int i=1;i<=n;i++){
            res=max(res,pos[i]+h[i]);
        }
        ans=min(ans,res);
    }while(next_permutation(p+1,p+n+1));
    cout<<(int)(ans+0.5)<<endl;
    return 0;
}