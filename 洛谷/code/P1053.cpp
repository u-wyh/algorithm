// https://www.luogu.com.cn/problem/P1053
// 题意：n 人原本按编号 1 到 n 围坐，每人指定两个希望挨着的人。可任选若干人循环交换座位，代价等于参与人数。求满足所有相邻要求的最小总代价，无解输出 -1。
// 数据范围：3 ≤ n ≤ 50000，每人给出两个不同的同学编号。

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n;

int tot;
int target[MAXN];
int help[MAXN];
int cnt1[MAXN],cnt2[MAXN];

int son1[MAXN],son2[MAXN];

void dfs(int u,int f){
    if(u==1){
        return ;
    }
    target[++tot]=u;
    if(son1[u]==f){
        dfs(son2[u],u);
    }
    else{
        dfs(son1[u],u);
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>son1[i]>>son2[i];
        if(son1[i]<i){
            if(son1[son1[i]]!=i&&son2[son1[i]]!=i){
                cout<<-1<<endl;
                return 0;
            }
        }
        if(son2[i]<i){
            if(son1[son2[i]]!=i&&son2[son2[i]]!=i){
                cout<<-1<<endl;
                return 0;
            }
        }
    }
    target[++tot]=1;
    dfs(son1[1],1);
    for(int i=1;i<=n;i++){
        cnt1[(target[i]-i+n)%n]++;
    }
    tot=0;
    target[++tot]=1;
    dfs(son2[1],1);
    for(int i=1;i<=n;i++){
        cnt2[(target[i]-i+n)%n]++;
    }
    int ans=INT_MIN;
    for(int i=0;i<=n;i++){
        ans=max(ans,max(cnt1[i],cnt2[i]));
    }
    ans=n-ans;
    cout<<ans<<endl;
    return 0;
}