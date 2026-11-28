// https://www.luogu.com.cn/problem/P2953
// 题意：输入游戏场数 G，以及每场游戏的起始正整数 N_i。
// 双方轮流操作（贝茜先手），
// 每次将当前数减去其十进制表示中的最大数码或最小非零数码，
// 减至 0 后无法再操作的一方判负。
// 假设双方均采取最优策略，判断每场游戏先手贝茜是否能赢。
// 输出共 G 行，对每场游戏若贝茜能赢输出 YES，否则输出 NO。
// 数据范围：对于 100% 的数据，1 <= G <= 100，
// 1 <= N_i <= 1000000。
// 难度评分：1500（洛谷分级换算）
// 算法标签：博弈论、动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int sg[MAXN];
int maxx,minn;
bool appear[2];

void func(int x){
    minn=9,maxx=0;
    while(x){
        int k=x%10;
        maxx=max(k,maxx);
        if(k!=0)
            minn=min(k,minn);
        x/=10;
    }
}

void build(){
    for(int i=10;i<=1000000;i++){
        func(i);
        appear[0]=appear[1]=false;
        if(minn!=0)
            appear[sg[i-minn]]=true;
        appear[sg[i-maxx]]=true;
        if(appear[0]){
            sg[i]=1;
        }
        else{
            sg[i]=0;
        }
    }
}

int main()
{
    int T;
    cin>>T;
    for(int i=1;i<=9;i++){
        sg[i]=1;
    }
    build();
    for(int i=1;i<1000;i++){
        cout<<setw(4)<<i<<": "<<sg[i]<<"    ";
        if(i%20==0){
            cout<<endl;
        }
    }
    while(T--){
        int n;
        cin>>n;
        if(sg[n]){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
