// https://www.luogu.com.cn/problem/P3144
// 题意：输入谷仓数 N、双向路数 M，M 条边 (u, v)，以及依次要关闭的 N 个谷仓编号排列。
// 每关闭一个谷仓，其相连的所有道路随之失效。
// 求初始状态以及每次关闭后（共 N 个时刻，最后一个关闭后不用查），剩余未关闭的谷仓是否全部连通。
// 输出 N 行，每行 YES 或 NO。
// 数据范围：1 <= N, M <= 3000，1 <= u, v <= N。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int fa[MAXN];
int ans[MAXN];
int n,m;
int order[MAXN],vis[MAXN];
vector<int>vec[MAXN];

int find(int i){
    return (fa[i]==i)?i:fa[i]=find(fa[i]);
}

void un(int x,int y){
     int fx=find(x);
     int fy=find(y);
     if(fx!=fy){
        fa[fx]=fy;
     }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        cin>>order[i];
        vis[i]=1;
    }
    for(int i=n;i>=1;i--){
        vis[order[i]]=0;
        int u=order[i];
        for(int j=0;j<vec[u].size();j++){
            int v=vec[u][j];
            if(!vis[u]&&!vis[v]){
                un(u,v);
            }
        }
        int f=find(u);
        int flag=1;
        for(int j=n;j>=i;j--){
            if(find(order[j])!=f){
                flag=0;
                ans[i]=0;
                break;
            }
        }
        if(flag){
            ans[i]=1;
        }
    }
    for(int i=1;i<=n;i++){
        if(ans[i]){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
