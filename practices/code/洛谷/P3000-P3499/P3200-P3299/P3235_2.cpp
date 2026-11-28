// https://www.luogu.com.cn/problem/P3235
// 题意：输入游戏局数 T 和终止阈值 F，每局给出石子堆数 N 和各堆石子数。
// 两人轮流选一堆不少于 F 的石子，再自选整数 M >= 2（不超过该堆石子数），
// 将这堆尽量均分成 M 份（极差至多为 1）继续游戏。
// 无法操作（所有堆都严格小于 F）者判负，判断先手还是后手必胜。
// 输出一行 T 个数（1 代表先手胜，0 代表后手胜），空格隔开。
// 数据范围：1 <= T, N < 100，1 <= F < 10^5，
// 每堆石子数为小于 10^5 的正整数。
// 难度评分：2600（洛谷分级换算）
// 算法标签：博弈论、SG函数、数论分块
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int F;
int sg[MAXN];
int vis[MAXN];

int getval(int x,int v){
    int q=x/v;
    int r=x%v;

    int ans=0;
    if(r&1){
        ans^=sg[q+1];
    }
    if((v-r)&1){
        ans^=sg[q];
    }
    return ans;
}

void prepare(){
    for(int x=max(F,2);x<=100000;x++){
        for(int lt=2,rt;lt<=x;lt=rt+1){
            int v=x/lt;
            rt=x/v;
            int val=getval(x,lt);
            vis[val]=x;
            if(lt+1<=rt){
                val=getval(x,lt+1);
                vis[val]=x;
            }
        }
        int mex=0;
        while(vis[mex]==x){
            mex++;
        }
        sg[x]=mex;
    }
}

int main()
{
    int T;
    cin>>T>>F;
    prepare();
    for(int i=1;i<=T;i++){
        int eor=0;
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            int v;
            cin>>v;
            eor^=sg[v];
        }
        if(eor){
            cout<<1<<' ';
        }
        else{
            cout<<0<<' ';
        }
    }
    return 0;
}