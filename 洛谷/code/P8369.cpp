// https://www.luogu.com.cn/problem/P8369
// 题意：给定三种颜色条纹长度 c, z, n（每种无限个）及 m 个长为 p 的 1*p 棋盘。
// 两人轮流选一种条纹对齐方格覆盖到棋盘上（不可越界或与已有条纹重叠），无法操作者负。
// 对每个棋盘判断先手必胜输出 1，否则输出 2。
// 数据范围：100% 数据满足 1 <= c, z, n, m, p <= 1000。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;

int n;
int length[3];
int sg[MAXN];
int val[MAXN];
bool vis[MAXN];
int maxv;

void prepare(){
    sg[0]=0;
    for(int i=1;i<=maxv;i++){
        for(int v=0;v<=maxv;v++){
            vis[v]=false;
        }
        for(int l=0;l<=2;l++){
            int len=length[l];
            for(int lt=0;lt<=i-len;lt++){
                int rt=i-len-lt;
                if(rt>=0){
                    vis[sg[lt]^sg[rt]]=true;
                }
            }
        }
        int mex=0;
        while(vis[mex]){
            mex++;
        }
        sg[i]=mex;
    }
}

int main()
{
    cin>>length[0]>>length[1]>>length[2];
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        maxv=max(maxv,val[i]);
    }
    prepare();
    for(int i=1;i<=n;i++){
        if(sg[val[i]]){
            cout<<1<<endl;
        }
        else{
            cout<<2<<endl;
        }
    }
    return 0;
}