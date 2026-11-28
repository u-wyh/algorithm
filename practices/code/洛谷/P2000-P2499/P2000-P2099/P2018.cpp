// https://www.luogu.com.cn/problem/P2018
// 题意：给定 N 人的上下级关系，先花 1 单位时间告诉一个人消息。
// 之后每单位时间，每个已知消息的人可告诉一名直属上级或下属。
// 输出传遍所有人的最短时间及所有最优起点，起点按编号递增。
// 数据范围：N ≤ 1000，人员编号在 [1,N]，1 号没有上级。
// 难度评分：1400（洛谷分级换算）
// 算法标签：枚举、深度优先搜索

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1001;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int sz[MAXN];
int deep[MAXN];
int sum[MAXN];
int t[MAXN];

void build(){
    fill(deep+1,deep+n+1,0);
    fill(sz+1,sz+n+1,0);
    fill(sum+1,sum+n+1,0);
}

void dfs1(int u,int f){
    deep[u]=deep[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            sz[u]++;
            dfs1(v,u);
        }
    }
}

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u;
        cin>>u;

        Next[cnt]=head[u];
        to[cnt]=i+1;
        head[u]=cnt++;

        Next[cnt]=head[i+1];
        to[cnt]=u;
        head[i+1]=cnt++;
    }
    int ans=INT_MAX;
    for(int i=1;i<=n;i++){
        build();
        dfs1(i,0);
        for(int i=1;i<=n;i++){
            cout<<sz[i]<<' '<<deep[i]<<endl;
            sum[i]=sz[i]+deep[i];
        }
        cout<<"--------------------------------------\n";
        sort(sum+1,sum+n+1,cmp);
        t[i]=sum[1];
        ans=min(ans,t[i]);
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        if(t[i]==ans){
            cout<<i<<' ';
        }
    }
    return 0;
}
