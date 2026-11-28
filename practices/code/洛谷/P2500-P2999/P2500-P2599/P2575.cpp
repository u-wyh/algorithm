// https://www.luogu.com.cn/problem/P2575
// 题意：T 组数据，每组有 n 行 20 列的棋盘，每行有 m 个棋子。
// 双方轮流将某棋子向右移到最近的空位（不能移则输），判断先手是否必胜。
// 每组输出 YES 或 NO。
// 数据范围：T <= 100，n <= 1000，m <= 20，
// 1 <= p_j <= 20。
// 难度评分：2200（洛谷分级换算）
// 算法标签：SG函数、博弈论、状态压缩
#include<bits/stdc++.h>
using namespace std;
const int MAXN = (1<<20)+5;

int sg[MAXN];
bool vis[25];

void prepare(){
    int N=(1<<20)-1;
    for(int i=N;i>=0;i--){
        for(int v=0;v<=24;v++){
            vis[v]=false;
        }
        for(int j=0;j<=19;j++){
            if(((i>>j)&1)){
                int k=j+1;
                for(;k<=19;k++){
                    if(!((i>>k)&1)){
                        int nxt=i-(1<<j)+(1<<k);
                        vis[sg[nxt]]=true;
                        break;
                    }
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
    prepare();
    int T;
    cin>>T;
    while(T--){
        int eor=0;
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            int m;
            cin>>m;
            int sta=0;
            for(int j=1;j<=m;j++){
                int v;
                cin>>v;
                v--;
                sta|=(1<<v);
            }
            eor^=sg[sta];
        }
        if(eor){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}