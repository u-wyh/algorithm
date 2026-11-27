// https://www.luogu.com.cn/problem/P5836
// 题意：一棵 N 个农场的树上每点养 G 或 H 种奶牛，
// M 个朋友各有偏好的品种和树上行走路径 (A_i, B_i)，
// 判断每人沿途能否喝到偏好的牛奶。
// 输入 N, M、品种串、树边及 M 个询问；
// 输出长为 M 的 01 串（1 表示满意）。
// 数据范围：1 <= N, M <= 10^5。
// 算法标签：并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int fa[MAXN];
char str[MAXN];
int ans[MAXN];
int cnt=0;

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    fa[find(x)] = find(y);
}


int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        cin>>str[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        if(str[u]==str[v])
            un(u,v);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        char c;
        cin>>u>>v>>c;
        if(find(u)==find(v)&&c!=str[u])
            ans[cnt++]=0;
        else
            ans[cnt++]=1;
    }
    for(int i=0;i<m;i++){
        cout<<ans[i];
    }
    return 0;
}
