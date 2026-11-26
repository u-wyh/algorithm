// https://www.luogu.com.cn/problem/P1364
// 题意：给一棵二叉树，每点有 w 名居民，父子相距 1。选一个节点建医院，让所有居民到医院的距离总和尽量小。输出最小总距离。
// 数据范围：1 ≤ n ≤ 100，1 ≤ w ≤ 10^5，左右孩子编号在 [0,n]，0 表示不存在。

#include<bits/stdc++.h>
using namespace std;

int n,ans=1e9,vis[110];
struct Node{
    int left,right,father,value;
}t[110];

int cal(int x,int d){
    if(!x||vis[x])
        return 0;
    vis[x]=1;
    return cal(t[x].left,d+1)+cal(t[x].right,d+1)+cal(t[x].father,d+1)+t[x].value*d;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>t[i].value>>t[i].left>>t[i].right;
    }
    for(int i=1;i<=n;i++){
        t[t[i].left].father=i;
        t[t[i].right].father=i;
    }
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        ans=min(ans,cal(i,0));
    }
    cout<<ans;
    return 0;
}
