// 用途：求无向图欧拉路径。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 例题：https://www.luogu.com.cn/problem/P2731
// 题意：求一条恰好走过无向图每条边一次的路径。
// 思路：检查奇度点数，再用 Hierholzer 算法回溯记录路径。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 2100;

int m;
vector<pair<int,int>>vec[MAXN];
int degree[MAXN];
stack<int>st;
int cnt=0;
bool vis[MAXM];

void dfs(int u){
    for(int i=0;i<vec[u].size();i++){
        if(!vis[vec[u][i].second]){
            //这样做是为了不初始化vis数组
            vis[vec[u][i].second]=true;
            vis[vec[u][i].second^1]=true;
            //将这两条边全部否认
            dfs(vec[u][i].first);
        }
    }
    st.push(u);
}

int main()
{
    cin>>m;
    int tmp=505;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        tmp=min(tmp,min(u,v));
        vec[u].push_back({v,cnt});
        cnt++;
        vec[v].push_back({u,cnt});
        cnt++;
        degree[u]++,degree[v]++;
    }
    for(int i=1;i<=500;i++){
        sort(vec[i].begin(),vec[i].end());
    }
    int s=505;
    //找到路径起点
    for(int i=1;i<=500;i++){
        if(degree[i]%2){
            s=i;
            break;
        }
    }
    if(s==505){
        s=tmp;
    }
    dfs(s);
    while(!st.empty()){
        cout<<st.top()<<endl;
        st.pop();
    }
    return 0;
}
